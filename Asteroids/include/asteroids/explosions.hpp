#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <stdexcept>

enum ExplosionType {
  SMALL,
  NORMAL,
  BIG
};

class Explosion {
private:
  sf::Texture texture_;
  std::shared_ptr<sf::Sprite> sprite_;
  float frame_ = 0;
  float anim_speed_ = 1;
  int frame_count_;
  bool ongoing_ = false;

public:
  Explosion(const ExplosionType& explosion_type);
  void call();
  void explode(const int &x, const int &y);
  const bool get_ongoing() const;
  const sf::Sprite& getSprite() const;
};

#endif