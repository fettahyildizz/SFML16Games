#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "asteroids/animation.hpp"

class Explosion : public Animation {
public:
  Explosion(
      const sf::Texture &texture, const float &frame_x, const float &frame_y,
      const float &x, const float &y, const float &w, const float &h,
      const bool &is_repeatable = false);


  void explode();
  void update(sf::RenderWindow &window);
  
};

void explosion_update(std::vector<Explosion *>& explosion_list, sf::RenderWindow &window);

#endif