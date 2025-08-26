#pragma once
#include <SFML/Graphics.hpp>

class c_transform
{
public:
    sf::Vector2f vel = {0.0f, 0.0f};
    sf::Vector2f pos = {0.0f, 0.0f};
    float angle = 0;
    c_transform(const sf::Vector2f &p, const sf::Vector2f &v, float a)
        : vel(v), pos(p), angle(a) {}
};

class c_shape
{
public:
    sf::CircleShape shape;
    c_shape(float radius,
            int point,
            const sf::Color &fill,
            const sf::Color &outline,
            float thickness)
    {
        auto s = sf::CircleShape(radius);
        s.setFillColor(fill);
        s.setOutlineColor(outline);
        s.setOutlineThickness(thickness);
        s.setOrigin(radius, radius);
        if (!(point == 0))
            s.setPointCount(point);
        shape = s;
    }
};

class c_lifeSpan
{
public:
    int remaining = 0;
    int total = 0;
    c_lifeSpan(int t)
        : total(t), remaining(t) {}
};

class c_input
{
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;

    c_input() = default;
};

class c_collision
{
public:
    float radius = 0;
    c_collision(float r) : radius(r) {}
};

class c_score
{
public:
    int score = 0;
    c_score(int s) : score(s) {}
};
