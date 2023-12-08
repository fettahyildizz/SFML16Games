#include "asteroids/asteroids.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using namespace sf;

static constexpr int W = 1200;
static constexpr int H = 800;
static constexpr int FRAME_LIMIT = 60;

int main() {
  RenderWindow app(sf::VideoMode(W, H), "Asterois!");
  app.setFramerateLimit(FRAME_LIMIT);

  Texture background_texture, spaceship_texture;
  background_texture.loadFromFile(
      "/home/delivers6/Asteroids/resources/Asteroids/images/background.jpg");
  Sprite sBackground(background_texture);

  auto spaceship = std::make_shared<Spaceship>();
  spaceship->setPosition(300, 300);

  std::chrono::duration<double> cycle_time;
  std::chrono::time_point<std::chrono::system_clock> start;
  sf::Text fps_text;
  sf::Font font;
  std::string font_path =
      "/home/delivers6/Asteroids/resources/Asteroids/arial.ttf";
  if (!font.loadFromFile(font_path)) {
    throw std::runtime_error("Can not find font file. Please check " +
                             font_path);
  }

  fps_text.setFont(font);        // font is a sf::Font
  fps_text.setCharacterSize(24); // in pixels, not points!
  fps_text.setFillColor(sf::Color::Red);
  fps_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

  int idx = 0;
  while (app.isOpen()) {
    auto prev_cycle_time_point = start;
    start = std::chrono::high_resolution_clock::now();
    cycle_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        start - prev_cycle_time_point);
    fps_text.setString("FPS: " + std::to_string((int)(1 / cycle_time.count())));

    Event event;
    while (app.pollEvent(event)) {
      if (event.type == Event::Closed) {
        app.close();
      }
    }

    idx++;
    spaceship->move();
    if(idx % 20 == 0)
    {
      spaceship->explode();
      
    }
    spaceship->check_collisions();
    /////draw//////
    app.clear();
    app.draw(sBackground);
    app.draw(spaceship->get_sprite());
    app.draw(spaceship->get_explosion_sprite());      
    app.draw(fps_text);
    app.display();
  }

  return 0;
}