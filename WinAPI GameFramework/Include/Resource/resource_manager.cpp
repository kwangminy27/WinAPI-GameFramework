#include "resource_manager.h"
#include "texture.h"

using namespace std;

bool ResourceManager::Initialize()
{
	auto texture = LoadTexture("Teemo"s, "Teemo.bmp"s);

	return true;
}

shared_ptr<Texture> ResourceManager::LoadTexture(string tag, string file_name, string path_tag)
{
	auto texture = FindTexture(tag);

	if (texture)
		return texture;

	texture = shared_ptr<Texture>(new Texture, [](Texture* p) {
		p->_Release();
		delete p;
	});

	if (!texture->LoadTexture(tag, file_name, path_tag))
		return nullptr_texture_;

	texture_collection_.insert(make_pair(move(tag), texture));

	return texture;
}

shared_ptr<Texture> const& ResourceManager::FindTexture(string tag) const
{
	auto const iter = texture_collection_.find(tag);

	if (iter == texture_collection_.end())
		return nullptr_texture_;

	return iter->second;
}

void ResourceManager::_Release()
{
}