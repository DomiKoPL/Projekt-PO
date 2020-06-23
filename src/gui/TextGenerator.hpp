#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextGenerator {
private:
    inline static sf::Texture m_font;
public:
    static sf::Texture get_text_texture(const std::string text, uint width);
    static void load();
};