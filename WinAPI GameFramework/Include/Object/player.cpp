#include "player.h"
#include "../input.h"
#include "../Scene/scene.h"
#include "object_manager.h"
#include "bullet.h"

using namespace std;

Player::Player(Player const& other) : Character(other)
{
}

void Player::_Release()
{
}

bool Player::_Initialize()
{
	set_position(100.f, 100.f);
	set_size(100.f, 100.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(300.f);

	auto const& input_manager = Input::instance();

	input_manager->AddKey("Skill1"s, '1');
	input_manager->AddKey("Skill2"s, '2');

	return true;
}

void Player::_Input(float time)
{
	auto const& input_manager = Input::instance();

	static auto KeyPush = [&input_manager](string tag) -> bool { return input_manager->KeyPush(tag); };
	static auto KeyPressed = [&input_manager](string tag) -> bool { return input_manager->KeyPressed(tag); };
	static auto KeyUp = [&input_manager](string tag) -> bool { return input_manager->KeyUp(tag); };

	if (KeyPressed("MoveUp"s))
		Move(0.f, -move_speed_ * time);

	if (KeyPressed("MoveDown"s))
		Move(0.f, move_speed_ * time);

	if (KeyPressed("MoveLeft"s))
		Move(-move_speed_ * time, 0.f);

	if (KeyPressed("MoveRight"s))
		Move(move_speed_ * time, 0.f);

	if (KeyPressed("Fire"s))
	{
		auto bullet = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet"s, layer()));

		bullet->set_position(position() + XY{ 75.f, 0.f });
	}

	if (KeyPressed("Skill1"s))
	{
		auto bullet1 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet"s, layer()));
		auto bullet2 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet"s, layer()));
		auto bullet3 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet"s, layer()));

		bullet1->set_position(position() + XY{ 75.f, 0.f });
		bullet1->set_move_dir({ 1.f, -1.f });
		bullet2->set_position(position() + XY{ 75.f, 0.f });
		bullet2->set_move_dir({ 1.f, 0.f });
		bullet3->set_position(position() + XY{ 75.f, 0.f });
		bullet3->set_move_dir({ 1.f, 1.f });
	}

	if (KeyPush("Skill2"s))
	{
		bullet_ = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet"s, layer()));
		bullet_->stop();
	}
	else if (KeyPressed("Skill2"s))
	{
		bullet_->set_position(position_);

		XY size = bullet_->size();
		size += XY{ 1.f, 0.5f } * 200.f * time;
		bullet_->set_size(size);
	}
	else if (KeyUp("Skill2"s))
	{
		bullet_->start();
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
	float left{ position_.x - (size_.x * pivot_.x) };
	float top{ position_.y - (size_.y * pivot_.y) };
	Rectangle(device_context, static_cast<int>(left), static_cast<int>(top), static_cast<int>(left + size_.x), static_cast<int>(top + size_.y));
}

unique_ptr<Object, function<void(Object*)>> Player::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>(new Player(*this), [](Object* p) {
		dynamic_cast<Player*>(p)->_Release();
		delete dynamic_cast<Player*>(p);
	});
}
