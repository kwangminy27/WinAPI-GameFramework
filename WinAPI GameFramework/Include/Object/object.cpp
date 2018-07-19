#include "object.h"
#include "../math.h"
#include "../Scene/scene.h"
#include "../Scene/layer.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"
#include "../Collision/collider.h"

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
	scene_ = scene;
}

void Object::set_layer(weak_ptr<Layer> const& layer)
{
	layer_ = layer;
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

bool Object::set_texture(weak_ptr<Texture> const& texture)
{
	texture_ = texture;

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

Object::Object(Object const& other) : Tag(other)
{
	*this = other;

	collider_collection_.clear();
	for (auto const& collider : other.collider_collection_)
	{
		auto temp_collider = collider->_Clone();
		temp_collider->set_object(weak_from_this());
		collider_collection_.push_back(move(temp_collider));
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
}

void Object::_LateUpdate(float time)
{
	for (auto const& collider : collider_collection_)
		collider->_Update(time);
}

void Object::_Collision(float time)
{
}

void Object::_Render(HDC device_context, float time)
{
	auto texture = texture_.lock();

	if (texture)
	{
		float left{ position_.x - (size_.x * pivot_.x) };
		float top{ position_.y - (size_.y * pivot_.y) };

		if (is_color_key_)
			TransparentBlt(device_context, static_cast<int>(left), static_cast<int>(top), static_cast<int>(size_.x), static_cast<int>(size_.y), texture->memory_device_context(), 0, 0, texture->width(), texture->height(), color_key_);
		else
			BitBlt(device_context, static_cast<int>(left), static_cast<int>(top), static_cast<int>(size_.x), static_cast<int>(size_.y), texture->memory_device_context(), 0, 0, SRCCOPY);
	}

	for (auto const& collider : collider_collection_)
		collider->_Render(device_context, time);
}
