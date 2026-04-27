module;
#include <stdexcept>
#include <source_location>
#include <string>
#include <string_view>
#include <filesystem>
#include <SDL3/SDL_error.h>
export module Natsuki.Exception;

export namespace Natsuki {
	class Exception :
		public std::runtime_error {
	public:
		Exception(std::string_view error,
				  std::source_location loc = std::source_location::current()) :
			runtime_error(
				"The c++23 call stack will be here, but for now, settle for that:\n"
				"File: "
				+ std::filesystem::path(loc.file_name()).filename().string()
				+ "\nLine: "
				+ std::to_string(loc.line())
				+ "\nError: "
				+ std::string(error)
			) {}
		Exception(std::source_location loc = std::source_location::current())
			:Exception(SDL_GetError(), loc) {}
	};

	inline constexpr void checkCall(bool v, std::source_location loc = std::source_location::current()) {
		if (!v) [[unlikely]] 
			throw Exception(loc);
	}
}