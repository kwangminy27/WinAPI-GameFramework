#pragma once

#include "../singleton.h"

class Texture;

class ResourceManager final : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
public:
	bool Initialize();
	std::shared_ptr<Texture> LoadTexture(std::string tag, std::string file_name, std::string path_tag = "TexturePath"s);
	std::shared_ptr<Texture> const& FindTexture(std::string tag) const;

private:
	ResourceManager() = default;
	ResourceManager(ResourceManager const&) = delete;
	ResourceManager& operator=(ResourceManager const&) = delete;

	virtual void _Release() override;

	std::shared_ptr<Texture> nullptr_texture_{};
	std::unordered_map<std::string, shared_ptr<Texture>> texture_collection_{};
};
