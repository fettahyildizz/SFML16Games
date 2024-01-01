#include "asteroids/spaceship.hpp"
#include "asteroids/animation.hpp"
#include <SFML/Graphics/Sprite.hpp>

using namespace sf;

Spaceship::Spaceship(const int &x, const int &y) {
  name_ = "spaceship";
  texture_.loadFromFile("/home/delivers6/SFML16Games/Asteroids/resources/"
                        "Asteroids/images/spaceship.png");
  texture_.setSmooth(true);
  sprite_ = std::make_shared<Sprite>();
  sprite_->setTexture(texture_);
  sprite_->setTextureRect(IntRect(40, 0, 40, 40));
  sprite_->setOrigin(20, 20);
  sprite_->setPosition(x, y);
  sprite_->setRotation(90 * deg2Rad);

  position_.x_ = x;
  position_.y_ = y;
  position_.angle_ = 90;

  angle_delta_ = position_.angle_;
}

void Spaceship::move() {

  if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
    position_.angle_ += ROTATION_SPEED;

  } else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
    position_.angle_ -= ROTATION_SPEED;
  }

  if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
    thrust_ = true;
  } else {
    thrust_ = false;
  }

  float angle_diff = position_.angle_ - angle_delta_;
  if (angle_diff < 0) {
    angle_delta_ += std::min((angle_diff / 20), float(-0.01));
  } else {
    angle_delta_ += std::max(std::abs((angle_diff / 20)), float(0.01));
  }

  if (thrust_ && speed_ < MAX_SPEED) {
    speed_ += 0.5;
  }

  if (position_.angle_ == std::ceil((int)angle_delta_)) {
    position_.angle_ = position_.angle_ % 360;
    angle_delta_ = position_.angle_;
  }
  speed_ *= 0.95;

  position_.x_ += speed_ * std::sin((180 - angle_delta_) * deg2Rad);
  position_.y_ += speed_ * std::cos((180 - angle_delta_) * deg2Rad);

  if (position_.x_ > W)
    position_.x_ = 0;
  else if (position_.x_ < 0)
    position_.x_ = W;
  if (position_.y_ > H)
    position_.y_ = 0;
  else if (position_.y_ < 0)
    position_.y_ = H;

  sprite_->setRotation(position_.angle_);
  sprite_->setPosition(position_.x_, position_.y_);
}

void Spaceship::set_position(const float &x, const float &y) {
  position_.x_ = x;
  position_.y_ = y;
  sprite_->setPosition(x, y);
}

void Spaceship::set_position(const Position &pos) {
  position_.x_ = pos.x_;
  position_.y_ = pos.y_;
  sprite_->setPosition(pos.x_, pos.y_);
}

const Position &Spaceship::get_position() const { return this->position_; }

sf::Sprite &Spaceship::get_sprite() { return *sprite_; }

void Spaceship::update(sf::RenderWindow &window) { window.draw(*sprite_); }
