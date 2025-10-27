export module SDLException;
import <stdexcept>;
import SDL;

export class SDLException :
	public std::runtime_error {
public:
	SDLException() :
		std::runtime_error(SDL::getError()) {}
	SDLException(std::string_view error) :
		std::runtime_error(error.data()) {}
};