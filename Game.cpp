#include "Game.h"
#include "SplashState.h"

namespace System {
	Game::Game(int width, int height, std::string win_title) {
		data->window.create(sf::VideoMode(width, height), win_title, sf::Style::Close | sf::Style::Titlebar);
		data->machine.add_state(state_ref(new SplashState(this->data)));
		this->Run();
	}

	void Game::Run() {
		float new_time, frame_time, interpolation;
		float current_time = this->clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		// Game loop logic
		while (this->data->window.isOpen()) {
			this->data->machine.process_state_changes();
			new_time = this->clock.getElapsedTime().asSeconds();
			frame_time = new_time - current_time;

			if (frame_time > 0.25f) {
				frame_time = 0.25;
			}

			current_time = new_time;
			accumulator += frame_time;

			while (accumulator >= delta) {
				this->data->machine.get_active_state()->HandleInput();
				this->data->machine.get_active_state()->Update(delta);

				accumulator -= delta;
			}

			interpolation = accumulator / delta;
			this->data->machine.get_active_state()->Draw(interpolation);
		}
	}
}