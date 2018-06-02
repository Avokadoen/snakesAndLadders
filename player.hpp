#pragma once

#include "tile.hpp"
#include <SFML/Graphics.hpp>

class Player{
private:
    sf::RectangleShape self;
    //static int playerCount;
public:
    Player();
    Player(sf::Vector2f pos, sf::Vector2f size, sf::Color c);
    //Player(sf::Vector2f pos, sf::Vector2f& scale);
    void move(Tile t);
    void setColor(sf::Color c);
    void draw(sf::RenderWindow& w);
};
