#ifndef WINDOWS_H
#define WINDOWS_H

#include "Entity.h"
#include <typeinfo>

extern int rate;

class wind {

protected:

    sf::RenderWindow wind_;

public:

    wind();
    virtual bool work() = 0;

};

class init_window : public wind {
    texture_manager provider_;
    sf::Sprite main_sprite_;

public:

    init_window();

    bool work();

};

class main_window : public wind {

    friend void tank::shoot(std::list<Entity *> &);

    std::vector<std::vector<bool>> map_;

    std::list<Entity *> to_draw;

    std::vector<tank> tanks;

    sf::Clock clock;

    float time;

    void handle_keyboard();

    void draw();

    void handle_event();

    void update_time();

    void move_entity(Entity &, const unsigned short &);

    void move_entity(Entity &);

    void handle_projectiles();

public:

    main_window();

    bool work();

};

#endif // WINDOWS_H
