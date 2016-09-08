#include <cmath>

#include "constants.h"
#include "entity.h"
#include "functions.h"

/// Constructors & Destructor

Entity::Entity(sf::Texture& texture){
    entity.setTexture(texture);

    entity.setOrigin(entity.getTextureRect().width / 2,
                     entity.getTextureRect().height / 2);
    randomizePosition();

    velocity = sf::Vector2f(ENEMY_SPEED / sqrt(2.0), ENEMY_SPEED / sqrt(2.0));
    mode = STILL;
}

Entity::Entity(sf::Texture& texture, sf::Vector2f position, sf::Vector2f initialVelocity){
    entity.setTexture(texture);

    entity.setOrigin(entity.getTextureRect().width / 2,
                     entity.getTextureRect().height / 2);
    entity.setPosition(position);

    velocity = initialVelocity;
    mode = STILL;
}

Entity::~Entity(){
}

/// Set methods

void Entity::setMode(MovementMode newMode){
    mode = newMode;
}

void Entity::resetTexture(sf::Texture& texture){
    entity.setTexture(texture);
}

///

void Entity::update(std::vector<sf::RectangleShape>& walls){
    if(mode == STILL)
        return;


    sf::Vector2f direction(0.0, 0.0);

    switch(mode){
    case LEFTRIGHT:
        direction.x = velocity.x;
        break;

    case UPDOWN:
        direction.y = velocity.y;
        break;

    case CUSTOM:
        direction = velocity;
        break;

    case SMART:
        //make enemy walk along path randomly
        break;

    case STALKER:
        //make enemy go where the player is
        break;

    default:
        break;

    }//end of switch

    entity.move(direction);

    if(collision(entity, walls)){
        entity.move(-direction);
        velocity = -velocity;
    }
}

void Entity::update(float tick, std::vector<sf::RectangleShape>& walls){
    if(mode == STILL)
        return;
    /*
    if(collision(entity, walls)){
        entity.move(-direction);
        velocity = -velocity;
    }
    */
    sf::Vector2f direction(0.0, 0.0);

    switch(mode){
    case CUSTOM:
        direction.x = velocity.x * tick;
        direction.y = velocity.y * tick;
        break;

    case LEFTRIGHT:
        direction.x = velocity.x * tick;
        break;

    case UPDOWN:
        direction.y = velocity.y * tick;
        break;

    case SMART:
        //make enemy walk along path randomly
        break;

    case STALKER:
        //make enemy go where the player is
        break;

    default:
        break;

    }//end of switch

    entity.move(direction);

    if(collision(entity, walls)){
        entity.move(-direction);
        velocity = -velocity;
    }
}

///

void Entity::randomizePosition(){
    giveRandomPosition(entity);

    //put the entity in the middle of the cell
    entity.setPosition(entity.getPosition().x + CELL_LENGTH / 2.0,
                       entity.getPosition().y + CELL_LENGTH / 2.0);
}

///

sf::Sprite& Entity::getEntity(){
    return entity;
}

