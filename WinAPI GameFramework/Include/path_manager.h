#pragma once

#include "singleton.h"

class PathManager final : public Singleton<PathManager>
{
	friend class Singleton<PathManager>;
public:
	bool Initialize();
	bool AddPath(std::string tag, std::filesystem::path path, std::string base_tag = "RootPath");
	std::filesystem::path const& FindPath(std::string tag) const;

private:
	PathManager() = default;
	PathManager(PathManager const&) = delete;
	PathManager& operator=(PathManager const&) = delete;

	virtual void _Release() override;

	std::filesystem::path path_nullptr_{};
	std::unordered_map<std::string, std::filesystem::path> path_collection_{};
};
