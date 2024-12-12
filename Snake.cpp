#include "Snake.hpp"

Snake::Snake(int startX, int startY) {
    body.push_back(sf::Vector2i(startX, startY));
    direction = sf::Vector2i(1, 0); // Commence en allant vers la droite
}

void Snake::move() {
    // Ajoute une nouvelle tête dans la direction actuelle
    sf::Vector2i newHead = body.front() + direction;
    body.insert(body.begin(), newHead);
    body.pop_back(); // Supprime la queue
}

void Snake::grow() {
    // Ajoute une nouvelle tête sans supprimer la queue
    sf::Vector2i newHead = body.front() + direction;
    body.insert(body.begin(), newHead);
}

void Snake::setDirection(sf::Vector2i newDir) {
    // Empêche le serpent de faire demi-tour sur lui-même
    if (direction.x * -1 != newDir.x || direction.y * -1 != newDir.y) {
        direction = newDir;
    }
}

bool Snake::checkCollision() {
    sf::Vector2i head = body.front();
    
    // Vérifie la collision avec les bords
    if (head.x < 0 || head.x >= 40 || head.y < 0 || head.y >= 30) {
        return true;
    }
    
    // Vérifie la collision avec le corps
    for (size_t i = 1; i < body.size(); i++) {
        if (head == body[i]) {
            return true;
        }
    }
    
    return false;
}

void Snake::draw(sf::RenderWindow& window) {
    // Effet de lueur pour le corps du serpent
    sf::RectangleShape glow(sf::Vector2f(CELL_SIZE + 4, CELL_SIZE + 4));
    glow.setFillColor(sf::Color(0, 255, 255, 64)); // Cyan transparent pour la lueur

    // Corps du serpent avec effet néon
    sf::RectangleShape segment(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
    
    for (size_t i = 0; i < body.size(); i++) {
        // Couleur qui varie du cyan au magenta
        float ratio = static_cast<float>(i) / body.size();
        sf::Color segmentColor(
            static_cast<sf::Uint8>(255 * (1 - ratio)),  // R
            static_cast<sf::Uint8>(50 + 205 * ratio),   // G
            static_cast<sf::Uint8>(255)                 // B
        );
        
        // Dessine la lueur
        glow.setPosition(body[i].x * CELL_SIZE - 2, body[i].y * CELL_SIZE - 2);
        window.draw(glow);
        
        // Dessine le segment
        segment.setFillColor(segmentColor);
        segment.setPosition(body[i].x * CELL_SIZE + 1, body[i].y * CELL_SIZE + 1);
        
        // Ajoute un contour blanc néon
        segment.setOutlineThickness(1);
        segment.setOutlineColor(sf::Color(255, 255, 255, 200));
        
        window.draw(segment);
    }
}

sf::Vector2i Snake::getHeadPosition() const {
    return body.front();
}

const std::vector<sf::Vector2i>& Snake::getBody() const {
    return body;
}
