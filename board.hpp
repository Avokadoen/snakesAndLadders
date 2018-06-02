#pragma once

#include <vector>
#include "eigen/Eigen/Dense"
#include "tile.hpp"
#include "player.hpp"

class Board{
private:
    int boardSize;
    int boardDimension;
    int diceSize;
    Eigen::MatrixXd markovChain;

    std::vector<Tile> tiles;
    std::vector<Player> player;
    std::vector<sf::RectangleShape> shortcuts;

public:
    Board();
    /*
    *@param board dimension and dice size
    */
    Board(int bs, int ds,int pc);
    float expectedStateInTime(Eigen::RowVectorXf x);
    float expectedVar();
    int leastNumberThrows();
    float expectedThrows();
    int chanceOf(float toWin);
    int simulate(std::uniform_real_distribution<>& dis, std::mt19937& gen);
    void emptySnakes();
    void createShortcut(int fromState, int toState);
    void createPrefab();
    void update();
    void draw(sf::RenderWindow& w);
};
