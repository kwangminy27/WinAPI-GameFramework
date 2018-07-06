#include "input.h"

using namespace std;

bool Input::Initialize()
{
	_AddKey("Ceremony"s, VK_LSHIFT, 'q', VK_RIGHT);

	return true;
}

void Input::Update(float delta_time)
{
	for (auto const& key : key_collection_)
	{
		int count{};
		for (auto const& value : key.second->element)
		{
			if (GetAsyncKeyState(value) & 0x8000)
				++count;
		}

		if (count == key.second->element.size())
		{
			if (!key.second->pressed)
			{
				key.second->push = true;
				key.second->pressed = true;
			}
			else
				key.second->push = false;
		}
		else if (key.second->pressed)
		{
			key.second->push = false;
			key.second->pressed = false;
			key.second->up = true;
		}
		else if (key.second->up)
			key.second->up = false;
	}
}

bool Input::KeyPush(std::string name)
{
	auto& key = _FindKey(name);

	return key->push;
}

bool Input::KeyPressed(std::string name)
{
	auto& key = _FindKey(name);

	return key->pressed;
}

bool Input::KeyUp(std::string name)
{
	auto& key = _FindKey(name);

	return key->up;
}

void Input::_Release()
{
}

unique_ptr<KeyInfo>& Input::_FindKey(string const& name)
{
	auto iter = key_collection_.find(name);

	if (iter == key_collection_.end())
		assert(!"Input::_FindKey");

	return iter->second;
}