#pragma once

#include <SFML/Graphics.hpp>
#include <random>


class Ball
{
public:
    sf::CircleShape body;

    sf::Vector2f pos;
    sf::Vector2f vel;

    float radius;

public:
    Ball(int posX, int posY, float velX, float velY, int radius=50, sf::Color=sf::Color::Green);
    ~Ball();

    void setRadius(int radius);
    void setVel(sf::Vector2f v);

    void move();
};
