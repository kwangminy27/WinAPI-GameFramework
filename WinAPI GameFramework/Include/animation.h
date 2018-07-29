#pragma once

#include "stdafx.h"

class AnimationClip;
class Object;

class Animation
{
	friend class Object;
public:
	bool Initialize();
	void Update(float time);

	bool AddAnimationClip(std::string const& tag);
	void ChangeClip(std::string const& tag);

	void set_default_clip(std::string const& tag);
	void set_current_clip(std::string const& tag);
	
	void set_object(std::weak_ptr<Object> const& object);

	float GetFrameWidth() const;
	float GetFrameHeight() const;

private:
	Animation() = default;
	Animation(Animation const& other);
	Animation(Animation&& other);
	Animation& operator=(Animation const&) = default;
	Animation& operator=(Animation&&) = default;

	void _Release();
	std::unique_ptr<Animation, std::function<void(Animation*)>> _Clone() const;

	std::weak_ptr<AnimationClip> const& _FindAnimationClip(std::string const& tag);

	int frame_x_{};
	int frame_y_{};
	float elapsed_time_{};

	std::weak_ptr<AnimationClip> animation_clip_nullptr_{};
	std::unordered_map<std::string, std::weak_ptr<AnimationClip>> animation_clip_collection_{};

	std::string default_clip_tag_{};
	std::string current_clip_tag_{};
	std::weak_ptr<AnimationClip> default_clip_{};
	std::weak_ptr<AnimationClip> current_clip_{};

	std::weak_ptr<Object> object_{};
};