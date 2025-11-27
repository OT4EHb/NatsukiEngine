export module SDLException;
import <stdexcept>;
import <source_location>;
import <string>;
import <filesystem>;
import SDL;

export class SDLException :
	public std::runtime_error {
public:
	SDLException(std::source_location loc = std::source_location::current()) :
		std::runtime_error(
			"Function name:\n "
			+ std::string(loc.function_name())
			+ "\nFile: \n "
			+ std::filesystem::path(loc.file_name()).filename().string()
			+"\nLine: "
			+ std::to_string(loc.line())
			+ "\nError: "
			+ std::string(SDL::getError())
		) {}
};

export inline void checkCallSDL(bool v, std::source_location loc = std::source_location::current()) {
	if (!v) throw SDLException(loc);
}