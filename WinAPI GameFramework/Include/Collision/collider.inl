#pragma once

using namespace std;

template <typename T> 
void Collider::SetCallBack(T* object, void (T::*function)(weak_ptr<Collider>, weak_ptr<Collider>, float), COLLISION_CALLBACK type)
{
	collision_callback_collection_.at(static_cast<size_t>(type)).push_back(bind(function, object, placeholders::_1, placeholders::_2, placeholders::_3));
}