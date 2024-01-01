#ifndef BULLET_HPP
#define BULLET_HPP

#include "asteroids/object.hpp"

class Bullet : public Object {
  sf::Texture texture_;
  

public:
  Bullet(const int &x, const int &y, const int &angle);
  
  void update(sf::RenderWindow &window);
  void move();
  void explode();

  sf::Sprite &get_sprite();
  const bool get_life() const;
};

#endif