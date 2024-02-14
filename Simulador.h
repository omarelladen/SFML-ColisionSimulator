#pragma once
#include <iostream>
using namespace std;
#include "Bola.h"

class Simulador
{
public:
	vector<Bola*> bolas;

	
	Simulador();
	~Simulador();

	float Colidiu(Bola* bola1, Bola* bola2);

	void Executar();
};

