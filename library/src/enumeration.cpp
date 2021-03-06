#include "enumeration.hpp"
#include <fmt/format.h>
#include "name_mangler.hpp"
#include "utility.hpp"

namespace reduction {
	bridge generate_c_wrapper_header(deduction::enumeration const & enumeration) {
		auto const mangledName = mangle_name(enumeration.full_name);

		//enum mangled_enum_name {
		//	mangled_enum_name_case_1,
		//	mangled_enum_name_case_2,
		//};
		fmt::MemoryWriter pub;
		pub << "enum " << mangledName << " {\n";
		std::for_each(std::begin(enumeration.case_labels), std::end(enumeration.case_labels), [&](const auto & caseLabel) {
			pub << "\t" << mangle_name(caseLabel.full_name) << ",\n";
		});
		pub << "};\n";

		auto const publicFileName = generate_file_name(mangledName, visibility::public_file, file_type::interface);

		fmt::MemoryWriter priv;
		priv.write(R"incl(extern "C" {{
	#include "{}"
}}
)incl", publicFileName);

		// mangled_enum_name map(fqd::enumeration value)
		priv << mangledName << " map(" << enumeration.full_name << " value);\n";
		// fqd::enumeration map(mangled_enum_name value)
		priv << enumeration.full_name << " map(" << mangledName << " value);\n";

		bridge::file_info publicFile {
			std::move(publicFileName),
			pub.str()
		};

		bridge::file_info privateFile {
			generate_file_name(mangledName, visibility::private_file, file_type::interface),
			priv.str()
		};

		return { std::move(publicFile), std::move(privateFile) };
	}

	bridge generate_c_wrapper_implementation(deduction::enumeration const & enumeration) {
		auto const mangledName = mangle_name(enumeration.full_name);

		fmt::MemoryWriter priv;

		priv.write("#include \"{}\"\n\n", generate_file_name(mangledName, visibility::private_file, file_type::interface));

		// Map C++ to C
		priv << mangledName << " map(" << enumeration.full_name << " value) {\n"
		<< "\tswitch (value) {\n";

		std::for_each(std::begin(enumeration.case_labels), std::end(enumeration.case_labels), [&](auto const & label) {
			priv << "\tcase " << label.full_name << ":\n"
			<< "\t\treturn " << mangle_name(label.full_name) << ";\n";
		});

		priv << "\t}\n}\n\n";

		// Map C to C++
		priv << enumeration.full_name << " map(" << mangledName << " value) {\n"
			<< "\tswitch (value) {\n";

		std::for_each(std::begin(enumeration.case_labels), std::end(enumeration.case_labels), [&](auto const & label) {
			priv << "\tcase " << mangle_name(label.full_name) << ":\n"
			<< "\t\treturn " << label.full_name << ";\n";
		});

		priv << "\t}\n}\n";

		bridge::file_info privateFile {
			generate_file_name(mangledName, visibility::private_file, file_type::implementation),
			priv.str()
		};

		return { {}, std::move(privateFile) };	}
}
