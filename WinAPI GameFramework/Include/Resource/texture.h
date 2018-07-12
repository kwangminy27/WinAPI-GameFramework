#pragma once

#include "../tag.h"

class Texture : public Tag
{
	friend class ResourceManager;
public:
	bool LoadTexture(std::string tag, std::string file_name, std::string path_tag);

protected:
	Texture() = default;
	Texture(Texture const& other);
	virtual ~Texture() = default;

	virtual void _Release() override;

	HDC memory_device_context_{};
	HBITMAP bitmap_{};
	HBITMAP old_bitmap_{};
};
