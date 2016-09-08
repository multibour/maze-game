#include <cstdlib>
//#include <string>

#include "constants.h"
#include "functions.h"

bool collision(const sf::Shape& shape_1, const sf::Shape& shape_2){
    return shape_1.getGlobalBounds().intersects(shape_2.getGlobalBounds());
}

bool collision(const sf::Shape& shape_1, const sf::Sprite& sprite_1){
    return shape_1.getGlobalBounds().intersects(sprite_1.getGlobalBounds());
}

bool collision(const sf::Sprite& sprite_1, const sf::Shape& shape_1){
    return shape_1.getGlobalBounds().intersects(sprite_1.getGlobalBounds());
}

///-------

bool collision(const sf::Shape& shape_1, std::vector<sf::RectangleShape>& shapeList){
    unsigned short int elementCount = shapeList.size();

    for(unsigned short int index = 0; index < elementCount; index++){
        if(collision(shape_1, shapeList[index]))
            return true;
    }

    return false;
}

bool collision(const sf::Sprite& sprite_1, std::vector<sf::RectangleShape>& shapeList){
    unsigned short int elementCount = shapeList.size();

    for(unsigned short int index = 0; index < elementCount; index++){
        if(collision(sprite_1, shapeList[index]))
            return true;
    }

    return false;
}

///------------------------------------

void giveRandomPosition(sf::Sprite& sprite_1){
    //srand(time(NULL));

    unsigned int cell_x = rand() % (MAZE_SIZE_X - 1) + 1; // [1 , N-1]
    unsigned int cell_y = rand() % (MAZE_SIZE_Y - 1) + 1; // [1 , N-1]

    sprite_1.setPosition(cell_x * CELL_LENGTH,
                         cell_y * CELL_LENGTH);
}

void giveRandomPosition(sf::Vector2f& pointSet){
    //srand(time(NULL));

    unsigned int cell_x = rand() % (MAZE_SIZE_X - 2) + 1; // [1 , N-1]
    unsigned int cell_y = rand() % (MAZE_SIZE_Y - 2) + 1; // [1 , N-1]

    pointSet.x = cell_x * CELL_LENGTH;
    pointSet.y = cell_y * CELL_LENGTH;
}


