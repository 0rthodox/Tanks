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
    virtual bool work() = 0;

};


//Init:


class init_window : public wind {

    texture_manager provider_;
    sf::Sprite main_sprite_;
    inscription main_inscription_;

public:

    init_window(const std::string &);

    bool work();

};

class main_window : public wind {

    inscription final_inscription_;

    std::vector<std::vector<bool>> map_;

    std::vector<tank> tanks;

    std::list<projectile> projectiles;

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

public:

    main_window();

    bool work();

};

#endif // WINDOWS_H
