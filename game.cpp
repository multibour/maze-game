#include <iostream>

#include "constants.h"
#include "game.h"
#include "functions.h"

Game::Game(){
    ///--- Set Window ---///
    window.create(sf::VideoMode(MAZE_SIZE_X * CELL_LENGTH, MAZE_SIZE_Y * CELL_LENGTH),
                  "Maze - Alpha 0.1",
                  sf::Style::Titlebar | sf::Style::Close,
                  sf::ContextSettings(0,0,6));
    window.setKeyRepeatEnabled(false);

    ///--- Set Player ---///
    startingPosition = sf::Vector2f(PLAYER_START_X, PLAYER_START_Y);
    player.setRadius(PLAYER_RADIUS);
    player.setFillColor(sf::Color::Yellow);
    player.setOrigin(PLAYER_RADIUS, PLAYER_RADIUS);
    player.setPosition(startingPosition);

    speed = PLAYER_SPEED;

    ///--- Set Finish tile ---///
    if(!texture_finish_tile.loadFromFile("./finish.png")){
        std::cerr << "Could not load file." << std::endl;
        _exit(EXIT_FAILURE);
    }
    finish_tile.setTexture(texture_finish_tile);
    finish_tile.setPosition((MAZE_SIZE_X - 0.5) * CELL_LENGTH, 0.0);

    ///--- Create Maze and Set Walls ---///
    gameArea.create();
    gameArea.setWalls(obstacleList);
}

Game::~Game(){
}

void Game::run(){
    while(window.isOpen()){
        processEvents();
        //processInputs();
        updateData();
        render();
    }
}

void Game::processEvents(){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed)
            window.close();
    }
}

/*
void Game::processInputs(){

}
*/

void Game::updateData(){
    ///--- Handle player movement ---///
    sf::Vector2f direction(0.f, 0.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        direction.y -= speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        direction.x += speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction.y += speed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        direction.x -= speed;

    ///--- Check for Collisions and Out-of-Bounds ---///
    player.move(0, direction.y);
    if(collision(player, obstacleList))
        player.move(0, -direction.y);

    player.move(direction.x, 0);
    if(collision(player, obstacleList))
        player.move(-direction.x, 0);

    ///--- Update Enemies ---///


    ///--- Check if reached the finish tile ---///
    if(collision(player, finish_tile)){
        player.setPosition(startingPosition);
        gameArea.create();
        gameArea.setWalls(obstacleList);
    }
}

void Game::render(){
    int elementCount = obstacleList.size();

    window.clear(sf::Color(31, 8, 125));

    window.draw(finish_tile);
    for(int i = 0; i < elementCount; i++)
        window.draw(obstacleList[i]);
    window.draw(player);

    window.display();
}

