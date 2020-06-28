#pragma once
#include <SFML/Graphics.hpp>

struct Frame {
   sf::IntRect rect;
   double duration; // in seconds
};

class Animation {
private:
   std::vector<Frame> frames;
   double totalLength;
   double progress;

public:
   Animation();
   virtual ~Animation();
   void addFrame(Frame&& frame);
   void update(sf::Sprite& target, double elapsed); 
   double getLength() const { return totalLength; }
   double get_progrees() const { return progress; }
   bool is_done() const;
};