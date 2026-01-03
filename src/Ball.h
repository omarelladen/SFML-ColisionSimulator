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
    Ball(float posX, float posY, float velX, float velY, float radius=50, sf::Color=sf::Color::Green);
    ~Ball();

    void setRadius(float radius);
    void setVel(sf::Vector2f v);

    void move();
};
