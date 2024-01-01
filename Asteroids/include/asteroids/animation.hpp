#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include <random>

static bool game_on = true;
static constexpr float deg2Rad = 3.14159 / 180;
static constexpr int W = 1200;
static constexpr int H = 800;
static constexpr int FRAME_LIMIT = 60;
static constexpr int BULLET_HEAT_THRESHOLD = 400;
static double game_speed = 1;
static double increment = 0.01;

static sf::Texture big_explosion_texture, normal_explosion_texture,
    small_explosion_texture;


enum EXPLOSION_TYPE { SMALL_EXPLOSION, NORMAL_EXPLOSION, BIG_EXPLOSION };

enum ROCK_TYPE { BIG_ROCK, SMALL_ROCK };

struct Position {
  float x_, y_;
  int angle_;
  Position() {
    x_ = 0;
    y_ = 0;
    angle_ = 0;
  }
  Position(const float &x, const float &y) {
    x_ = x;
    y_ = y;
  }
  Position(const float &x, const float &y, const float &angle) {
    x_ = x;
    y_ = y;
    angle_ = angle;
  }
};

class Animation {
protected:
  const bool is_repeatable_;
  std::vector<sf::IntRect> frames_;
  std::shared_ptr<sf::Sprite> sprite_;
  std::shared_ptr<Position> position_;
  const float frame_x_, frame_y_, frame_w_, frame_h_;
  float speed_ = 0.4, iterator_ = 0, frame_ = 0;
  int frame_count_;
  bool is_ongoing_ = false;

public:
  Animation(const sf::Texture &texture, const float &frame_x,
            const float &frame_y, const float &x, const float &y,
            const float &w, const float &h, const bool &is_repeatable = true);

  Animation(const sf::Texture &texture, const float &frame_x,
            const float &frame_y, const float &x, const float &y,
            const float &w, const float &h, const float &angle,
            const bool &is_repeatable = true);

  virtual void update(sf::RenderWindow &window);

  void trigger();

  void move(const float &x, const float &y);
  std::shared_ptr<sf::Sprite> get_sprite();
  std::shared_ptr<Position> get_position();
  void set_speed(const float &speed);
  const bool get_ongoing() const;
};

#endif