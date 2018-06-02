#include "board.hpp"
#include "globals.hpp"
#include "player.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
//#include <stdexcept>

// TODO: player class
Board::Board(){
    throw std::invalid_argument("illegal board");
}

Board::Board(int bs, int ds, int pc){


    boardDimension = bs;
    if(boardDimension > MAX_DIMENSION) boardDimension = MAX_DIMENSION;
    boardSize = boardDimension * boardDimension;

    diceSize = ds;
    markovChain.resize(boardSize-1, boardSize);

    sf::Vector2f scale(WINDOW_X/boardDimension, WINDOW_Y/boardDimension);
    bool flipX = false;
    Tile* newTile;
    for(int i = 0; i < boardDimension; i++){
        for(int j = 0; j < boardDimension ; j++){
            sf::Vector2f position;
            position.x = j*scale.x;
            position.y = ((WINDOW_Y - scale.y) - (i * scale.y));

            if(flipX) position.x = (WINDOW_X - scale.x) - position.x;

            newTile = new Tile(position, scale);
            auto end = tiles.end();
            tiles.insert(end, *newTile);
        }
        flipX = !flipX;
    }

    Player* newPlayer;
    sf::Vector2f pcScale(scale.x/pc, scale.y/pc);
    for(int i = 0; i < pc; i++){
        newPlayer = new Player(sf::Vector2f(rand() % (int)scale.x-pcScale.x,(WINDOW_Y - scale.y) + rand() % (int)scale.y)
        ,pcScale, sf::Color(0+i*40, 27+i*25, 60+i*18));
        //sf::Vector2f(i*scale.x, WINDOW_Y-i*scale.y)
        //(sf::Vector2f(rand() % (int)scale.x,(WINDOW_Y - scale.y) + rand() % (int)scale.y), pcScale);

        auto end = player.end();
        player.insert(end, *newPlayer);
    }


    emptySnakes();
}

float Board::expectedStateInTime(Eigen::RowVectorXf x){
    /*int size = x.size();

    float sum = 0;
    for(int i = 0; i < size; i++){
        sum +=  i * x(i);
    }
    return sum/size;*/
}

float Board::expectedVar(){
    /*int rows = markovChain.rows();
    int cols = markovChain.cols();

    float expected = expectedThrows();

    Eigen::RowVectorXf x(cols);

    float sum = 0;
    float currExpect = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            x(j) = markovChain(i, j);
        }
        currExpect +=  expectedStateInTime(x);
        std::cout << currExpect << std::endl;
        //sum += currExpect;

        for(int j = 0; j < cols; j++){
            sum += pow((j - currExpect), 2) * x(j);
        }
    }
    int kek = sqrt(sum - pow(expected, 2));

    return kek;*/
}

int Board::chanceOf(float toWin){
    int throws = 1;

    Eigen::MatrixXd chance(boardSize, boardSize);
    Eigen::MatrixXd tempMarkov(boardSize, boardSize);

    tempMarkov.setZero();
    for(int i = 0; i < boardSize-1; i++){
        for(int j = 0; j < boardSize; j++){
            tempMarkov(i, j) = markovChain(i,j);
        }
    }
    tempMarkov(boardSize-1, boardSize-1) = 1;

    chance = tempMarkov;

    while(chance(0, boardSize-1) < toWin){
        chance = chance * tempMarkov;
        throws++;
    }

    //std::cout << tempMarkov << std::endl;

    return throws;
}

int Board::simulate(std::uniform_real_distribution<>& dis, std::mt19937& gen){
    // will be used to track markov chain position
    int positionY = 0;
    int throws = 0;
    // used to simulate dice
    float roll;

    while (positionY != boardSize-1) {
        roll = dis(gen);
        throws += 1;
        int count = 36;
        while(roll > 0){
            count -= 1;
            roll -= markovChain(positionY, count);
        }
        positionY = count;
    }

    return throws;
}

int Board::leastNumberThrows(){
    return chanceOf(0.01);
}

// @R: 0 = failed
float Board::expectedThrows(){
    int t = 0;
    for(int i = 0; i < boardSize-1; i++){
        for(int j = 0; j <= boardSize; j++){
            if(markovChain(i, j) == 0){
                t = j;
            }
            else{
                break;
            }
        }
    }
    if(t >= boardSize-1){ return 0; }

    Eigen::MatrixXd Q;
    Q.resize(t,t);

    for(int i = 0; i < t; i++){
        for(int j = 0; j < t; j++){
            Q(i,j) = markovChain(i,j+1);
        }
    }

    //std::cout << Q;

    Eigen::MatrixXd fundemental = (Eigen::MatrixXd::Identity(t,t) - Q).inverse();

    Eigen::RowVectorXd expectedThrows(t);

    Eigen::RowVectorXd one(t);
    for(int i = 0; i < t; i++){
        one(i) = 1;
    }
    expectedThrows = one * fundemental;

//    std::cout << expectedThrows << std::endl;

    return expectedThrows(t-1);
}

void Board::emptySnakes(){

    markovChain.setZero();

    for(int i = 0; i < boardSize-1; i++){
        for(int j = i+1; j <= diceSize + i; j++){
            if(j >= boardSize) markovChain(i, boardSize-1) += 1.0f/diceSize;
            else markovChain(i, j) = 1.0f/diceSize;
        }
    }


    std::cout << markovChain << std::endl;
}

void Board::createShortcut(int fromState, int toState){
    if( fromState >= 0 && fromState < boardSize-1 &&
    toState >= 0 && toState < boardSize-1 ){
        for(int i = 0; i < boardSize-1; i++){
            markovChain(i, toState) += markovChain(i, fromState);
            markovChain(i, fromState) = 0;
        }
    }


}

void Board::createPrefab(){
    boardSize = 36;
    diceSize = 6;

    markovChain.resize(boardSize-1, boardSize);

    emptySnakes();
    createShortcut(2, 5);
    createShortcut(8, 1);
    createShortcut(16, 32);
    createShortcut(18, 25);
    createShortcut(29, 15);
    std::cout << markovChain;
}

void Board::update(){
    // TODO:
}

void Board::draw(sf::RenderWindow& w){

    for(auto&& i : tiles){
        i.draw(w);
    }

    for(auto&& i : player){
        i.draw(w);
    }
}
