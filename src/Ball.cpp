#include "Ball.h"
#include <random>


Ball::Ball(std::mt19937& gen):
	body(50),  /////////////
	radius(50),
	// pos(0,0),
	vel(0,0)
{

    setRadius(50);
    body.setFillColor(sf::Color::Green);

    std::uniform_real_distribution<float> distVel(0.2f, 0.6f);  // Velocidade entre 0.2 e 0.6
    std::uniform_int_distribution<int> distPos(200, 900);  // Posição entre 100 e 1100 (no eixo x e y)

    // Gerando a velocidade aleatória
    vel = Vector2f(distVel(gen), distVel(gen));

    // Gerando a posição aleatória
    pos = Vector2f(distPos(gen), distPos(gen));  // Posição entre 100 e 1100

    body.setPosition(pos);
}

Ball::~Ball()
{
}


void Ball::setRadius(float r)
{
    radius = r;
    body.setRadius(r);
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

void Ball::execute()
{
    move();
    // draw_me();
}
