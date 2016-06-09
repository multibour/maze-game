#include <cstdlib>
#include <ctime>
#include <stack>
#include <iostream>

#include "maze.h"

using namespace std;

Maze::Maze(){
    current.x = 0;
    current.y = 0;
    maze[0][0].visited = true;
    //reset();
}

Maze::~Maze(){
}

///--- Private Methods ---///

void Maze::reset(){
    for(int i = 0; i < MAZE_SIZE; i++){
        for(int j = 0; j < MAZE_SIZE; j++){
            maze[i][j].up = true;
            maze[i][j].right = true;
            maze[i][j].down = true;
            maze[i][j].left = true;
            maze[i][j].visited = false;
        }
    }
    current.x = 0;
    current.y = 0;
    maze[0][0].visited = true;
}


void Maze::randomUnvisitedCell(){
    do{
        current.x = rand() % MAZE_SIZE;
        current.y = rand() % MAZE_SIZE;
    }while(maze[current.y][current.x].visited);
    maze[current.y][current.x].visited = true;
}


bool Maze::anyUnvisitedCells(){
    for(int i = 0; i < MAZE_SIZE; i++){
        for(int j = 0; j < MAZE_SIZE; j++){
            if(!(maze[i][j].visited))
                return true;
        }
    }
    return false;
}

bool Maze::chooseRandomUnvisitedNeighbor(){//
    int x = current.x;
    int y = current.y;

    bool up = false;
    bool left = false;
    bool down = false;
    bool right = false;

    if(y != 0){ //look up
        if(!maze[y-1][x].visited)
            up = true;
    }
    if(x != 0){ //look left
        if(!maze[y][x-1].visited)
            left = true;
    }
    if(y != MAZE_SIZE-1){ //look down
        if(!maze[y+1][x].visited)
            down = true;
    }
    if(x != MAZE_SIZE-1){ //look right
        if(!maze[y][x+1].visited)
            right = true;
    }

    if(!(up || left || down || right)) //if all are visited
        return false;

    int index = rand() % 4; //0,1,2,3
    while(true){
        if(index == 0 && up){
            temp.y = y-1;
            temp.x = x;
            maze[y][x].up = false;
            maze[y-1][x].down = false;
            return true;
        }
        if(index == 1 && left){
            temp.y = y;
            temp.x = x-1;
            maze[y][x].left = false;
            maze[y][x-1].right = false;
            return true;
        }
        if(index == 2 && down){
            temp.y = y+1;
            temp.x = x;
            maze[y][x].down = false;
            maze[y+1][x].up = false;
            return true;
        }
        if(index == 3 && right){
            temp.y = y;
            temp.x = x+1;
            maze[y][x].right = false;
            maze[y][x+1].left = false;
            return true;
        }

        if(index == 3)
            index = 0;
        else
            index++;
    }
}

///--- Public Methods ---///

void Maze::create(){//
    reset();
    srand(time(NULL));
    std::stack<CustomTuple> cellStack;

    while(anyUnvisitedCells()){
        if(chooseRandomUnvisitedNeighbor()){
            cellStack.push(current);//push to stack
            current = temp;
            maze[current.y][current.x].visited = true;
        }
        else if(!cellStack.empty()){//stack is not empty
            current = cellStack.top();
            cellStack.pop();//pop from stack
        }
        else{
            randomUnvisitedCell();
            maze[current.y][current.x].visited = true;
        }
    }

    std::cout << "Maze created!" << std::endl;
}

void Maze::setWalls(std::vector<sf::RectangleShape>& walls){
    walls.clear();

    ///-- Set Info of vertical and horizontal Walls --///
    sf::RectangleShape verticalWall(sf::Vector2f(2.0, length));
    verticalWall.setOrigin(1.0, length/2);
    verticalWall.setFillColor(sf::Color::Green);

    sf::RectangleShape horizontalWall(sf::Vector2f(length, 2.0));
    horizontalWall.setOrigin(length/2, 1.0);
    horizontalWall.setFillColor(sf::Color::Green);

    ///-- Set necessary walls and push them to vector --///
    for(int iii = 0; iii < MAZE_SIZE; iii++){
        for(int jjj = 0; jjj < MAZE_SIZE; jjj++){
            if(iii == MAZE_SIZE-1)
                ;//rightmost cells' right walls will not be placed.
            else if(maze[jjj][iii].right){
                verticalWall.setPosition((iii+1) * length , jjj*length + length/2);
                walls.push_back(verticalWall);
            }

            if(jjj == MAZE_SIZE-1)
                ;//bottom cells' lower walls will not be placed.
            else if(maze[jjj][iii].down){
                horizontalWall.setPosition(iii*length + length/2, (jjj+1) * length);
                walls.push_back(horizontalWall);
            }
        }//for loop
    }//for loop

    ///-- Set the walls around the Map --///
    verticalWall.setSize(sf::Vector2f(2.0, length * MAZE_SIZE));
    verticalWall.setOrigin(1.0, 0.0);
    horizontalWall.setSize(sf::Vector2f(length * MAZE_SIZE, 2.0));
    horizontalWall.setOrigin(0.0, 1.0);

    verticalWall.setPosition(0.0, 0.0);
    horizontalWall.setPosition(0.0, 0.0);
    walls.push_back(verticalWall);
    walls.push_back(horizontalWall);

    verticalWall.setPosition(MAZE_SIZE * length, 0.0);
    horizontalWall.setPosition(0.0, MAZE_SIZE * length);
    walls.push_back(verticalWall);
    walls.push_back(horizontalWall);
}








