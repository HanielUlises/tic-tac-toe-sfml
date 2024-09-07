#include "InputManager.h"

namespace System {
	InputManager::InputManager() {
	}

	InputManager::~InputManager() {
	}

    bool InputManager::is_sprite_clicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window) {
        if (sf::Mouse::isButtonPressed(button)) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

            if (object.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos))) {
                return true;
            }
        }
        return false;
    }


	sf::Vector2i InputManager::get_mouse_position(sf::RenderWindow & window) {
		return sf::Mouse::getPosition(window);
	}

}