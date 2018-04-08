# Reduction

Reduction is a sibling project to [Deduction](https://github.com/Grayson/deduction).  Where Deduction "deduces" a JSON description from C/C++ files, Reduction "reduces" C++ libraries into C wrapper libraries based on that description.  The intention is these wrapper libraries can readily  be used to create bindings for other languages.

## Example

Following from the [Example](https://github.com/Grayson/deduction#example) used in `deduction`, `reduction` would produce two files.

The first will be a header file:

	// examplelib-core.h
	char const * const examplelib_version_info();
	
	typedef examplelib_core_t void *;
	examplelib_core_t examplelib_core_create();
	void examplelib_core_destroy(examplelib_core_t core);
	
	void examplelib_core_do_something(examplelib_core_t core);

The second will be the wrapper implementation:

	#include <examplelib/core.h>
	extern "C" {
		#include "examplelib-core.h"
		
		char const * const examplelib_version_info() {
			return examplelib::version_info.c_str();
		}
		
		examplelib_core_t examplelib_core_create() {
			auto const *realCore = new examplelib::core();
			return static_cast<examplelib_core_t>(realCore);
		}
		
		void examplelib_core_destroy(examplelib_core_t core) {
			auto const *realCore = static_cast<examplelib::core *>(core);
			delete realCore;
		}
	
		void examplelib_core_do_something(examplelib_core_t core) {
			auto const *realCore = static_cast<examplelib::core *>(core);
			realCore->do_something();
		}
	}

## Contact

[Grayson Hansard](grayson.hansard@gmail.com)  
[@Grayson](http://twitter.com/Grayson)
