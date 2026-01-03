#include "Ball.h"
#include <random>


Ball::Ball(int x, int y, float vx, float vy, int radius, sf::Color color):
    body(radius),
    radius(radius),
    pos(0,0),
    vel(0,0)
{
    vel = Vector2f(vx, vy);

    pos = Vector2f(x, y);
    body.setPosition(pos);

    body.setFillColor(color);
}

Ball::~Ball()
{
}

void Ball::setRadius(int r)
{
    if (r > 0)
    {
        radius = r;
        body.setRadius(r);
    }
}

void Ball::setVel(Vector2f v)
{
    vel = v;
}


void Ball::move()
{
    body.move(vel);
    pos = body.getPosition();
}
