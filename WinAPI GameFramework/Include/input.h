#pragma once

#include "singleton.h"

struct KeyInfo
{
	std::string name{};
	std::vector<__int8> element{};
	bool push{};
	bool pressed{};
	bool up{};
};

class Input : public Singleton<Input>
{
	friend class Singleton<Input>;
public:
	bool Initialize();
	void Update(float delta_time);
	bool KeyPush(std::string name);
	bool KeyPressed(std::string name);
	bool KeyUp(std::string name);

private:
	virtual void _Release();

	template <typename T, typename... Types>
	void _AddKey(T const& element, Types... Args)
	{
		if (!key_dummy_)
			key_dummy_.reset(new KeyInfo);

		key_dummy_->element.push_back(element);

		_AddKey(Args...);
	}

	template <typename... Types>
	void _AddKey(std::string const& name, Types... Args)
	{
		if (!key_dummy_)
			key_dummy_.reset(new KeyInfo);

		key_dummy_->name = name;

		_AddKey(Args...);
	}

	void _AddKey()
	{
		std::string name = key_dummy_->name;
		key_collection_.insert(std::make_pair(std::move(name), std::move(key_dummy_)));
	}

	std::unique_ptr<KeyInfo>& _FindKey(string const& name);

	std::unordered_map<std::string, std::unique_ptr<KeyInfo>> key_collection_{};
	std::unique_ptr<KeyInfo> key_dummy_{};
};