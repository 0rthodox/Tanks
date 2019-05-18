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

    Entity(unsigned short, float, float, unsigned short, unsigned short);

    void adjust_provider(texture_keeper *, unsigned short);

    void set_direction(const unsigned short &);

    void set_speed(const unsigned short &);

    void set_sprite(const float &, const float &);

    void move(unsigned short);

    const sf::Sprite get_sprite();

    const unsigned short get_speed();

    const unsigned short get_direction();

    void update_impulse(const sf::Vector2f &);

    sf::Vector2f get_impulse();

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

    projectile(float w = 5, float h = 5, unsigned short direction = 0, unsigned short speed = 7) :
       Entity(2, w, h, direction, speed) {}

};

class tank : public Entity {

    std::vector<projectile> ammo_;
    std::list<Entity *> loaded_;

public:

    tank(float w = 5, float h = 5, unsigned short direction = 0, unsigned short speed = 3) :
        Entity(1, w, h, direction, speed), ammo_(3) {}

    void load_ammo();

    void shoot(std::list<Entity *> &);

    const unsigned short check_loaded();

};

#endif // ENTITY_H
