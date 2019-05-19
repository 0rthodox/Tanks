#include "Entity.h"

Entity::Entity() {}

Entity::Entity(const unsigned short & texture_number, const float & w, const float & h, const unsigned short & direction, const unsigned short & speed, const sf::Vector2f & position) : impulse_() {

    adjust_provider(&T, texture_number);

    set_sprite(w, h);

    set_direction(direction);

    set_speed(speed);

    set_position(position);
}

void Entity::set_direction(const unsigned short & new_direction) {

    direction_ = new_direction;

    spr_.setTextureRect(sf::IntRect(w_ * direction_, 0, w_, h_));

}

void Entity::set_speed(const unsigned short & new_speed) {

    speed_ = new_speed;

}

void Entity::adjust_provider(texture_keeper * keeper, unsigned short number) {

    provider_.set_data(keeper);
    provider_.set_number(number);

}

const sf::Sprite Entity::get_sprite() {

    return spr_;

}

void Entity::set_sprite(const float & w, const float & h) {

    spr_.setTexture(provider_.get_texture());

    w_ = w;
    h_ = h;

    spr_.scale(scale / w_, scale / h_);

}

const unsigned short Entity::get_direction() {
    return direction_;
}

const unsigned short Entity::get_speed() {
    return speed_;
}

void Entity::update_impulse(const sf::Vector2f & dp) {

    impulse_ += dp;

}

sf::Vector2f Entity::get_impulse() {

    return impulse_;

}

void Entity::set_position(const float & x, const float & y) {
    spr_.setPosition(x, y);
}

void Entity::set_position(const sf::Vector2f & new_position) {
    spr_.setPosition(new_position);
}

const sf::Vector2f Entity::get_position() {
    return spr_.getPosition();
}

projectile tank::shoot() {
    return projectile(direction_, get_position());
}
