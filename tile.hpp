#pragma once

#include <SFML/Graphics.hpp>

class Tile{
private:
    sf::RectangleShape self;
    sf::Text idText;
    static int nextId;
    static bool FontSet;
    static sf::Font BatmanForever;
public:

    Tile();
    Tile(sf::Vector2f pos, sf::Vector2f& scale);
    void setColor(sf::Color c);
    void draw(sf::RenderWindow& w);
    sf::Vector2f getPosition();
    sf::Vector2f getScale();
};
