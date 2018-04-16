#pragma once

#include <deduction/datatypes/enumeration.hpp>
#include "bridge.hpp"

namespace reduction {
	bridge generate_c_wrapper_header(deduction::enumeration const & enumeration);
	bridge generate_c_wrapper_implementation(deduction::enumeration const & enumeration);
}
