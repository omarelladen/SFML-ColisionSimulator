#pragma once

#include <SFML/Graphics.hpp>


class Ball
{
private:
    float r;
    float m;
    sf::CircleShape body;
    sf::Vector2f pos;
    sf::Vector2f v;

    Ball *p_prev_col;

public:
    Ball(float x, float y,
         float vx, float vy,
         float r, float m,
         sf::Color = sf::Color::Green
    );
    ~Ball();

    sf::CircleShape getBody();
    float getX();
    float getY();
    float getVX();
    float getVY();
    float getR();
    float getM();
    Ball *getPrevCol();

    void setVX(float vx);
    void setVY(float vy);
    void setPrevCol(Ball *p_b);

    void move();
};
