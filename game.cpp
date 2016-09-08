#include <iostream>
#include <string>

#include "constants.h"
#include "game.h"
#include "functions.h"

Game::Game(){
    ///--- Initial Check ---///

    if(MAZE_SIZE_X < 3 || MAZE_SIZE_Y < 3){
        std::cerr << "Invalid initial values(s)." << std::endl;
        _exit(EXIT_FAILURE);
    }


    ///--- Set Window ---///

    window.create(sf::VideoMode(800, 600),
                  "Maze - Alpha 0.4",
                  sf::Style::Titlebar | sf::Style::Close,
                  sf::ContextSettings(0,0,6));
    window.setKeyRepeatEnabled(false);


    ///--- Load Textures ---///

    std::string prefix = "./textures/";

    if(!texture_key.loadFromFile(prefix + "key.png")
       || !texture_finish_tile.loadFromFile(prefix + "finish.png")
       || !texture_enemy.loadFromFile(prefix + "enemy.png")){
        std::cerr << "Could not load texture file(s)." << std::endl;
        _exit(EXIT_FAILURE);
    }


    ///--- Set Player ---///

    startingPosition = sf::Vector2f(PLAYER_START_X, PLAYER_START_Y);
    player.setRadius(PLAYER_RADIUS);
    player.setFillColor(sf::Color::Yellow);
    player.setOrigin(PLAYER_RADIUS, PLAYER_RADIUS);
    player.setPosition(startingPosition);

    speed = PLAYER_SPEED; //game speed could change in-game in the future


    ///--- Set View ---///

    view.setCenter(player.getPosition());
    view.setSize(window.getSize().x, window.getSize().y);
    view.zoom(0.5);
    window.setView(view);


    ///--- Set Key ---///

    keyIsTaken = false;

    key.setTexture(texture_key);

    giveRandomPosition(key);


    ///--- Set Finish tile ---///

    finish_tile.setTexture(texture_finish_tile);
    finish_tile.setOrigin(finish_tile.getGlobalBounds().width, 0.0);
    finish_tile.setPosition(MAZE_SIZE_X * CELL_LENGTH, 0.0);


    ///--- Set Enemies, (testing phase) ---///

    enemyCount = 1;

    sf::Vector2f enemyPositionVector;
    giveRandomPosition(enemyPositionVector);
    enemyPositionVector.x += CELL_LENGTH / 2.0;
    enemyPositionVector.y += CELL_LENGTH / 2.0;

    Entity testEntity(texture_enemy);
    testEntity.setMode(CUSTOM);
    //testEntity.resetTexture(texture_enemy);

    enemyList.push_back(testEntity);


    ///--- Create Maze and Set Walls ---///

    gameArea.create();
    gameArea.setWalls(obstacleList);
}

Game::~Game(){
    for(unsigned int i = 0; i < obstacleList.size(); i++){
        if(collision(obstacleList[i], enemyList.front().getEntity()))
            std::cout << "Enemy hits the wall :(" << std::endl;
    }
}


void Game::run(){
    while(window.isOpen()){//game loop
        ///-- Event handling --///
        sf::Event event;
        while(window.pollEvent(event)){//event loop
            switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                view.setSize(event.size.width, event.size.height);
                view.zoom(0.5);
                window.setView(view);
                break;

            default:
                break;
            }
        } //end of event loop

        ///-- Update & Render --///
        updateData();
        render();
    } //end of game loop
}


void Game::updateData(){
    ///--- Get tick duration ---///

    float ElapsedTime = game_tick.getElapsedTime().asSeconds();
    game_tick.restart();


    ///--- Handle player movement ---///

    sf::Vector2f direction(0.f, 0.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction.y -= speed * ElapsedTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction.x += speed * ElapsedTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction.y += speed * ElapsedTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction.x -= speed * ElapsedTime;


    ///--- Check for Collisions and Out-of-Bounds ---///

    player.move(0, direction.y);
    if(collision(player, obstacleList))
        player.move(0, -direction.y);

    player.move(direction.x, 0);
    if(collision(player, obstacleList))
        player.move(-direction.x, 0);


    ///--- Update Key ---///

    if(!keyIsTaken){
        if(collision(player, key)){
            keyIsTaken = true;
            std::cout << "Picked up key!" << std::endl;
        }
    }


    ///--- Update Enemies ---///

    for(unsigned int index = 0; index < enemyCount; index++)
        enemyList[index].update(ElapsedTime, obstacleList);


    ///--- Check if player collides any enemy ---///

    for(unsigned int index = 0; index < enemyCount; index++){
        if(collision(player, enemyList[index].getEntity())){
            keyIsTaken = false;
            player.setPosition(startingPosition);
            break;
        }
    }


    ///--- Check if reached the finish tile ---///

    if(keyIsTaken){
        if(collision(player, finish_tile)){
            std::cout << "Finished level! Creating a new one..." << std::endl;

            player.setPosition(startingPosition);

            keyIsTaken = false;
            giveRandomPosition(key);

            gameArea.create();
            gameArea.setWalls(obstacleList);

            if(enemyCount < MAX_ENEMIES){
                enemyCount++;
                enemyList.push_back(Entity(texture_enemy));
            }
        }
    }


    ///--- Update View ---///

    view.setCenter(player.getPosition());
    window.setView(view);
}

void Game::render(){
    unsigned int elementCount = obstacleList.size();

    //Clear
    window.clear(sf::Color(31, 8, 125));

    //Draw
    window.draw(finish_tile);

    if(!keyIsTaken)
        window.draw(key);


    for(unsigned int index = 0; index < enemyCount; index++)
        window.draw(enemyList[index].getEntity());

    for(unsigned int i = 0; i < elementCount; i++)
        window.draw(obstacleList[i]);

    window.draw(player);

    //Display
    window.display();
}

