#include "player.h"
#include "../input.h"
#include "../math.h"
#include "../Scene/scene.h"
#include "object_manager.h"
#include "bullet.h"
#include "rotation_bullet.h"

using namespace std;

float Player::barrel_size() const
{
	return barrel_size_;
}

void Player::set_barrel_size(float barrel_size)
{
	barrel_size_ = barrel_size;
}

Player::Player(Player const& other) : Character(other)
{
}

void Player::_Release()
{
}

bool Player::_Initialize()
{
	set_position(100.f, 100.f);
	set_size(60.f, 40.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(300.f);
	set_rotation_speed(360.f);
	set_barrel_size(50.f);

	auto const& input_manager = Input::instance();

	input_manager->AddKey("Skill1"s, '1');
	input_manager->AddKey("Skill2"s, '2');
	input_manager->AddKey("Skill3"s, '3');

	set_texture("Teemo"s, L"Teemo.bmp"s, "TexturePath"s);

	return true;
}

void Player::_Input(float time)
{
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

	if (KeyPressed("Skill1"s))
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

	if (KeyPressed("Skill3"s))
	{
		auto rotation_bullet = dynamic_pointer_cast<RotationBullet>(ObjectManager::instance()->CreateCloneObject("RotationBullet"s, layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };
		barrel_end -= XY{ cos(Math::DegreeToRadian(angle_)) * rotation_bullet->rotation_range(), sin(Math::DegreeToRadian(angle_)) * rotation_bullet->rotation_range() };

		rotation_bullet->set_rotation_center(barrel_end);
		rotation_bullet->set_angle(angle_);
		rotation_bullet->set_rotation_angle(angle_);
	}
}

void Player::_Update(float time)
{
}

void Player::_LateUpdate(float time)
{
}

void Player::_Collision(float time)
{
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
