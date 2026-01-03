#pragma once

#include "Ball.h"


class Simulator
{
private:
    std::vector<Ball*> balls;
    int num_balls;

public:
    Simulator(int num_balls);
    ~Simulator();

    int getNumBalls();

    bool colided(Ball* ball1, Ball* ball2);
    void execute();
};
