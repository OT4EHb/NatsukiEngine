#include <GameState.hpp>
#include <Game.hpp>

constexpr float sprite_size = 80.f;
constexpr float inverse_size = 1.f / sprite_size;

void GameState::checkResult(Result result) {
	switch (result) {
		case Result::WIN:
			area.allOpen();
			{
				Natsuki::RendererGuard g(game.renderer);
				render();
			}
			Natsuki::MessageBox()
				.setFlag(Natsuki::MessageBox::Flags::INFORMATION)
				.setTitle("Result")
				.setMessage("You win. Click OK to start over.")
				.show();
			area.reset();
			break;
		case Result::LOSE:
			area.allOpen();
			{
				Natsuki::RendererGuard g(game.renderer);
				render();
			}
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

GameState::GameState(Mineswaper &game) :game(game),
area(10, 10, 12, game.renderer) {}

void GameState::enter() {
	game.eventler.mouse.setDown(Natsuki::MouseSystem::Button::LEFT,
								[this](SDL_MouseButtonEvent &e) {
		checkResult(area.onClick(static_cast<size_t>(e.x * inverse_size),
								 static_cast<size_t>(e.y * inverse_size)));
	}
	);
	game.eventler.mouse.setDown(Natsuki::MouseSystem::Button::RIGHT,
								[this](SDL_MouseButtonEvent &e) {
		area.setFlag(static_cast<size_t>(e.x * inverse_size),
					 static_cast<size_t>(e.y * inverse_size));
	}
	);
	game.eventler.key.setDown(SDL_Scancode::SDL_SCANCODE_ESCAPE, [this](SDL_KeyboardEvent &e) {
		game.stater.change<MenuState>(game);
	}
	);
}

void GameState::exit() {
	game.eventler.mouse.clearDown(Natsuki::MouseSystem::Button::LEFT);
	game.eventler.mouse.clearDown(Natsuki::MouseSystem::Button::RIGHT);
}

bool GameState::render() {
	area.render(game.renderer, sprite_size);
	return true;
}

SDL_AppResult GameState::event(SDL_Event &e) {
	return game.eventler(e);
}