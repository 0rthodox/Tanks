#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include "support.h"

extern texture_keeper T;

class Entity {

public:

    Entity();

    Entity(unsigned short texture_number, float w, float h, unsigned short direction, unsigned short speed);

    void set_direction(unsigned short new_direction);

    void set_speed(unsigned short new_speed);

    void set_sprite();

    void adjust_provider(texture_keeper * keeper, unsigned short number);

    sf::Sprite get_sprite();

    void set_size_of_sprite(float w, float h);

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

    void load_ammo(projectile prj, short amount);

};

#endif // ENTITY_H
