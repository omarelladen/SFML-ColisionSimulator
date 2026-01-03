#pragma once

#include <SFML/Graphics.hpp>
#include <random>


class Ball
{
private:
    float radius;

    sf::CircleShape body;

    sf::Vector2f pos;
    sf::Vector2f vel;

public:
    Ball(float x, float y,
         float vx, float vy,
         float r = 50,
         sf::Color = sf::Color::Green
    );
    ~Ball();

    sf::CircleShape getBody();

    float getPosX();
    float getPosY();
    float getVelX();
    float getVelY();
    float getRadius();

    void setVelX(float vx);
    void setVelY(float vy);
    void setRadius(float r);

    void move();
};
