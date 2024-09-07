#include "SplashState.h"

#include <sstream>
#include <iostream>
#include <string>

#include "Definitions.h"

namespace System {
	SplashState::SplashState (game_data_ref _data) : data(_data) {}

	void SplashState::Init() {
		std::string path = "Resources/textures/Splashhh.png";
		this->data->assets.load_texture("Splash State Background", path);

		background.setTexture(this->data->assets.get_texture("Splash State Background"));
	}

	void SplashState::HandleInput() {
		sf::Event ev;
		
		while (this->data->window.pollEvent(ev)) {
			if (sf::Event::Closed == ev.type) {
				this->data->window.close();
			}
		}
	}

	void SplashState::Update(float delta) {
		// Transition to main menu
		if (this->clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) {
			std::cerr << "Going to the main menu" << std::endl;
			this->data->machine.add_state(state_ref(new MainMenuState(data)), true);
		}
	}

	void SplashState::Draw(float delta) {
		this->data->window.clear(sf::Color::Red);
		this->data->window.draw(this->background);
		this->data->window.display();
	}
}