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

void Player::BeHit(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
	if (src.expired() || dest.expired())
		return;

	auto caching_dest = dest.lock();

	if (caching_dest->tag() == "BulletBody")
		caching_dest->object()->set_activation(false);
}

Player::Player(Player const& other) : Character(other)
{
}

Player::Player(Player&& other) noexcept : Character(move(other))
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

	set_texture("Teemo", L"Teemo.bmp", "TexturePath");

	auto collider_sphere = dynamic_pointer_cast<ColliderSphere>(AddCollider<ColliderSphere>("PlayerBody"));
	collider_sphere->set_model({ 0.f, 0.f, 25.f });
	collider_sphere->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		BeHit(src, dest, time);
	}, COLLISION_CALLBACK::ENTER);

	return true;
}

void Player::_Input(float time)
{
	Character::_Input(time);

	auto const& input_manager = Input::instance();

	static auto KeyPush = [&input_manager](string tag) -> bool { return input_manager->KeyPush(tag); };
	static auto KeyPressed = [&input_manager](string tag) -> bool { return input_manager->KeyPressed(tag); };
	static auto KeyUp = [&input_manager](string tag) -> bool { return input_manager->KeyUp(tag); };

	if (KeyPressed("MoveLeft"))
		Rotate(-time);

	if (KeyPressed("MoveRight"))
		Rotate(time);

	if (KeyPressed("MoveUp"))
		MoveByAngle(time);

	if (KeyPressed("MoveDown"))
		MoveByAngle(-time);

	if (KeyPush("Fire"))
	{
 		auto bullet = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		bullet->set_position(barrel_end);
		bullet->set_angle(angle_);
		auto collider = dynamic_pointer_cast<ColliderSphere>(bullet->AddCollider<ColliderSphere>("BulletBody"));
		collider->set_model({ 0.f, 0.f, 5.f });
	}

	if (KeyPush("Skill1"))
	{
		auto bullet1 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));
		auto bullet2 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));
		auto bullet3 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		bullet1->set_position(barrel_end);
		bullet1->set_angle(angle_ - 30.f);
		auto collider1 = dynamic_pointer_cast<ColliderSphere>(bullet1->AddCollider<ColliderSphere>("BulletBody"));
		collider1->set_model({ 0.f, 0.f, 5.f });

		bullet2->set_position(barrel_end);
		bullet2->set_angle(angle_);
		auto collider2 = dynamic_pointer_cast<ColliderSphere>(bullet2->AddCollider<ColliderSphere>("BulletBody"));
		collider2->set_model({ 0.f, 0.f, 5.f });

		bullet3->set_position(barrel_end);
		bullet3->set_angle(angle_ + 30.f);
		auto collider3 = dynamic_pointer_cast<ColliderSphere>(bullet3->AddCollider<ColliderSphere>("BulletBody"));
		collider3->set_model({ 0.f, 0.f, 5.f });
	}

	if (KeyPush("Skill2"))
	{
		bullet_ = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));
		auto collider = dynamic_pointer_cast<ColliderSphere>(bullet_->AddCollider<ColliderSphere>("BulletBody"));
		collider->set_model({ 0.f, 0.f, 5.f });
		bullet_->stop();
	}
	else if (KeyPressed("Skill2"))
	{
		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		bullet_->set_position(barrel_end);
		bullet_->set_angle(angle_);

		static float const kGrowthSpeed = 200.f;
		bullet_->set_size(bullet_->size() + (kGrowthSpeed * time));
		bullet_->set_growth_speed(kGrowthSpeed);
	}
	else if (KeyUp("Skill2"))
	{
		bullet_->start();
	}

	if (KeyPush("Skill3"))
	{
		auto rotation_bullet = dynamic_pointer_cast<RotationBullet>(ObjectManager::instance()->CreateCloneObject("RotationBullet", layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };
		barrel_end -= XY{ cos(Math::DegreeToRadian(angle_)) * rotation_bullet->rotation_range(), sin(Math::DegreeToRadian(angle_)) * rotation_bullet->rotation_range() };

		rotation_bullet->set_rotation_center(barrel_end);
		rotation_bullet->set_angle(angle_);
		rotation_bullet->set_rotation_angle(angle_);
		auto collider = dynamic_pointer_cast<ColliderSphere>(rotation_bullet->AddCollider<ColliderSphere>("RotationBulletBody"));
		collider->set_model({ 0.f, 0.f, 5.f });
	}

	if (KeyPush("Skill4"))
	{
		auto guided_bullet = dynamic_pointer_cast<GuidedBullet>(ObjectManager::instance()->CreateCloneObject("GuidedBullet", layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		guided_bullet->set_position(barrel_end);
		guided_bullet->set_angle(angle_);
		auto collider = dynamic_pointer_cast<ColliderSphere>(guided_bullet->AddCollider<ColliderSphere>("GuidedBulletBody"));
		collider->set_model({ 0.f, 0.f, 5.f });
	}

	if (KeyPush("Skill5"))
	{
		auto parabola_bullet = dynamic_pointer_cast<ParabolaBullet>(ObjectManager::instance()->CreateCloneObject("ParabolaBullet", layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		parabola_bullet->set_position(barrel_end);
		parabola_bullet->set_angle(angle_ - 60.f);
		parabola_bullet->set_start_angle(angle_ - 60.f);
		auto collider = dynamic_pointer_cast<ColliderSphere>(parabola_bullet->AddCollider<ColliderSphere>("ParabolaBulletBody"));
		collider->set_model({ 0.f, 0.f, 5.f });
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
