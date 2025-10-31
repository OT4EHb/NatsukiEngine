export module SDLException;
import <stdexcept>;
import <source_location>;
import SDL;

export class SDLException :
	public std::runtime_error {
public:
	SDLException(std::source_location loc = std::source_location::current()) :
		std::runtime_error(
			"Function name:\n "
			+ std::string(loc.function_name()) + "\nError: "
			+ std::string(SDL::getError())
		) {}
};

export constexpr void checkCallSDL(bool v) {
	if (!v) throw SDLException();
}