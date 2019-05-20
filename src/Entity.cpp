#include "Entity.h"

Entity::Entity() {}

Entity::Entity(const unsigned short & texture_number, const float & w, const float & h, const unsigned short & direction, const unsigned short & speed, const sf::Vector2f & position) {

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

void Entity::set_position(const float & x, const float & y) {
    spr_.setPosition(x, y);
}

void Entity::set_position(const sf::Vector2f & new_position) {
    spr_.setPosition(new_position);
}

const sf::Vector2f Entity::get_position() {
    return spr_.getPosition();
}

tank::tank(const unsigned short & direction, const sf::Vector2f & position,
         const unsigned short & speed, const float & w, const float & h) :
        Entity(1, w, h, direction, speed, position) {
            set_main_cooldown(sf::seconds(1.f));
            set_time_of_last_launch(sf::seconds(-1.f));
        }

void tank::set_main_cooldown(const sf::Time & new_cooldown) {
    main_cooldown_ = new_cooldown;
}

void tank::set_time_of_last_launch(const sf::Time & new_time) {
    time_of_last_launch_ = new_time;
}

sf::Time tank::get_main_cooldown() const {
    return main_cooldown_;
}

sf::Time tank::get_time_of_last_launch() const {
    return time_of_last_launch_;
}

void tank::set_health(const short & new_health) {
    health_ = new_health;
}

short tank::get_health() const {
    return health_;
}
