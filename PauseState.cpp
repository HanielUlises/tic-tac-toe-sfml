#include "PauseState.h"
#include "Definitions.h"
#include "GameState.h"
#include "GameState.h"
#include "MainMenuState.h"

#include <sstream>
#include <iostream>

namespace System {
	PauseState::PauseState(game_data_ref _data) : data(_data) {}

	void PauseState::Init() {
		this->data->assets.load_texture("Pause Background", PAUSE_BACKGROUND_PATH);
		this->data->assets.load_texture("Resume Button", RESUME_BUTTON);
		this->data->assets.load_texture("Home Button", HOME_BUTTON);

		this->background.setTexture(this->data->assets.get_texture("Pause Background"));
		this->resume_button.setTexture(this->data->assets.get_texture("Resume Button"));
		this->home_button.setTexture(this->data->assets.get_texture("Home Button"));

		this->resume_button.setPosition((this->data->window.getSize().x / 2) - (this->resume_button.getLocalBounds().width / 2), (this->data->window.getSize().y / 3) - (this->resume_button.getLocalBounds().height / 2));
		this->home_button.setPosition((this->data->window.getSize().x / 2) - (this->home_button.getLocalBounds().width / 2), (this->data->window.getSize().y / 3 * 2) - (this->home_button.getLocalBounds().height / 2));


	}

	void PauseState::HandleInput() {
		sf::Event ev;

		while (this->data->window.pollEvent(ev)) {
			if (sf::Event::Closed == ev.type) {
				this->data->window.close();
			}
			if (this->data->inputs.is_sprite_clicked(this->resume_button, sf::Mouse::Left, this->data->window)) {
				this->data->machine.remove_state();
			}
			if (this->data->inputs.is_sprite_clicked(this->home_button, sf::Mouse::Left, this->data->window)) {
				this->data->machine.remove_state();
				this->data->machine.add_state(state_ref(new MainMenuState(data)), true);
			}
		}
	}

	void PauseState::Update(float delta) {

	}

	void PauseState::Draw(float delta) {
		this->data->window.clear(sf::Color::Red);

		this->data->window.draw(this->background);
		this->data->window.draw(this->resume_button);
		this->data->window.draw(this->home_button);

		this->data->window.display();
	}
}


