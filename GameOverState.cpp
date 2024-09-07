#include "GameOverState.h"
#include "Definitions.h"
#include "GameState.h"
#include "MainMenuState.h"

#include <sstream>
#include <iostream>

namespace System {
	GameOverState::GameOverState(game_data_ref _data) : data(_data) {}

	void GameOverState::Init() {
		this->data->assets.load_texture("Retry Button", RETRY_BUTTON);
		this->data->assets.load_texture("Home Button", HOME_BUTTON);

		this->retry_button.setTexture(this->data->assets.get_texture("Retry Button"));
		this->home_button.setTexture(this->data->assets.get_texture("Home Button"));

		this->retry_button.setPosition((this->data->window.getSize().x / 2) - (this->retry_button.getLocalBounds().width / 2), (this->data->window.getSize().y / 3) - (this->retry_button.getLocalBounds().height / 2));
		this->home_button.setPosition((this->data->window.getSize().x / 2) - (this->home_button.getLocalBounds().width / 2), (this->data->window.getSize().y / 3 * 2) - (this->home_button.getLocalBounds().height / 2));

	}

	void GameOverState::HandleInput() {
		sf::Event ev;

		while (this->data->window.pollEvent(ev)) {
			if (sf::Event::Closed == ev.type) {
				this->data->window.close();
			}
			if (this->data->inputs.is_sprite_clicked(this->retry_button, sf::Mouse::Left, this->data->window)) {
				this->data->machine.add_state(state_ref(new GameState(data)), true);
			}

			if (this->data->inputs.is_sprite_clicked(this->home_button, sf::Mouse::Left, this->data->window)) {
				this->data->machine.add_state(state_ref(new MainMenuState(data)), true);
			}
		}
	}

	void GameOverState::Update(float delta) {

	}

	void GameOverState::Draw(float delta) {
		this->data->window.clear(sf::Color::Red);

		this->data->window.draw(this->retry_button);
		this->data->window.draw(this->home_button);

		this->data->window.display();
	}
}


