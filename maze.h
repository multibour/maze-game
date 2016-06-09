#include <SFML/Graphics.hpp>
#include <vector>
//#include <tuple>

const int MAZE_SIZE = 9;
const float length = 80.0;


struct CustomTuple{
    int x;
    int y;
};

struct singleCell{
    //has walls?
    bool up;
    bool right;
    bool down;
    bool left;

    //is visited?
    bool visited;
};

///--- Maze Class ---///
class Maze{
    private: ///private variables
        singleCell maze[MAZE_SIZE][MAZE_SIZE];

        CustomTuple current;
        CustomTuple temp;

    private: ///private methods
        void reset();

        void randomUnvisitedCell();

        bool anyUnvisitedCells();
        bool chooseRandomUnvisitedNeighbor();


    public: ///public methods
        Maze();
        ~Maze();

        void create();
        void setWalls(std::vector<sf::RectangleShape>&);

};

