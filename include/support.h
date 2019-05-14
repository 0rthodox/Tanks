#ifndef SUPPORT_H
#define SUPPORT_H

#include <string>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

class texture_manager;

class texture_keeper {
    friend texture_manager;
    std::vector<sf::Texture> data_;
public:
    texture_keeper(int k);
};

class texture_manager {
    texture_keeper * data_;
    unsigned short number_;
public:
    texture_manager() {}
    texture_manager(texture_keeper * data, unsigned short number);
    void set_data(texture_keeper * data);
    void set_number(unsigned short number);
    sf::Texture & get_texture();
};


#endif // SUPPORT_H
