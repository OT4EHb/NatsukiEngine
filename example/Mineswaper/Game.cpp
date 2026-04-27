#include <NatsukiMain.hpp>

import Natsuki;
import Area;

class Mineswaper :public Natsuki::Game<Mineswaper> {
	static constexpr float sprite_size = 80.f;
	static constexpr float inverse_size = 1.f / sprite_size;
private:
	Natsuki::SDL sdl{Natsuki::SDL::Flags::VIDEO};
	Natsuki::Window window{"Mineswaper", 800, 800};
	Natsuki::Renderer renderer{window};
	Natsuki::EventHandler eventler;
	Area area{10, 10, 12, renderer};
public:
	Mineswaper();
	SDL_AppResult iterate();
	SDL_AppResult eventHandler(SDL_Event &);
	static void setMetadata() {
		Natsuki::Metadata::setAppName("Mineswaper");
	}

	void checkResult(Result);
};

SET_GAME(Mineswaper);

void Mineswaper::checkResult(Result result) {
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

Mineswaper::Mineswaper() {
	eventler.mouse.setDown(Natsuki::MouseSystem::Button::LEFT,
						   [this](SDL_MouseButtonEvent &e) {
		checkResult(area.onClick(static_cast<size_t>(e.x * inverse_size),
								 static_cast<size_t>(e.y * inverse_size)));
	}
	);
	eventler.mouse.setDown(Natsuki::MouseSystem::Button::RIGHT,
						   [this](SDL_MouseButtonEvent &e) {
		area.setFlag(static_cast<size_t>(e.x * inverse_size),
								 static_cast<size_t>(e.y * inverse_size));
	}
	);
}

SDL_AppResult Mineswaper::iterate() {
	Natsuki::RendererGuard guard(renderer);
	area.render(renderer, sprite_size);
	return SDL_APP_CONTINUE;
}

SDL_AppResult Mineswaper::eventHandler(SDL_Event &event) {
	if (event.type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}

	return eventler(event);
}