#include <SFML/Graphics.hpp>
#include <vector>

#include "maze.h"
//#include "entity.h"

class Game{
    private: ///--- private variables
        //Window
        sf::RenderWindow window;

        //Player
        sf::CircleShape player;
        sf::Vector2f startingPosition; //starting position
        float speed;

        //Walls & Obstacles
        std::vector<sf::RectangleShape> obstacleList;
        std::vector<sf::FloatRect> obstacleGlobalBoundList;

        //Finish tile
        sf::Texture texture_finish_tile;
        sf::Sprite finish_tile;

        //Maze
        Maze gameArea;

        //Enemies
        //std::vector<Entity> enemyList;

    private: ///--- private methods
        void processEvents();
        //void processInputs();
        void updateData();
        void render();

    public:
        Game(); //default constructor
        ~Game(); //destructor

        void run();
};


