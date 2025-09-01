
#include "Game.hpp"

void Game::init()
{
    // reads config file
    std::ifstream file("game.config");
    if (!file.is_open())
    {
        std::cerr << "File not found!\n";
        return;
    }
    std::string r;
    file >> r >> this->m_windowConfig.W >> this->m_windowConfig.H >> this->m_windowConfig.FPS >> this->m_windowConfig.SCR;
    std::cout << "loaded " + r + " config\n";
    file >> r >> this->m_fontConfig.FS >> this->m_fontConfig.S >> this->m_fontConfig.R >> this->m_fontConfig.G >> this->m_fontConfig.B;
    std::cout << "loaded " + r + " config\n";
    file >> r >> this->m_playerConfig.SR >> this->m_playerConfig.CR >> this->m_playerConfig.S >> this->m_playerConfig.FR >> this->m_playerConfig.FG >> this->m_playerConfig.FB >> this->m_playerConfig.OR >> this->m_playerConfig.OG >> this->m_playerConfig.OB >> this->m_playerConfig.OT >> this->m_playerConfig.V;
    std::cout << "loaded " + r + " config\n";
    file >> r >> this->m_enemyConfig.SR >> this->m_enemyConfig.CR >> this->m_enemyConfig.SMIN >> this->m_enemyConfig.SMAX >> this->m_enemyConfig.OR >> this->m_enemyConfig.OG >> this->m_enemyConfig.OB >> this->m_enemyConfig.OT >> this->m_enemyConfig.VMIN >> this->m_enemyConfig.VMAX >> this->m_enemyConfig.L >> this->m_enemyConfig.SI;
    std::cout << "loaded " + r + " config\n";
    file >> r >> this->m_bulletConfig.SR >> this->m_bulletConfig.CR >> this->m_bulletConfig.S >> this->m_bulletConfig.FR >> this->m_bulletConfig.FG >> this->m_bulletConfig.FB >> this->m_bulletConfig.OR >> this->m_bulletConfig.OG >> this->m_bulletConfig.OB >> this->m_bulletConfig.OT >> this->m_bulletConfig.V >> this->m_bulletConfig.L >> this->m_bulletConfig.C;
    std::cout << "loaded " + r + " config\n";
    file >> r >> this->m_spBulletConfig.SR >> this->m_spBulletConfig.CR >> this->m_spBulletConfig.S >> this->m_spBulletConfig.FR >> this->m_spBulletConfig.FG >> this->m_spBulletConfig.FB >> this->m_spBulletConfig.OR >> this->m_spBulletConfig.OG >> this->m_spBulletConfig.OB >> this->m_spBulletConfig.OT >> this->m_spBulletConfig.V >> this->m_spBulletConfig.L >> this->m_spBulletConfig.C >> this->m_spBulletConfig.P;
    std::cout << "loaded " + r + " config\n";

    this->window.create(sf::VideoMode(this->m_windowConfig.W, this->m_windowConfig.H), "Geometry Wars");

    // initializes player
    spawnPlayer();
    if (!this->m_font.loadFromFile(this->m_fontConfig.FS))
        std::cout << "Font not found\n";
    spawnText(sf::Vector2f(this->window.getSize().x / this->m_fontOffSet, this->window.getSize().y / this->m_fontOffSet), "Hello");
}

void Game::polEv()
{
    while (this->window.pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            this->window.close();
        }
        s_userinput();
    }
}

void Game::m_movement()
{
    auto &i = this->m_player->input;
    auto &t = this->m_player->transform;
    if (i->up)
        t->pos.y -= t->vel.y;
    if (i->down)
        t->pos.y += t->vel.y;
    if (i->right)
        t->pos.x += t->vel.x;
    if (i->left)
        t->pos.x -= t->vel.x;
    if (i->shoot && currentFrame - this->lastBulletSpawned >= this->m_bulletConfig.C)
        spawnBullet(this->m_player, m_mosPos());
    if (i->special && currentFrame - this->lastSpecialSpawned >= 10)
        spawnSpecial(this->m_player);
}

sf::Vector2f Game::m_mosPos()
{
    return (sf::Vector2f)sf::Mouse::getPosition(this->window);
}

int Game::randNumber(int min, int max)
{
    // I dont know how to explain this quite honestly
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

void Game::spawnEnemy()
{
    auto e = this->m_entities.addEntity("enemy");
    e->transform = std::make_shared<c_transform>(
        sf::Vector2f(randNumber(100, (int)this->window.getSize().x - 100),
                     randNumber(100, (int)this->window.getSize().y - 100)),
        sf::Vector2f(randNumber(this->m_enemyConfig.SMIN, this->m_enemyConfig.SMAX),
                     randNumber(this->m_enemyConfig.SMIN, this->m_enemyConfig.SMAX)),
        3);
    e->shape = std::make_shared<c_shape>(
        this->m_enemyConfig.SR,
        randNumber(this->m_enemyConfig.VMIN, this->m_enemyConfig.VMAX),
        sf::Color(randNumber(0, 255), randNumber(0, 255), randNumber(0, 255)),
        sf::Color(this->m_enemyConfig.OR, this->m_enemyConfig.OG, this->m_enemyConfig.OB),
        this->m_enemyConfig.OT);
    e->collision = std::make_shared<c_collision>(this->m_enemyConfig.CR);
}

void Game::spawnPlayer()
{
    this->m_player = this->m_entities.addEntity("player");
    this->m_player->shape = std::make_shared<c_shape>(
        this->m_playerConfig.SR,
        this->m_playerConfig.V,
        sf::Color(this->m_playerConfig.FR, this->m_playerConfig.FG, this->m_playerConfig.FB),
        sf::Color(this->m_playerConfig.OR, this->m_playerConfig.OG, this->m_playerConfig.OB),
        1.4f);
    this->m_player->transform = std::make_shared<c_transform>(
        sf::Vector2f(this->window.getSize().x / 2, this->window.getSize().y / 2),
        sf::Vector2f(this->m_playerConfig.S, this->m_playerConfig.S),
        5.0f);
    this->m_player->input = std::make_shared<c_input>();
    this->m_player->collision = std::make_shared<c_collision>(this->m_playerConfig.CR);
}

void Game::spawnBullet(std::shared_ptr<Entity> e, const sf::Vector2f &target)
{
    auto b = this->m_entities.addEntity("bullet");
    auto &bc = this->m_bulletConfig;
    b->lifespan = std::make_shared<c_lifeSpan>(bc.L);
    b->shape = std::make_shared<c_shape>(
        bc.SR,
        bc.V,
        sf::Color(bc.FR, bc.FG, bc.FB),
        sf::Color(bc.OR, bc.OG, bc.OB),
        bc.OT);

    // angle calculation of the bullet speed
    auto a = target - e->transform->pos;
    float dis = std::sqrt(a.x * a.x + a.y * a.y);
    sf::Vector2f n_vel((a.x / dis) * bc.S, (a.y / dis) * bc.S);
    b->transform = std::make_shared<c_transform>(e->transform->pos, n_vel, 0);
    b->collision = std::make_shared<c_collision>(bc.CR);
    lastBulletSpawned = currentFrame;
}

void Game::spawnParticle(std::shared_ptr<Entity> e)
{
    EntityVec ex;
    auto &s = e->shape;
    auto &t = e->transform;
    for (size_t i = 0; i < s->shape.getPointCount(); i++)
    {
        auto ep = this->m_entities.addEntity("particle");
        ep->shape = std::make_shared<c_shape>(s->shape.getRadius() * 0.6,
                                              s->shape.getPointCount(),
                                              s->baseColor,
                                              s->outlineColor,
                                              s->shape.getOutlineThickness());
        ep->lifespan = std::make_shared<c_lifeSpan>(30);

        /*
            okay just to be honest
            I do not know how the fuck does this calculation does it
            to make it short
            it gets the angle of each midpoint of the side of the polygon
            converts to point
            then normalizes the speed
        */
        float step = 2 * M_PI / s->shape.getPointCount();
        float angle = i * step + step / 2.0f;
        float x = t->pos.x + s->shape.getRadius() * std::cos(angle);
        float y = t->pos.y + s->shape.getRadius() * std::sin(angle);
        sf::Vector2f target(x, y);
        auto a = target - t->pos;
        float dis = std::sqrt(a.x * a.x + a.y * a.y);
        sf::Vector2f n_vel((a.x / dis) * this->m_enemyConfig.SMAX, (a.y / dis) * this->m_enemyConfig.SMAX);
        ep->transform = std::make_shared<c_transform>(t->pos, n_vel, t->angle);
        ex.push_back(ep);
    }
}

void Game::spawnSpecial(std::shared_ptr<Entity> e)
{
    EntityVec ex;
    auto &b = this->m_spBulletConfig;
    auto &t = e->transform;
    for (size_t i = 0; i < this->m_spBulletConfig.P; i++)
    {
        auto ep = this->m_entities.addEntity("special_bullet");
        ep->shape = std::make_shared<c_shape>(b.SR,
                                              b.V,
                                              sf::Color(b.FR, b.FG, b.FB),
                                              sf::Color(b.OR, b.OG, b.OB),
                                              b.OT);
        ep->lifespan = std::make_shared<c_lifeSpan>(b.L);

        /*
            okay just to be honest
            I do not know how the fuck does this calculation does it
            to make it short
            it gets the angle of each midpoint of the side of the polygon
            converts to point
            then normalizes the speed
        */
        float step = 2 * M_PI / ep->shape->shape.getPointCount();
        float angle = i * step + step / 2.0f;
        float x = t->pos.x + ep->shape->shape.getRadius() * std::cos(angle);
        float y = t->pos.y + ep->shape->shape.getRadius() * std::sin(angle);
        sf::Vector2f target(x, y);
        auto a = target - t->pos;
        float dis = std::sqrt(a.x * a.x + a.y * a.y);
        sf::Vector2f n_vel((a.x / dis) * this->m_enemyConfig.SMAX, (a.y / dis) * this->m_enemyConfig.SMAX);
        ep->transform = std::make_shared<c_transform>(t->pos, n_vel, t->angle);
        ep->collision = std::make_shared<c_collision>(b.CR);
        ex.push_back(ep);
        lastSpecialSpawned = currentFrame;
    }
}

void Game::spawnText(sf::Vector2f loc, std::string text)
{
    auto &f = this->m_fontConfig;
    this->m_text.setFont(this->m_font);
    this->m_text.setCharacterSize(f.S);
    this->m_text.setString(text);
    this->m_text.setFillColor(sf::Color(f.R, f.G, f.B));
    this->m_text.setPosition(loc);
}

void Game::s_render()
{
    this->window.clear(sf::Color::Black);
    for (auto &e : this->m_entities.getEntities("particle"))
    {
        this->window.draw(e->shape->shape);
    }
    for (auto &e : this->m_entities.getEntities("special_bullet"))
    {
        this->window.draw(e->shape->shape);
    }
    for (auto &e : this->m_entities.getEntities("bullet"))
    {
        this->window.draw(e->shape->shape);
    }
    for (auto &e : this->m_entities.getEntities("enemy"))
    {
        this->window.draw(e->shape->shape);
    }
    for (auto &e : this->m_entities.getEntities("player"))
    {
        this->window.draw(e->shape->shape);
    }
    this->window.draw(this->m_text);
    this->window.display();
}

void Game::s_enemyspawner()
{
    if (currentFrame % this->m_enemyConfig.SI == this->m_enemyConfig.SI - 1)
    {
        spawnEnemy();
    }
}

void Game::s_userinput()
{
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::W)
            this->m_player->input->up = true;
        if (ev.key.code == sf::Keyboard::S)
            this->m_player->input->down = true;
        if (ev.key.code == sf::Keyboard::A)
            this->m_player->input->left = true;
        if (ev.key.code == sf::Keyboard::D)
            this->m_player->input->right = true;
    }
    else if (ev.type == sf::Event::KeyReleased)
    {
        if (ev.key.code == sf::Keyboard::W)
            this->m_player->input->up = false;
        if (ev.key.code == sf::Keyboard::S)
            this->m_player->input->down = false;
        if (ev.key.code == sf::Keyboard::A)
            this->m_player->input->left = false;
        if (ev.key.code == sf::Keyboard::D)
            this->m_player->input->right = false;
    }

    // --- MOUSE HANDLING (for shooting) ---
    if (ev.type == sf::Event::MouseButtonPressed)
    {
        if (ev.mouseButton.button == sf::Mouse::Left)
            this->m_player->input->shoot = true;
        if (ev.mouseButton.button == sf::Mouse::Right)
            this->m_player->input->special = true;
    }
    else if (ev.type == sf::Event::MouseButtonReleased)
    {
        if (ev.mouseButton.button == sf::Mouse::Left)
            this->m_player->input->shoot = false;
        if (ev.mouseButton.button == sf::Mouse::Right)
            this->m_player->input->special = false;
    }
}

void Game::s_update()
{
    this->window.setFramerateLimit(60);

    // enemy update
    for (auto &e : this->m_entities.getEntities("enemy"))
    {
        auto &t = e->transform;
        auto &s = e->shape->shape;
        t->pos += t->vel;
        s.setPosition(t->pos);
        s.rotate(t->angle);
    }

    // special bullter
    for (auto &e : this->m_entities.getEntities("special_bullet"))
    {
        auto &t = e->transform;
        auto &s = e->shape->shape;
        t->pos += t->vel;
        s.setPosition(t->pos);
        s.rotate(t->angle);
    }

    // particle update
    for (auto &e : this->m_entities.getEntities("particle"))
    {
        auto &t = e->transform;
        auto &s = e->shape->shape;
        t->pos += t->vel;
        s.setPosition(t->pos);
        s.rotate(t->angle);
    }

    // bullet update
    for (auto &e : this->m_entities.getEntities("bullet"))
    {
        auto &t = e->transform;
        auto &s = e->shape->shape;
        t->pos += t->vel;
        s.setPosition(t->pos);
    }

    // player update
    for (auto &p : this->m_entities.getEntities("player"))
    {
        auto &t = p->transform;
        auto &s = p->shape->shape;
        s.setPosition(t->pos);
        s.rotate(t->angle);
    }
    currentFrame++;
}

void Game::s_lifespan()
{
    for (auto &e : this->m_entities.getEntities())
    {
        if (!e->lifespan)
            continue;
        auto &l = e->lifespan;
        auto &s = e->shape->shape;
        l->remaining--;
        auto col_f = s.getFillColor();
        col_f.a = (float)l->remaining / l->total * 255;
        s.setFillColor(col_f);

        auto col_o = s.getOutlineColor();
        col_o.a = (float)l->remaining / l->total * 255;
        s.setOutlineColor(col_o);
        if (e->lifespan->remaining <= 0)
        {
            e->destroy();
        }
    }
}

void Game::s_collision()
{
    for (auto &e : this->m_entities.getEntities("enemy"))
    {
        if (e->transform->pos.x > this->window.getSize().x || e->transform->pos.x < 0)
        {
            e->transform->vel.x = -e->transform->vel.x;
        }
        if (e->transform->pos.y > this->window.getSize().y || e->transform->pos.y < 0)
        {
            e->transform->vel.y = -e->transform->vel.y;
        }

        // collision with bullet
        for (auto &b : this->m_entities.getEntities("bullet"))
        {
            // check for enemy bullet collision
            int collision = (int)(e->collision->radius + b->collision->radius);
            auto &p = b->transform->pos;
            auto &en = e->transform->pos;
            int dis = (int)((p.x - en.x) * (p.x - en.x) + (p.y - en.y) * (p.y - en.y));
            if (dis < collision * collision)
            {
                e->destroy();
                spawnParticle(e);
                b->destroy();
            }
        }

        // collision for special
        for (auto &b : this->m_entities.getEntities("special_bullet"))
        {
            // check for enemy bullet collision
            int collision = (int)(e->collision->radius + b->collision->radius);
            auto &p = b->transform->pos;
            auto &en = e->transform->pos;
            int dis = (int)((p.x - en.x) * (p.x - en.x) + (p.y - en.y) * (p.y - en.y));
            if (dis < collision * collision)
            {
                e->destroy();
                spawnParticle(e);
            }
        }

        // check for player collision
        int collision = (int)(e->collision->radius + this->m_player->collision->radius);
        auto &p = this->m_player->transform->pos;
        auto &en = e->transform->pos;
        int dis = (int)((p.x - en.x) * (p.x - en.x) + (p.y - en.y) * (p.y - en.y));
        if (dis < collision * collision)
        {
            spawnParticle(this->m_player);
            this->m_player->destroy();
            spawnPlayer();
        }
    }
}

Game::Game()
{
    init();
}

Game::~Game()
{
}

void Game::Run()
{
    while (this->window.isOpen())
    {
        // update the ques of the entitymanager
        this->m_entities.update();
        polEv();

        // game logic checking
        s_lifespan();
        s_collision();
        s_enemyspawner();
        s_userinput();
        m_movement();

        // rendering and animations
        s_update();
        s_render();
    }
}
