#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <memory>
#include <queue>

class MusicManager {
    std::map<const std::string, std::deque<sf::Sound>> m_sounds;
    std::map<const std::string, std::shared_ptr<sf::SoundBuffer>> m_sounds_buffers;
    std::map<const std::string, std::shared_ptr<sf::Music>> m_music;
public:
    static MusicManager& instance();
    void play_sound(const std::string name);
    void play_music(const std::string name);
    void stop_music(const std::string name);
    void change_master_volume(float offset);
    void change_music_volume(float offset);
    void change_sound_volume(float offset);
    float get_master_volume();
    float get_music_volume();
    float get_sound_volume();
};