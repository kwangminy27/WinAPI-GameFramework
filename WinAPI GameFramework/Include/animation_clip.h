#pragma once

#include "stdafx.h"

class Texture;

class AnimationClip
{
	friend class Animation;
private:
	AnimationClip() = default;
	AnimationClip(AnimationClip const& other);
	AnimationClip(AnimationClip&& other);
	AnimationClip& operator=(AnimationClip const&) = default;
	AnimationClip& operator=(AnimationClip&&) = default;

	void _Release();
	std::unique_ptr<AnimationClip, std::function<void(AnimationClip*)>> _Clone();

	std::string tag_{};
	ANIMATION_CLIP type_{};
	ANIMATION_OPTION option_{};
	ANIMATION_FRAME_INFO frame_info_{};
	std::weak_ptr<Texture> texture_{};
	float completion_time_{};
};