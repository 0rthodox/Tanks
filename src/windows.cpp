#include "windows.h"

wind::wind() {}

bool init_window::work() {

        wind_.create(sf::VideoMode(16 * scale, 9 * scale), "TANKS");

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

init_window::init_window() : provider_(&T, 0) {

    main_sprite_.setTexture(provider_.get_texture());
    main_sprite_.setScale(1 / 120., 1 / 120.);

}

main_window::main_window() : clock() {

    map_.resize(9);
    for(auto & str : map_)
        str.assign(16, false);
    map_[2][2] = true;
    map_[6][2] = true;
    map_[2][13] = true;
    map_[6][13] = true;

    tanks.resize(2);
    for(auto & t : tanks) {
        projectile prj;
        t.load_ammo(prj, 3);
        to_draw.push_back(&t);
    }

}

bool main_window::work() {

    wind_.create(sf::VideoMode(16 * scale, 9 * scale), "TANKS");

        while(wind_.isOpen()) {

            handle_event();

            update_time();

            handle_keyboard();

            draw();

        }

        return false;

}

void main_window::handle_event() {

    sf::Event event;

    while(wind_.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            wind_.close();
        } else if(event.type == sf::Event::MouseButtonPressed) {

        }

    }
}

void main_window::handle_keyboard() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    tanks[0].move(0);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    tanks[0].move(1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    tanks[0].move(2);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    tanks[0].move(3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    tanks[1].move(3);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    tanks[1].move(0);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    tanks[1].move(1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    tanks[1].move(2);
    }

}

void main_window::draw() {
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

    for(auto & drawable : to_draw) {
        wind_.draw(drawable->get_sprite());
    }

    wind_.display();

}

void main_window::update_time() {
    time = clock.restart().asSeconds();
}
