#include "player.h"
#include "../input.h"
#include "../math.h"
#include "../Scene/scene.h"
#include "../Scene/layer.h"
#include "object_manager.h"
#include "bullet.h"
#include "rotation_bullet.h"
#include "guided_bullet.h"
#include "parabola_bullet.h"
#include "../Collision/collider_rect.h"
#include "../Collision/collider_sphere.h"

using namespace std;

float Player::barrel_size() const
{
	return barrel_size_;
}

void Player::set_barrel_size(float barrel_size)
{
	barrel_size_ = barrel_size;
}

void Player::BulletHit(weak_ptr<Collider> src, weak_ptr<Collider> dest, float time)
{
	auto caching_dest = dest.lock();

	if(!caching_dest)
		return;

	if (caching_dest->tag() == "BulletBody"s)
		caching_dest->object()->set_activation(false);
}

Player::Player(Player const& other) : Character(other)
{
}

Player::Player(Player&& other) noexcept : Character(other)
{
}

void Player::_Release()
{
}

bool Player::_Initialize()
{
	set_position(100.f, 100.f);
	set_size(50.f, 50.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(300.f);
	set_rotation_speed(360.f);
	set_barrel_size(50.f);

	auto const& input_manager = Input::instance();

	input_manager->AddKey("Skill1"s, '1');
	input_manager->AddKey("Skill2"s, '2');
	input_manager->AddKey("Skill3"s, '3');
	input_manager->AddKey("Skill4"s, '4');
	input_manager->AddKey("Skill5"s, '5');

	set_texture("Teemo"s, L"Teemo.bmp"s, "TexturePath"s);

	/*auto collider_rect = dynamic_pointer_cast<ColliderRect>(AddCollider<ColliderRect>("PlayerBody"s));
	collider_rect->set_model({ 0.f, 0.f, 50.f, 50.f });
	collider_rect->set_pivot({ 0.5f, 0.5f });
	collider_rect->SetCallBack<Player>(this, &Player::BulletHit, COLLISION_CALLBACK::ENTER);*/

	auto collider_sphere = dynamic_pointer_cast<ColliderSphere>(AddCollider<ColliderSphere>("PlayerBody"s));
	collider_sphere->set_model({ 0.f, 0.f, 25.f });
	collider_sphere->SetCallBack<Player>(this, &Player::BulletHit, COLLISION_CALLBACK::LEAVE);

	return true;
}

void Player::_Input(float time)
{
	Character::_Input(time);

	auto const& input_manager = Input::instance();

	static auto KeyPush = [&input_manager](string tag) -> bool { return input_manager->KeyPush(tag); };
	static auto KeyPressed = [&input_manager](string tag) -> bool { return input_manager->KeyPressed(tag); };
	static auto KeyUp = [&input_manager](string tag) -> bool { return input_manager->KeyUp(tag); };

	if (KeyPressed("MoveLeft"s))
		Rotate(-time);

	if (KeyPressed("MoveRight"s))
		Rotate(time);

	if (KeyPressed("MoveUp"s))
		MoveByAngle(time);

	if (KeyPressed("MoveDown"s))
		MoveByAngle(-time);

	if (KeyPressed("Fire"s))
	{
		auto bullet = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet"s, layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		bullet->set_position(barrel_end);
		bullet->set_angle(angle_);
	}

	if (KeyPush("Skill1"s))
	{
		auto bullet1 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet"s, layer()));
		auto bullet2 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet"s, layer()));
		auto bullet3 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet"s, layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		bullet1->set_position(barrel_end);
		bullet1->set_angle(angle_ - 30.f);
		bullet2->set_position(barrel_end);
		bullet2->set_angle(angle_);
		bullet3->set_position(barrel_end);
		bullet3->set_angle(angle_ + 30.f);
	}

	if (KeyPush("Skill2"s))
	{
		bullet_ = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet"s, layer()));
		bullet_->stop();
	}
	else if (KeyPressed("Skill2"s))
	{
		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		bullet_->set_position(barrel_end);
		bullet_->set_angle(angle_);

		static float const kGrowthSpeed = 200.f;
		bullet_->set_size(bullet_->size() + (kGrowthSpeed * time));
	}
	else if (KeyUp("Skill2"s))
	{
		bullet_->start();
	}

	if (KeyPush("Skill3"s))
	{
		auto rotation_bullet = dynamic_pointer_cast<RotationBullet>(ObjectManager::instance()->CreateCloneObject("RotationBullet"s, layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };
		barrel_end -= XY{ cos(Math::DegreeToRadian(angle_)) * rotation_bullet->rotation_range(), sin(Math::DegreeToRadian(angle_)) * rotation_bullet->rotation_range() };

		rotation_bullet->set_rotation_center(barrel_end);
		rotation_bullet->set_angle(angle_);
		rotation_bullet->set_rotation_angle(angle_);
	}

	if (KeyPush("Skill4"s))
	{
		auto guided_bullet = dynamic_pointer_cast<GuidedBullet>(ObjectManager::instance()->CreateCloneObject("GuidedBullet"s, layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		guided_bullet->set_position(barrel_end);
		guided_bullet->set_angle(angle_);
	}

	if (KeyPush("Skill5"s))
	{
		auto parabola_bullet = dynamic_pointer_cast<ParabolaBullet>(ObjectManager::instance()->CreateCloneObject("ParabolaBullet"s, layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		parabola_bullet->set_position(barrel_end);
		parabola_bullet->set_angle(angle_ - 60.f);
		parabola_bullet->set_start_angle(angle_ - 60.f);
	}
}

void Player::_Update(float time)
{
	Character::_Update(time);
}

void Player::_LateUpdate(float time)
{
	Character::_LateUpdate(time);
}

void Player::_Collision(float time)
{
	Character::_Collision(time);
}

void Player::_Render(HDC device_context, float time)
{
	Character::_Render(device_context, time);

	MoveToEx(device_context, static_cast<int>(position_.x), static_cast<int>(position_.y), nullptr);
	XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };
	LineTo(device_context, static_cast<int>(barrel_end.x), static_cast<int>(barrel_end.y));
}

unique_ptr<Object, function<void(Object*)>> Player::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>(new Player(*this), [](Object* p) {
		dynamic_cast<Player*>(p)->_Release();
		delete dynamic_cast<Player*>(p);
	});
}
