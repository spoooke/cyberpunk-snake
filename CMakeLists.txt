cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouve SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Ajoute les fichiers source
add_executable(SnakeGame
    main.cpp
    Snake.cpp
    Game.cpp
)

# Lie les bibliothèques SFML
target_link_libraries(SnakeGame
    sfml-graphics
    sfml-window
    sfml-system
)
