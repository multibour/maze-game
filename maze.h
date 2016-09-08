#include <SFML/Graphics.hpp>
#include <vector>

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
        singleCell** maze; //2D singleCell array

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

        const singleCell* operator[](unsigned int);

        void create();
        void setWalls(std::vector<sf::RectangleShape>&);
};

