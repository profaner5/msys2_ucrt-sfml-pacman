#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>

const int MAP_WIDTH = 19;
const int MAP_HEIGHT = 21;
const int TILE_SIZE = 24;

int initial_map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
    {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
    {1,1,1,1,0,1,1,1,2,1,2,1,1,1,0,1,1,1,1},
    {2,2,2,1,0,1,2,2,2,2,2,2,2,1,0,1,2,2,2},
    {1,1,1,1,0,1,2,1,1,2,1,1,2,1,0,1,1,1,1},
    {2,2,2,2,0,2,2,1,2,2,2,1,2,2,0,2,2,2,2},
    {1,1,1,1,0,1,2,1,1,1,1,1,2,1,0,1,1,1,1},
    {2,2,2,1,0,1,2,2,2,2,2,2,2,1,0,1,2,2,2},
    {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
    {1,0,0,1,0,0,0,0,0,2,0,0,0,0,0,1,0,0,1},
    {1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main() {
    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int>(MAP_WIDTH * TILE_SIZE), static_cast<unsigned int>(MAP_HEIGHT * TILE_SIZE)}), "Pac-Man UCRT64");
    window.setFramerateLimit(60);

    int map[MAP_HEIGHT][MAP_WIDTH];
    auto resetGame = [&]() {
        for (int y = 0; y < MAP_HEIGHT; ++y)
            for (int x = 0; x < MAP_WIDTH; ++x)
                map[y][x] = initial_map[y][x];
    };
    resetGame();

    float px = 9 * TILE_SIZE + TILE_SIZE / 2.0f;
    float py = 16 * TILE_SIZE + TILE_SIZE / 2.0f;
    float speed = 2.0f;
    int dirX = 0, dirY = 0;
    int nextDirX = 0, nextDirY = 0;

    sf::CircleShape pacmanShape(TILE_SIZE / 2.5f);
    pacmanShape.setFillColor(sf::Color::Yellow);
    pacmanShape.setOrigin({pacmanShape.getRadius(), pacmanShape.getRadius()});

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  { nextDirX = -1; nextDirY = 0; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) { nextDirX = 1;  nextDirY = 0; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    { nextDirX = 0;  nextDirY = -1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  { nextDirX = 0;  nextDirY = 1; }

        int currentTileX = static_cast<int>(px / TILE_SIZE);
        int currentTileY = static_cast<int>(py / TILE_SIZE);

        if (std::fmod(px, TILE_SIZE) - TILE_SIZE / 2.0f < speed && 
            std::fmod(py, TILE_SIZE) - TILE_SIZE / 2.0f < speed) {
            
            int nextX = currentTileX + nextDirX;
            int nextY = currentTileY + nextDirY;
            if (nextX >= 0 && nextX < MAP_WIDTH && map[nextY][nextX] != 1) {
                dirX = nextDirX;
                dirY = nextDirY;
            }
        }

        float nextPx = px + dirX * speed;
        float nextPy = py + dirY * speed;
        
        int testTileX = static_cast<int>((nextPx + dirX * (TILE_SIZE / 2.0f)) / TILE_SIZE);
        int testTileY = static_cast<int>((nextPy + dirY * (TILE_SIZE / 2.0f)) / TILE_SIZE);

        if (testTileX >= 0 && testTileX < MAP_WIDTH && testTileY >= 0 && testTileY < MAP_HEIGHT) {
            if (map[testTileY][testTileX] != 1) {
                px = nextPx;
                py = nextPy;
            }
        }

        if (px < 0) px = MAP_WIDTH * TILE_SIZE - 1;
        if (px >= MAP_WIDTH * TILE_SIZE) px = 0;

        int eatX = static_cast<int>(px / TILE_SIZE);
        int eatY = static_cast<int>(py / TILE_SIZE);
        if (map[eatY][eatX] == 0) {
            map[eatY][eatX] = 2; // съедено
        }

        window.clear(sf::Color::Black);

        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                if (map[y][x] == 1) {
                    sf::RectangleShape wall(sf::Vector2f(TILE_SIZE - 1.0f, TILE_SIZE - 1.0f));
                    wall.setPosition({static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE)});
                    wall.setFillColor(sf::Color::Blue);
                    window.draw(wall);
                } else if (map[y][x] == 0) {
                    sf::CircleShape dot(3.0f);
                    dot.setFillColor(sf::Color(255, 183, 174));
                    dot.setPosition({static_cast<float>(x * TILE_SIZE + TILE_SIZE / 2.0f - 3.0f), 
                                     static_cast<float>(y * TILE_SIZE + TILE_SIZE / 2.0f - 3.0f)});
                    window.draw(dot);
                }
            }
        }

        pacmanShape.setPosition({px, py});
        window.draw(pacmanShape);

        window.display();
    }

    return 0;
}