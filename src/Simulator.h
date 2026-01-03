#pragma once

#include "Ball.h"

using namespace std;


class Simulator
{
public:
    vector<Ball*> balls;
    int num_balls;

	
    Simulator(int num_balls);
    ~Simulator();

    float Colided(Ball* ball1, Ball* ball2);
    void Execute();
};

