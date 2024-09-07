#include "GameState.h"
#include "Definitions.h"
#include "PauseState.h"
#include "GameOverState.h"

#include <sstream>
#include <iostream>

namespace System {
	GameState::GameState(game_data_ref _data) : data(_data) {}

	void GameState::Init() {
		game_state = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->AI = new MinMax(turn, this->data);

		this->data->assets.load_texture("Pause Button", PAUSE_BUTTON_PATH);
		this->data->assets.load_texture("Grid Sprite", GRID_SPRITE_PATH);
		this->data->assets.load_texture("X Piece", X_PIECE_PATH);
		this->data->assets.load_texture("O Piece", O_PIECE_PATH);
		this->data->assets.load_texture("X Winning Piece", X_WINNING_PIECE_PATH);
		this->data->assets.load_texture("O Winning Piece", O_WINNING_PIECE_PATH);

		background.setTexture(this->data->assets.get_texture("Background"));
		pause_button.setTexture(this->data->assets.get_texture("Pause Button"));
		grid_sprite.setTexture(this->data->assets.get_texture("Grid Sprite"));

		pause_button.setPosition(this->data->window.getSize().x - pause_button.getLocalBounds().width, pause_button.getPosition().y);
		grid_sprite.setPosition((SCREEN_WIDTH / 2) - (grid_sprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (grid_sprite.getGlobalBounds().height / 2));

		init_grid_pieces();

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				grid_arr[i][j] = EMPTY_PIECE;
			}
		}
	}

	void GameState::HandleInput() {
		sf::Event ev;

		while (this->data->window.pollEvent(ev)) {
			if (sf::Event::Closed == ev.type) {
				this->data->window.close();
			}

			if (this->data->inputs.is_sprite_clicked(this->pause_button, sf::Mouse::Left, this->data->window)) {
				this->data->machine.add_state(state_ref(new PauseState(data)), false);
			}
			else if (this->data->inputs.is_sprite_clicked(this->grid_sprite, sf::Mouse::Left, this->data->window)){
				if (STATE_PLAYING == game_state) {
					this->check_n_place_piece();
				}
			}
		}
	}

	void GameState::Update(float delta) {
		if (STATE_DRAW == game_state || STATE_LOSE == game_state || STATE_WON == game_state) {
			if (this->clock.getElapsedTime().asSeconds() > TIME_PREV_GAME_OVER) {
				this->data->machine.add_state(state_ref(new GameOverState(data)), true);
			}
		}
	}

	void GameState::Draw(float delta) {
		this->data->window.clear(sf::Color::Red);

		this->data->window.draw(this->background);
		this->data->window.draw(this->pause_button);
		this->data->window.draw(this->grid_sprite);


		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->data->window.draw(this->grid_pieces[i][j]);
			}
		}

		this->data->window.display();

	}

	void GameState::init_grid_pieces() {
		sf::Vector2u temp_sprite_size = this->data->assets.get_texture("X Piece").getSize();

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				grid_pieces[i][j].setTexture(this->data->assets.get_texture("X Piece"));
				grid_pieces[i][j].setPosition(grid_sprite.getPosition().x + (temp_sprite_size.x * i) - 7, grid_sprite.getPosition().y +
					(temp_sprite_size.y * j) - 7);
				grid_pieces[i][j].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void GameState::check_n_place_piece() {
		sf::Vector2i touch_point = this->data->inputs.get_mouse_position(this->data->window);
		sf::FloatRect grid_size = grid_sprite.getGlobalBounds();

		sf::Vector2f gap_outside_grid = sf::Vector2f((SCREEN_WIDTH - grid_size.width)/2, (SCREEN_HEIGHT - grid_size.height) / 2);
		sf::Vector2f grid_local_touch_position = sf::Vector2f(touch_point.x - gap_outside_grid.x, touch_point.y - gap_outside_grid.y);
		sf::Vector2f grid_section_size = sf::Vector2f(grid_size.width / 3, grid_size.height / 3);

		int column, row;

		// Column adjustments
		if (grid_local_touch_position.x < grid_section_size.x) {
			column = 1;
		}
		else if (grid_local_touch_position.x < grid_section_size.x * 2) {
			column = 2;
		}
		else if (grid_local_touch_position.x < grid_size.width) {
			column = 3;
		}
		// Rows
		if (grid_local_touch_position.y < grid_section_size.y) {
			row = 1;
		}
		else if (grid_local_touch_position.y < grid_section_size.y * 2) {
			row = 2;
		}
		else if (grid_local_touch_position.y < grid_size.height) {
			row = 3;
		}

		if (grid_arr[column - 1][row - 1] == EMPTY_PIECE) {
			grid_arr[column - 1][row - 1] = turn;
			if (PLAYER_PIECE == turn) {
				grid_pieces[column - 1][row - 1].setTexture(this->data->assets.get_texture("X Piece"));
				this->player_win_check(turn);
			}
			grid_pieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void GameState::player_win_check(int turn) {
		check_match(0, 0, 1, 0, 2, 0, turn);
		check_match(0, 1, 1, 1, 2, 1, turn);
		check_match(0, 2, 1, 2, 2, 2, turn);
		check_match(0, 0, 0, 1, 0, 2, turn);
		check_match(1, 0, 1, 1, 1, 2, turn);
		check_match(2, 0, 2, 1, 2, 2, turn);
		check_match(0, 0, 1, 1, 2, 2, turn);
		check_match(0, 2, 1, 1, 2, 0, turn);

		if (STATE_WON != game_state) {
			game_state = STATE_AI_PLAYING;
			AI->place_piece(&grid_arr, grid_pieces, &game_state);

			check_match(0, 0, 1, 0, 2, 0, AI_PIECE);
			check_match(0, 1, 1, 1, 2, 1, AI_PIECE);
			check_match(0, 2, 1, 2, 2, 2, AI_PIECE);
			check_match(0, 0, 0, 1, 0, 2, AI_PIECE);
			check_match(1, 0, 1, 1, 1, 2, AI_PIECE);
			check_match(2, 0, 2, 1, 2, 2, AI_PIECE);
			check_match(0, 0, 1, 1, 2, 2, AI_PIECE);
			check_match(0, 2, 1, 1, 2, 0, AI_PIECE);
		}
		int empty_num = 9;

		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if (EMPTY_PIECE != grid_arr[x][y]) {
					empty_num--;
				}
			}
		}

		if (empty_num == 0 && (STATE_WON != game_state) && (STATE_LOSE != game_state)) {
			game_state = STATE_DRAW;
		}

		if (STATE_DRAW == game_state || STATE_LOSE == game_state || STATE_WON == game_state) {
			// GAME OVER
			this->clock.restart();
		}
	}
	void GameState::check_match(int x1, int y1, int x2, int y2, int x3, int y3, int piece_check) {
		if (STATE_LOSE != game_state && STATE_WON != game_state && STATE_DRAW != game_state) {
			if (piece_check == grid_arr[x1][y1] && piece_check == grid_arr[x2][y2] && piece_check == grid_arr[x3][y3]) {
				std::string winning_piece_string;
				if (O_PIECE == piece_check) {
					winning_piece_string = "O Winning Piece";
				}
				else {
					winning_piece_string = "X Winning Piece";
				}
				grid_pieces[x1][y1].setTexture(this->data->assets.get_texture(winning_piece_string));
				grid_pieces[x2][y2].setTexture(this->data->assets.get_texture(winning_piece_string));
				grid_pieces[x3][y3].setTexture(this->data->assets.get_texture(winning_piece_string));

				if (PLAYER_PIECE == piece_check) {
					game_state = STATE_WON;
				}
				else {
					game_state = STATE_LOSE;
				}
			}
		}
	}
}


