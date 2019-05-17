#ifndef WINDOWS_H
#define WINDOWS_H

#include "Entity.h"

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

    std::list<Entity *> to_draw;

    std::vector<tank> tanks;

    void handle_keyboard();

    void draw();

    void handle_event();

public:

    main_window();

    bool work();

};

#endif // WINDOWS_H
