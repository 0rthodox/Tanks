#include "support.h"

void texture_manager::set_data(texture_keeper * data) {
    data_ = data;
}

void texture_manager::set_number(unsigned short number) {
    number_ = number;
}

texture_manager::texture_manager(texture_keeper * data, unsigned short number) {
    std::cout << "Initializing texture manager" << std::endl;
    set_data(data);
    set_number(number);
}

sf::Texture & texture_manager::get_texture() {
    return data_->data_.at(number_);
}

texture_keeper::texture_keeper(int k) {
    std::string name;
    for(int i = 0; i < k; ++i) {
        name += "A";
        sf::Image I;
        I.loadFromFile("images/" + name + ".png");
        I.createMaskFromColor(sf::Color::White);
        sf::Texture T;
        T.loadFromImage(I);
        data_.push_back(T);
    }
    std::cout << data_.size();

}

sf::Vector2f check_bounds(const sf::Vector2f & position , const short & xlim, const short & ylim) {

    float dx = 0, dy = 0;

    if (position.x < 0)
        dx = -position.x;
    else if (position.x > (xlim - 1) * scale)
        dx = (xlim - 1) * scale - position.x;

    if (position.y < 0)
        dy = -position.y;
    else if (position.y > (ylim - 1) * scale)
        dy = (ylim - 1) * scale - position.y;

    return sf::Vector2f(dx, dy);

}

keys::keys(const sf::Keyboard::Key & up, const sf::Keyboard::Key & left, const sf::Keyboard::Key & down,
           const sf::Keyboard::Key & right, const sf::Keyboard::Key & launch, const sf::Keyboard::Key & shoot) {
    set_up(up);
    set_left(left);
    set_down(down);
    set_right(right);
    set_launch(launch);
    set_shoot(shoot);
}

void keys::set_up(const sf::Keyboard::Key & new_key) {
    Up_ = new_key;
}

void keys::set_left(const sf::Keyboard::Key & new_key) {
    Left_ = new_key;
}

void keys::set_down(const sf::Keyboard::Key & new_key) {
    Down_ = new_key;
}

void keys::set_right(const sf::Keyboard::Key & new_key) {
    Right_ = new_key;
}

void keys::set_launch(const sf::Keyboard::Key & new_key) {
    Launch_ = new_key;
}

void keys::set_shoot(const sf::Keyboard::Key & new_key) {
    Shoot_ = new_key;
}


sf::Keyboard::Key keys::get_up() const {
    return Up_;
}

sf::Keyboard::Key keys::get_left() const {
    return Left_;
}

sf::Keyboard::Key keys::get_down() const {
    return Down_;
}

sf::Keyboard::Key keys::get_right() const {
    return Right_;
}

sf::Keyboard::Key keys::get_launch() const {
    return Launch_;
}

sf::Keyboard::Key keys::get_shoot() const {
    return Shoot_;
}
