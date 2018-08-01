#include "core.h"
#include "input.h"
#include "camera.h"
#include "Object/mouse_ui.h"
#include "Object/object_manager.h"

using namespace std;

bool Input::Initialize()
{
	AddKey("MoveUp"s, VK_UP);
	AddKey("MoveDown"s, VK_DOWN);
	AddKey("MoveLeft"s, VK_LEFT);
	AddKey("MoveRight"s, VK_RIGHT);
	AddKey("Fire"s, VK_SPACE);
	AddKey("Pause"s, VK_CONTROL, '1');
	AddKey("LeftButton"s, VK_LBUTTON);
	AddKey("RightButton"s, VK_RBUTTON);
	AddKey("MiddleButton"s, VK_MBUTTON);

	ShowCursor(false);

	return true;
}

void Input::Update(float time)
{
	for (auto const& key : key_collection_)
	{
		int count{};
		for (auto const& value : key.second->element)
		{
			if (GetAsyncKeyState(value) & 0x8000)
				++count;
		}

		if (count == key.second->element.size())
		{
			if (!key.second->pressed)
			{
				key.second->push = true;
				key.second->pressed = true;
			}
			else
				key.second->push = false;
		}
		else if (key.second->pressed)
		{
			key.second->push = false;
			key.second->pressed = false;
			key.second->up = true;
		}
		else if (key.second->up)
			key.second->up = false;
	}

	UpdateMouseCursor();
	ManageMouseCursorState();
}

bool Input::KeyPush(string const& tag) const
{
	auto const& key = _FindKey(tag);

	return key->push;
}

bool Input::KeyPressed(string const& tag) const
{
	auto const& key = _FindKey(tag);

	return key->pressed;
}

bool Input::KeyUp(string const& tag) const
{
	auto const& key = _FindKey(tag);

	return key->up;
}

void Input::_Release()
{
}

unique_ptr<KeyInfo> const& Input::_FindKey(string const& tag) const
{
	auto const iter = key_collection_.find(tag);

	if (iter == key_collection_.end())
		return key_nullptr_;
	
	return iter->second;
}

void Input::AddKey()
{
	string tag = key_buffer_->tag;
	key_collection_.insert(make_pair(move(tag), move(key_buffer_)));
}

XY const& Input::mouse_client_position() const
{
	return mouse_client_position_;
}

XY const& Input::mouse_world_position() const
{
	return mouse_world_position_;
}

XY const& Input::mouse_displacement() const
{
	return mouse_displacement_;
}

shared_ptr<Object> Input::mouse() const
{
	return mouse_;
}

void Input::set_mouse(shared_ptr<Object> const& mouse)
{
	mouse_ = mouse;
}

void Input::UpdateMouseCursor()
{
	POINT mouse_position{};
	GetCursorPos(&mouse_position);
	ScreenToClient(Core::instance()->main_window(), &mouse_position);

	mouse_displacement_.x = static_cast<float>(mouse_position.x) - mouse_client_position_.x;
	mouse_displacement_.y = static_cast<float>(mouse_position.y) - mouse_client_position_.y;

	mouse_client_position_ = { static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y) };

	mouse_world_position_ = mouse_client_position_ + Camera::instance()->world();

	mouse_->set_position(mouse_client_position_);
}

void Input::ManageMouseCursorState()
{
	if (!mouse_show_flag_ && mouse_client_position_.x <= 0.f && mouse_client_position_.x >= static_cast<float>(RESOLUTION::WIDTH) && mouse_client_position_.y <= 0.f && mouse_client_position_.y >= static_cast<float>(RESOLUTION::HEIGHT))
	{
		mouse_show_flag_ = true;
		ShowCursor(true);
	}
	else if (mouse_show_flag_ && mouse_client_position_.x > 0.f && mouse_client_position_.x < static_cast<float>(RESOLUTION::WIDTH) && mouse_client_position_.y > 0.f && mouse_client_position_.y < static_cast<float>(RESOLUTION::HEIGHT))
	{
		mouse_show_flag_ = false;
		ShowCursor(false);
	}
}

void Input::RenderMouseCursor(HDC device_context, float time)
{
	dynamic_cast<MouseUI*>(mouse_.get())->_Render(device_context, time);
}