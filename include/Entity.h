#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include "support.h"

extern int scale;

extern texture_keeper T;

class  main_window;

class Entity {

    friend main_window;

public:

    Entity();

    Entity(const unsigned short &, const float &, const float &, const unsigned short &, const unsigned short &, const sf::Vector2f &);

    void adjust_provider(texture_keeper *, unsigned short);

    void set_direction(const unsigned short &);

    void set_position(const float &, const float &);

    void set_position(const sf::Vector2f &);

    void set_speed(const unsigned short &);

    void set_sprite(const float &, const float &);

    const sf::Sprite get_sprite();

    const unsigned short get_speed();

    const unsigned short get_direction();

    void update_impulse(const sf::Vector2f &);

    sf::Vector2f get_impulse();

    const sf::Vector2f get_position();

    virtual ~Entity() = default;

protected:

    float w_;
    float h_;

    sf::Vector2f impulse_;

    sf::Sprite spr_;

    unsigned short direction_;

    unsigned short speed_;

    texture_manager provider_;

};

class projectile : public Entity {

public:

    projectile(const unsigned short & direction = 0, const sf::Vector2f & position = sf::Vector2f(), const unsigned short & speed = 60, const float & w = 5, const float & h = 5) :
       Entity(2, w, h, direction, speed, position) {}

};

class tank : public Entity {

public:

    tank(const unsigned short & direction = 0, const sf::Vector2f & position = sf::Vector2f(),  const unsigned short & speed = 30, const float & w = 5, const float & h = 5) :
        Entity(1, w, h, direction, speed, position) {}

    projectile shoot();



};

#endif // ENTITY_H
