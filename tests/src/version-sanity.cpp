#include "catch.hpp"
#include <reduction/reduction.hpp>

TEST_CASE("version sanity", "[version]") {
	REQUIRE(reduction::version == "0.0.1");
}