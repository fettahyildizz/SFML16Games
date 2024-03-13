#include "chess/chess.hpp"

using namespace sf;

int main() {
  RenderWindow app(VideoMode(W, H), "Chess");
  app.setFramerateLimit(FRAME_LIMIT);
  srand(time(NULL));

  
  while (app.isOpen()) {

    Event event;
    while (app.pollEvent(event)) {
      if (event.type == Event::Closed) {
        app.close();
      }
    }
    app.clear();

    app.draw(quad);
    app.display();
  }
  return 0;
}