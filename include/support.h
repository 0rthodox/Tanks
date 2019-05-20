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

class keys {
    sf::Keyboard::Key Up_;
    sf::Keyboard::Key Left_;
    sf::Keyboard::Key Down_;
    sf::Keyboard::Key Right_;
    sf::Keyboard::Key Launch_;
    sf::Keyboard::Key Shoot_;

public:
//CDtors:
    keys(const sf::Keyboard::Key & = sf::Keyboard::Unknown, const sf::Keyboard::Key & = sf::Keyboard::Unknown, const sf::Keyboard::Key & = sf::Keyboard::Unknown,
         const sf::Keyboard::Key & = sf::Keyboard::Unknown, const sf::Keyboard::Key & = sf::Keyboard::Unknown, const sf::Keyboard::Key & = sf::Keyboard::Unknown);

//Setters:
    void set_up(const sf::Keyboard::Key &);
    void set_left(const sf::Keyboard::Key &);
    void set_down(const sf::Keyboard::Key &);
    void set_right(const sf::Keyboard::Key &);
    void set_launch(const sf::Keyboard::Key &);
    void set_shoot(const sf::Keyboard::Key &);

//Getters:
    sf::Keyboard::Key get_up() const;
    sf::Keyboard::Key get_left() const;
    sf::Keyboard::Key get_down() const;
    sf::Keyboard::Key get_right() const;
    sf::Keyboard::Key get_launch() const;
    sf::Keyboard::Key get_shoot() const;

};
#endif // SUPPORT_H
