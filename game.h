#include <SFML/Graphics.hpp>
#include <vector>

#include "maze.h"

class Game{
    private: //--- private variables
        unsigned short int window_x;
        unsigned short int window_y;
        sf::RenderWindow window;

        sf::CircleShape player;
        bool moveUp, moveRight, moveDown, moveLeft;
        float speed;
        sf::Vector2f start;

        std::vector<sf::RectangleShape> obstacleList;

        sf::Texture texture_finish_tile;
        sf::Sprite finish_tile;

        Maze gameArea;

    private: //--- private methods
        void processEvents();
        void processInputs(/*sf::Keyboard::Key, bool*/);
        void updateData();
        void render();

    public:
        Game(); //default constructor
        ~Game(); //destructor

        void run();
};


