#include "TextGenerator.hpp"
#include "../Log.hpp"
#include "../TextureManager.hpp"
#include <cctype>

sf::Texture TextGenerator::get_text_texture(const std::string text, uint width) {
    uint character_width = 46, character_height = 37;

    sf::RenderTexture texture;
    if(not texture.create(width, width * character_height / character_width)) {
        Log::log(Log::ERROR, "TexGenerator create texture error\n");
    }

    // texture.clear(sf::Color::Red);

    uint width_per_character = width / text.size();
    Log::log(Log::INFO, "{} {}\n", width, width * character_height / character_width);
    Log::log(Log::INFO, "Wid = {}\n", width_per_character);
    sf::Sprite character;
    character.setTexture(TextureManager::instance().get_texture("Resources/Space Shooter - 1/Font46x37.png"));
    character.setScale(1.f * width_per_character / character_width, 1.f * width_per_character / character_width);
    sf::Vector2u pos;

    for(const char& c : text) {
        character.setPosition(sf::Vector2f(pos));
        int x = 0, y = 0;
        if(std::isdigit(c)) {
            x = character_width * (c - '0');
            y = 0;
        } else if(std::isalpha(c)){
            int letter_id = std::tolower(c) - 'a';
            x = character_width * ((7+letter_id)%10);
            y = character_height * ((7+letter_id)/10 + 1);
        } else {
            x = character_width;
            y = character_height;
        }
        
        if(std::tolower(c) == 'm' or std::tolower(c) == 'w') {
            character.setTextureRect(sf::IntRect(x + 3, y, character_width - 5, character_height));
            pos.x += width_per_character - 5;
            std::string x; x += c;
            Log::log(Log::ERROR, "{}\n", x);
        } else if(std::tolower(c) == 'i' or c == ' '){
            character.setTextureRect(sf::IntRect(x + 15, y, character_width - 30, character_height));
            pos.x += width_per_character - 45;
        } else {
            character.setTextureRect(sf::IntRect(x + 9, y, character_width - 18, character_height));
            pos.x += width_per_character - 26;
        }
        texture.draw(character);
        texture.display();

    }
    return texture.getTexture();
}