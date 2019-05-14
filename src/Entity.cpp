#include "Entity.h"

Entity::Entity(unsigned short texture_number, float w, float h, unsigned short direction, unsigned short speed) {

    set_direction(direction);

    set_speed(speed);

    adjust_provider(&T, texture_number);

    set_sprite();

    set_size_of_sprite(w, h);

}

void Entity::set_direction(unsigned short new_direction) {

    direction_ = new_direction;

    spr_.setTextureRect(sf::IntRect(w_ * direction_, 0, w_, h_));

}

void Entity::set_speed(unsigned short new_speed) {

    speed_ = new_speed;

}

void tank::load_ammo(projectile prj, short amount) {

    ammo_.assign(amount, prj);

}

void Entity::adjust_provider(texture_keeper * keeper, unsigned short number) {

    provider_.set_data(keeper);
    provider_.set_number(number);

}

sf::Sprite Entity::get_sprite() {

    return spr_;

}

void Entity::set_sprite() {

    spr_.setTexture(provider_.get_texture());

}

void Entity::set_size_of_sprite(float w, float h) {

    w_ = w;
    h_ = h;

}
