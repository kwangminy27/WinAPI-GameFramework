#include "object.h"
#include "../Scene/scene.h"
#include "../Scene/layer.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"

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

Object::Object(Object const& other)
{
	*this = other;
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
		BitBlt(device_context, static_cast<int>(left), static_cast<int>(top), size_.x, size_.y,
			texture->memory_device_context(), 0, 0, SRCCOPY);
	}
}
