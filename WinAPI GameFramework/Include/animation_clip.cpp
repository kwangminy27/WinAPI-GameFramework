#include "animation_clip.h"

using namespace std;

AnimationClip::AnimationClip(AnimationClip const& other)
{
	*this = other;
}

AnimationClip::AnimationClip(AnimationClip&& other)
{
	*this = move(other);
}

void AnimationClip::_Release()
{
}

unique_ptr<AnimationClip, function<void(AnimationClip*)>> AnimationClip::_Clone()
{
	return unique_ptr<AnimationClip, function<void(AnimationClip*)>>{ new AnimationClip(*this), [](AnimationClip *p) {
		p->_Release();
		delete p;
	} };
}