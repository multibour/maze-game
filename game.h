#include <SFML/Graphics.hpp>
#include <vector>

#include "maze.h"
#include "entity.h"

class Game{
    private: ///--- private variables
        //Window
        sf::RenderWindow window;
        sf::View view;

        //Player
        sf::CircleShape player;
        sf::Vector2f startingPosition;
        float speed;

        //Key
        sf::Texture texture_key;
        sf::Sprite key;
        bool keyIsTaken;

        //Walls & Obstacles
        std::vector<sf::RectangleShape> obstacleList;

        //Finish tile
        sf::Texture texture_finish_tile;
        sf::Sprite finish_tile;

        //Maze
        Maze gameArea;

        //Enemies
        sf::Texture texture_enemy;
        std::vector<Entity> enemyList;
        unsigned int enemyCount;

        //Time handling
        sf::Clock game_tick;

    private: ///--- private methods
        void updateData();
        void render();

    public:
        Game(); //default constructor
        ~Game(); //destructor

        void run();
};

