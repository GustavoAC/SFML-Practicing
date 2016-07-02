#ifndef _ACTION_MAP_HPP
#define _ACTION_MAP_HPP

//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
#include <unordered_map>
#include "configuration.hpp"

template<typename T = int>
class ActionMap {
  public:
    ActionMap(const ActionMap<T>&) = delete;
    ActionMap<T>& operator=(const ActionMap<T>&) = delete;

    ActionMap() = default;

    void map(const T& key,const Action& action);
    const Action& get(const T& key) const;

  private:
    std::unordered_map<T,Action> _map;
};

#include "action_map.inl"

#endif
