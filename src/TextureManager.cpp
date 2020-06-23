#include "TextureManager.hpp"


TextureManager& TextureManager::instance() {
    static TextureManager _instance;
    return _instance;
}

sf::Texture& TextureManager::get_texture(const std::string path) {
    if(not m_textures.count(path)) {
        m_textures[path].loadFromFile(path);
    }
    return m_textures[path];
}