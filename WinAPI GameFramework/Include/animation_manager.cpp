#include "path_manager.h"
#include "Resource/resource_manager.h"
#include "animation_manager.h"
#include "animation_clip.h"

using namespace std;
using namespace filesystem;

bool AnimationManager::Initialize()
{
	_LoadTextureAltas("Halbae", L"halbae.csv");
	_LoadTextureAltas("Effect", L"effect.csv");

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

bool AnimationManager::_CreateAnimationClip(string const& tag, ANIMATION_CLIP_TYPE type, ANIMATION_OPTION option, float completion_time, ANIMATION_FRAME_INFO const& frame_info, string const& texture_tag, wstring const& file_name, string const& path_tag)
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

bool AnimationManager::_LoadTextureAltas(string const& tag, wstring const& file_name, string const& path_tag)
{
	path path_buffer = PathManager::instance()->FindPath(path_tag);

	wstring full_path = path_buffer.wstring();
	full_path += file_name;

	ifstream file{ full_path };

	if (file.bad())
		return false;

	string texture_file{};
	stringstream ss{};
	getline(file, texture_file);
	ss.str(texture_file);
	getline(ss, texture_file, ',');

	wstring wstring_texture_file{};
	wstring_texture_file.assign(texture_file.begin(), texture_file.end());

	auto texture = ResourceManager::instance()->LoadTexture(tag, wstring_texture_file);
	
	while (true)
	{
		auto animation_clip = shared_ptr<AnimationClip>{ new AnimationClip, [](AnimationClip* p) {
			p->_Release();
			delete p;
		} };

		string line{};
		stringstream line_stream{};

		getline(file, line);

		if (line.empty())
			break;

		line_stream.str(line);
	
		string tag{};
		string type{};
		string option{};
		string size_x{};
		string size_y{};
		string start_x{};
		string start_y{};
		string end_x{};
		string count{};
		string count_x{};
		string count_y{};
		string completion_time{};

		getline(line_stream, tag, ',');
		getline(line_stream, type, ',');
		getline(line_stream, option, ',');
		getline(line_stream, size_x, ',');
		getline(line_stream, size_y, ',');
		getline(line_stream, start_x, ',');
		getline(line_stream, start_y, ',');
		getline(line_stream, end_x, ',');
		getline(line_stream, count, ',');
		getline(line_stream, count_x, ',');
		getline(line_stream, count_y, ',');
		getline(line_stream, completion_time, ',');

		animation_clip->tag_ = tag;
		animation_clip->type_ = static_cast<ANIMATION_CLIP_TYPE>(stoi(type));
		animation_clip->option_ = static_cast<ANIMATION_OPTION>(stoi(option));
		animation_clip->frame_info_.size.x = stof(size_x);
		animation_clip->frame_info_.size.y = stof(size_y);
		animation_clip->frame_info_.start_x = stoi(start_x);
		animation_clip->frame_info_.start_y = stoi(start_y);
		animation_clip->frame_info_.end_x = stoi(end_x);
		animation_clip->frame_info_.count = stoi(count);
		animation_clip->frame_info_.count_x = stoi(count_x);
		animation_clip->frame_info_.count_y = stoi(count_y);
		animation_clip->texture_ = texture;
		animation_clip->completion_time_ = stof(completion_time);
		
		animation_clip_prototype_collection_.insert(make_pair(tag, move(animation_clip)));
	}

	return true;
}
