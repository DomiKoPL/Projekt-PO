#include "Animation.hpp"

Animation::Animation() { 
    progress = totalLength = 0.0;
}

void Animation::addFrame(Frame&& frame) {
    totalLength += frame.duration; 
    frames.push_back(std::move(frame)); 
}

void Animation::update(sf::Sprite& target, double elapsed) {
    progress += elapsed;
    double p = progress;
    for(size_t i = 0; i < frames.size(); i++) {
        p -= frames[i].duration;  

        // if we have progressed OR if we're on the last frame, apply and stop.
        if (p <= 0.0 || &(frames[i]) == &frames.back())
        {
            target.setTextureRect(frames[i].rect);  
            break; // we found our frame
        }
    }
}

bool Animation::is_done() const {
    return (progress >= totalLength);
}

Animation::~Animation() {
    
}