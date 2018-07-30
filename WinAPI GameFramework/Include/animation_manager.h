#pragma once

#include "singleton.h"

class AnimationClip;

class AnimationManager : public Singleton<AnimationManager>
{
	friend class Singleton<AnimationManager>;
public:
	bool Initialize();
	std::shared_ptr<AnimationClip> const& FindAnimationClipPrototype(std::string const& tag);

private:
	AnimationManager() = default;
	AnimationManager(AnimationManager const&) = delete;
	AnimationManager& operator=(AnimationManager const&) = delete;

	virtual void _Release() override;

	bool _CreateAnimationClip(std::string const& tag, ANIMATION_CLIP type, ANIMATION_OPTION option, float completion_time, ANIMATION_FRAME_INFO const& frame_info, std::string const& texture_tag, std::wstring const& file_name, std::string const& path_tag = "TexturePath");
	bool _LoadTextureAltas(std::string const& tag, std::wstring const& file_name, std::string const& path_tag = "DataPath");

	std::shared_ptr<AnimationClip> animation_clip_prototype_nullptr_{};
	std::unordered_map<std::string, std::shared_ptr<AnimationClip>> animation_clip_prototype_collection_{};
};