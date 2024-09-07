#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace System {
	struct GameData {
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager inputs;
	};

	// Shared instances
	// For accessing and manipulation 
	typedef std::shared_ptr<GameData> game_data_ref;

	class Game {
	public: 
		Game(int width, int height, std::string win_title);
	private:
		const float delta = 1.0f / 60.0f;
		sf::Clock clock;

		game_data_ref data = std::make_shared<GameData>();

		void Run();
	};
}