#include "windows.h"

wind::wind() {}

//Init Window:

bool init_window::work() {

        main_sprite_.setTexture(provider_.get_texture());
        main_sprite_.setScale(1 / 120., 1 / 120.);

        wind_.create(sf::VideoMode(X * scale, Y * scale), "TANKS");

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

            if(main_sprite_.getColor().a > 128) {
                sf::Color new_color = main_sprite_.getColor();
                new_color.a -= 3;
                main_sprite_.setColor(new_color);
            } else {
                wind_.draw(main_inscription_.get());
                main_inscription_.flicker(240, 255, 1);
            }

            wind_.display();
        }

        return false;
}

init_window::init_window(const std::string & inscr) :
    provider_(&T, 0), main_inscription_(inscr, sf::Vector2f(X / 2 * scale, Y / 2 * scale), sf::Color(250, 167, 108)) {}


void init_window::set_message(const std::string & new_message, const sf::Vector2f & new_position) {
    main_inscription_.set_text(new_message);
    main_inscription_.set_position(new_position);
}

//Main window:

main_window::main_window() {

    map_.resize(9);
    for(auto & str : map_)
        str.assign(16, false);
    map_[2][2] = true;
    map_[3][3] = true;
    map_[4][4] = true;
    map_[5][3] = true;
    map_[6][2] = true;
    map_[2][13] = true;
    map_[3][12] = true;
    map_[4][11] = true;
    map_[5][12] = true;
    map_[6][13] = true;

    tanks.push_back(tank(1, sf::Vector2f()));
    tanks[0].set_keys(sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::S,
                      sf::Keyboard::D, sf::Keyboard::E, sf::Keyboard::Q);
    tanks[0].color(sf::Color(71, 167, 106));
    tanks.push_back(tank(3, sf::Vector2f((X - 1) * scale, (Y - 1) * scale)));
    tanks[1].set_keys(sf::Keyboard::Numpad8, sf::Keyboard::Numpad4, sf::Keyboard::Numpad5,
                      sf::Keyboard::Numpad6, sf::Keyboard::Numpad9, sf::Keyboard::Numpad7);
    tanks[1].color(sf::Color(62, 95, 138));

}

std::string main_window::work() {

    wind_.create(sf::VideoMode(16 * scale, 9 * scale), "TANKS");
    wind_.setFramerateLimit(rate);

        while(wind_.isOpen()) {

            handle_event();

            update_time();

            handle_keyboard();

            handle_projectiles();

            handle_point();

            if(!tanks_are_alive() || P.is_captured())
                return final_message();

            draw();

        }

        return "";

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

    for (auto & tank : tanks) {

        if(sf::Keyboard::isKeyPressed(tank.get_up())) {
            move_entity(tank, 0);
        } else if (sf::Keyboard::isKeyPressed(tank.get_right())) {
            move_entity(tank, 1);
        } else if (sf::Keyboard::isKeyPressed(tank.get_down())) {
            move_entity(tank, 2);
        } else if (sf::Keyboard::isKeyPressed(tank.get_left())) {
            move_entity(tank, 3);
        }
        if (sf::Keyboard::isKeyPressed(tank.get_launch())) {
            launch_missile(tank);
        }

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

    wind_.draw(P.get_circle());

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
                if(static_cast<float>(tank.get_health()) <= 0.5 * static_cast<float>(tank.get_max_health()))
                    tank.lose_bricks();
                it = projectiles.erase(it);
                break;
            }
        }
    }

}

void main_window::handle_point() {
    for(unsigned i = 0; i < tanks.size(); ++i) {
        P.be_captured(tanks[i], i, time / 10);
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

std::string main_window::final_message() {
    if(tanks[0].get_health() <= 0 || P.check_condition() >= 1)
        return "BLUE WON";
    return "GREEN WON";
}

//Gamelooop:

void gameloop() {
    init_window iw("START");
    while(iw.work()) {
        main_window mw;
        auto message = mw.work();
        if(message != "")
            iw.set_message(message);
        else
            iw.set_message("CLOSE TO EXIT");
    }
}
