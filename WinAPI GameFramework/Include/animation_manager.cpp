#include "path_manager.h"
#include "animation_manager.h"
#include "animation_clip_atlas.h"

using namespace std;

bool AnimationManager::Initialize()
{
	return true;
}

bool AnimationManager::LoadAnimationClipAtlas(string const& tag, wstring const& file_name, string const& path_tag)
{
	if (FindAnimationClipAtlas(tag))
		return false;

	auto animation_clip_atlas = shared_ptr<AnimationClipAtlas>{ new AnimationClipAtlas, [](AnimationClipAtlas* p) {
		p->_Release();
		delete p;
	} };

	// 1. info 파일 로딩
	// 2. clip 분할해서 저장
}

shared_ptr<AnimationClipAtlas> const& AnimationManager::FindAnimationClipAtlas(string const& tag)
{
	auto iter = animation_clip_atlas_prototype_collection_.find(tag);

	if (iter == animation_clip_atlas_prototype_collection_.end())
		return animation_clip_atlas_nullptr_;

	return iter->second;
}

void AnimationManager::_Release()
{
}