#include "Ball.h"
#include <random>


Ball::Ball(float x, float y, float vx, float vy, float radius, sf::Color color):
    radius(radius),
    body(radius),
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

float Ball::getPosX()
{
    return pos.x;
}

float Ball::getPosY()
{
    return pos.y;
}

float Ball::getVelX()
{
    return vel.x;
}

float Ball::getVelY()
{
    return vel.y;
}

float Ball::getRadius()
{
    return radius;
}

void Ball::setRadius(float r)
{
    if (r > 0)
    {
        radius = r;
        body.setRadius(r);
    }
}

void Ball::setVelX(float vx)
{
    vel.x = vx;
}

void Ball::setVelY(float vy)
{
    vel.y = vy;
}

void Ball::move()
{
    body.move(vel);
    pos = body.getPosition();
}
