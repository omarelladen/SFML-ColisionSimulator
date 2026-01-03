#pragma once

#include <SFML/Graphics.hpp>
#include <random>

using namespace sf;


class Ball
{
public:
    CircleShape body;

    Vector2f pos;
    Vector2f vel;

    float radius;

public:
    Ball(int posX, int posY, float velX, float velY, int radius=50, sf::Color=sf::Color::Green);
    ~Ball();

    void setRadius(int radius);
    void setVel(Vector2f v);

    void move();
};
