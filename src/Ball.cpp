#include "Ball.h"
#include <random>


Ball::Ball(float x, float y, float vx, float vy, float radius, sf::Color color):
    body(radius),
    radius(radius),
    pos(0,0),
    vel(0,0)
{
    vel = sf::Vector2f(vx, vy);

    pos = sf::Vector2f(x, y);
    body.setPosition(pos);

    body.setFillColor(color);
}

Ball::~Ball()
{
}

void Ball::setRadius(float r)
{
    if (r > 0)
    {
        radius = r;
        body.setRadius(r);
    }
}

void Ball::setVel(sf::Vector2f v)
{
    vel = v;
}


void Ball::move()
{
    body.move(vel);
    pos = body.getPosition();
}
