#include "asteroids/animation.hpp"
#include "asteroids/object.hpp"
#include <cmath>

using namespace sf;

class Spaceship : public Object {
private:
  static constexpr float MAX_SPEED = 8;
  static constexpr float ROTATION_SPEED = 4;
  static constexpr float rotational_acceleration = 0.05;

  Texture texture_;
  bool thrust_, is_exploding_;
  float angle_delta_;

public:
  Spaceship(const int& x, const int& y);

  void update(sf::RenderWindow& window);
  void move();
    
  void set_position(const float &x, const float &y);
  void set_position(const Position &pos);
  
  const Position& get_position() const;
  
  sf::Sprite& get_sprite();
};
