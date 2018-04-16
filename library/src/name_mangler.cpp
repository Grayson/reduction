#include "name_mangler.hpp"

namespace reduction {
	std::string mangle_name(std::string name) {
		while (auto const pos = name.find("::")) {
			if (pos == std::string::npos)
				break;
			name.replace(pos, 2, "_");
		}
		return name;
	}
}
