#include "audio_manager.h"
#include "path_manager.h"

using namespace std;
using namespace filesystem;
using namespace DirectX;

bool AudioManager::Initialize()
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	AUDIO_ENGINE_FLAGS audio_engine_flags = AudioEngine_Default;
#ifdef _DEBUG
	audio_engine_flags = audio_engine_flags | AudioEngine_Debug;
#endif
	audio_engine_ = std::make_unique<AudioEngine>(audio_engine_flags);

	_LoadSoundEffect("town1", L"town1.wav");

	return true;
}

void AudioManager::Update()
{
	if (!audio_engine_->Update())
	{
		// 실패 시 처리
	}
}

shared_ptr<SoundEffect> AudioManager::FindSoundEffect(string const& tag)
{
	auto iter = sound_effect_collection_.find(tag);

	if (iter == sound_effect_collection_.end())
		return shared_ptr<SoundEffect>{};

	return iter->second;
}

void AudioManager::KeepSoundEffectInstance(std::unique_ptr<DirectX::SoundEffectInstance> sound_effect_instance)
{
	sound_effect_instance_list_.push_back(move(sound_effect_instance));
}

void AudioManager::Suspend()
{
	audio_engine_->Suspend();
}

void AudioManager::Resume()
{
	audio_engine_->Resume();
}

void AudioManager::_Release()
{
}

bool AudioManager::_LoadSoundEffect(string const& tag, wstring const& file_name, string const& path_tag)
{
	path path_buffer = PathManager::instance()->FindPath(path_tag);

	if (path_buffer.empty())
		return false;

	wstring full_path = path_buffer.wstring();
	full_path += file_name;

	auto sound_effect = std::make_unique<SoundEffect>(audio_engine_.get(), full_path.c_str());

	sound_effect_collection_.insert(make_pair(tag, move(sound_effect)));

	return true;
}