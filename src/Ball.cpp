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

sf::CircleShape Ball::getBody()
{
	return body;
}

float Ball::getX()
{
    return pos.x;
}

float Ball::getY()
{
    return pos.y;
}

float Ball::getVX()
{
    return vel.x;
}

float Ball::getVY()
{
    return vel.y;
}

float Ball::getR()
{
    return radius;
}

void Ball::setVX(float vx)
{
    vel.x = vx;
}

void Ball::setVY(float vy)
{
    vel.y = vy;
}

void Ball::move()
{
    body.move(vel);
    pos = body.getPosition();
}
