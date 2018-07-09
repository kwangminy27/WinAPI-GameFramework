#include "layer.h"

using namespace std;

void Layer::set_scene(std::shared_ptr<Scene> const& scene)
{
	scene_ = scene;
}

void Layer::set_z_order(int z_order)
{
	z_order_ = z_order;
}

void Layer::_Release()
{
}

bool Layer::_Initialize(float time)
{
	return true;
}

void Layer::_Input(float time)
{
}

void Layer::_Update(float time)
{
}

void Layer::_LastUpdate(float time)
{
}

void Layer::_Collision(float time)
{
}

void Layer::_Render(HDC device_context, float time)
{
}
