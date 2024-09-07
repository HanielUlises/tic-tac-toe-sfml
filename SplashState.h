#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Game.h"
#include "MainMenuState.h"

namespace System {
	class SplashState : public State{
	public: 
		SplashState(game_data_ref _data);
		void Init();
		void HandleInput();
		void Update(float delta);
		void Draw(float delta);

	private:
		game_data_ref data;
		sf::Clock clock;
		sf::Sprite background;
	};
}