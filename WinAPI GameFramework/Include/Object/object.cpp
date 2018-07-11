#include "object.h"
#include "../Scene/scene.h"
#include "../Scene/layer.h"

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

void Object::set_scene(shared_ptr<Scene> const& scene)
{
	scene_ = scene;
}

void Object::set_layer(shared_ptr<Layer> const& layer)
{
	layer_ = layer;
}

Object::Object(Object const& other)
{
	*this = other;
}
