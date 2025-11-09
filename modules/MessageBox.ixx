export module MessageBox;
import <string>;
import <SDL3/SDL_messagebox.h>;
import Window;

export class MessageBox {
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
	MessageBox() = default;
	inline MessageBox &setFlag(MessageBox::Flags flag) noexcept;
	inline MessageBox &addFlag(MessageBox::Flags flag) noexcept;
	inline MessageBox &setTitle(std::string_view str);
	inline MessageBox &setMessage(std::string_view str);
	inline MessageBox &setParrent(Window &window);
	inline bool show();
};

inline MessageBox &MessageBox::setFlag(MessageBox::Flags flag) noexcept {
	flags = flag;
	return *this;
}

inline MessageBox &MessageBox::addFlag(MessageBox::Flags flag) noexcept {
	auto sdlFlag = static_cast<SDL_MessageBoxFlags>(flags)
		| static_cast<SDL_MessageBoxFlags>(flag);
	flags = static_cast<MessageBox::Flags>(sdlFlag);
	return *this;
}

inline MessageBox &MessageBox::setTitle(std::string_view str) {
	title = str;
	return *this;
}

inline MessageBox &MessageBox::setMessage(std::string_view str) {
	message = str;
	return *this;
}

inline MessageBox &MessageBox::setParrent(Window &window) {
	parrent = window.window;
}

inline bool MessageBox::show() {
	return SDL_ShowSimpleMessageBox(static_cast<SDL_MessageBoxFlags>(flags),
									title.c_str(), message.c_str(), parrent);
}