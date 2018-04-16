#include "utility.hpp"

namespace reduction {
	std::string generate_file_name(std::string base, visibility visibility, file_type type) {
		return base
			+ (visibility == visibility::private_file ? "_priv" : "")
			+ (type == file_type::interface ? ".h" : ".c");
	}
}
