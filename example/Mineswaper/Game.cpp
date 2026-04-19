#include <NatsukiMain.hpp>

import Natsuki;
import Area;

class Mineswaper :public Natsuki::Game<Mineswaper> {
	static constexpr size_t sprite_size = 80;
	static constexpr float inverse_size = 1.f / 80.f;
private:
	Natsuki::SDL sdl{Natsuki::SDL::Flags::VIDEO};
	Natsuki::Window window{"Mineswaper", 800, 800};
	Natsuki::Renderer renderer{window};
	Area area{10, 10, 10, renderer};
public:
	SDL_AppResult iterate();
	SDL_AppResult eventHandler(SDL_Event &);
	static void setMetadata() {
		Natsuki::Metadata::setAppName("Mineswaper");
	}
};

SET_GAME(Mineswaper);

SDL_AppResult Mineswaper::iterate() {
	Natsuki::RendererGuard guard(renderer);
	area.render(renderer, sprite_size);
	return SDL_APP_CONTINUE;
}

SDL_AppResult Mineswaper::eventHandler(SDL_Event &event) {
	if (event.type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		auto &e = event.button;
		auto result = Result::NONE;
		if (e.button == SDL_BUTTON_LEFT) {
			result = area.onClick(e.x * inverse_size, e.y * inverse_size);
		}
		else if (e.button == SDL_BUTTON_RIGHT) {
			result = area.setFlag(e.x * inverse_size, e.y * inverse_size);
		}
		switch (result) {
			case Result::WIN:
				area.allOpen();
				iterate();
				Natsuki::MessageBox()
					.setFlag(Natsuki::MessageBox::Flags::INFORMATION)
					.setTitle("Result")
					.setMessage("You win. Click OK to start over.")
					.show();
				area.reset();
				break;
			case Result::LOSE:
				area.allOpen();
				iterate();
				Natsuki::MessageBox()
					.setTitle("Result")
					.setMessage("You lose. Click OK to start over.")
					.show();
				area.reset();
				break;
			default:
				break;
		}
	}
	return SDL_APP_CONTINUE;
}