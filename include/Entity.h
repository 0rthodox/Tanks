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
    Entity(const unsigned short &, const float &, const float &,
           const unsigned short &, const unsigned short &, const sf::Vector2f &);
    virtual ~Entity() = default;

//Setters:
    void adjust_provider(texture_keeper *, unsigned short);
    void set_direction(const unsigned short &);
    void set_position(const float &, const float &);
    void set_position(const sf::Vector2f &);
    void set_speed(const unsigned short &);
    void set_sprite(const float &, const float &);

//Getters:
    sf::Sprite get_sprite() const;
    unsigned short get_speed() const;
    unsigned short get_direction() const;
    sf::Vector2f get_position() const;

//Other:
    bool intersects(const Entity &);

protected:
    float w_;
    float h_;
    sf::Sprite spr_;
    unsigned short direction_;
    unsigned short speed_;
    texture_manager provider_;
};

class projectile : public Entity {

    short damage_;

public:
    projectile(const unsigned short & = 0, const sf::Vector2f & = sf::Vector2f(),
               const unsigned short & = 400, const float & = 5, const float & = 5);
    void set_damage(const short &);
    short get_damage() const ;


};

class tank : public Entity {

    sf::Time main_cooldown_;
    sf::Time time_of_last_launch_;
    short health_;

public:

//CD-tors:
    tank(const unsigned short & = 0, const sf::Vector2f & = sf::Vector2f(),
         const unsigned short & = 120, const float & = 5, const float & = 5);

//Setters:
    void set_main_cooldown(const sf::Time &);
    void set_time_of_last_launch(const sf::Time &);
    void set_health(const short &);

//Getters:
    sf::Time get_main_cooldown() const;
    sf::Time get_time_of_last_launch() const;
    short get_health() const;

//Other:
    void be_hit(const short &);
};

#endif // ENTITY_H
