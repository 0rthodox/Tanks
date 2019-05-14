#include "support.h"

void texture_manager::set_data(std::vector<sf::Texture> * data) {
    data_ = data;
}

void texture_manager::set_number(unsigned short number) {
    if(number_ <= data_->size())
        number_ = number;
    else
        number_ = 0;
}

texture_manager::texture_manager(std::vector<sf::Texture> * data, unsigned short number) {
    set_data(data);
    set_number(number);
}

sf::Texture & texture_manager::get_texture() {
    return data_->at(number_);
}
