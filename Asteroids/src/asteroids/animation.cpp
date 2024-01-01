#include "asteroids/animation.hpp"

Animation::Animation(const sf::Texture &texture, const float &frame_x,
                     const float &frame_y, const float &x, const float &y,
                     const float &w, const float &h, const bool &is_repeatable)
    : frame_x_(frame_x), frame_y_(frame_y), frame_w_(w), frame_h_(h),
      is_repeatable_(is_repeatable) {
  frame_count_ = texture.getSize().x / texture.getSize().y;
  for (int i = 0; i < frame_count_; i++) {
    frames_.push_back(sf::IntRect(frame_x + i * w, frame_y, w, h));
  }
  sprite_ = std::make_shared<sf::Sprite>();
  sprite_->setTexture(texture);
  sprite_->setOrigin(w / 2, h / 2);
  sprite_->setTextureRect(frames_[0]);
  sprite_->setPosition(x, y);
  position_ = std::make_shared<Position>(x, y);
}

Animation::Animation(const sf::Texture &texture, const float &frame_x,
                     const float &frame_y, const float &x, const float &y,
                     const float &w, const float &h, const float &angle,
                     const bool &is_repeatable)
    : frame_x_(frame_x), frame_y_(frame_y), frame_w_(w), frame_h_(h),
      is_repeatable_(is_repeatable) {

  frame_count_ = texture.getSize().x / texture.getSize().y;
  for (int i = 0; i < frame_count_; i++) {
    frames_.push_back(sf::IntRect(frame_x + i * w, frame_y, w, h));
  }
  sprite_ = std::make_shared<sf::Sprite>();
  sprite_->setTexture(texture);
  sprite_->setOrigin((float)w / 2, (float)h / 2);
  sprite_->setTextureRect(frames_[0]);
  sprite_->setPosition(x, y);
  sprite_->setRotation(angle);
  position_ = std::make_shared<Position>(x, y, angle);
}

void Animation::update(sf::RenderWindow &window) {
  if (is_ongoing_ || is_repeatable_) {
    frame_ += speed_;
    if (frame_ >= frame_count_) {
      frame_ = 0;
      is_ongoing_ = false;
    }
    sprite_->setPosition(position_->x_, position_->y_);
    sprite_->setTextureRect(frames_[(int)frame_]);
  }
  if (is_ongoing_ || is_repeatable_) {
    window.draw(*sprite_);
  }
}

void Animation::trigger() { is_ongoing_ = true; }

void Animation::move(const float &x, const float &y) {
  position_->x_ = x;
  position_->y_ = y;
  sprite_->setPosition(x, y);
}

void Animation::set_speed(const float &speed) { speed_ = speed; }

std::shared_ptr<sf::Sprite> Animation::get_sprite() { return sprite_; }
std::shared_ptr<Position> Animation::get_position() { return position_; }
const bool Animation::get_ongoing() const { return is_ongoing_; }