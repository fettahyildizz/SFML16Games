#include "asteroids/bullet.hpp"
#include "asteroids/animation.hpp"
#include <memory>

Bullet::Bullet(const int &x, const int &y, const int &angle) {
    name_ = "bullet";
  texture_.loadFromFile("/home/delivers6/SFML16Games/Asteroids/resources/"
                        "Asteroids/images/fire_blue.png");
  sprite_ = std::make_shared<sf::Sprite>();
  sprite_->setTexture(texture_);
  sprite_->setTextureRect(
      sf::IntRect(0, 0, texture_.getSize().y / 2, texture_.getSize().y));
  sprite_->setOrigin((float)texture_.getSize().y / 4, texture_.getSize().y);
  sprite_->setRotation(angle);
  sprite_->setPosition(x, y);

  position_.x_ = x;
  position_.y_ = y;
  position_.angle_ = angle;

  speed_ = 6;
}
void Bullet::update(sf::RenderWindow &window) {
  if (position_.x_ > W || position_.x_ < 0 || position_.y_ < 0 ||
      position_.y_ > H) {
    life_ = 0;
  } else {
    position_.x_ += speed_ * std::sin((180 - position_.angle_) * deg2Rad);
    position_.y_ += speed_ * std::cos((180 - position_.angle_) * deg2Rad);
    sprite_->setPosition(position_.x_, position_.y_);
  }
    window.draw(*sprite_);
}

sf::Sprite &Bullet::get_sprite() { return *sprite_; }

void Bullet::move() {
  if (position_.x_ > W || position_.x_ < 0 || position_.y_ < 0 ||
      position_.y_ > H) {
    life_ = 0;
  } else {
    position_.x_ += speed_ * std::sin((180 - position_.angle_) * deg2Rad);
    position_.y_ += speed_ * std::cos((180 - position_.angle_) * deg2Rad);
    sprite_->setPosition(position_.x_, position_.y_);
  }
}

void Bullet::explode(){};

const bool Bullet::get_life() const { return life_; }
