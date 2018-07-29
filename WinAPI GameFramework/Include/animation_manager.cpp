#include "path_manager.h"
#include "Resource/resource_manager.h"
#include "animation_manager.h"
#include "animation_clip.h"

using namespace std;

bool AnimationManager::Initialize()
{
	ANIMATION_FRAME_INFO animation_frame_info{};
	animation_frame_info.size = { 45.f, 60.f };
	animation_frame_info.start_x = 0;
	animation_frame_info.start_y = 1;
	animation_frame_info.end_x = 13;
	animation_frame_info.count = 13;
	animation_frame_info.count_x = 13;
	animation_frame_info.count_y = 0;
	animation_frame_info.count_max_x = 21;
	animation_frame_info.count_max_y = 8;
	_CreateAnimationClip("Idle", ANIMATION_CLIP::ATLAS, ANIMATION_OPTION::LOOP, 1.f, animation_frame_info, "Person", L"Left.bmp");

	return true;
}

shared_ptr<AnimationClip> const & AnimationManager::FindAnimationClipPrototype(string const& tag)
{
	auto iter = animation_clip_prototype_collection_.find(tag);

	if (iter == animation_clip_prototype_collection_.end())
		return animation_clip_prototype_nullptr_;

	return iter->second;
}

void AnimationManager::_Release()
{
}

bool AnimationManager::_CreateAnimationClip(string const& tag, ANIMATION_CLIP type, ANIMATION_OPTION option, float completion_time, ANIMATION_FRAME_INFO const& frame_info, string const& texture_tag, wstring const& file_name, string const& path_tag)
{
	if (FindAnimationClipPrototype(tag))
		return false;

	auto animation_clip = shared_ptr<AnimationClip>{ new AnimationClip, [](AnimationClip* p) {
		p->_Release();
		delete p;
	} };

	animation_clip->tag_ = tag;
	animation_clip->type_ = type;
	animation_clip->option_ = option;
	animation_clip->frame_info_ = frame_info;
	animation_clip->completion_time_ = completion_time;

	animation_clip->texture_ = ResourceManager::instance()->LoadTexture(texture_tag, file_name, path_tag);

	animation_clip_prototype_collection_.insert(make_pair(tag, move(animation_clip)));

	return true;
}