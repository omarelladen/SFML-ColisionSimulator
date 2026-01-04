#include "Ball.h"
#include <random>


Ball::Ball(float x, float y,
           float vx, float vy,
           float r,
           sf::Color color
):
    radius(r),
    body(r),
    pos(0,0),
    v(0,0)
{
    v = sf::Vector2f(vx, vy);

    pos = sf::Vector2f(x, y);
    body.setPosition(pos);

    body.setFillColor(color);
}

Ball::~Ball()
{
}

sf::CircleShape Ball::getBody() {return body;}

float Ball::getX() {return pos.x;}

float Ball::getY() {return pos.y;}

float Ball::getVX() {return v.x;}

float Ball::getVY() {return v.y;}

float Ball::getR() {return radius;}

void Ball::setVX(float vx)
{
    v.x = vx;
}

void Ball::setVY(float vy)
{
    v.y = vy;
}

void Ball::move()
{
    body.move(v);
    pos = body.getPosition();
}
