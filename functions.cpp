#include "functions.h"

bool collision(const sf::Shape& shape_1, const sf::Shape& shape_2){
    return shape_1.getGlobalBounds().intersects(shape_2.getGlobalBounds());
}

bool collision(const sf::Shape& shape_1, const sf::Sprite& sprite_1){
    return shape_1.getGlobalBounds().intersects(sprite_1.getGlobalBounds());
}

bool collision(const sf::Shape& shape_1, sf::FloatRect bound){
    return shape_1.getGlobalBounds().intersects(bound);
}

bool collision(const sf::Shape& shape_1, std::vector<sf::RectangleShape>& shapeList){
    static unsigned short int elementCount;
    elementCount = shapeList.size();

    for(unsigned short int index = 0; index < elementCount; index++){
        if(collision(shape_1, shapeList[index]))
            return true;
    }

    return false;
}

