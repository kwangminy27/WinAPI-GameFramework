#pragma once

#include "../tag.h"

class Scene;
class Object;

class Layer : public Tag
{
	friend class Scene;
	friend class ObjectManager;
public:
	bool Initialize();

	std::shared_ptr<Scene> scene() const;
	int z_order() const;

	void set_scene(std::weak_ptr<Scene> const& scene);
	void set_z_order(int z_order);

	std::shared_ptr<Object> const& FindObject(std::string const& tag) const;

private:
	Layer() = default;

	virtual void _Release() override;

	void _Input(float time);
	void _Update(float time);
	void _LateUpdate(float time);
	void _Collision(float time);
	void _Render(HDC device_context, float time);

	void _AddObject(std::weak_ptr<Object> const& object);
	void _EraseObject(std::weak_ptr<Object> const& object);

	int z_order_{};
	std::shared_ptr<Object> object_nullptr_{};
	std::list<std::shared_ptr<Object>> object_list_{};
	std::weak_ptr<Scene> scene_{};
};