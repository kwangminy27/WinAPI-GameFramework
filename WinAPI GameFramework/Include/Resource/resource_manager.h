#pragma once

#include "../singleton.h"

class Texture;

class ResourceManager final : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
public:
	bool Initialize();
	std::shared_ptr<Texture> LoadTexture(std::string const& tag, std::wstring const& file_name, std::string path_tag = "TexturePath");
	std::shared_ptr<Texture> const& FindTexture(std::string const& tag) const;

private:
	ResourceManager() = default;
	ResourceManager(ResourceManager const&) = delete;
	ResourceManager& operator=(ResourceManager const&) = delete;

	virtual void _Release() override;

	std::shared_ptr<Texture> texture_nullptr_{};
	std::unordered_map<std::string, shared_ptr<Texture>> texture_collection_{};
};
