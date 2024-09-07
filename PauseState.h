#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace System {
	class PauseState : public State {
	public:
		PauseState(game_data_ref _data);

		void Init();
		void HandleInput();
		void Update(float delta);
		void Draw(float delta);

	private:
		game_data_ref data;
		sf::Sprite background;
		sf::Sprite resume_button;
		sf::Sprite home_button;

	};
}
