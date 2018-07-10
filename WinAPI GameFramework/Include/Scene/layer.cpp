#include "layer.h"
#include "../Object/object.h"

using namespace std;

void Layer::set_scene(std::shared_ptr<Scene> const& scene)
{
	scene_ = scene;
}

void Layer::set_z_order(int z_order)
{
	z_order_ = z_order;
}

void Layer::_Release()
{
}

bool Layer::_Initialize(std::shared_ptr<Scene> const& scene)
{
	Tag::_Initialize();

	set_scene(scene);

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
			(*iter)->_Collision(time);
			++iter;
		}
	}
}

void Layer::_Render(HDC device_context, float time)
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
			(*iter)->_Render(device_context, time);
			++iter;
		}
	}
}
