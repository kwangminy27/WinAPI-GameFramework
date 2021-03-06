#include "player.h"
#include "../input.h"
#include "../math.h"
#include "../camera.h"
#include "../Scene/scene.h"
#include "../Scene/layer.h"
#include "object_manager.h"
#include "bullet.h"
#include "rotation_bullet.h"
#include "guided_bullet.h"
#include "parabola_bullet.h"
#include "effect.h"
#include "number.h"
#include "../Collision/collider_rect.h"
#include "../Collision/collider_circle.h"

using namespace std;

bool Player::Initialize()
{
	type_ = OBJECT_TYPE::PLAYER;

	set_position(3920.f, 1960.f);
	set_size(50.f, 50.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(600.f);
	set_rotation_speed(360.f);
	set_barrel_size(50.f);
	set_physics_flag(true);

	auto const& input_manager = Input::instance();

	input_manager->AddKey("Skill1"s, '1');
	input_manager->AddKey("Skill2"s, '2');
	input_manager->AddKey("Skill3"s, '3');
	input_manager->AddKey("Skill4"s, '4');
	input_manager->AddKey("Skill5"s, '5');

	set_texture("Teemo", L"Teemo.bmp", "TexturePath");

	auto collider_rect = dynamic_pointer_cast<ColliderRect>(AddCollider<ColliderRect>("PlayerBody"));
	collider_rect->set_model({ 0.f, 0.f, 50.f, 50.f });
	collider_rect->set_pivot({ 0.5f, 0.5f });
	collider_rect->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		BeHit(src, dest, time);
	}, COLLISION_CALLBACK::ENTER);

	auto collider_shield_left = dynamic_pointer_cast<ColliderRect>(AddCollider<ColliderRect>("PlayerShield"));
	collider_shield_left->set_model({ 0.f, 0.f, 1.f, 100.f });
	collider_shield_left->set_pivot({ 50.f, 0.5f });
	collider_shield_left->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		ProtectBulletForLeftRightShield(src, dest, time);
	}, COLLISION_CALLBACK::ENTER);
	collider_shield_left->set_enablement(false);

	auto collider_shield_right = dynamic_pointer_cast<ColliderRect>(AddCollider<ColliderRect>("PlayerShield"));
	collider_shield_right->set_model({ 0.f, 0.f, 1.f, 100.f });
	collider_shield_right->set_pivot({ -50.f, 0.5f });
	collider_shield_right->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		ProtectBulletForLeftRightShield(src, dest, time);
	}, COLLISION_CALLBACK::ENTER);
	collider_shield_right->set_enablement(false);

	auto collider_shield_top = dynamic_pointer_cast<ColliderRect>(AddCollider<ColliderRect>("PlayerShield"));
	collider_shield_top->set_model({ 0.f, 0.f, 100.f, 1.f });
	collider_shield_top->set_pivot({ 0.5f, 50.f });
	collider_shield_top->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		ProtectBulletForTopBottomShield(src, dest, time);
	}, COLLISION_CALLBACK::ENTER);
	collider_shield_top->set_enablement(false);

	auto collider_shield_bottom = dynamic_pointer_cast<ColliderRect>(AddCollider<ColliderRect>("PlayerShield"));
	collider_shield_bottom->set_model({ 0.f, 0.f, 100.f, 1.f });
	collider_shield_bottom->set_pivot({ 0.5f, -50.f });
	collider_shield_bottom->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		ProtectBulletForTopBottomShield(src, dest, time);
	}, COLLISION_CALLBACK::ENTER);
	collider_shield_bottom->set_enablement(false);

	AddAnimationClip("motion4");
	set_color_key(RGB(255, 0, 255));

	return true;
}

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
	auto caching_tag = caching_dest->tag();

	if (caching_tag == "MonsterBulletBody")
	{
		caching_dest->object()->set_activation(false);

		auto bomb_effect = dynamic_pointer_cast<Effect>(ObjectManager::instance()->CreateCloneObject("BombEffect", layer()));
		bomb_effect->set_position(caching_dest->intersect_position());
		bomb_effect->set_size(100.f, 200.f);
		bomb_effect->set_pivot(0.5f, 1.f);
		bomb_effect->set_target(weak_from_this());
		bomb_effect->AddAnimationClip("Bomb");
	}
}

void Player::ProtectBulletForLeftRightShield(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
	if (src.expired() || dest.expired())
		return;

	auto caching_dest = dest.lock();

	if (caching_dest->tag() == "MonsterBulletBody")
	{
		float dir_x = cos(Math::DegreeToRadian(caching_dest->object()->angle())) * -1.f;
		float dir_y = sin(Math::DegreeToRadian(caching_dest->object()->angle()));
		float new_angle = Math::GetAngle({ 0.f, 0.f }, { dir_x, dir_y });
		caching_dest->object()->set_angle(new_angle);
	}
}

void Player::ProtectBulletForTopBottomShield(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
	if (src.expired() || dest.expired())
		return;

	auto caching_dest = dest.lock();

	if (caching_dest->tag() == "MonsterBulletBody")
	{
		float dir_x = cos(Math::DegreeToRadian(caching_dest->object()->angle()));
		float dir_y = sin(Math::DegreeToRadian(caching_dest->object()->angle())) * -1.f;
		float new_angle = Math::GetAngle({ 0.f, 0.f }, { dir_x, dir_y });
		caching_dest->object()->set_angle(new_angle);
	}
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

void Player::_Input(float time)
{
	Character::_Input(time);

	auto const& input_manager = Input::instance();

	static auto const& KeyPush = [&input_manager](string const& tag) -> bool { return input_manager->KeyPush(tag); };
	static auto const& KeyPressed = [&input_manager](string const& tag) -> bool { return input_manager->KeyPressed(tag); };
	static auto const& KeyUp = [&input_manager](string const& tag) -> bool { return input_manager->KeyUp(tag); };

	if (KeyPressed("MoveLeft"))
		Move(-move_speed_ * time, 0.f);

	if (KeyPressed("MoveRight"))
		Move(move_speed_ * time, 0.f);

	if (KeyPressed("MoveUp"))
	{
		Move(0.f, -move_speed_ * time);

		if (!physics_flag_)
		{
			energy_ += 2500.f;
			physics_flag_ = true;
		}
	}

	if (KeyPressed("MoveDown"))
		Move(0.f, move_speed_ * time);

	if (KeyPush("Fire"))
	{
 		auto bullet = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		bullet->set_position(barrel_end);
		bullet->set_angle(angle_);

		auto collider_circle = dynamic_pointer_cast<ColliderCircle>(bullet->AddCollider<ColliderCircle>("BulletBody"));
		collider_circle->set_model({ 0.f, 0.f, 10.f });
	}

	if (KeyPush("Skill1"))
	{
		auto bullet1 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));
		auto bullet2 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));
		auto bullet3 = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		bullet1->set_position(barrel_end);
		bullet1->set_angle(angle_ - 30.f);

		auto collider1 = dynamic_pointer_cast<ColliderCircle>(bullet1->AddCollider<ColliderCircle>("BulletBody"));
		collider1->set_model({ 0.f, 0.f, 10.f });

		bullet2->set_position(barrel_end);
		bullet2->set_angle(angle_);

		auto collider2 = dynamic_pointer_cast<ColliderCircle>(bullet2->AddCollider<ColliderCircle>("BulletBody"));
		collider2->set_model({ 0.f, 0.f, 10.f });

		bullet3->set_position(barrel_end);
		bullet3->set_angle(angle_ + 30.f);

		auto collider3 = dynamic_pointer_cast<ColliderCircle>(bullet3->AddCollider<ColliderCircle>("BulletBody"));
		collider3->set_model({ 0.f, 0.f, 10.f });
	}

	if (KeyPush("Skill2"))
	{
		bullet_ = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));

		auto collider = dynamic_pointer_cast<ColliderCircle>(bullet_->AddCollider<ColliderCircle>("BulletBody"));
		collider->set_model({ 0.f, 0.f, 10.f });
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

		auto collider = dynamic_pointer_cast<ColliderCircle>(rotation_bullet->AddCollider<ColliderCircle>("RotationBulletBody"));
		collider->set_model({ 0.f, 0.f, 10.f });
	}

	if (KeyPush("Skill4"))
	{
		auto guided_bullet = dynamic_pointer_cast<GuidedBullet>(ObjectManager::instance()->CreateCloneObject("GuidedBullet", layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		guided_bullet->set_position(barrel_end);
		guided_bullet->set_angle(angle_);

		auto collider_circle = dynamic_pointer_cast<ColliderCircle>(guided_bullet->AddCollider<ColliderCircle>("GuidedBulletBody"));
		collider_circle->set_model({ 0.f, 0.f, 10.f });
	}

	if (KeyPush("Skill5"))
	{
		auto parabola_bullet = dynamic_pointer_cast<ParabolaBullet>(ObjectManager::instance()->CreateCloneObject("ParabolaBullet", layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };

		parabola_bullet->set_position(barrel_end);
		parabola_bullet->set_angle(angle_ - 60.f);
		parabola_bullet->set_start_angle(angle_ - 60.f);

		auto collider = dynamic_pointer_cast<ColliderCircle>(parabola_bullet->AddCollider<ColliderCircle>("ParabolaBulletBody"));
		collider->set_model({ 0.f, 0.f, 10.f });
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

	auto camera_position = Camera::instance()->world();
	auto position_on_the_camera_coordinate_system = position_ - camera_position;

	MoveToEx(device_context, static_cast<int>(position_on_the_camera_coordinate_system.x), static_cast<int>(position_on_the_camera_coordinate_system.y), nullptr);
	XY barrel_end{ position_on_the_camera_coordinate_system.x + cos(Math::DegreeToRadian(angle_)) * barrel_size_, position_on_the_camera_coordinate_system.y + sin(Math::DegreeToRadian(angle_)) * barrel_size_ };
	LineTo(device_context, static_cast<int>(barrel_end.x), static_cast<int>(barrel_end.y));
}

unique_ptr<Object, function<void(Object*)>> Player::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>(new Player(*this), [](Object* p) {
		dynamic_cast<Player*>(p)->_Release();
		delete dynamic_cast<Player*>(p);
	});
}
