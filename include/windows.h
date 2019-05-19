#ifndef WINDOWS_H
#define WINDOWS_H

#include "Entity.h"

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

    std::vector<std::vector<bool>> map_;

    std::vector<tank> tanks;

    std::list<projectile> projectiles;

    sf::Clock clock;

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

public:

    main_window();

    bool work();

};

#endif // WINDOWS_H
