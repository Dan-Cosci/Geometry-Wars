#include <EntityManager.hpp>

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
    for (auto &e : this->m_que)
    {
        this->m_entities.push_back(e);
        this->m_entityMap[e->tag()].push_back(e);
    }
    this->m_que.clear();

    this->m_entities.erase(std::remove_if(
                               this->m_entities.begin(), this->m_entities.end(),
                               [](const std::shared_ptr<Entity> &e)
                               { return !e->isActive(); }),
                           this->m_entities.end());

    for (auto &[tag, vec] : this->m_entityMap)
    {
        vec.erase(std::remove_if(
                      vec.begin(), vec.end(),
                      [](const std::shared_ptr<Entity> &e)
                      { return !e->isActive(); }),
                  vec.end());
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    auto e = std::shared_ptr<Entity>(new Entity(this->m_totalEntities++, tag));
    this->m_que.push_back(e);
    return e;
}

EntityVec &EntityManager::getEntities()
{
    return this->m_entities;
}

EntityVec &EntityManager::getEntities(const std::string &tag)
{
    return this->m_entityMap[tag];
}
