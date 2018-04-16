#pragma once

#include <string>

namespace reduction {
	enum class visibility {
		public_file,
		private_file,
	};

	enum class file_type {
		interface,
		implementation,
	};

	std::string generate_file_name(std::string base, visibility visibility, file_type type);
}
