#include "input.h"

using namespace std;

bool Input::Initialize()
{
	AddKey("MoveUp"s, VK_UP);
	AddKey("MoveDown"s, VK_DOWN);
	AddKey("MoveLeft"s, VK_LEFT);
	AddKey("MoveRight"s, VK_RIGHT);
	AddKey("Fire"s, VK_SPACE);
	AddKey("Pause"s, VK_CONTROL, '1');
	
	return true;
}

void Input::Update(float delta_time)
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
		return nullptr_key_;
	
	return iter->second;
}

void Input::AddKey()
{
	string tag = key_buffer_->tag;
	key_collection_.insert(make_pair(move(tag), move(key_buffer_)));
}