#include "support.h"

void texture_manager::set_data(texture_keeper * data) {
    data_ = data;
}

void texture_manager::set_number(unsigned short number) {
    number_ = number;
}

texture_manager::texture_manager(texture_keeper * data, unsigned short number) {
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


//Class font


font::font() {
    if(!font_.loadFromFile("fonts/ARLRDBD.ttf"))
        std::cout << "Failed";
}

const sf::Font & font::get_font() {
    return font_;
}


//Inscription

inscription::inscription(const std::string & inscr, const sf::Vector2f & new_position, const sf::Color & new_color) : text_(inscr, F.get_font(), 2 * scale) {
    set_position(new_position);
    set_color(new_color);
    text_.setStyle(sf::Text::Regular);
}

void inscription::set_position(const sf::Vector2f & new_position) {
    text_.setPosition(new_position - sf::Vector2f(text_.getGlobalBounds().width / 2, text_.getGlobalBounds().height / 2));
}

sf::Text inscription::get() const {
    return text_;
}

void inscription::set_color(const sf::Color & new_color) {
    text_.setFillColor(new_color);
}

void inscription::flicker(const sf::Uint32 & smallest, const sf::Uint32 & biggest, const sf::Uint32 & delta) {
    if(smallest >= 0 && biggest < 256) {
        sf::Color new_color = text_.getFillColor();
        if(text_.getFillColor().a > smallest) {
            new_color.a -= delta;
        } else {
            new_color.a = biggest;
        }
        text_.setFillColor(new_color);
    }
}
