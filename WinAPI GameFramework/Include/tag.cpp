#include "tag.h"

using namespace std;

void Tag::set_tag(string const& tag)
{
	tag_ = tag;
}

string const& Tag::tag() const
{
	return tag_;
}

void Tag::set_enablement(bool enablement)
{
	enablement_= enablement;
}

void Tag::set_activation(bool activation)
{
	activation_ = activation;
}

bool Tag::enablement() const
{
	return enablement_;
}

bool Tag::activation() const
{
	return activation_;
}
