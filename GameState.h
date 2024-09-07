#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "MinMax.h"

namespace System {
	class GameState : public State {
	public:
		GameState(game_data_ref _data);

		void Init();
		void HandleInput();
		void Update(float delta);
		void Draw(float delta);

	private:
		void init_grid_pieces();
		void check_n_place_piece();
		void player_win_check(int turn);
		void check_match(int x1, int y1, int x2, int y2, int x3, int y3, int piece_check);

		game_data_ref data;
		sf::Sprite background;
		sf::Sprite pause_button;
		sf::Sprite grid_sprite;
		sf::Sprite grid_pieces[3][3];

		int grid_arr[3][3];
		int turn, game_state;

		MinMax* AI;
		sf::Clock clock;
	};
}
