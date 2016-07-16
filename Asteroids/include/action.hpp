#ifndef _ACTION_HPP_
#define _ACTION_HPP_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstring>

template <class T> class ActionTarget;

class Action {
  public:
    enum Type {
        RealTime=1,
        Pressed=1<<1,
        Released=1<<2
    };

    Action(const Action& other);
    Action& operator=(const Action& other);

    Action(const sf::Keyboard::Key& key, int type=Type::RealTime|Type::Pressed);
    Action(const sf::Mouse::Button& button, int type=Type::RealTime|Type::Pressed);

    bool test() const;

    bool operator==(const sf::Event& event) const;
    bool operator==(const Action& other) const;

  private:
    friend class ActionTarget<int>;
    sf::Event _event;
    int _type;
};

#endif
