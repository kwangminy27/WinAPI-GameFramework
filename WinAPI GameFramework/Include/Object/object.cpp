#include "object.h"
#include "../math.h"
#include "../physics.h"
#include "../camera.h"
#include "../Scene/scene.h"
#include "../Scene/layer.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"
#include "../Collision/collider.h"
#include "../animation.h"
#include "../animation_clip.h"

using namespace std;

XY Object::position() const
{
	return position_;
}

XY Object::size() const
{
	return size_;
}

XY Object::pivot() const
{
	return pivot_;
}

float Object::angle() const
{
	return angle_;
}

float Object::move_speed() const
{
	return move_speed_;
}

float Object::rotation_speed() const
{
	return rotation_speed_;
}

DWORD Object::color_key() const
{
	return color_key_;
}

bool Object::is_color_key() const
{
	return is_color_key_;
}

bool Object::physics_flag() const
{
	return physics_flag_;
}

float Object::velocity() const
{
	return velocity_;
}

float Object::energy() const
{
	return energy_;
}

void Object::set_position(float x, float y)
{
	position_.x = x;
	position_.y = y;
}

void Object::set_position(XY const & xy)
{
	position_ = xy;
}

void Object::set_size(float x, float y)
{
	size_.x = x;
	size_.y = y;
}

void Object::set_size(XY const & xy)
{
	size_ = xy;
}

void Object::set_pivot(float x, float y)
{
	pivot_.x = x;
	pivot_.y = y;
}

void Object::set_pivot(XY const & xy)
{
	pivot_ = xy;
}

void Object::set_angle(float angle)
{
	angle_ = angle;
}

void Object::set_move_speed(float move_speed)
{
	move_speed_ = move_speed;
}

void Object::set_rotation_speed(float rotation_speed)
{
	rotation_speed_ = rotation_speed;
}

void Object::set_color_key(COLORREF color_key)
{
	color_key_ = color_key;
	is_color_key_ = true;
}

void Object::set_physics_flag(bool flag)
{
	physics_flag_ = flag;
}

void Object::set_velocity(float velocity)
{
	velocity_ = velocity;
}

void Object::set_energy(float energy)
{
	energy_ = energy;
}

list<shared_ptr<Collider>> const& Object::collider_collection() const
{
	return collider_collection_;
}

shared_ptr<Scene> Object::scene() const
{
	return scene_.lock();
}

shared_ptr<Layer> Object::layer() const
{
	return layer_.lock();
}

void Object::set_scene(weak_ptr<Scene> const& scene)
{
	if (scene.expired())
		return;

	scene_ = scene;
}

void Object::set_layer(weak_ptr<Layer> const& layer)
{
	if (layer.expired())
		return;

	layer_ = layer;
}

void Object::set_texture(weak_ptr<Texture> const& texture)
{
	if (texture.expired())
		return;

	texture_ = texture;
}

bool Object::set_texture(string const& tag, wstring const& file_name, string const& path_tag)
{
	texture_ = ResourceManager::instance()->LoadTexture(tag, file_name, path_tag);

	return true;
}

bool Object::set_texture(std::string const& tag)
{
	texture_ = ResourceManager::instance()->FindTexture(tag);

	return true;
}

void Object::Move(float x, float y)
{
	position_.x += x;
	position_.y += y;
}

void Object::Move(float x, float y, float time)
{
	position_.x += x * time;
	position_.y += y * time;
}

void Object::Move(XY xy)
{
	position_.x += xy.x;
	position_.y += xy.y;
}

void Object::Move(XY xy, float time)
{
	position_.x += xy.x * time;
	position_.y += xy.y * time;
}

void Object::MoveByAngle(float time)
{
	position_.x += cos(Math::DegreeToRadian(angle_)) * move_speed_ * time;
	position_.y += sin(Math::DegreeToRadian(angle_)) * move_speed_ * time;
}

void Object::Rotate(float time)
{
	angle_ += rotation_speed_ * time;
}

bool Object::AddAnimationClip(string const& tag, ANIMATION_CLIP type, ANIMATION_OPTION option, float completion_time, ANIMATION_FRAME_INFO const& frame_info, string const& texture_tag, wstring const& file_name, string const& path_tag)
{
	if (!animation_)
	{
		animation_ = unique_ptr<Animation, function<void(Animation*)>>{ new Animation, [](Animation* p) {
			p->_Release();
			delete p;
		} };

		animation_->set_object(weak_from_this());
	}

	return animation_->CreateAnimationClip(tag, type, option, completion_time, frame_info, texture_tag, file_name, path_tag);;
}

bool Object::LoadAnimation(wstring const& file_name, string path_tag)
{
	if (!animation_)
	{
		animation_ = unique_ptr<Animation, function<void(Animation*)>>{ new Animation, [](Animation* p) {
			p->_Release();
			delete p;
		} };

		animation_->set_object(weak_from_this());
	}

	return animation_->LoadAnimation(file_name, path_tag);
}

Object::Object(Object const& other) : Tag(other)
{
	position_ = other.position_;
	size_ = other.size_;
	pivot_ = other.pivot_;
	angle_ = other.angle_;
	move_speed_ = other.move_speed_;
	rotation_speed_ = other.rotation_speed_;
	color_key_ = other.color_key_;
	is_color_key_ = other.is_color_key_;

	physics_flag_ = other.physics_flag_;
	velocity_ = other.velocity_;
	energy_ = other.energy_;

	collider_collection_.clear();
	for (auto const& collider : other.collider_collection_)
	{
		auto caching_collider = collider->_Clone();
		caching_collider->set_object(shared_from_this());
		collider_collection_.push_back(move(caching_collider));
	}

	scene_ = other.scene_;
	layer_ = other.layer_;
	texture_ = other.texture_;

	if (other.animation_)
	{
		animation_ = other.animation_->_Clone();
		animation_->set_object(weak_from_this());
	}
}

Object::Object(Object&& other) noexcept : Tag(other)
{
	*this = move(other);
}

bool Object::_Initialize()
{
	return true;
}

void Object::_Input(float time)
{
}

void Object::_Update(float time)
{
	static float const kWeightingFactor = 800.f;

	if (physics_flag_)
	{
		energy_ -= kWeightingFactor * Physics::GravitionalAcceleration() * time;
		velocity_ -= energy_ * time;
		position_.y += velocity_ * time;
	}

	if (animation_)
		animation_->Update(time);
}

void Object::_LateUpdate(float time)
{
	for (auto const& collider : collider_collection_)
	{
		if(collider->enablement())
			collider->_Update(time);
	}
}

void Object::_Collision(float time)
{
}

void Object::_Render(HDC device_context, float time)
{
	if (texture_.expired())
		return;

	auto caching_texture = texture_.lock();

	XY position_on_the_world_coordinate_system = position_;
	XY position_on_the_camera_coordinate_system = position_on_the_world_coordinate_system - Camera::instance()->world();

	int left = static_cast<int>(position_on_the_camera_coordinate_system.x - size_.x * pivot_.x);
	int top = static_cast<int>(position_on_the_camera_coordinate_system.y - size_.y * pivot_.y);
	int width = static_cast<int>(size_.x);
	int height = static_cast<int>(size_.y);

	if (is_color_key_)
	{
		if (animation_)
		{
			width = static_cast<int>(animation_->GetFrameWidth());
			height = static_cast<int>(animation_->GetFrameHeight());

			int frame_left = static_cast<int>(animation_->frame_x * width);
			int frame_top = static_cast<int>(animation_->frame_y * height);

			TransparentBlt(device_context, left, top, width, height, caching_texture->memory_device_context(), frame_left, frame_top, width, height, color_key_);
		}
		else
			TransparentBlt(device_context, left, top, width, height, caching_texture->memory_device_context(), 0, 0, caching_texture->width(), caching_texture->height(), color_key_);
	}
	else
		BitBlt(device_context, left, top, width, height, caching_texture->memory_device_context(), 0, 0, SRCCOPY);

	for (auto const& collider : collider_collection_)
	{
		if (collider->enablement())
			collider->_Render(device_context, time);
	}
}