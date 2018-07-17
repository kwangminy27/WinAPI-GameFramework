#pragma once

using namespace std;

template <typename T>
void ObjectManager::CreatePrototype(string const& tag, shared_ptr<Scene> const& scene)
{
	if (_FindPrototype(tag))
		return;

	auto prototype = unique_ptr<Object, function<void(Object*)>>(new T, [](Object* p) {
		p->_Release();
		delete p;
	});

	prototype->set_scene(scene);
	prototype->set_tag(tag);

	if (!prototype->_Initialize())
		return;

	prototype_collection_.insert(make_pair(string{ tag }, move(prototype)));
}

template <typename T>
shared_ptr<Object> ObjectManager::CreateObject(string const& tag, shared_ptr<Layer> const& layer)
{
	if (!layer)
		return object_nullptr_;

	auto object = shared_ptr<Object>(new T, [](Object* p) {
		p->_Release();
		delete p;
	});

	object->scene_ = layer->scene();
	object->layer_ = layer;
	object->set_tag(tag);

	if (!object->_Initialize())
		return object_nullptr_;

	layer->_AddObject(object);
	scene_object_collection_.insert(make_pair(move(tag), object));

	return object;
}