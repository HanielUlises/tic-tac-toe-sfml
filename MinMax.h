#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

#include "Game.h"

namespace System {
	class MinMax {
	public:
		MinMax(int _player_piece, game_data_ref _data);

		void place_piece(int (*grid_arr)[3][3],sf::Sprite grid_pieces[3][3], int *game_state);

	private:
		void check_section(int x1, int y1, int x2, int y2, int X, int Y, int piece_check, int(*grid_arr)[3][3], sf::Sprite grid_pieces[3][3]);
		void check_piece_empty(int X, int Y, int(*grid_arr)[3][3], sf::Sprite grid_pieces[3][3]);
		
		int ai_piece;
		int player_piece;

		std::vector<std::array<int, 6>> check_match_vec;

		game_data_ref data;
	};
}