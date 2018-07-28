#pragma once

#include "singleton.h"

class AnimationClipAtlas;

class AnimationManager : public Singleton<AnimationManager>
{
	friend class Singleton<AnimationManager>;
public:
	bool Initialize();
	bool LoadAnimationClipAtlas(std::string const& tag, std::wstring const& file_name, std::string const& path_tag);
	std::shared_ptr<AnimationClipAtlas> const& FindAnimationClipAtlas(std::string const& tag);

private:
	AnimationManager() = default;
	AnimationManager(AnimationManager const&) = delete;
	AnimationManager& operator=(AnimationManager const&) = delete;

	virtual void _Release() override;

	std::shared_ptr<AnimationClipAtlas> animation_clip_atlas_nullptr_{};
	std::unordered_map<std::string, std::shared_ptr<AnimationClipAtlas>> animation_clip_atlas_prototype_collection_{};
};