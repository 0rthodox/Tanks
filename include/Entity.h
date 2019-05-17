#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include "support.h"

extern int scale;

extern texture_keeper T;

class Entity {

public:

    Entity();

    Entity(unsigned short texture_number, float w, float h, unsigned short direction, unsigned short speed);

    void adjust_provider(texture_keeper * keeper, unsigned short number);

    void set_direction(unsigned short new_direction);

    void set_speed(unsigned short new_speed);

    void set_sprite(float w, float h);

    void move(unsigned short new_direction);

    sf::Sprite get_sprite();

protected:

    float w_;
    float h_;

    sf::Sprite spr_;

    unsigned short direction_;

    unsigned short speed_;

    texture_manager provider_;

};

class projectile : public Entity {

public:

    projectile();

};

class tank : public Entity {

    std::list<projectile> ammo_;

public:

    tank(float w = 5, float h = 5, unsigned short direction = 0, unsigned short speed = 1) :
        Entity(1, w, h, direction, speed) {}

    void load_ammo(projectile prj, short amount);

    void shoot();

};

#endif // ENTITY_H
