#ifndef ROCK_HPP
#define ROCK_HPP

#include "asteroids/object.hpp"
#include <memory>

class Rock : public Object {
  sf::Texture texture_;
  std::shared_ptr<Animation> animation_;
  double max_rock_speed_constant = 2.5;

public:
  Rock(const float &x, const float &y, const float &angle, const float &w,
       const float &h, const ROCK_TYPE &rock_type);
  Rock(const float &x, const float &y, const float &angle, const float &w,
       const float &h, const ROCK_TYPE &rock_type, const float &game_speed);
  void update(sf::RenderWindow &window);
  void move();

  void set_animation_speed(const float &speed);
  sf::Sprite &get_sprite();
  const bool get_life() const;
};

void create_random_rock(std::vector<Object *>& object_list);

#endif