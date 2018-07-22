#include "object_manager.h"
#include "../Scene/scene.h"
#include "../Scene/layer.h"
#include "object.h"

using namespace std;

void ObjectManager::ErasePrototype(weak_ptr<Scene> const& scene)
{
	if (scene.expired())
		return;

	auto caching_scene = scene.lock();

	for (auto iter = prototype_collection_.begin(); iter != prototype_collection_.end();)
	{
		if (iter->second->scene() == caching_scene)
			iter = prototype_collection_.erase(iter);
		else
			++iter;
	}
}

void ObjectManager::ClearExpiredSceneObject() // weak�� ��� ��� ����ִ� ��⿡�� expired �� ��ҵ��� �����ϴ� weak_ptr�� �����ϸ� �������� ����� ���ϵ��� �� �� �ְԵȴ�.
{
	for (auto iter = scene_object_collection_.begin(); iter != scene_object_collection_.end();)
	{
		if (iter->second.expired())
		{
			iter = scene_object_collection_.erase(iter);
			continue;
		}

		++iter;
	}
}

shared_ptr<Object> ObjectManager::CreateCloneObject(string const& tag, weak_ptr<Layer> const& layer)
{
	if (layer.expired())
		return object_nullptr_;

	auto caching_layer = layer.lock();

	auto const& prototype = _FindPrototype(tag);

	if (!prototype)
		return object_nullptr_;
	
	shared_ptr<Object> object{ prototype->_Clone() };

	object->set_layer(layer);

	caching_layer->_AddObject(object);
	scene_object_collection_.insert(make_pair(move(tag), object));

	return object;
}

pair<unordered_multimap<string, weak_ptr<Object>>::iterator, unordered_multimap<string, weak_ptr<Object>>::iterator> ObjectManager::FindObjects(string const& tag)
{
	return scene_object_collection_.equal_range(tag);
}

void ObjectManager::_Release()
{
}

unique_ptr<Object, function<void(Object*)>> const& ObjectManager::_FindPrototype(string const& tag) const
{
	auto const iter = prototype_collection_.find(tag);

	if (iter == prototype_collection_.end())
		return prototype_nullptr_;

	return iter->second;
}
