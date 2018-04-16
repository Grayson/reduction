#include "catch.hpp"
#include <reduction/reduction.hpp>

char const * const EnumerationJson = R"json({
"items": [
	{
		"_type": "enumeration",
		"name": "testenum",
		"full_name": "reduction::testenum",
		"cases": [
			{ "name": "foo", "full_name": "reduction::testenum::foo" },
			{ "name": "bar", "full_name": "reduction::testenum::bar" },
			{ "name": "baz", "full_name": "reduction::testenum::baz" }
		]
	}
]
})json";

TEST_CASE("parse json", "[enumeration]") {
	auto const result = reduction::parse_json(EnumerationJson);
	REQUIRE(result.items.size() == 1);

	auto & enumeration = mpark::get<deduction::enumeration>(result.items[0]);
	REQUIRE(enumeration.name == "testenum");
	REQUIRE(enumeration.full_name == "reduction::testenum");
	REQUIRE(enumeration.case_labels.size() == 3);
	REQUIRE(enumeration.case_labels[0].name == "foo");
	REQUIRE(enumeration.case_labels[0].full_name == "reduction::testenum::foo");
	REQUIRE(enumeration.case_labels[1].name == "bar");
	REQUIRE(enumeration.case_labels[1].full_name == "reduction::testenum::bar");
	REQUIRE(enumeration.case_labels[2].name == "baz");
	REQUIRE(enumeration.case_labels[2].full_name == "reduction::testenum::baz");
}
