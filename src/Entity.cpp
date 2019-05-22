#include "Entity.h"


//Entity: CDtors


Entity::Entity() {}

Entity::Entity(const unsigned short & texture_number, const float & w, const float & h, const unsigned short & direction, const unsigned short & speed, const sf::Vector2f & position) {

    adjust_provider(&T, texture_number);

    set_sprite(w, h);

    set_direction(direction);

    set_speed(speed);

    set_position(position);
}

//Entity: Setters

void Entity::set_direction(const unsigned short & new_direction) {

    direction_ = new_direction;

    float old_Y_position = spr_.getTextureRect().top;

    spr_.setTextureRect(sf::IntRect(w_ * direction_, old_Y_position, w_, h_));

}

void Entity::set_speed(const unsigned short & new_speed) {

    speed_ = new_speed;

}

void Entity::adjust_provider(texture_keeper * keeper, unsigned short number) {

    provider_.set_data(keeper);
    provider_.set_number(number);

}

void Entity::set_sprite(const float & w, const float & h) {

    spr_.setTexture(provider_.get_texture());

    w_ = w;
    h_ = h;

    spr_.scale(scale / w_, scale / h_);

}

void Entity::set_position(const float & x, const float & y) {
    spr_.setPosition(x, y);
}

void Entity::set_position(const sf::Vector2f & new_position) {
    spr_.setPosition(new_position);
}

//Entity: Getters

sf::Sprite Entity::get_sprite() const {

    return spr_;

}

unsigned short Entity::get_direction() const {
    return direction_;
}

unsigned short Entity::get_speed() const {
    return speed_;
}

sf::FloatRect Entity::get_bounds() const {
    return spr_.getGlobalBounds();
}

sf::Vector2f Entity::get_position() const {
    return spr_.getPosition();
}

//Entity:Others

bool Entity::intersects(const Entity & E) {
    return get_sprite().getGlobalBounds().intersects(E.get_sprite().getGlobalBounds());
}


//Tank: CDtors


tank::tank(const unsigned short & direction, const sf::Vector2f & position,
         const unsigned short & speed, const float & w, const float & h) :
        Entity(1, w, h, direction, speed, position) {
            set_max_health(100);
            set_health(max_health_);
            set_main_cooldown(sf::seconds(1.f));
            set_time_of_last_launch(sf::seconds(-1.f));
        }


//Tank: Setters


void tank::set_main_cooldown(const sf::Time & new_cooldown) {
    main_cooldown_ = new_cooldown;
}

void tank::set_time_of_last_launch(const sf::Time & new_time) {
    time_of_last_launch_ = new_time;
}

void tank::set_health(const short & new_health) {
    health_ = new_health;
}

void tank::set_max_health(const short & new_health) {
    max_health_ = new_health;
}

void projectile::set_damage(const short & new_damage) {
    damage_ = new_damage;
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

void tank::color(const sf::Color & new_color) {
    spr_.setColor(new_color);
}

//Tank: Getters

sf::Time tank::get_main_cooldown() const {
    return main_cooldown_;
}

sf::Time tank::get_time_of_last_launch() const {
    return time_of_last_launch_;
}

short tank::get_health() const {
    return health_;
}

short tank::get_max_health() const {
    return max_health_;
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

//Tank: Other

void tank::be_hit(const short & damage) {
    health_ -= damage;
}

void tank::lose_bricks() {
    auto old_rect = spr_.getTextureRect();
    if(old_rect.top == 0) {
        old_rect.top += 5;
        spr_.setTextureRect(old_rect);
    }
}

//Projectile:CDtors

projectile::projectile(const unsigned short & direction, const sf::Vector2f & position,
               const unsigned short & speed, const float & w, const float & h) :
       Entity(2, w, h, direction, speed, position) {
    set_damage(25);
    }

//Projectile:Getters


short projectile::get_damage() const  {
    return damage_;
}

//Point:

point::point() {
    condition_ = 0.5;
    circle_.setFillColor(sf::Color::White);
    circle_.setRadius(scale);
    circle_.setPosition(sf::Vector2f((X - 2) * scale / 2, (Y - 2) * scale / 2));
    circle_.setOutlineThickness(5.f);
}

void point::be_captured(tank & t, const float & num, const float & delta) {
    if(circle_.getGlobalBounds().intersects(t.get_bounds())) {
        if(num)
            condition_ += delta;
        else
            condition_ -= delta;
        if(condition_ < 0.5) {
            if(condition_ < 0.25)
                circle_.setOutlineColor(sf::Color(30, 89, 69));
            else
                circle_.setOutlineColor(sf::Color(137, 172, 118));
        } else if (condition_ > 0.5) {
            if(condition_ > 0.75)
                circle_.setOutlineColor(sf::Color(0, 47, 85));
            else
                circle_.setOutlineColor(sf::Color(96, 110, 140));
        }
    }
}

float point::check_condition() const {
    return condition_;
}

sf::CircleShape point::get_circle() {
    return circle_;
}

bool point::is_captured() {
    return (condition_ <= 0 || condition_ >= 1);
}
