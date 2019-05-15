#include "windows.h"

wind::wind() {}

bool init_window::work() {

        wind_.create(sf::VideoMode(960, 540), "TANKS");

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

init_window::init_window() : provider_(&T, 0){

    main_sprite_.setTexture(provider_.get_texture());
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

    wind_.create(sf::VideoMode(960, 540), "TANKS");

    tank t(5, 5, 0, 1);

        while(wind_.isOpen()) {

            sf::Event event;

            while(wind_.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    wind_.close();
                }
                else if(event.type == sf::Event::MouseButtonPressed) {
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    t.set_direction(0);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    t.set_direction(1);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    t.set_direction(2);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    t.set_direction(3);
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

            wind_.draw(t.get_sprite());


            wind_.display();
        }

        return false;

}
