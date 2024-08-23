#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bola
{
public:
	CircleShape corpo;

	float raio;
	Vector2f pos;
	Vector2f vel;


	Bola();
	~Bola();

	void setRaio(float raio);
	void setVel(Vector2f v);

	void mover();
	void executar();
};