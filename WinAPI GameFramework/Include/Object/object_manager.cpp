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

void ObjectManager::ClearExpiredSceneObject() // weak을 들고 계속 살아있는 모듈에서 expired 된 요소들을 참조하는 weak_ptr을 정리하면 쓸데없는 계산을 안하도록 할 수 있게된다.
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
