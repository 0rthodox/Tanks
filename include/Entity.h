#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


class Entity {

public:

    Entity(sf::Texture & texture, float w, float h, unsigned short direction);

    void set_direction(unsigned short new_direction);

    void draw(sf::RenderWindow window);

protected:

    float w_;
    float h_;


    sf::Sprite spr_;

    unsigned short direction_;

};

class projectile : public Entity {

    short speed_;

public:

    projectile(sf::Texture & texture, float w, float h, unsigned short direction, short speed) :
        Entity(texture, w, h, direction), speed_(speed) {}

};

class tank : public Entity {

    std::vector<projectile> ammo_;

public:

    void load_ammo(projectile prj, short amount);

};

#endif // ENTITY_H
