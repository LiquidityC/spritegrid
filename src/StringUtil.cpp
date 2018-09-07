#include "StringUtil.h"

bool
hasSuffix(const std::string &full, const std::string &suffix)
{
	if (suffix.size() > full.size())
		return false;
	return full.compare(full.size() - suffix.size(), suffix.size(), suffix.c_str()) == 0;
}

