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

    tanks.push_back(tank(1, sf::Vector2f()));
    tanks.push_back(tank(3, sf::Vector2f(15 * scale, 8 * scale)));

}

bool main_window::work() {

    wind_.create(sf::VideoMode(16 * scale, 9 * scale), "TANKS");
    wind_.setFramerateLimit(rate);

        while(wind_.isOpen()) {

            handle_event();

            update_time();

            handle_keyboard();

            handle_projectiles();

            if(!tanks_are_alive())
                break;

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
                    move_entity(tanks[0], 0);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    move_entity(tanks[0], 1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    move_entity(tanks[0], 2);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    move_entity(tanks[0], 3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    move_entity(tanks[1], 3);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    move_entity(tanks[1], 0);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    move_entity(tanks[1], 1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    move_entity(tanks[1], 2);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        launch_missile(tanks[0]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {
        launch_missile(tanks[1]);
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

    for(auto & tank : tanks) {
        wind_.draw(tank.get_sprite());
    }
    for(auto & prj : projectiles) {
        wind_.draw(prj.get_sprite());
    }

    wind_.display();

}

void main_window::update_time() {
    time = clock.restart().asSeconds();
}

void main_window::move_entity(Entity & e, const unsigned short & new_direction) {

    if(e.get_direction() != new_direction)
        e.set_direction(new_direction);

    move_entity(e);

}

void main_window::move_entity(Entity & e) {

    sf::Vector2f dp(time * scale * e.speed_ * ((e.direction_ == 1) - (e.direction_ == 3)) / 60,
                    time * scale * e.speed_ * ((e.direction_ == 2) - (e.direction_ == 0)) / 60);

    std::modf(dp.x, &dp.x);
    std::modf(dp.y, &dp.y);

    e.spr_.move(dp);

    e.spr_.move(check_bounds(e.get_position()));

}

void main_window::handle_projectiles() {
    for(auto it = projectiles.begin(); it != projectiles.end(); ++it) {

        move_entity(*it);

        if((it->get_position().x == 0 && it->get_direction() == 3) || (it->get_position().x == 15 * scale && it->get_direction() == 1)
           || (it->get_position().y == 0 && it->get_direction() == 0) || (it->get_position().y == 8 * scale && it->get_direction() == 2))
            it = projectiles.erase(it);

        for(auto & tank : tanks) {

            if(tank.intersects(*it)) {
                tank.be_hit(it->get_damage());
                it = projectiles.erase(it);
                break;
            }
        }
    }

}

void main_window::launch_missile(tank & t) {
    sf::Time current_time = const_clock.getElapsedTime();
    if(current_time - t.get_time_of_last_launch() >= t.get_main_cooldown()) {
        t.set_time_of_last_launch(current_time);
        projectiles.push_back(projectile(t.get_direction(),
                                         t.get_position() + sf::Vector2f(scale * ((t.get_direction() == 1) - (t.get_direction() == 3)),
                                                                                            scale * ((t.get_direction() == 2) - (t.get_direction() == 0)))));
    }
}

bool main_window::tanks_are_alive() {
    for(const auto & tank : tanks) {
        if(tank.get_health() <= 0)
            return false;
    }
    return true;
}
