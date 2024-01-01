#include "asteroids/rock.hpp"
#include <memory>

Rock::Rock(const float &x, const float &y, const float &angle, const float &w,
           const float &h, const ROCK_TYPE &rock_type) {
  name_ = "rock";
  if (rock_type == ROCK_TYPE::SMALL_ROCK) {
    texture_.loadFromFile(
        "/home/delivers6/SFML16Games/Asteroids/resources/Asteroids/"
        "images/rock_small.png");
  } else if (rock_type == ROCK_TYPE::BIG_ROCK) {
    texture_.loadFromFile("/home/delivers6/SFML16Games/Asteroids/resources/"
                          "Asteroids/images/rock.png");
  }
  position_.x_ = x;
  position_.y_ = y;
  position_.angle_ = angle;

  dx_ = (rand() % 8) - 4;
  if (dx_ > 0)
  {
    dx_ = std::max(static_cast<double>(dx_), 0.75);
  }
  else 
  {
    dx_ = std::min(static_cast<double>(dx_), -0.75);
  }

  dy_ = (rand() % 8) - 4;
  if (dy_ > 0)
  {
    dy_ = std::max(static_cast<double>(dy_), 0.75);
  }
  else 
  {
    dy_ = std::min(static_cast<double>(dy_), -0.75);
  }
  animation_ =
      std::make_shared<Animation>(texture_, 0, 0, x, y, texture_.getSize().y,
                                  texture_.getSize().y, angle);
}

Rock::Rock(const float &x, const float &y, const float &angle, const float &w,
           const float &h, const ROCK_TYPE &rock_type, const float& game_speed) {
  name_ = "rock";
  if (rock_type == ROCK_TYPE::SMALL_ROCK) {
    texture_.loadFromFile(
        "/home/delivers6/SFML16Games/Asteroids/resources/Asteroids/"
        "images/rock_small.png");
  } else if (rock_type == ROCK_TYPE::BIG_ROCK) {
    texture_.loadFromFile("/home/delivers6/SFML16Games/Asteroids/resources/"
                          "Asteroids/images/rock.png");
  }
  position_.x_ = x;
  position_.y_ = y;
  position_.angle_ = angle;

  dx_ = (rand() % 8) - 4;
  if (dx_ > 0)
  {
    dx_ = std::max(static_cast<double>(dx_), 0.75);
    dy_ *= std::min((pow(game_speed,0.18)), max_rock_speed_constant);
  }
  else 
  {
    dx_ = std::min(static_cast<double>(dx_), -0.75);
    dy_ *= std::min((pow(game_speed,0.18)), max_rock_speed_constant);
  }

  dy_ = (rand() % 8) - 4;
  if (dy_ > 0)
  {
    dy_ = std::max(static_cast<double>(dy_), 0.75);
    dy_ *= std::min((pow(game_speed,0.18)), max_rock_speed_constant);
  }
  else 
  {
    dy_ = std::min(static_cast<double>(dy_), -0.75);
    dy_ *= std::min((pow(game_speed,0.18)), max_rock_speed_constant);
  }

  animation_ =
      std::make_shared<Animation>(texture_, 0, 0, x, y, texture_.getSize().y,
                                  texture_.getSize().y, angle);
}

void Rock::update(sf::RenderWindow &window) 
{ 
  move();
  animation_->update(window); 
  }

void Rock::move() {

  position_.x_ += dx_;
  position_.y_ += dy_;
  if (position_.x_ < 0) {
    position_.x_ = W;
  } else if (position_.x_ > W) {
    position_.x_ = 0;
  }

  if (position_.y_ < 0) {
    position_.y_ = H;
  }
  if (position_.y_ > H) {
    position_.y_ = 0;
  }

  animation_->move(position_.x_, position_.y_);
}


void Rock::set_animation_speed(const float &speed) {
  animation_->set_speed(speed);
}
const bool Rock::get_life() const { return life_; }
sf::Sprite &Rock::get_sprite() { return *animation_->get_sprite(); }

void create_random_rock(std::vector<Object *>& object_list)
{
  Rock *rock = new Rock(W + (rand() % static_cast<int>(2 * W - W + 1)),
                            H + (rand() % static_cast<int>(2 * H - H + 1)), rand() % 360,
                            25, 25, ROCK_TYPE::BIG_ROCK, increment);
      rock->set_animation_speed(0.2);
      object_list.push_back(rock);
}