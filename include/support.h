#ifndef SUPPORT_H
#define SUPPORT_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class texture_manager {
    std::vector<sf::Texture> * data_;
    unsigned short number_;
public:
    texture_manager() {}
    texture_manager(std::vector<sf::Texture> * data, unsigned short number);
    void set_data(std::vector<sf::Texture> * data);
    void set_number(unsigned short number);
    sf::Texture & get_texture();
};
#endif // SUPPORT_H
