#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Snake {
public:
    Snake(int startX, int startY);
    void move();
    void grow();
    void setDirection(sf::Vector2i newDir);
    bool checkCollision();
    void draw(sf::RenderWindow& window);
    sf::Vector2i getHeadPosition() const;
    const std::vector<sf::Vector2i>& getBody() const;

private:
    std::vector<sf::Vector2i> body;
    sf::Vector2i direction;
    static const int CELL_SIZE = 20;
};
