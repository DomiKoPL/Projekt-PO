#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureManager {
private:
    std::map<const std::string, sf::Texture> m_textures;
public:
    static TextureManager& instance();
    sf::Texture& get_texture(const std::string path);
    void add_texture(const std::string name, sf::Texture&& texture);
};