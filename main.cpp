#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main() {
    // Créer la fenêtre du jeu
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");
    window.setFramerateLimit(10); // Limite les FPS pour que le serpent ne bouge pas trop vite

    // Créer et démarrer le jeu
    Game game(window);
    game.run();

    return 0;
}
