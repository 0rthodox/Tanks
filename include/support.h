#ifndef SUPPORT_H
#define SUPPORT_H

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <cmath>

#include <SFML/Graphics.hpp>

class texture_manager;

extern int scale;

sf::Vector2f check_bounds(const sf::Vector2f &, const short & = 16 , const short & = 9);

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
//Keys
    texture_manager() {}
    texture_manager(texture_keeper *, unsigned short);
//Setters:
    void set_data(texture_keeper *);
    void set_number(unsigned short);

//Getters:
    sf::Texture & get_texture();
};

struct Keys {
    sf::Keyboard::Key Up_;
    sf::Keyboard::Key Left_;
    sf::Keyboard::Key Down_;
    sf::Keyboard::Key Right_;
    sf::Keyboard::Key Launch_;
    sf::Keyboard::Key Shoot_;
};
#endif // SUPPORT_H
