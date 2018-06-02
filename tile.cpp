#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include "globals.hpp"

int Tile::nextId = 1;
bool Tile::FontSet = false;
sf::Font Tile::BatmanForever;

Tile::Tile(){
    throw std::invalid_argument("illegal tile");
}

Tile::Tile(sf::Vector2f pos, sf::Vector2f& size){

    if(FontSet == false){
        if(!BatmanForever.loadFromFile("batmfa__.ttf")){
            throw std::runtime_error("failed to load batmfa__.tff");
        }
        FontSet = true;
    }


    idText.setFont(BatmanForever);
    idText.setPosition(pos.x + size.x/2, pos.y + size.y/2);
    idText.setCharacterSize(size.x/4);
    idText.setString(std::to_string(nextId++));
    idText.setColor(sf::Color::Black);

    self.setFillColor(sf::Color::White);
    self.setOutlineColor(sf::Color::Black);
    self.setOutlineThickness(-3);
    self.setSize(size);
    self.setPosition(pos);

}

void Tile::setColor(sf::Color c){
    self.setFillColor(c);
}

void Tile::draw(sf::RenderWindow& w){
    w.draw(self);
    w.draw(idText);
}

sf::Vector2f Tile::getPosition(){
    return self.getPosition();
}

sf::Vector2f Tile::getScale(){
    return self.getScale();
}
