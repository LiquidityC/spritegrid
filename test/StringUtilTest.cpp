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
