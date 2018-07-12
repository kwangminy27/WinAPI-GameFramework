#pragma once

#include "../tag.h"

class Texture : public Tag
{
	friend class ResourceManager;
public:
	bool LoadTexture(std::string tag, std::wstring file_name, std::string path_tag);

	HDC memory_device_context() const;
	int width() const;
	int height() const;

protected:
	Texture() = default;
	Texture(Texture const& other);
	virtual ~Texture() = default;

	virtual void _Release() override;

	HDC memory_device_context_{};
	HBITMAP bitmap_{};
	HBITMAP old_bitmap_{};
	BITMAP bitmap_structure_{};
	int width_{};
	int height_{};
};
