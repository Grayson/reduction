# Deduction

Deduction is a sibling project to [Reduction](https://github.com/Grayson/reduction).  Where Reduction "reduces" C/C++ header files into a JSON description, Deduction "deduces" C files that wrap the public C/C++ datatypes.  The intention is to provide a C wrapper library that can be readily used to create bindings for other languages.

## Example

Following from the [Example](https://github.com/Grayson/reduction#example) used in `Reduction`, `deduction` would produce two files.

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
