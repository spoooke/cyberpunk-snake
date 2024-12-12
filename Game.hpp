#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.hpp"

class Game {
public:
    Game(sf::RenderWindow& window);
    void run();

private:
    void processEvents();
    void update();
    void render();
    void spawnFood();
    void reset();  
    bool isGameOver;
    bool showGameOverMenu;  

    sf::RenderWindow& window;
    Snake snake;
    sf::Vector2i food;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;    
    sf::Text restartText;     
    sf::Clock clock;  
    int score;
    
    static const int CELL_SIZE = 20;
    static const int GRID_WIDTH = 40;
    static const int GRID_HEIGHT = 30;
};
