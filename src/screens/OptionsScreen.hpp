#pragma once
#include "BaseScreen.hpp"
#include "../gui/Button.hpp"
#include "../gui/ProgressBar.hpp"

class OptionsScreen : public BaseScreen {
private:
    sf::Sprite m_master_volume;
    Button m_master_volume_add, m_master_volume_substract;
    ProgressBar m_master_bar;

    sf::Sprite m_music_volume;
    Button m_music_volume_add, m_music_volume_substract;
    ProgressBar m_music_bar;

    sf::Sprite m_sound_volume;
    Button m_sound_volume_add, m_sound_volume_substract;
    ProgressBar m_sound_bar;

    Button m_menu;

    std::vector<std::reference_wrapper<Button>> m_buttons;
    std::vector<std::reference_wrapper<ProgressBar>> m_bars;
public:
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, float elapsed);
    void handle_event(sf::RenderWindow& window, sf::Event event);
    void reset();
    OptionsScreen();
    ~OptionsScreen();
};