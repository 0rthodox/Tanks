#ifndef WINDOWS_H
#define WINDOWS_H

#include "Entity.h"

extern int rate;
extern font F;


//Wind:


class wind {

protected:

    sf::RenderWindow wind_;

public:

    wind();

};


//Init:


class init_window : public wind {

    texture_manager provider_;
    sf::Sprite main_sprite_;
    inscription main_inscription_;

public:

    init_window(const std::string &);

    bool work();

    void set_message(const std::string &, const sf::Vector2f & = sf::Vector2f(X / 2 * scale, Y / 2 * scale));

};

class main_window : public wind {

    inscription final_inscription_;

    std::vector<std::vector<bool>> map_;

    std::vector<tank> tanks;

    std::list<projectile> projectiles;

    point P;

    sf::Clock clock;

    sf::Clock const_clock;

    float time;

    void handle_keyboard();

    void draw();

    void handle_event();

    void update_time();

    void move_entity(Entity &, const unsigned short &);

    void move_entity(Entity &);

    void handle_projectiles();

    bool check_hit(const tank &);

    bool check_hits();

    void launch_missile(tank &);

    bool tanks_are_alive();

    std::string final_message();

    void handle_point();

public:

    main_window();

    std::string work();

};

void gameloop();

#endif // WINDOWS_H
