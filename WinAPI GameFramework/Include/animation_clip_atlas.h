#pragma once

#include "stdafx.h"

class AnimationClip;

class AnimationClipAtlas
{
	friend class AnimationManager;
private:
	void _Release();

	std::unordered_map<std::string, std::shared_ptr<AnimationClip>> animation_clip_collection_{};
};