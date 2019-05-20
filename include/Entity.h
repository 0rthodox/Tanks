#ifndef ENTITY_H
#define ENTITY_H

#include "support.h"

extern int scale;

extern texture_keeper T;

class  main_window;

class Entity {

    friend main_window;

public:

//CD-tors

    Entity();

    Entity(const unsigned short &, const float &, const float &, const unsigned short &, const unsigned short &, const sf::Vector2f &);

    virtual ~Entity() = default;

//Setters:

    void adjust_provider(texture_keeper *, unsigned short);

    void set_direction(const unsigned short &);

    void set_position(const float &, const float &);

    void set_position(const sf::Vector2f &);

    void set_speed(const unsigned short &);

    void set_sprite(const float &, const float &);

//Getters:

    const sf::Sprite get_sprite();

    const unsigned short get_speed();

    const unsigned short get_direction();

    const sf::Vector2f get_position();

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

    projectile(const unsigned short & direction = 0, const sf::Vector2f & position = sf::Vector2f(),
               const unsigned short & speed = 400, const float & w = 5, const float & h = 5) :
       Entity(2, w, h, direction, speed, position) {}

};

class tank : public Entity {

    sf::Time main_cooldown_;

    sf::Time time_of_last_launch_;

    short health_;

public:

    tank(const unsigned short & = 0, const sf::Vector2f & = sf::Vector2f(),
         const unsigned short & = 120, const float & = 5, const float & = 5);

    void set_main_cooldown(const sf::Time &);

    void set_time_of_last_launch(const sf::Time &);

    void set_health(const short &);

    sf::Time get_main_cooldown() const;

    sf::Time get_time_of_last_launch() const;

    short get_health() const;

};

#endif // ENTITY_H
