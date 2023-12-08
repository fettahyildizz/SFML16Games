#include "asteroids/explosions.hpp"


Explosion::Explosion(const ExplosionType &explosion_type) {
  if (explosion_type == ExplosionType::BIG) {
    texture_.loadFromFile(
        "/home/delivers6/Asteroids/resources/Asteroids/images/"
        "explosions/type_C.png");

  } else if (explosion_type == ExplosionType::NORMAL) {
    texture_.loadFromFile(
        "/home/delivers6/Asteroids/resources/Asteroids/images/"
        "explosions/type_B.png");

  } else if (explosion_type == ExplosionType::SMALL) {
    texture_.loadFromFile(
        "/home/delivers6/Asteroids/resources/Asteroids/images/"
        "explosions/type_A.png");

  } else {
    std::runtime_error("Texture file for explosion can not found.");
  }
  sprite_ = std::make_shared<sf::Sprite>(texture_);
  sprite_->setTextureRect(
      sf::IntRect(0, 0, texture_.getSize().y, texture_.getSize().y));
  frame_count_ = texture_.getSize().x / texture_.getSize().y;
  sprite_->setOrigin((int)(texture_.getSize().y / 2),
                     (int)(texture_.getSize().y / 2) * (0.75));
}

void Explosion::explode(const int &x, const int &y) {
  sprite_->setPosition(x, y);
  if (!ongoing_)
    ongoing_ = true;
}
void Explosion::call() {
  sprite_->setTextureRect(sf::IntRect((int)frame_ * texture_.getSize().y, 0,
                                      texture_.getSize().y,
                                      texture_.getSize().y));
  frame_ += anim_speed_;
  if (frame_ > frame_count_) {
    frame_ -= frame_count_;
    ongoing_ = false;
  }
}

const sf::Sprite &Explosion::getSprite() const { return *sprite_; }

const bool Explosion::get_ongoing() const { return ongoing_; }
