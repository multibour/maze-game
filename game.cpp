#include <iostream>

#include "game.h"
#include "functions.h"

using namespace std;

Game::Game(){
    ///--- Set Window ---///
    window_x = 720;
    window_y = 720;
    window.create(sf::VideoMode(window_x, window_y), "Maze Game - A0.1",
                  sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(0,0,6));
    window.setKeyRepeatEnabled(false);

    ///--- Set Player ---///
    const float radius = 7.5;
    start = sf::Vector2f(10.0, 10.0);

    player.setRadius(radius);
    player.setFillColor(sf::Color::Yellow);
    player.setOrigin(radius, radius);
    //player.setOutlineThickness(5.0);
    //player.setOutlineColor(sf::Color::Magenta);
    player.setPosition(start);

    speed = 0.7;
    moveUp = moveRight = moveDown = moveLeft = false;

    ///--- Set Finish tile ---///
    if(!texture_finish_tile.loadFromFile("./finish.png")){
        cerr << "Could not load file." << endl;
    }
    finish_tile.setTexture(texture_finish_tile);
    finish_tile.setOrigin(finish_tile.getTexture()->getSize().x / 2.0, finish_tile.getTexture()->getSize().y / 2.0);
    finish_tile.setPosition((MAZE_SIZE-1) * length + length/2, length/2);

    ///--- Set Walls ---///
    gameArea.create();
    gameArea.setWalls(obstacleList);
}

Game::~Game(){

}

void Game::run(){
    while(window.isOpen()){
        processEvents();
        processInputs();
        updateData();
        render();
    }
}


void Game::processEvents(){
    sf::Event event;
    while(window.pollEvent(event)){
        /*
        if(event.type == sf::Event::KeyPressed)
            processInput(event.key.code, true);

        else if(event.type == sf::Event::KeyReleased)
            processInput(event.key.code, false);
        */
        if(event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::processInputs(/*sf::Keyboard::Key key, bool isPressed*/){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveUp = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        moveRight = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        moveDown = true;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        moveLeft = true;
}

void Game::updateData(){
    ///--- Handle player movement ---///
    sf::Vector2f direction(0.f, 0.f);

    if(moveUp)
        direction.y -= speed;
    if(moveRight)
        direction.x += speed;
    if(moveDown)
        direction.y += speed;
    if(moveLeft)
        direction.x -= speed;

    moveUp = moveDown = moveLeft = moveRight = false;

    ///--- Check for Collisions and Out-of-Bounds ---///

    player.move(0, direction.y);
    if(collision(player, obstacleList))
        player.move(0, -direction.y);

    player.move(direction.x, 0);
    if(collision(player, obstacleList) )
        player.move(-direction.x, 0);

    ///--- Check if reached the finish tile ---///
    if(collision(player, finish_tile)){
        player.setPosition(start);
        gameArea.create();
        gameArea.setWalls(obstacleList);
    }
}

void Game::render(){
    static int elementCount;
    elementCount = obstacleList.size();

    window.clear(sf::Color(31, 8, 124));

    window.draw(finish_tile);
    for(int i = 0; i < elementCount; i++)
        window.draw(obstacleList[i]);
    window.draw(player);

    window.display();
}



