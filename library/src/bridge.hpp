#pragma once

#include <string>

namespace reduction {
	struct bridge {
		struct file_info {
			std::string name;
			std::string contents;
		};

		file_info pub;
		file_info priv;
	};
}
