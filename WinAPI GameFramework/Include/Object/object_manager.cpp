#include "object_manager.h"
#include "../Scene/scene.h"
#include "../Scene/layer.h"
#include "object.h"

using namespace std;

void ObjectManager::ErasePrototype(shared_ptr<Scene> const& scene)
{
	for (auto iter = prototype_collection_.begin(); iter != prototype_collection_.end();)
	{
		if (iter->second->scene() == scene)
			iter = prototype_collection_.erase(iter);
		else
			++iter;
	}
}

shared_ptr<Object> ObjectManager::CreateCloneObject(string const& tag, shared_ptr<Layer> const& layer)
{
	if (!layer)
		return nullptr_object_;

	auto const& prototype = _FindPrototype(tag);

	if (!prototype)
		return nullptr_object_;
	
	shared_ptr<Object> object{ prototype->_Clone() };

	object->set_layer(layer->self_.lock());

	if (!object->_Initialize())
		return nullptr_object_;

	layer->_AddObject(object);

	return object;
}

void ObjectManager::_Release()
{
}

unique_ptr<Object, function<void(Object*)>> const& ObjectManager::_FindPrototype(string const& tag) const
{
	auto const iter = prototype_collection_.find(tag);

	if (iter == prototype_collection_.end())
		return nullptr_prototype_;

	return iter->second;
}
