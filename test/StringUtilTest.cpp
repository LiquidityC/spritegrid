#include <string>
#include "catch.hpp"
#include "../src/StringUtil.h"

TEST_CASE( "Test hasSuffix", "[string][suffix]")
{
	std::string str = "Bananas are not straight";
	REQUIRE(hasSuffix(str, "straight"));
	REQUIRE(hasSuffix(str, "not straight"));
	REQUIRE(!hasSuffix(str, "are straight"));
	REQUIRE(!hasSuffix(str, "bent"));
}

TEST_CASE( "Test hasAnySuffix", "[string][suffix]")
{
	std::string str = "Bananas are not straight";

	std::vector<std::string> options;

	options.push_back("bent");
	REQUIRE(!hasAnySuffix(str, options));
	options.push_back("straight");
	REQUIRE(hasAnySuffix(str, options));
	options.pop_back();
	REQUIRE(!hasAnySuffix(str, options));
	options.push_back("test");
	options.push_back("no match");
	options.push_back("are not straight");
	options.push_back("are straight");
	REQUIRE(hasAnySuffix(str, options));
	options.clear();
	REQUIRE(!hasAnySuffix(str, options));
}
