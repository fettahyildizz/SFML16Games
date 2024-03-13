#include "asteroids/asteroids.hpp"

using namespace sf;

int main() {
  RenderWindow app(sf::VideoMode(W, H), "Asterodis!");
  app.setFramerateLimit(FRAME_LIMIT);
  srand(time(NULL));

  std::vector<Object *> object_list;
  std::vector<Explosion *> explosion_list;
  int bullet_heat = 0;
  int bullet_heat_limit = BULLET_HEAT_THRESHOLD;

  sf::Text fps_text, game_over_text, score_text;
  sf::Font font;
  std::string font_path =
      "/home/delivers6/SFML16Games/Asteroids/resources/Asteroids/arial.ttf";
  if (!font.loadFromFile(font_path)) {
    throw std::runtime_error("Can not find font file. Please check " +
                             font_path);
  }

  big_explosion_texture.loadFromFile(
      "/home/delivers6/SFML16Games/Asteroids/resources/Asteroids/images/"
      "explosions/type_C.png");

  normal_explosion_texture.loadFromFile(
      "/home/delivers6/SFML16Games/Asteroids/resources/Asteroids/images/"
      "explosions/type_B.png");

  small_explosion_texture.loadFromFile(
      "/home/delivers6/SFML16Games/Asteroids/resources/Asteroids/images/"
      "explosions/type_A.png");

  fps_text.setFont(font);        // font is a sf::Font
  fps_text.setCharacterSize(24); // in pixels, not points!
  fps_text.setFillColor(sf::Color::Red);
  fps_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

  game_over_text.setFont(font);        // font is a sf::Font
  game_over_text.setCharacterSize(36); // in pixels, not points!
  game_over_text.setFillColor(sf::Color::Red);
  game_over_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  game_over_text.setPosition(static_cast<int>(W / 2), static_cast<int>(H / 2));
  game_over_text.setString("Game over");

  score_text.setFont(font);        // font is a sf::Font
  score_text.setCharacterSize(24); // in pixels, not points!
  score_text.setFillColor(sf::Color::Green);
  score_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
  score_text.setPosition(W - 160, 60);

  Texture background_texture, spaceship_texture;
  background_texture.loadFromFile("/home/delivers6/SFML16Games/Asteroids/"
                                  "resources/Asteroids/images/background.jpg");
  background_texture.setSmooth(true);
  Sprite sBackground(background_texture);

  Spaceship *spaceship = new Spaceship(500, 500);

  object_list.push_back(spaceship);

  for (int i = 0; i < 5;) {
    Rock *rock = new Rock(W + (rand() % static_cast<int>(2 * W - W + 1)),
                          H + (rand() % static_cast<int>(2 * H - H + 1)), rand() % 360, 25,
                          25, ROCK_TYPE::BIG_ROCK);

    rock->set_animation_speed(0.2);
    object_list.push_back(rock);
    i++;
  }

  for (int i = 0; i < 5;) {
    Rock *rock = new Rock(W + (rand() % static_cast<int>(2 * W - W + 1)),
                          H + (rand() % static_cast<int>(2 * H - H + 1)), rand() % 360, 25,
                          25, ROCK_TYPE::SMALL_ROCK);

    rock->set_animation_speed(0.2);
    object_list.push_back(rock);
    i++;
  }

  std::chrono::duration<double> cycle_time;
  std::chrono::time_point<std::chrono::system_clock> start;

  while (app.isOpen()) {
    auto prev_cycle_time_point = start;
    start = std::chrono::high_resolution_clock::now();
    cycle_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        start - prev_cycle_time_point);
    fps_text.setString("FPS: " + std::to_string(static_cast<int>(1 / cycle_time.count())));


    if (explosion_list.empty() && !game_on) {
      app.close();
    }

    Event event;
    while (app.pollEvent(event)) {
      if (event.type == Event::Closed) {
        app.close();
      }

      if (event.type == Event::KeyPressed && game_on) {
        if ((event.key.code == Keyboard::Space) && (bullet_heat < bullet_heat_limit)) {
          bullet_heat += 10;
          Bullet *b = new Bullet(spaceship->get_position().x_,
                                 spaceship->get_position().y_,
                                 spaceship->get_position().angle_);
          object_list.push_back(b);
        }
      }
    }
    if (game_on) {
      {
        spaceship->move();
      }
    }
    collide_update(object_list, explosion_list);
    life_update(object_list);

    /////draw//////
    app.clear();
    app.draw(sBackground);

    explosion_update(explosion_list, app);

    object_update(object_list, app);

    app.draw(fps_text);
    
    app.draw(score_text);
    if (!game_on) {
      app.draw(game_over_text);
    }
    app.display();

    if ((static_cast<int>(game_speed) % 20 == 0)) {
      create_random_rock(object_list);
    }
    if(game_on)
    {
      game_speed += increment;
      increment += 0.0003;
      if (bullet_heat > bullet_heat_limit)
      {
        bullet_heat_limit = 300;
        bullet_heat -= 2;
      }
      else {
        bullet_heat_limit = BULLET_HEAT_THRESHOLD;
        bullet_heat -= 1;
        bullet_heat = std::max(bullet_heat, 0);
      }
    }
    score_text.setString("Score: " + std::to_string(static_cast<int>(game_speed)));
  }

  return 0;
}