#include "scene.h"
#include "layer.h"
#include "scene_component.h"
#include "main_scene.h"

using namespace std;

bool Scene::_Initialize(std::shared_ptr<Scene> const& scene)
{
	Tag::_Initialize();

	_CreateLayer("BackGround"s, numeric_limits<int>::min());
	_CreateLayer("Default"s, 0);
	_CreateLayer("UI"s, numeric_limits<int>::max());

	for (auto& e : layer_list_)
		e->_Initialize(scene);

	scene_component_ = _CreateSceneCompoenet<MainScene>("MainScene"s);
	scene_component_->_Initialize(scene);

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

unique_ptr<Layer, function<void(Layer*)>> const& Scene::FindLayer(std::string const& tag) const
{
	for (auto& e : layer_list_)
	{
		if (e->tag() == tag)
			return e;
	}

	return nullptr_layer_;
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

	layer_list_.sort([](auto const& left, auto const& right) -> bool {
		return left->z_order_ < right->z_order_;
	});
}