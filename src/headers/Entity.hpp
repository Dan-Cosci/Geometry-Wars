#pragma once
#include <iostream>
#include <memory>

#include "Components.hpp"

class Entity
{
private:
    friend class EntityManager;
    bool m_active = true;
    size_t m_id = 0;
    std::string m_tag = "default";

    // private constructor
    Entity() {};
    Entity(size_t i, const std::string &t)
        : m_id(i), m_tag(t) {};

public:
    std::shared_ptr<c_shape> shape;
    std::shared_ptr<c_transform> transform;
    std::shared_ptr<c_lifeSpan> lifespan;
    std::shared_ptr<c_input> input;
    std::shared_ptr<c_score> score;
    std::shared_ptr<c_collision> collision;
    std::shared_ptr<c_health> health;

    bool isActive() const { return this->m_active; }
    void destroy() { this->m_active = false; }
    const std::string &tag() const { return this->m_tag; }
    const size_t id() const { return this->m_id; }
};
