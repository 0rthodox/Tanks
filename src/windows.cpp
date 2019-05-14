#include "windows.h"

wind::wind() {}

bool init_window::work() {

        wind_.create(sf::VideoMode(640, 360), "TANKS");

        main_sprite_.scale(scale, scale);

        while(wind_.isOpen()) {

            sf::Event event;

            while(wind_.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    wind_.close();
                }
                else if(event.type == sf::Event::MouseButtonPressed) {
                    wind_.close();
                    return true;
                }
            }

            wind_.clear(sf::Color::White);

            wind_.draw(main_sprite_);

            wind_.display();
        }

        return false;
}

init_window::init_window() {

    main_texture_.loadFromFile("main_init.png");
    main_sprite_ = sf::Sprite(main_texture_);
    main_sprite_.setScale(1 / 120., 1 / 120.);

}

main_window::main_window() {

    map_.resize(9);
    for(auto & str : map_)
        str.assign(16, false);
    map_[2][2] = true;
    map_[6][2] = true;
    map_[2][13] = true;
    map_[6][13] = true;

}

bool main_window::work() {

    wind_.create(sf::VideoMode(640, 360), "TANKS");

        while(wind_.isOpen()) {

            sf::Event event;

            while(wind_.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    wind_.close();
                }
                else if(event.type == sf::Event::MouseButtonPressed) {
                }
            }

            wind_.clear(sf::Color::White);

            for(unsigned  short i = 0; i < map_.size(); ++i)
                for(unsigned short j = 0; j < map_[i].size(); ++j) {
                    sf::RectangleShape elem(sf::Vector2f(scale, scale));
                    elem.setPosition(j * scale, i * scale);
                    if(!map_[i][j])
                        elem.setFillColor(sf::Color(207, 155, 143, 216));
                    else
                        elem.setFillColor(sf::Color::Cyan);
                    wind_.draw(elem);
                }


            wind_.display();
        }

        return false;

}
