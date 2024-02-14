#include "Bola.h"

Bola::Bola():
	corpo(50),/////////////
	raio(0),
	//pos(0,0),
	vel(0,0)
{
	time_t t;
	srand((unsigned)time(&t));

	setRaio(50);
	corpo.setFillColor(sf::Color::Red);

	vel = Vector2f((rand() % 4 + 0.2) / 9.0, (rand() % 4 + 0.2) / 9.0); // 
	pos = Vector2f(rand() % 100 + 100, rand() % 100 + 100);////////////
}

Bola::~Bola()
{
}


void Bola::setRaio(float r)
{
	raio = r;
	//corpo.setSize(tam); (p/ RectangleShape)
	corpo.setRadius(r);
}

void Bola::setVel(Vector2f v)
{
	vel = v;
}


void Bola::mover()
{
	corpo.move(vel);
	pos = corpo.getPosition();
}

void Bola::executar()
{
	mover();
	//desenhar_se();
}