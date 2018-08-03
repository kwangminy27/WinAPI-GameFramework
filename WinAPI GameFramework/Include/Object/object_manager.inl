#pragma once

using namespace std;

template <typename T>
void ObjectManager::CreatePrototype(string const& tag, weak_ptr<Scene> const& scene)
{
	if (_FindPrototype(tag))
		return;

	if (scene.expired())
		return;

	auto prototype = unique_ptr<Object, function<void(Object*)>>(new T, [](Object* p) {
		p->_Release();
		delete p;
	});

	prototype->set_scene(scene);
	prototype->set_tag(tag);

	if (!prototype->Initialize())
		return;

	prototype_collection_.insert(make_pair(move(tag), move(prototype)));
}

template <typename T>
shared_ptr<Object> ObjectManager::CreateObject(string const& tag, weak_ptr<Layer> const& layer)
{
	if (layer.expired())
		return object_nullptr_;

	auto caching_layer = layer.lock();

	auto object = shared_ptr<Object>(new T, [](Object* p) {
		p->_Release();
		delete p;
	});

	object->scene_ = caching_layer->scene();
	object->layer_ = caching_layer;
	object->set_tag(tag);

	if (!object->Initialize())
		return object_nullptr_;

	caching_layer->_AddObject(object);
	scene_object_collection_.insert(make_pair(move(tag), object));

	return object;
}