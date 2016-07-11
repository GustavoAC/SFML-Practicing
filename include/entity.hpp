#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <SFML/Graphics.hpp>
#include "configuration.hpp"

class World;

class Entity : public sf::Drawable {
  public:
    //Constructors
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity(Configuration::Textures tex_id, World& world);
    virtual ~Entity();

    //Helpers
    virtual bool isAlive() const;
    const sf::Vector2f& getPosition() const;

    template<typename ... Args>
    void setPosition(Args&& ... args) {
        _sprite.setPosition(std::forward<Args>(args)...);
    }
    virtual bool isCollide(const Entity& other) const = 0;

    //Updates
    virtual void update(sf::Time deltaTime) = 0;
    virtual void onDestroy();

  protected:
    friend class Meteor;
    friend class Player;
    friend class Saucer;
    friend class ShootPlayer;
    friend class ShootSaucer;

    sf::Sprite _sprite;
    sf::Vector2f _impulse;
    World& _world;
    bool _alive;

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
