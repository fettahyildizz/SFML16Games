#include "asteroids/spaceship.hpp"

using namespace sf;

Spaceship::Spaceship() {
  explosion_ = std::make_shared<Explosion>(ExplosionType::BIG);
  spaceship_texture.loadFromFile(
      "/home/delivers6/Asteroids/resources/Asteroids/images/spaceship.png");
  sprite_ = std::make_shared<Sprite>(spaceship_texture);
  sprite_->setTextureRect(IntRect(40, 0, 40, 40));
  sprite_->setOrigin(20, 20);
}

void Spaceship::explode() { explosion_->explode(position_.x_, position_.y_); }


void Spaceship::check_collisions()
{
  if(explosion_->get_ongoing())
  {
    explosion_->call();
  }
}

void Spaceship::move() {
  if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
    position_.angle_ += ROTATION_SPEED;
  } else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
    position_.angle_ -= ROTATION_SPEED;
  }

  if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
    thrust = true;
  } else {
    thrust = false;
  }

  float angle_diff = position_.angle_ - angle_delta;
  if (angle_diff < 0) {
    angle_delta += std::min((angle_diff / 20), float(-0.01));
  } else {
    angle_delta += std::max(std::abs((angle_diff / 20)), float(0.01));
  }

  if (thrust && speed < MAX_SPEED) {
    speed += 0.5;
  }

  if (position_.angle_ == std::ceil((int)angle_delta)) {
    position_.angle_ = position_.angle_ % 360;
    angle_delta = position_.angle_;
  }
  speed *= 0.95;

  position_.x_ += speed * std::sin((180 - angle_delta) * deg2Rad);
  position_.y_ += speed * std::cos((180 - angle_delta) * deg2Rad);

  sprite_->setRotation(position_.angle_);
  sprite_->setPosition(position_.x_, position_.y_);
}

const Sprite &Spaceship::get_sprite() const { return *sprite_; }

const sf::Sprite &Spaceship::get_explosion_sprite() const {
  return explosion_->getSprite();
}

void Spaceship::setPosition(const float &x, const float &y) {
  position_.x_ = x;
  position_.y_ = y;
  sprite_->setPosition(x, y);
}

void Spaceship::set_position(const Position<> &pos) {
  position_.x_ = pos.x_;
  position_.y_ = pos.y_;
  sprite_->setPosition(pos.x_, pos.y_);
}