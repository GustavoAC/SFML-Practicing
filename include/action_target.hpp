#ifndef _ACTION_TARGET_HPP_
#define _ACTION_TARGET_HPP_

#include <functional>
#include <utility>
#include <list>
#include "action_map.hpp"

template<class T = int>
class ActionTarget {
  public:
    // Deletes copy constructors
    ActionTarget(const ActionTarget<T>&) = delete;
    ActionTarget<T>& operator=(const ActionTarget<T>&) = delete;

    using FuncType = std::function<void(const sf::Event&)>;

    ActionTarget(const ActionMap<T>& map);

    bool processEvent(const sf::Event& event) const;
    void processEvents()const;

    void bind(const T& key, const FuncType& callback);
    void unbind(const T& key);

  private:
    std::list<std::pair<T,FuncType>> _eventsRealTime;
    std::list<std::pair<T,FuncType>> _eventsPoll;
    const ActionMap<T>& _actionMap;
};

#include "action_target.inl"

#endif
