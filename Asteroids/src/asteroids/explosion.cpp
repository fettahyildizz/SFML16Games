#include "asteroids/explosion.hpp"

Explosion::Explosion(const sf::Texture &texture, const float &frame_x,
                     const float &frame_y, const float &x, const float &y,
                     const float &w, const float &h, const bool &is_repeatable)
    : Animation(texture, frame_x, frame_y, x, y, w, h, is_repeatable) {
  sprite_->setOrigin((int)(texture.getSize().y / 2),
                     (int)(texture.getSize().y / 2) * (0.75));
  is_ongoing_ = true;
  speed_ = 0.6;
}

void Explosion::explode() { this->trigger(); }

void Explosion::update(sf::RenderWindow &window) {
  if (is_ongoing_) {
    frame_ += speed_;
    if (frame_ >= frame_count_) {
      frame_ = 0;
      is_ongoing_ = false;
    }
    sprite_->setPosition(position_->x_, position_->y_);
    sprite_->setTextureRect(frames_[(int)frame_]);
  }
  if (is_ongoing_) {
    window.draw(*sprite_);
  }
}


void explosion_update(std::vector<Explosion *>& explosion_list, sf::RenderWindow &window) {
  
  for (auto a = explosion_list.begin(); a != explosion_list.end();) {
    Explosion* explosion = *a;
    if(!explosion->get_ongoing())
    {
        explosion_list.erase(a);
        delete explosion;
        continue;
    }
    else
    {
        explosion->update(window);
        a++;
    }
  }
  
}