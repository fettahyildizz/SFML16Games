#include "asteroids/explosions.hpp"
#include "asteroids/object.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>


using namespace sf;

class Spaceship : public Object<float> {
private:
  static constexpr float MAX_SPEED = 8;
  static constexpr float ROTATION_SPEED = 4;
  float rotational_acceleration = 0.05;
  
  std::shared_ptr<Explosion> explosion_;
  Texture spaceship_texture;
  std::shared_ptr<Sprite> sprite_;
  bool thrust;
  float angle_delta = position_.angle_;
  

public:
  Spaceship();
  const Sprite& get_sprite() const;
  const sf::Sprite& get_explosion_sprite() const;

  void setPosition(const float &x, const float &y);
  void set_position(const Position<>& pos);

  void check_collisions();
  void explode();
  void move();
};