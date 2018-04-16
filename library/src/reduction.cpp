#include "reduction.hpp"
#include <deduction/json/json.hpp>
#include <deduction/json/parse-result.hpp>
#include <fmt/format.h>

#include "enumeration.hpp"
#include "header-converter.hpp"
#include "implementation-converter.hpp"

namespace
{
	using namespace reduction;

	struct header_visitor {
		bridge operator()(const deduction::alias & a) const { return {}; }
		bridge operator()(const deduction::enumeration & en) const { return generate_c_wrapper_header(en); }
		bridge operator()(const deduction::function & fun) const { return {}; }
		bridge operator()(const deduction::structure & st) const { return {}; }
		bridge operator()(const deduction::variable & var) const { return {}; }
	};

	struct implementation_visitor {
		bridge operator()(const deduction::alias & a) const { return {}; }
		bridge operator()(const deduction::enumeration & en) const { return generate_c_wrapper_implementation(en); }
		bridge operator()(const deduction::function & fun) const { return {}; }
		bridge operator()(const deduction::structure & st) const { return {}; }
		bridge operator()(const deduction::variable & var) const { return {}; }
	};

}

namespace reduction {
	std::string const version = "0.0.1";

	deduction::parse_result parse_json(std::string const & jsonString)
	{
		try {
			auto json = nlohmann::json::parse(jsonString);
			return json.at("items").get<deduction::parse_result>();
		}
		catch (nlohmann::json::parse_error error) {
			return deduction::parse_result {};
		}
	}

	std::vector<bridge> create_wrappers(deduction::parse_result parsedResults) {
		std::vector<bridge> bridges;
		header_visitor visitor;
		std::for_each(std::begin(parsedResults.items), std::end(parsedResults.items), [&](auto const & item) {
			bridges.emplace_back(mpark::visit(visitor, item));
		});
		return bridges;
	}
}
