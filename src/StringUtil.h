#pragma once

#include <string>
#include <vector>

bool hasSuffix(const std::string& str, const std::string& suffix);

bool hasAnySuffix(const std::string& str,
				  const std::vector<std::string>& suffixes);
