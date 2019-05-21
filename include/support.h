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


//Texture Keeper


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
//CDtors
    texture_manager() {}
    texture_manager(texture_keeper *, unsigned short);
//Setters:
    void set_data(texture_keeper *);
    void set_number(unsigned short);

//Getters:
    sf::Texture & get_texture();
};


//Keys


struct Keys {
    sf::Keyboard::Key Up_;
    sf::Keyboard::Key Left_;
    sf::Keyboard::Key Down_;
    sf::Keyboard::Key Right_;
    sf::Keyboard::Key Launch_;
    sf::Keyboard::Key Shoot_;
};


//Effect


class effect {
    sf::Time cooldown_;
    sf::Time last_cast_;

public:
//CDtors
    virtual ~effect() = default;
//Other
    virtual void cast() = 0;
    virtual void purify() = 0;
    void check(const sf::Time &);
};


//Font


class font {
    sf::Font font_;
public:
    font();
    const sf::Font & get_font();
};

extern font F;


//Textblock


class textblock {
    sf::RectangleShape background_;
    sf::Text text_;
public:
    textblock(const sf::Vector2f &, const std::string & = "", const sf::Color & = sf::Color());
    void set_string(const std::string &);
    void set_position(const sf::Vector2f &);
    std::pair<sf::RectangleShape, sf::Text> get();
};

//Text

class inscription {
    sf::Text text_;
public:

//CDtors:
    inscription(const std::string & = "", const sf::Vector2f & = sf::Vector2f(), const sf::Color & = sf::Color());

//Setters:
    void set_position(const sf::Vector2f & = sf::Vector2f());
    void set_color(const sf::Color & = sf::Color());

//Getters:
    sf::Text get() const;

//Other:
    void flicker(const sf::Uint32 & = 128, const sf::Uint32 & = 255, const sf::Uint32 & = 16);
};

#endif // SUPPORT_H
