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
	bool KeyPush(std::string const& name);
	bool KeyPressed(std::string const& name);
	bool KeyUp(std::string const& name);

private:
	Input() = default;
	Input(Input const&) = delete;
	Input& operator=(Input const&) = delete;

	virtual void _Release() override;

	template <typename T, typename... Types>
	void _AddKey(T const& element, Types... Args)
	{
		if (!key_dummy_)
			key_dummy_.reset(new KeyInfo);

		key_dummy_->element.push_back(element);

		_AddKey(Args...);
	}

	template <typename... Types>
	void _AddKey(std::string const& tag, Types... Args)
	{
		if (!key_dummy_)
			key_dummy_.reset(new KeyInfo);

		key_dummy_->tag = tag;

		_AddKey(Args...);
	}

	void _AddKey()
	{
		std::string tag = key_dummy_->tag;
		key_collection_.insert(std::make_pair(std::move(tag), std::move(key_dummy_)));
	}

	std::unique_ptr<KeyInfo>& _FindKey(string const& name);

	std::unordered_map<std::string, std::unique_ptr<KeyInfo>> key_collection_{};
	std::unique_ptr<KeyInfo> key_dummy_{};
};