#include "guided_bullet.h"
#include "object_manager.h"
#include "../Resource/resource_manager.h"
#include "../math.h"
#include "../Collision/collider_rect.h"
#include "../Collision/collider_circle.h"

using namespace std;

bool GuidedBullet::is_guided() const
{
	return is_guided_;
}

shared_ptr<Object> GuidedBullet::target() const
{
	return target_.lock();
}

void GuidedBullet::set_target(weak_ptr<Object> const& target)
{
	if (target.expired())
		return;

	target_ = target;
}

GuidedBullet::GuidedBullet(GuidedBullet const& other) : Bullet(other)
{
	is_guided_ = other.is_guided_;
	target_ = other.target_;
}

GuidedBullet::GuidedBullet(GuidedBullet&& other) noexcept : Bullet(move(other))
{
	is_guided_ = move(other.is_guided_);
	target_ = move(other.target_);
}

void GuidedBullet::_Release()
{
}

bool GuidedBullet::_Initialize()
{
	set_size(20.f, 20.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(500.f);
	set_rotation_speed(1080.f);
	set_range(500.f);

	texture_ = ResourceManager::instance()->LoadTexture("Bullet", L"Bullet.bmp", "TexturePath");
	set_color_key(RGB(0, 248, 0));

	return true;
}

void GuidedBullet::_Input(float time)
{
	Object::_Input(time);
}

void GuidedBullet::_Update(float time)
{
	Object::_Update(time);

	static float const kGuidedRange = 400.f;

	if (range_ > kGuidedRange)
	{
		MoveByAngle(time);
		range_ -= move_speed_ * time;
	}
	else
	{
		if (!is_guided())
		{
			is_guided_ = true;

			auto monsters = ObjectManager::instance()->FindObjects("Monster");
			if (monsters.first != monsters.second)
			{
				auto destination = min_element(monsters.first, monsters.second, [this](auto const& e1, auto const& e2) {
					return Math::GetDistance(position_, e1.second.lock()->position()) < Math::GetDistance(position_, e2.second.lock()->position());
				});

				set_target(destination->second.lock());
			}
		}

		if (target())
		{
			angle_ = Math::GetAngle(position_, target()->position());

			MoveByAngle(time);

			if (Math::GetDistance(position_, target()->position()) <= 1.f)
				set_activation(false);

			return;
		}
		else
		{
			MoveByAngle(time);
			range_ -= move_speed_ * time;

			if (range_ <= 0.f)
				set_activation(false);
		}
	}
}

void GuidedBullet::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void GuidedBullet::_Collision(float time)
{
	Object::_Collision(time);
}

void GuidedBullet::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> GuidedBullet::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>(new GuidedBullet(*this), [](Object* p) {
		dynamic_cast<GuidedBullet*>(p)->_Release();
		delete dynamic_cast<GuidedBullet*>(p);
	});
}
