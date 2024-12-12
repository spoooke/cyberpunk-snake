#include "Game.hpp"
#include <random>

Game::Game(sf::RenderWindow& window) 
    : window(window), 
      snake(GRID_WIDTH/2, GRID_HEIGHT/2),
      isGameOver(false),
      showGameOverMenu(false),
      score(0) {
    
    // Initialise la position de la nourriture
    spawnFood();
    
    // Charge la police pour le score
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        // Utilise une police système si Arial n'est pas disponible
        font.loadFromFile("/System/Library/Fonts/Supplemental/Courier.ttf");
    }
    
    // Configure le texte du score
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(0, 255, 255)); // Cyan néon
    scoreText.setOutlineThickness(1);
    scoreText.setOutlineColor(sf::Color(0, 128, 128));
    scoreText.setPosition(10, 10);

    // Configure le texte de game over
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color(255, 0, 128)); // Rose néon
    gameOverText.setOutlineThickness(2);
    gameOverText.setOutlineColor(sf::Color(128, 0, 255));

    // Configure le texte de restart
    restartText.setFont(font);
    restartText.setString("Press SPACE to restart\nPress ESC to quit");
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color(0, 255, 255)); // Cyan néon
    restartText.setOutlineThickness(1);
    restartText.setOutlineColor(sf::Color(0, 128, 128));
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (!isGameOver) {
            update();
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (isGameOver) {
                // Gestion des touches dans le menu Game Over
                if (event.key.code == sf::Keyboard::Space) {
                    reset();  // Réinitialise le jeu
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            } else {
                // Gestion des touches pendant le jeu
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        snake.setDirection(sf::Vector2i(0, -1));
                        break;
                    case sf::Keyboard::Down:
                        snake.setDirection(sf::Vector2i(0, 1));
                        break;
                    case sf::Keyboard::Left:
                        snake.setDirection(sf::Vector2i(-1, 0));
                        break;
                    case sf::Keyboard::Right:
                        snake.setDirection(sf::Vector2i(1, 0));
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void Game::reset() {
    // Réinitialise le jeu
    snake = Snake(GRID_WIDTH/2, GRID_HEIGHT/2);
    score = 0;
    scoreText.setString("Score: 0");
    isGameOver = false;
    showGameOverMenu = false;
    spawnFood();
}

void Game::update() {
    if (isGameOver) return;
    
    // Déplace le serpent
    snake.move();
    
    // Vérifie la collision avec la nourriture
    if (snake.getHeadPosition() == food) {
        snake.grow();
        spawnFood();
        score += 10;
        scoreText.setString("Score: " + std::to_string(score));
    }
    
    // Vérifie la collision avec les murs ou le corps
    if (snake.checkCollision()) {
        isGameOver = true;
        showGameOverMenu = true;
    }
}

void Game::render() {
    window.clear(sf::Color(10, 10, 20)); // Fond sombre bleuté
    
    // Dessine la grille cyberpunk
    sf::RectangleShape gridLine(sf::Vector2f(1, window.getSize().y));
    gridLine.setFillColor(sf::Color(0, 255, 255, 20)); // Cyan très transparent
    
    // Lignes verticales
    for (int x = 0; x < GRID_WIDTH; x++) {
        gridLine.setPosition(x * CELL_SIZE, 0);
        window.draw(gridLine);
    }
    
    // Lignes horizontales
    gridLine.setSize(sf::Vector2f(window.getSize().x, 1));
    for (int y = 0; y < GRID_HEIGHT; y++) {
        gridLine.setPosition(0, y * CELL_SIZE);
        window.draw(gridLine);
    }
    
    // Dessine la nourriture avec effet de pulsation
    float pulse = (1 + sin(clock.getElapsedTime().asSeconds() * 5)) / 2;
    sf::CircleShape foodGlow(CELL_SIZE);
    foodGlow.setFillColor(sf::Color(255, 0, 128, static_cast<sf::Uint8>(64 * pulse))); // Rose néon
    foodGlow.setPosition(food.x * CELL_SIZE, food.y * CELL_SIZE);
    window.draw(foodGlow);
    
    sf::CircleShape foodShape(CELL_SIZE/2);
    foodShape.setFillColor(sf::Color(255, 0, 128)); // Rose néon
    foodShape.setPosition(food.x * CELL_SIZE + CELL_SIZE/4, food.y * CELL_SIZE + CELL_SIZE/4);
    foodShape.setOutlineThickness(1);
    foodShape.setOutlineColor(sf::Color::White);
    window.draw(foodShape);
    
    // Dessine le serpent
    snake.draw(window);
    
    // Dessine le score
    window.draw(scoreText);
    
    // Si game over, affiche le menu avec style cyberpunk
    if (showGameOverMenu) {
        // Effet de fond semi-transparent
        sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(overlay);
        
        // Centre et dessine les textes
        sf::FloatRect gameOverRect = gameOverText.getLocalBounds();
        gameOverText.setOrigin(gameOverRect.width/2, gameOverRect.height/2);
        gameOverText.setPosition(window.getSize().x/2, window.getSize().y/2 - 50);
        
        sf::FloatRect restartRect = restartText.getLocalBounds();
        restartText.setOrigin(restartRect.width/2, restartRect.height/2);
        restartText.setPosition(window.getSize().x/2, window.getSize().y/2 + 50);
        
        // Effet de pulsation sur le texte
        float textPulse = (1 + sin(clock.getElapsedTime().asSeconds() * 3)) / 2;
        gameOverText.setScale(1 + textPulse * 0.1f, 1 + textPulse * 0.1f);
        
        window.draw(gameOverText);
        window.draw(restartText);
    }
    
    window.display();
}

void Game::spawnFood() {
    // Génère une position aléatoire pour la nourriture
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, GRID_WIDTH - 1);
    std::uniform_int_distribution<> disY(0, GRID_HEIGHT - 1);
    
    bool validPosition;
    do {
        validPosition = true;
        food = sf::Vector2i(disX(gen), disY(gen));
        
        // Vérifie que la nourriture n'apparaît pas sur le serpent
        for (const auto& segment : snake.getBody()) {
            if (segment == food) {
                validPosition = false;
                break;
            }
        }
    } while (!validPosition);
}
