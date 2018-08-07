#pragma once

#include "singleton.h"

class AudioManager final : public Singleton<AudioManager>
{
	friend class Singleton<AudioManager>;
public:
	bool Initialize();
	void Update();
	std::shared_ptr<DirectX::SoundEffect> FindSoundEffect(std::string const& tag);
	void KeepSoundEffectInstance(std::unique_ptr<DirectX::SoundEffectInstance> sound_effect_instance);

private:
	AudioManager() = default;
	AudioManager(AudioManager const&) = delete;
	AudioManager& operator=(AudioManager const&) = delete;

	virtual void _Release() override;

	bool _LoadSoundEffect(std::string const& tag, std::wstring const& file_name, std::string const& path_tag = "SoundPath");

	std::unique_ptr<DirectX::AudioEngine> audio_engine_{};
	std::unordered_map<std::string, std::shared_ptr<DirectX::SoundEffect>> sound_effect_collection_{};
	std::list<std::unique_ptr<DirectX::SoundEffectInstance>> sound_effect_instance_list_{};
};