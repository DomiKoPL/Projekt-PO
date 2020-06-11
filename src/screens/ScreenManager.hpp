#pragma once
#include "BaseScreen.hpp"
#include <map>
#include <string>

class ScreenManager {
private:
    inline static BaseScreen* current_screen;
    inline static std::map<const std::string, BaseScreen*> screens;
    inline static bool close_window = false;
public:
    static void draw(sf::RenderWindow& window);
    static void update(sf::RenderWindow& window, float elapsed);
    static void handle_event(sf::RenderWindow& window, sf::Event event);
    static void setup();
    static void clear();
    static void set_screen(const std::string screen);
    static void close();
    
    ScreenManager();
    ~ScreenManager();
};