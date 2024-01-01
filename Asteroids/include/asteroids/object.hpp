#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "asteroids/animation.hpp"
#include "asteroids/explosion.hpp"

class Object {
protected:
  std::string name_;
  bool life_ = 1;
  Position position_;
  std::shared_ptr<sf::Sprite> sprite_;
  float dx_, dy_ = 0;
  float speed_ = 0;

public:
  virtual ~Object() = default;
  virtual sf::Sprite &get_sprite() = 0;
  virtual void update(sf::RenderWindow &window) = 0;
  virtual void move() = 0;

  void die() { life_ = 0; }

  bool isCollide(Object *object) {
    bool ret = false;

    if (get_sprite().getGlobalBounds().intersects(
            object->get_sprite().getGlobalBounds())) {

      ret = true;
    }

    return ret;
  }

  const bool get_life() const { return life_; }
  const std::string get_name() const { return name_; }
  const Position &get_position() const { return position_; }
};

static void collide_update(std::vector<Object *> &object_list,
                           std::vector<Explosion *> &explosion_list) {
  for (auto a = object_list.begin(); a != object_list.end();) {
    Object *obj1 = *a;
    if ((obj1->get_name() != "rock")) {
      a++;
      continue;
    }

    for (auto b = object_list.begin(); b != object_list.end();) {
      Object *obj2 = *b;
      if ((obj2->get_name() == "rock")) {
        b++;
        continue;
      }
      if (obj1->isCollide(obj2)) {
        if (obj2->get_name() == "bullet") {
          Explosion *explosion = new Explosion(
              normal_explosion_texture, 0, 0, obj1->get_position().x_,
              obj1->get_position().y_, normal_explosion_texture.getSize().y,
              normal_explosion_texture.getSize().y);
          explosion_list.push_back(explosion);
          obj1->die();
          obj2->die();        
          b++;
        } else if (obj2->get_name() == "spaceship") {
          Explosion *explosion = new Explosion(
              big_explosion_texture, 0, 0, obj2->get_position().x_,
              obj2->get_position().y_, big_explosion_texture.getSize().y,
              big_explosion_texture.getSize().y);
          explosion_list.push_back(explosion);
          obj1->die();
          obj2->die();
          game_on = false;
          b++;
        } else {
          b++;
        }
      } else {
        b++;
      }
    }
    a++;
  }
}

static void life_update(std::vector<Object *> &object_list) {
  for (auto a = object_list.begin(); a != object_list.end();) {
    Object *object = *a;
    if (!object->get_life()) {
      object_list.erase(a);
      delete object;
    } else {
      a++;
    }
  }
}

static void object_update(std::vector<Object *> &object_list,
                          sf::RenderWindow &window) {

  
  for (auto a = object_list.begin(); a != object_list.end();) {
    Object *object = *a;
    object->update(window);
    a++;
  }

}

#endif