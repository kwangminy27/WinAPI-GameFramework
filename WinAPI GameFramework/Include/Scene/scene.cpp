#include "scene.h"
#include "layer.h"

using namespace std;

bool Scene::_Initialize(std::shared_ptr<Scene> const& scene)
{
	_CreateLayer("BackGround"s, numeric_limits<int>::min());
	_CreateLayer("Default"s, 0);
	_CreateLayer("UI"s, numeric_limits<int>::max());

	for (auto& e : layer_list_)
		e->set_scene(scene);

	return true;
}

void Scene::_Input(float time)
{
	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->activation())
		{
			iter = layer_list_.erase(iter);
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

void Scene::_Update(float time)
{
	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->activation())
		{
			iter = layer_list_.erase(iter);
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

void Scene::_LastUpdate(float time)
{
	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->activation())
		{
			iter = layer_list_.erase(iter);
			continue;
		}
		else if (!(*iter)->enablement())
		{
			++iter;
			continue;
		}
		else
		{
			(*iter)->_LastUpdate(time);
			++iter;
		}
	}
}

void Scene::_Collision(float time)
{
	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->activation())
		{
			iter = layer_list_.erase(iter);
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

void Scene::_Render(HDC device_context, float time)
{
	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->activation())
		{
			iter = layer_list_.erase(iter);
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

void Scene::_Release()
{
}

void Scene::_CreateLayer(string const& tag, int z_order)
{
	auto layer = unique_ptr<Layer, function<void(Layer*)>>(new Layer, [](Layer* p) {
		p->_Release();
		delete p;
	});

	layer->set_tag(tag);
	layer->set_z_order(z_order);

	layer_list_.push_back(move(layer));
}
