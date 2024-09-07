#include "MinMax.h"
#include "Definitions.h"

#include <iostream>

namespace System {
	MinMax::MinMax(int _player_piece, game_data_ref _data) : 
		player_piece(_player_piece), data(_data) {
		if (O_PIECE == player_piece) {
			ai_piece = X_PIECE;
		}
		else {
			ai_piece = O_PIECE;
		}

		check_match_vec.push_back({ 0, 2, 1, 2, 2, 2 });
		check_match_vec.push_back({ 0, 2, 0, 1, 0, 0 });
		check_match_vec.push_back({ 0, 2, 1, 1, 2, 0 });
		check_match_vec.push_back({ 2, 2, 1, 2, 0, 2 });
		check_match_vec.push_back({ 2, 2, 2, 1, 2, 0 });
		check_match_vec.push_back({ 2, 2, 1, 1, 0, 0 });
		check_match_vec.push_back({ 0, 0, 0, 1, 0, 2 });
		check_match_vec.push_back({ 0, 0, 1, 0, 2, 0 });
		check_match_vec.push_back({ 0, 0, 1, 1, 2, 2 });
		check_match_vec.push_back({ 2, 0, 2, 1, 2, 2 });
		check_match_vec.push_back({ 2, 0, 1, 0, 0, 0 });
		check_match_vec.push_back({ 2, 0, 1, 1, 0, 2 });
		check_match_vec.push_back({ 0, 1, 1, 1, 2, 1 });
		check_match_vec.push_back({ 1, 2, 1, 1, 1, 0 });
		check_match_vec.push_back({ 2, 1, 1, 1, 0, 1 });
		check_match_vec.push_back({ 0, 1, 2, 1, 1, 1 });
		check_match_vec.push_back({ 1, 2, 1, 0, 1, 1 });
		check_match_vec.push_back({ 0, 2, 2, 0, 1, 1 });
		check_match_vec.push_back({ 2, 2, 0, 0, 1, 1 });
		check_match_vec.push_back({ 0, 2, 2, 2, 1, 2 });
		check_match_vec.push_back({ 0, 0, 2, 0, 1, 0 });
		check_match_vec.push_back({ 0, 2, 0, 0, 0, 1 });
		check_match_vec.push_back({ 2, 2, 2, 0, 2, 1 });
	}

	void MinMax::place_piece(int(*grid_arr)[3][3], sf::Sprite grid_pieces[3][3], int* game_state) {
		try {
			for (int i = 0; i < check_match_vec.size(); i++) {
				check_section(check_match_vec[i][0], check_match_vec[i][1], check_match_vec[i][2], check_match_vec[i][3], check_match_vec[i][4], check_match_vec[i][5], AI_PIECE, grid_arr, grid_pieces);
			}

			for (int i = 0; i < check_match_vec.size(); i++) {
				check_section(check_match_vec[i][0], check_match_vec[i][1], check_match_vec[i][2], check_match_vec[i][3], check_match_vec[i][4], check_match_vec[i][5], PLAYER_PIECE, grid_arr, grid_pieces);
			}

			// Center is empty
			// Check other places
			check_piece_empty(1, 1, grid_arr, grid_pieces);

			check_piece_empty(0, 2, grid_arr, grid_pieces);
			check_piece_empty(2, 2, grid_arr, grid_pieces);
			check_piece_empty(0, 0, grid_arr, grid_pieces);
			check_piece_empty(2, 0, grid_arr, grid_pieces);

			check_piece_empty(1, 2, grid_arr, grid_pieces);
			check_piece_empty(0, 1, grid_arr, grid_pieces);
			check_piece_empty(2, 1, grid_arr, grid_pieces);
			check_piece_empty(1, 0, grid_arr, grid_pieces);


		}
		catch (int error){

		}

		*game_state = STATE_PLAYING;
	}

	void MinMax::check_section(int x1, int y1, int x2, int y2, int X, int Y, int piece_check, int(*grid_arr)[3][3], sf::Sprite grid_pieces[3][3]) {
		if ((*grid_arr)[x1][y1] == piece_check && (*grid_arr)[x2][y2] == piece_check) {
			if ((*grid_arr)[X][Y] = EMPTY_PIECE) {
				(*grid_arr)[X][Y] = AI_PIECE;
				grid_pieces[X][Y].setTexture(this->data->assets.get_texture("O Piece"));

				grid_pieces[X][Y].setColor(sf::Color(255, 255, 255, 255));

				throw - 1;
			}
		}
	}

	void MinMax::check_piece_empty(int X, int Y, int(*grid_arr)[3][3], sf::Sprite grid_pieces[3][3]) {
		if ((*grid_arr)[X][Y] == EMPTY_PIECE) {
			(*grid_arr)[X][Y] = AI_PIECE;
			grid_pieces[X][Y].setTexture(this->data->assets.get_texture("O Piece"));
			grid_pieces[X][Y].setColor(sf::Color(255, 255, 255, 255));

			throw - 2;
		}
	}
}

