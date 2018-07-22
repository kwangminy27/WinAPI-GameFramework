#pragma once

using namespace std;

template <typename T>
shared_ptr<Collider> Object::AddCollider(string tag)
{
	auto collider = shared_ptr<Collider>{new T, [](Collider* p) {
		p->_Release();
		delete p;
	}};

	collider->set_tag(tag);
	collider->set_object(weak_from_this());

	if (!collider->_Initialize())
		return collider_nullptr_;

	collider_collection_.push_back(collider);

	return collider;
}