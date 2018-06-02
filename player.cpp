#include "player.hpp"
#include "globals.hpp"
#include <iostream>
//int Player::playerCount = 0;

Player::Player(){
    throw std::invalid_argument("illegal tile");

}

Player::Player(sf::Vector2f pos, sf::Vector2f size, sf::Color c){
    self.setPosition(pos);
    self.setSize(size);
    setColor(c);
}

void Player::move(Tile t){
    sf::Vector2f tilePosition = t.getPosition();
    sf::Vector2f scale = t.getScale();
    sf::Vector2f pcScale = self.getScale();
    std::cout << scale.x;
    //- pcScale.x |- pcScale.y TODO: fix this, only set in corner of tile
    self.setPosition(rand() % (int)scale.x + tilePosition.x , tilePosition.y + rand() % (int)scale.y );
}

void Player::setColor(sf::Color c){
    self.setFillColor(c);
}

void Player::draw(sf::RenderWindow& w){
    w.draw(self);
}
