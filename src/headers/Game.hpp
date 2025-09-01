#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <random>
#include <fstream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "EntityManager.hpp"
#include "Entity.hpp"

// config data holder
struct WindowConfig
{
    int W, H, FPS, SCR;
};
struct FontConfig
{
    std::string FS;
    int S, R, G, B;
};
struct PlayerConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
    float S;
};
struct EnemyConfig
{
    int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI;
    float SMIN, SMAX;
};
struct BulletConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L, C;
    float S;
};
struct SpBulletConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L, C, P;
    float S;
};

class Game
{
private:
    // init window variable
    sf::RenderWindow window;
    sf::Event ev;
    sf::Font m_font;
    sf::Text m_text;

    // game entities
    std::shared_ptr<Entity> m_player;
    EntityManager m_entities;

    // game variable
    int score = 0;
    int lastEnemySpawned = 0;
    int lastBulletSpawned = 0;
    int lastSpecialSpawned = 0;
    int currentFrame = 0;
    int m_fontOffSet = 50;
    bool running = true;

    // config data holder
    WindowConfig m_windowConfig;
    FontConfig m_fontConfig;
    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;
    SpBulletConfig m_spBulletConfig;

    // initial function
    void init();
    void polEv();
    void m_movement();
    sf::Vector2f m_mosPos();
    int randNumber(int min, int max);

    // spawning of entities
    void spawnEnemy();
    void spawnPlayer();
    void spawnBullet(std::shared_ptr<Entity> e, const sf::Vector2f &target);
    void spawnParticle(std::shared_ptr<Entity> e);
    void spawnSpecial(std::shared_ptr<Entity> e);
    void spawnText(sf::Vector2f loc, std::string text);

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
