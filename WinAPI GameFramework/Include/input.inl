#pragma once

using namespace std;

template <typename T, typename... Types>
void Input::AddKey(T const& element, Types... Args)
{
	if (!key_buffer_)
		key_buffer_.reset(new KeyInfo);

	key_buffer_->element.push_back(element);

	AddKey(Args...);
}

template <typename... Types>
void Input::AddKey(string const& tag, Types... Args)
{
	if (!key_buffer_)
		key_buffer_.reset(new KeyInfo);

	key_buffer_->tag = tag;

	AddKey(Args...);
}