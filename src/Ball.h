#pragma once

#include <SFML/Graphics.hpp>
#include <random>

using namespace sf;


class Ball
{
public:
    CircleShape body;

    float radius;
    Vector2f pos;
    Vector2f vel;


    Ball(std::mt19937& gen);
    ~Ball();

    void setRadius(float radius);
    void setVel(Vector2f v);

    void move();
    void execute();
};
