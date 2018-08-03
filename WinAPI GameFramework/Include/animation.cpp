#include "Object/object.h"
#include "Object/effect.h"
#include "Resource/resource_manager.h"
#include "animation_manager.h"
#include "animation.h"
#include "animation_clip.h"

using namespace std;

bool Animation::Initialize()
{
	return true;
}

// <규칙>
// 1. animation_clip은 직사각형 모양으로 sprite atlas에 구성되야 한다.
// 2. frame_x는 start_x부터 시작한다.
// 3. 마지막 줄은 frame이 가득차지 않을 수 있다.
void Animation::Update(float time)
{
	if (current_clip_.expired())
		return;

	auto current_clip = current_clip_.lock();
	auto& frame_info = current_clip->frame_info_;
	float interval_time = current_clip->completion_time_ / frame_info.count;

	elapsed_time_ += time;

	while (elapsed_time_ >= interval_time)
	{
		elapsed_time_ -= interval_time;

		++frame_x_;

		if (frame_y_ == frame_info.start_y + frame_info.count_y)
		{
			if (frame_x_ == frame_info.end_x)
			{
				frame_x_ = frame_info.start_x;
				frame_y_ = frame_info.start_y;

				switch (current_clip->option_)
				{
				case ANIMATION_OPTION::RETURN:
					ChangeClip(default_clip_tag_);
					break;
				case ANIMATION_OPTION::DESTROY:
					object_.lock()->set_activation(false);
					// notification callback
					break;
				}
			}
		}

		if (frame_x_ >= frame_info.start_x + frame_info.count_x)
		{
			++frame_y_;

			frame_x_ = frame_info.start_x;
		}
	}
}

bool Animation::AddAnimationClip(string const& tag)
{
	auto const& animation_manager = AnimationManager::instance();

	auto animation_clip = animation_manager->FindAnimationClipPrototype(tag);

	if (!animation_clip)
		return false;

	animation_clip_collection_.insert(make_pair(tag, move(animation_clip)));

	if (animation_clip_collection_.size() == 1)
	{
		set_default_clip(tag);
		set_current_clip(tag);
	}

	return true;
}

void Animation::ChangeClip(string const& tag)
{
	if (current_clip_tag_ == tag)
		return;

	set_current_clip(tag);
}

void Animation::set_default_clip(string const& tag)
{
	default_clip_tag_ = tag;
	default_clip_ = _FindAnimationClip(tag);
}

void Animation::set_current_clip(string const& tag)
{
	current_clip_tag_ = tag;
	current_clip_ = _FindAnimationClip(tag);
	
	if (current_clip_.expired() || object_.expired())
		return;

	auto current_clip = current_clip_.lock();
	frame_x_ = current_clip->frame_info_.start_x;
	frame_y_ = current_clip->frame_info_.start_y;
	elapsed_time_ = 0.f;

	object_.lock()->set_texture(current_clip->texture_);
}

void Animation::set_object(weak_ptr<Object> const& object)
{
	object_ = object;
}

int Animation::frame_x() const
{
	return frame_x_;
}

int Animation::frame_y() const
{
	return frame_y_;
}

float Animation::GetFrameWidth() const
{
	return current_clip_.lock()->frame_info_.size.x;
}

float Animation::GetFrameHeight() const
{
	return current_clip_.lock()->frame_info_.size.y;
}

Animation::Animation(Animation const& other)
{
	*this = other;
}

Animation::Animation(Animation&& other)
{
	*this = move(other);
}

void Animation::_Release()
{
}

unique_ptr<Animation, function<void(Animation*)>> Animation::_Clone() const
{
	return unique_ptr<Animation, function<void(Animation*)>>{ new Animation(*this), [](Animation* p) {
		p->_Release();
		delete p;
	} };
}

weak_ptr<AnimationClip> const& Animation::_FindAnimationClip(string const& tag)
{
	auto iter = animation_clip_collection_.find(tag);

	if (iter == animation_clip_collection_.end())
		return animation_clip_nullptr_;

	return iter->second;
}