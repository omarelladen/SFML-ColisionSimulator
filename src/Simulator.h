#pragma once

#include "Ball.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>


class Simulator
{
private:
    std::vector<Ball*> balls;
    unsigned int num_balls;
    unsigned int win_w;
    unsigned int win_h;

public:
    Simulator(unsigned int num_balls,
              float r, float m,
              int win_w, int win_h);
    ~Simulator();

    unsigned int getNumBalls() const;

    void execute();

private:
    bool colidedBalls(Ball *ball1, Ball *ball2) const;
    void updateColisionVel(Ball *b1, Ball *b2);
    bool colidedWallV(Ball *b) const;
    bool colidedWallH(Ball *b) const;
    void checkColisionsBalls(std::vector<Ball*>& balls);
    void checkColisionsWalls(std::vector<Ball*>& balls);
};
