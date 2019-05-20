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

sf::Sprite Entity::get_sprite() const {

    return spr_;

}

void Entity::set_sprite(const float & w, const float & h) {

    spr_.setTexture(provider_.get_texture());

    w_ = w;
    h_ = h;

    spr_.scale(scale / w_, scale / h_);

}

unsigned short Entity::get_direction() const {
    return direction_;
}

unsigned short Entity::get_speed() const {
    return speed_;
}

void Entity::set_position(const float & x, const float & y) {
    spr_.setPosition(x, y);
}

void Entity::set_position(const sf::Vector2f & new_position) {
    spr_.setPosition(new_position);
}

sf::Vector2f Entity::get_position() const {
    return spr_.getPosition();
}

tank::tank(const unsigned short & direction, const sf::Vector2f & position,
         const unsigned short & speed, const float & w, const float & h) :
        Entity(1, w, h, direction, speed, position) {
            set_health(100);
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

void tank::be_hit(const short & damage) {
    health_ -= damage;
}

void projectile::set_damage(const short & new_damage) {
    damage_ = new_damage;
}

short projectile::get_damage() const  {
    return damage_;
}

projectile::projectile(const unsigned short & direction, const sf::Vector2f & position,
               const unsigned short & speed, const float & w, const float & h) :
       Entity(2, w, h, direction, speed, position) {
    set_damage(50);
    }


bool Entity::intersects(const Entity & E) {
    return get_sprite().getGlobalBounds().intersects(E.get_sprite().getGlobalBounds());
}

void tank::set_keys(const sf::Keyboard::Key & up, const sf::Keyboard::Key & left, const sf::Keyboard::Key & down,
                    const sf::Keyboard::Key & right, const sf::Keyboard::Key & launch, const sf::Keyboard::Key & shoot) {
    set_up(up);
    set_left(left);
    set_down(down);
    set_right(right);
    set_launch(launch);
    set_shoot(shoot);
}

void tank::set_up(const sf::Keyboard::Key & new_key) {
    keys.Up_ = new_key;
}

void tank::set_left(const sf::Keyboard::Key & new_key) {
    keys.Left_ = new_key;
}

void tank::set_down(const sf::Keyboard::Key & new_key) {
    keys.Down_ = new_key;
}

void tank::set_right(const sf::Keyboard::Key & new_key) {
    keys.Right_ = new_key;
}

void tank::set_launch(const sf::Keyboard::Key & new_key) {
    keys.Launch_ = new_key;
}

void tank::set_shoot(const sf::Keyboard::Key & new_key) {
    keys.Shoot_ = new_key;
}


sf::Keyboard::Key tank::get_up() const {
    return keys.Up_;
}

sf::Keyboard::Key tank::get_left() const {
    return keys.Left_;
}

sf::Keyboard::Key tank::get_down() const {
    return keys.Down_;
}

sf::Keyboard::Key tank::get_right() const {
    return keys.Right_;
}

sf::Keyboard::Key tank::get_launch() const {
    return keys.Launch_;
}

sf::Keyboard::Key tank::get_shoot() const {
    return keys.Shoot_;
}
