#include "MusicManager.hpp"


MusicManager& MusicManager::instance() {
    static MusicManager music_manager;
    return music_manager;
}

void MusicManager::play_sound(const std::string name) {
    if(not m_sounds_buffers.count(name)) {
        m_sounds_buffers[name] = std::make_shared<sf::SoundBuffer>();
        m_sounds_buffers[name]->loadFromFile(name);
    }  

    auto& sounds = m_sounds[name];
    while(sounds.size() > 0u and sounds.front().getStatus() == sf::Sound::Stopped) {
        sounds.pop_front();
    }

    if(sounds.size() < 6u) {
        sounds.push_back(sf::Sound());
        sounds.back().setBuffer(*m_sounds_buffers[name]);
        sounds.back().play();
    }
}

void MusicManager::play_music(const std::string name) {
    if(not m_music.count(name)) {
        m_music[name] = std::make_shared<sf::Music>();
        m_music[name]->openFromFile(name);
    }
    
    m_music[name]->setVolume(15);
    m_music[name]->play();
    m_music[name]->setLoop(true);
}

void MusicManager::stop_music(const std::string name) {
    if(m_music.count(name)) {
        m_music[name]->stop();
    }
}