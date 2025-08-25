#pragma once
#include <iostream>
#include <random>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "EntityManager.hpp"
#include "Entity.hpp"

class Game
{
private:
    // init window factors
    sf::RenderWindow window;
    sf::Event ev;

    // game variables
    std::shared_ptr<Entity> m_player;
    EntityManager m_entities;

    int score = 0;
    int lastEnemySpawned = 0;
    int currentFrame = 0;
    bool running = true;

    // initial function
    void init();
    void polEv();
    void m_movement();

    // Systems
    void s_render();
    void s_enemyspawner();
    void s_userinput();
    void s_update();
    void s_lifespan();
    void s_collision();

public:
    // constructor and desctrutor
    Game();
    ~Game();
    void Run();
};
