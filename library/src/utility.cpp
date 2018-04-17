#include "utility.hpp"

namespace reduction {
	std::string generate_file_name(std::string base, visibility visibility, file_type type) {
		bool isPrivate = visibility == visibility::private_file;
		return base
			+ (isPrivate ? "_priv" : "")
			+ (type == file_type::interface
			   	? isPrivate ? ".hpp" : ".h"
			   	: ".cpp");
	}
}
