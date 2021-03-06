#include "scene.h"
#include "layer.h"
#include "scene_component.h"
#include "start_scene.h"
#include "main_scene.h"
#include "../Object/object_manager.h"

using namespace std;

void Scene::CreateLayer(string const& tag, int z_order)
{
	auto layer = shared_ptr<Layer>(new Layer, [](Layer* p) {
		p->_Release();
		delete p;
	});

	layer->set_scene(weak_from_this());
	layer->set_z_order(z_order);
	layer->set_tag(tag);

	layer_list_.push_back(layer);

	layer_list_.sort([](auto const& left, auto const& right) -> bool {
		return left->z_order() < right->z_order();
	});
}

shared_ptr<Layer> const& Scene::FindLayer(string const& tag) const
{
	for (auto const& e : layer_list_)
	{
		if (e->tag() == tag)
			return e;
	}

	return layer_nullptr_;
}

list<shared_ptr<Layer>> const& Scene::layer_list() const
{
	return layer_list_;
}

bool Scene::_Initialize()
{
	scene_component_ = _CreateSceneCompoenet<StartScene>("StartScene");
	scene_component_->Initialize();

	return true;
}

void Scene::_Input(float time)
{
	scene_component_->_Input(time);

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
	scene_component_->_Update(time);

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

void Scene::_LateUpdate(float time)
{
	scene_component_->_LateUpdate(time);

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
			(*iter)->_LateUpdate(time);
			++iter;
		}
	}
}

void Scene::_Collision(float time)
{
	scene_component_->_Collision(time);

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
	scene_component_->_Render(device_context, time);

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