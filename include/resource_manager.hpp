#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>

template<typename RESOURCE,typename IDENTIFIER = int>
class ResourceManager {
  public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    ResourceManager() = default;

    template<typename ... Args>
    void load(const IDENTIFIER& id,Args&& ... args);

    RESOURCE& get(const IDENTIFIER& id)const;

  private:
    std::unordered_map<IDENTIFIER,std::unique_ptr<RESOURCE>> _map;
};

template<typename IDENTIFIER>
class ResourceManager<sf::Music,IDENTIFIER> {
  public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    ResourceManager() = default;

    template<typename ... Args>
    void load(const IDENTIFIER& id,Args&& ... args);

    sf::Music& get(const IDENTIFIER& id)const;

  private:
    std::unordered_map<IDENTIFIER,std::unique_ptr<sf::Music>> _map;
};

#include "resource_manager.inl"

#endif
