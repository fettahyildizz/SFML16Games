#include "chess/utils.hpp"


void draw_quad(sf::ConvexShape& polygon, const sf::Color& color)
{
    
polygon.setPointCount(4);
polygon.setFillColor(color);
polygon.setPoint(0, sf::Vector2f(700, 500));
polygon.setPoint(1, sf::Vector2f(300, 500));
polygon.setPoint(2, sf::Vector2f(400, 300));
polygon.setPoint(3, sf::Vector2f(600, 300));
polygon.setOutlineColor(sf::Color::Green);
polygon.setOutlineThickness(5);
polygon.setPosition(10, 20);
}