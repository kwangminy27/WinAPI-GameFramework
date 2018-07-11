#pragma once

#include "stdafx.h"

class Tag
{
public:
	std::string const& tag() const;
	void set_tag(std::string const& tag);

	bool enablement() const;
	void set_enablement(bool flag);
	
	bool activation() const;
	void set_activation(bool flag);

protected:
	Tag() = default;

	virtual void _Release() = 0;

	std::string tag_{};
	bool enablement_{true};
	bool activation_{true};
};