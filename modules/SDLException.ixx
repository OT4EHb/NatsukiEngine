module;
#include <stdexcept>
#include <source_location>
#include <string>
#include <filesystem>
export module Natsuki.SDLException;
import Natsuki.SDL;


export namespace Natsuki {
	using std::runtime_error;

	class SDLException :
		public runtime_error {
	public:
		SDLException(std::source_location loc = std::source_location::current()) :
			runtime_error(
				"Function name:\n "
				+ std::string(loc.function_name())
				+ "\nFile: \n "
				+ std::filesystem::path(loc.file_name()).filename().string()
				+ "\nLine: "
				+ std::to_string(loc.line())
				+ "\nError: "
				+ std::string(SDL::getError())
			) {}
	};

	inline constexpr void checkCallSDL(bool v, std::source_location loc = std::source_location::current()) {
		if (!v) throw SDLException(loc);
	}
}