#pragma once

#include "bridge.hpp"

namespace reduction {
	template <typename TDeductionClass>
	bridge generate_c_wrapper_implementation(TDeductionClass const & klass);
}
