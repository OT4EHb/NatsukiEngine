module;
#include <stdexcept>
#include <source_location>
#include <string>
#include <string_view>
#include <filesystem>
export module Natsuki.Exception;
import Natsuki.SDL;


export namespace Natsuki {
	class Exception :
		public std::runtime_error {
	public:
		Exception(std::string_view error,
				  std::source_location loc = std::source_location::current()) :
			runtime_error(
				"Function name:\n "
				+ std::string(loc.function_name())
				+ "\nFile: \n "
				+ std::filesystem::path(loc.file_name()).filename().string()
				+ "\nLine: "
				+ std::to_string(loc.line())
				+ "\nError: "
				+ std::string(error)
			) {}
		Exception(std::source_location loc = std::source_location::current())
			:Exception(SDL::getError(), loc) {}
	};

	inline constexpr void checkCallSDL(bool v, std::source_location loc = std::source_location::current()) {
		if (!v) throw Exception(loc);
	}
}