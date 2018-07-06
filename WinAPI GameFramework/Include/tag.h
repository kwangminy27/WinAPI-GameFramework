#pragma once

#include "stdafx.h"

class Tag
{
public:
	Tag() = default;

	bool Initialize();
	void set_tag(std::string const& tag);
	std::string const& tag() const;
	void set_enablement(bool flag);
	void set_activation(bool flag);
	bool enablement() const;
	bool activation() const;

protected:
	virtual void _Release() = 0;

	std::string tag_{};
	bool enablement_{};
	bool activation_{};
};