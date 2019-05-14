#include "support.h"

void texture_manager::set_data(texture_keeper * data) {
    data_ = data;
}

void texture_manager::set_number(unsigned short number) {
    if(number_ <= data_->data_.size())
        number_ = number;
    else
        number_ = 0;
}

texture_manager::texture_manager(texture_keeper * data, unsigned short number) {
    set_data(data);
    set_number(number);
}

sf::Texture & texture_manager::get_texture() {
    return data_->data_.at(number_);
}

texture_keeper::texture_keeper(int k) {
    sf::Texture T;
    std::string name = "A";
    for(int i = 0; i < k; ++i) {
        T.loadFromFile("images/" + name + ".png");
        data_.push_back(T);
        name += "A";
    }
    std::cout << data_.size();

}
