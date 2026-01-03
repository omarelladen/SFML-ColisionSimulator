#pragma once

#include "Ball.h"


class Simulator
{
public:
    std::vector<Ball*> balls;
    int num_balls;


    Simulator(int num_balls);
    ~Simulator();

    float colided(Ball* ball1, Ball* ball2);
    void execute();
};

