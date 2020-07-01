#include "MusicManager.hpp"
#include "Settings.hpp"

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

    if(sounds.size() >= 6u) {
        sounds.front().stop();
        sounds.pop_front();
    }

    float master = Settings::get<float>("volume", "master");
    float sound = Settings::get<float>("volume", "sound");

    sounds.push_back(sf::Sound());
    sounds.back().setVolume(master * sound / 100.f);
    sounds.back().setBuffer(*m_sounds_buffers[name]);
    sounds.back().play();
}

void MusicManager::play_music(const std::string name) {
    if(not m_music.count(name)) {
        m_music[name] = std::make_shared<sf::Music>();
        m_music[name]->openFromFile(name);
    }
    
    float master = Settings::get<float>("volume", "master");
    float music = Settings::get<float>("volume", "music");

    m_music[name]->setVolume(master * music / 100.f);
    m_music[name]->play();
    m_music[name]->setLoop(true);
}

void MusicManager::stop_music(const std::string name) {
    if(m_music.count(name)) {
        m_music[name]->stop();
    }
}


void MusicManager::change_master_volume(float offset) {
    float master = Settings::get<float>("volume", "master");
    master = std::max(0.f, std::min(100.f, master + offset));
    Settings::set<float>("volume", "master", master);

    float sound_volume = Settings::get<float>("volume", "sound");
    float music_volume = Settings::get<float>("volume", "music");

    for(auto& [name, sounds] : m_sounds) {
        for(auto& sound : sounds) {
            sound.setVolume(master * sound_volume / 100.f);
        }
    }

    for(auto& [name, music] : m_music) {
        music->setVolume(master * music_volume / 100.f);
    }
}

void MusicManager::change_music_volume(float offset) {
    float music_volume = Settings::get<float>("volume", "music");
    music_volume = std::max(0.f, std::min(100.f, music_volume + offset));
    Settings::set<float>("volume", "music", music_volume);
    float master = Settings::get<float>("volume", "master");

    for(auto& [name, music] : m_music) {
        music->setVolume(master * music_volume / 100.f);
    }
}

void MusicManager::change_sound_volume(float offset) {
    float sound_volume = Settings::get<float>("volume", "sound");
    sound_volume = std::max(0.f, std::min(100.f, sound_volume + offset));
    Settings::set<float>("volume", "sound", sound_volume);
    float master = Settings::get<float>("volume", "master");
    
    for(auto& [name, sounds] : m_sounds) {
        for(auto& sound : sounds) {
            sound.setVolume(master * sound_volume / 100.f);
        }
    }
}

float MusicManager::get_master_volume() {
    return Settings::get<float>("volume", "master");
}

float MusicManager::get_music_volume() {
    return Settings::get<float>("volume", "music");
}

float MusicManager::get_sound_volume() {
    return Settings::get<float>("volume", "sound");
}
