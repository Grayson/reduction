#include <string>
#include <vector>
#include <deduction/datatypes/parse-result.hpp>
#include "bridge.hpp"

namespace reduction {
	extern std::string const version;

	deduction::parse_result parse_json(std::string const & jsonString);
	std::vector<bridge> create_wrappers(deduction::parse_result parsedResults);
}
