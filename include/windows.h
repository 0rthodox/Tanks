#ifndef WINDOWS_H
#define WINDOWS_H

#include "Entity.h"

extern int scale;

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

public:

    main_window();

    bool work();

};

#endif // WINDOWS_H
