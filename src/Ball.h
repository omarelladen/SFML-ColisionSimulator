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

    sf::CircleShape getBody() const;
    float getX() const;
    float getY() const;
    float getVX() const;
    float getVY() const;
    float getR() const;
    float getM() const;
    Ball *getPrevCol() const;

    void setVX(float vx);
    void setVY(float vy);
    void setPrevCol(Ball *p_b);
    void setX(float vx);
    void setY(float vy);

    void move();
};
