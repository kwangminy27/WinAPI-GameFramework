#pragma once

#include "singleton.h"

struct KeyInfo
{
	std::string tag{};
	std::vector<__int8> element{};
	bool push{};
	bool pressed{};
	bool up{};
};

class Input final : public Singleton<Input>
{
	friend class Singleton<Input>;
public:
	bool Initialize();
	void Update(float delta_time);

	bool KeyPush(std::string const& tag);
	bool KeyPressed(std::string const& tag);
	bool KeyUp(std::string const& tag);

	template <typename T, typename... Types> void AddKey(T const& element, Types... Args);
	template <typename... Types> void AddKey(std::string const& tag, Types... Args);
	void AddKey();

private:
	Input() = default;
	Input(Input const&) = delete;
	Input& operator=(Input const&) = delete;

	virtual void _Release() override;

	std::unique_ptr<KeyInfo> const& _FindKey(string const& tag) const;

	std::unique_ptr<KeyInfo> nullptr_key_{};
	std::unordered_map<std::string, std::unique_ptr<KeyInfo>> key_collection_{};
	std::unique_ptr<KeyInfo> key_buffer_{};
};

#include "input.inl"