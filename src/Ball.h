#pragma once

#include <SFML/Graphics.hpp>
#include <random>


class Ball
{
private:
    float r;
    sf::CircleShape body;
    sf::Vector2f pos;
    sf::Vector2f v;

public:
    Ball(float x, float y,
         float vx, float vy,
         float r = 30,
         sf::Color = sf::Color::Green
    );
    ~Ball();

    sf::CircleShape getBody();
    float getX();
    float getY();
    float getVX();
    float getVY();
    float getR();

    void setVX(float vx);
    void setVY(float vy);

    void move();
};
