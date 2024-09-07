#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace System {
	class MainMenuState : public State {
	public:
		MainMenuState(game_data_ref _data);

		void Init();
		void HandleInput();
		void Update(float delta);
		void Draw(float delta);

	private:
		game_data_ref data;
		sf::Sprite background;
		sf::Sprite play_button;
		sf::Sprite play_button_outer;
		sf::Sprite title;
	};
}
