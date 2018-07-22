#include "layer.h"
#include "../Object/object.h"
#include "../Collision/collision_manager.h"

using namespace std;

shared_ptr<Scene> Layer::scene() const
{
	return scene_.lock();
}

int Layer::z_order() const
{
	return z_order_;
}

void Layer::set_scene(weak_ptr<Scene> const& scene)
{
	if (scene.expired())
		return;

	scene_ = scene;
}

void Layer::set_z_order(int z_order)
{
	z_order_ = z_order;
}

shared_ptr<Object> const& Layer::FindObject(string const& tag) const
{
	for (auto iter = object_list_.begin(); iter != object_list_.end(); ++iter)
	{
		if ((*iter)->tag() == tag)
			return *iter;
	}

	return object_nullptr_;
}

void Layer::_Release()
{
}

bool Layer::_Initialize()
{
	return true;
}

void Layer::_Input(float time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->activation())
		{
			iter = object_list_.erase(iter);
			continue;
		}
		else if (!(*iter)->enablement())
		{
			++iter;
			continue;
		}
		else
		{
			(*iter)->_Input(time);
			++iter;
		}
	}
}

void Layer::_Update(float time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->activation())
		{
			iter = object_list_.erase(iter);
			continue;
		}
		else if (!(*iter)->enablement())
		{
			++iter;
			continue;
		}
		else
		{
			(*iter)->_Update(time);
			++iter;
		}
	}
}

void Layer::_LateUpdate(float time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->activation())
		{
			iter = object_list_.erase(iter);
			continue;
		}
		else if (!(*iter)->enablement())
		{
			++iter;
			continue;
		}
		else
		{
			(*iter)->_LateUpdate(time);
			++iter;
		}
	}
}

void Layer::_Collision(float time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->activation())
		{
			iter = object_list_.erase(iter);
			continue;
		}
		else if (!(*iter)->enablement())
		{
			++iter;
			continue;
		}
		else
		{
			CollisionManager::instance()->AddCollider(*iter);
			++iter;
		}
	}
}

void Layer::_Render(HDC device_context, float time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->activation())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Render(device_context, time);
			++iter;
		}
	}
}

void Layer::_AddObject(weak_ptr<Object> const& object)
{
	if (object.expired())
		return;

	object_list_.push_back(object.lock());
}

void Layer::_EraseObject(weak_ptr<Object> const& object)
{
	if (object.expired())
		return;

	auto caching_object = object.lock();

	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if ((*iter) == caching_object)
		{
			object_list_.erase(iter);
			return;
		}
	}
}
