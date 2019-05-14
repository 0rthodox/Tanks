#include "Entity.h"

Entity::Entity(sf::Texture & texture, float w, float h, unsigned short direction) : w_(w), h_(h) {

    spr_.setTexture(texture);

    set_direction(direction);

}

void Entity::set_direction(unsigned short new_direction) {

    direction_ = new_direction;

    spr_.setTextureRect(sf::IntRect(w_ * direction_, 0, w_, h_));

}

void tank::load_ammo(projectile prj, short amount) {

    ammo_.assign(amount, prj);

}

void Entity::draw(sf::RenderWindow & window) {
    window.draw(spr_);
}
