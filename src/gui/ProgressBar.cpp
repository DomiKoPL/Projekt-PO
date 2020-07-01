#include "ProgressBar.hpp"
#include "../TextureManager.hpp"

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_box, states);
    target.draw(m_fill, states);
}

void ProgressBar::update(float val) {
    float p = (val - m_min) / m_max;
    float w = 201 * p;
    m_fill.setScale(w / 6.f, 16.f / 14.f);
}

ProgressBar::ProgressBar() : ProgressBar(0.f, 0.f) {

}

ProgressBar::ProgressBar(float min, float max) : m_min{min}, m_max{max} {
    m_box.setTexture(TextureManager::instance().get_texture("Resources/PNG/UI bar/load bar/loadbar.png"));
    auto[w, h] = TextureManager::instance().get_texture("Resources/PNG/UI bar/load bar/loadbar.png").getSize();
    m_box.setOrigin(w / 2.f, h / 2.f);
    m_fill.setTexture(TextureManager::instance().get_texture("Resources/PNG/UI bar/load bar/box.png"));
    m_fill.setPosition(12 - w / 2.f, 8 - h / 2.f);
}

void ProgressBar::set_size(float width, float height) {
    auto[w, h] = TextureManager::instance().get_texture("Resources/PNG/UI bar/load bar/loadbar.png").getSize();
    setScale(width / w, height / h);
}
