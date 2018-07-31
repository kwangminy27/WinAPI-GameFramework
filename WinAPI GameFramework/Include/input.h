#pragma once

#include "singleton.h"

class Object;

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

	bool KeyPush(std::string const& tag) const;
	bool KeyPressed(std::string const& tag) const;
	bool KeyUp(std::string const& tag) const;

	template <typename T, typename... Types> void AddKey(T const& element, Types... Args);
	template <typename... Types> void AddKey(std::string const& tag, Types... Args);
	void AddKey();

	XY const& mouse_client_position() const;
	XY const& mouse_world_position() const;
	XY const& mouse_displacement() const;

	void RenderMouse(HDC device_context, float time);

private:
	Input() = default;
	Input(Input const&) = delete;
	Input& operator=(Input const&) = delete;

	virtual void _Release() override;

	std::unique_ptr<KeyInfo> const& _FindKey(string const& tag) const;

	std::unique_ptr<KeyInfo> key_nullptr_{};
	std::unordered_map<std::string, std::unique_ptr<KeyInfo>> key_collection_{};
	std::unique_ptr<KeyInfo> key_buffer_{};

	XY mouse_client_position_{};
	XY mouse_world_position_{};
	XY mouse_displacement_{};
	bool mouse_show_flag_{};

	std::unique_ptr<Object, std::function<void(Object*)>> mouse_{};
};

#include "input.inl"