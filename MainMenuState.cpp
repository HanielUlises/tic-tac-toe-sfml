#include "MainMenuState.h"
#include "Definitions.h"
#include "GameState.h"

#include <sstream>
#include <iostream>

namespace System {
	MainMenuState::MainMenuState(game_data_ref _data) : data(_data){}

	void MainMenuState::Init() {
		this->data->assets.load_texture("Background", MAIN_MENU_BACKGROUND_PATH);
		this->data->assets.load_texture("Play Button", MAIN_MENU_PLAY_BUTTON);
		this->data->assets.load_texture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
		this->data->assets.load_texture("Title", MAIN_MENU_TITLE_PATH);

		this->background.setTexture(this->data->assets.get_texture("Background"));
		this->play_button.setTexture(this->data->assets.get_texture("Play Button"));
		this->play_button_outer.setTexture(this->data->assets.get_texture("Play Button Outer"));
		this->title.setTexture(this->data->assets.get_texture("Title"));

		this->play_button.setPosition((SCREEN_WIDTH / 2) - (this->play_button.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->play_button.getGlobalBounds().height / 2));

		this->play_button_outer.setPosition((SCREEN_WIDTH / 2) - (this->play_button_outer.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->play_button_outer.getGlobalBounds().height / 2));

		this->title.setPosition((SCREEN_WIDTH / 2) - (this->title.getGlobalBounds().width / 2), this->title.getGlobalBounds().height * 0.1);

	}

	void MainMenuState::HandleInput() {
		sf::Event ev;

		while (this->data->window.pollEvent(ev)) {
			if (sf::Event::Closed == ev.type) {
				this->data->window.close();
			}
			if (this->data->inputs.is_sprite_clicked(this->play_button, sf::Mouse::Left, this->data->window)) {
				this->data->machine.add_state(state_ref(new GameState(data)), true);
			}
		}
	}

	void MainMenuState::Update(float delta) {

	}

	void MainMenuState::Draw(float delta) {
		this->data->window.clear(sf::Color::Red);

		this->data->window.draw(this->background);
		this->data->window.draw(this->play_button);
		this->data->window.draw(this->play_button_outer);
		this->data->window.draw(this->title);

		this->data->window.display();
	}
}


