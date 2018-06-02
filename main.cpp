#include <iostream>
#include <SFML/Graphics.hpp>

#include "eigen/Eigen/Dense"
#include "board.hpp"
#include "globals.hpp"


int main(int argc, char* argv[]){

    // This is used to seed the generator
    std::random_device rd;
    // We seed the Mersenne twister
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 1);

    // Create board singleton
    Board board(6, 6, 0);
    board.createPrefab();
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Snakes & ladders");

    int simulationAmount = 100;
    if(argc > 1){
        std::cout << "hello";
        simulationAmount = atoi(argv[1]);
    }

    //self.setPosition(sf::Vector2f(10.0f, 10.0f));
    std::cout << std::endl << "Chance greater than 50%: " <<board.chanceOf(0.5f) << std::endl;
    std::cout << std::endl << "Chance greater than 99%: " << board.chanceOf(0.99f) << std::endl;
    std::cout << std::endl << "Least number of throws: " <<board.leastNumberThrows() << std::endl;
    std::cout << std::endl << "Expect throws: " << board.expectedThrows() << std::endl;
    //std::cout << std::endl << "test " << board.expectedVar() << std::endl;


    float throwSum = 0;
    int simResult = 0;
    int lastThrowCount = 0;
    float variance = 0;
    for(int i = 0; i < simulationAmount; i++){
        simResult = board.simulate(dist, gen);

        if(i > 0){
            variance += abs(lastThrowCount - simResult);
        }

        throwSum += simResult;
        lastThrowCount = simResult;
    }
    float average = throwSum/simulationAmount;
    std::cout << std::endl << "Average from simulation: " << average << std::endl;

    float var = variance/(simulationAmount-1);
    std::cout << std::endl << "simulated variance: " << var << std::endl;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        board.draw(window);
        window.display();
    }


}
