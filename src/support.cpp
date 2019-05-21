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

void effect::check(const sf::Time & curr_time) {
    if(curr_time - last_cast_ >= cooldown_)
        purify();
}
