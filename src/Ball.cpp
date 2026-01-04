#include "Ball.h"


Ball::Ball(float x, float y,
           float vx, float vy,
           float r,
           sf::Color color
):
    r(r),
    body(r),
    pos(0,0),
    v(0,0),
    p_prev_col(nullptr)
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

float Ball::getR() {return r;}

Ball *Ball::getPrevCol() {return p_prev_col;}

void Ball::setVX(float vx)
{
    v.x = vx;
}

void Ball::setVY(float vy)
{
    v.y = vy;
}

void Ball::setPrevCol(Ball *p_b)
{
    p_prev_col = p_b;
}

void Ball::move()
{
    body.move(v);
    pos = body.getPosition();
}
