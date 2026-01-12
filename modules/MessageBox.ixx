module;
#include <string>
#include <SDL3/SDL_messagebox.h>
export module Natsuki.MessageBox;
import Natsuki.Window;

export namespace Natsuki {
	class MessageBox {
	public:
		enum class Flags :SDL_MessageBoxFlags {
			ERROR = SDL_MESSAGEBOX_ERROR,
			WARNING = SDL_MESSAGEBOX_WARNING,
			INFORMATION = SDL_MESSAGEBOX_INFORMATION,
			LEFT_TO_RIGHT = SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
			RIGHT_TO_LEFT = SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT
		};
	private:
		SDL_Window *parrent{nullptr};
		std::string title{};
		std::string message{};
		MessageBox::Flags flags{MessageBox::Flags::ERROR};
	public:
		constexpr inline MessageBox() = default;
		constexpr inline MessageBox &setFlag(MessageBox::Flags flag) noexcept;
		constexpr inline MessageBox &addFlag(MessageBox::Flags flag) noexcept;
		constexpr inline MessageBox &setTitle(std::string_view str);
		constexpr inline MessageBox &setMessage(std::string_view str);
		constexpr inline MessageBox &setParrent(Window &window);
		inline bool show();
	};
}

using namespace Natsuki;

constexpr inline MessageBox &MessageBox::setFlag(MessageBox::Flags flag) noexcept {
	flags = flag;
	return *this;
}

constexpr inline MessageBox &MessageBox::addFlag(MessageBox::Flags flag) noexcept {
	auto sdlFlag = static_cast<SDL_MessageBoxFlags>(flags)
		| static_cast<SDL_MessageBoxFlags>(flag);
	flags = static_cast<MessageBox::Flags>(sdlFlag);
	return *this;
}

constexpr inline MessageBox &MessageBox::setTitle(std::string_view str) {
	title = str;
	return *this;
}

constexpr inline MessageBox &MessageBox::setMessage(std::string_view str) {
	message = str;
	return *this;
}

constexpr inline MessageBox &MessageBox::setParrent(Window &window) {
	parrent = window;
	return *this;
}

inline bool MessageBox::show() {
	return SDL_ShowSimpleMessageBox(static_cast<SDL_MessageBoxFlags>(flags),
									title.c_str(), message.c_str(), parrent);
}