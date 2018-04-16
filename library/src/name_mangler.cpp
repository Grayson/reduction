#include "name_mangler.hpp"

namespace reduction {
	std::string mangle_name(std::string const & name) {
		auto mangledName = name;

		while (auto const pos = mangledName.find("::")) {
			if (pos == std::string::npos)
				break;
			mangledName.replace(pos, 2, "_");
		}

		return mangledName;
	}
}
