#include <algorithm>
#include "StringUtil.h"

bool
hasSuffix(const std::string &full, const std::string &suffix)
{
	if (suffix.size() > full.size())
		return false;
	return full.compare(full.size() - suffix.size(), suffix.size(), suffix.c_str()) == 0;
}

bool
hasAnySuffix(const std::string& str,
			 const std::vector<std::string>& suffixes)
{
	return std::any_of(suffixes.cbegin(), suffixes.cend(),
					   [&str](const std::string& suffix) {
						   return hasSuffix(str, suffix);
					   });
}
