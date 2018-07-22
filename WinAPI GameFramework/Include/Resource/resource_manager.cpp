#include "resource_manager.h"
#include "texture.h"

using namespace std;

bool ResourceManager::Initialize()
{
	LoadTexture("BackBuffer", L"BackBuffer.bmp", "TexturePath");
	LoadTexture("StarBack", L"StarBack.bmp", "TexturePath");

	return true;
}

shared_ptr<Texture> ResourceManager::LoadTexture(string const& tag, wstring const& file_name, string const& path_tag)
{
	auto texture = FindTexture(tag);

	if (texture)
		return texture;

	texture = shared_ptr<Texture>(new Texture, [](Texture* p) {
		p->_Release();
		delete p;
	});

	texture->set_tag(tag);

	if (!texture->LoadTexture(tag, file_name, path_tag))
		return texture_nullptr_;

	texture_collection_.insert(make_pair(move(tag), texture));

	return texture;
}

shared_ptr<Texture> const& ResourceManager::FindTexture(string const& tag) const
{
	auto const iter = texture_collection_.find(tag);

	if (iter == texture_collection_.end())
		return texture_nullptr_;

	return iter->second;
}

void ResourceManager::_Release()
{
}
