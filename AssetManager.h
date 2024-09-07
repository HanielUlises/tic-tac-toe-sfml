#pragma once

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

namespace System {
	class AssetManager {
	public:
		AssetManager(){}
		~AssetManager(){}

		void load_texture(std::string name, std::string file_name);
		sf::Texture& get_texture(std::string name);

		void load_font(std::string name, std::string file_name);
		sf::Font& get_font(std::string name);

	private:
		std::map<std::string, sf::Texture> textures;
		std::map<std::string, sf::Font> fonts;
	};
}
