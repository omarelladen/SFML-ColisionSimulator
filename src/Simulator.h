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
              unsigned int win_w, unsigned int win_h);
    ~Simulator();

    unsigned int getNumBalls() const;

    void execute();

private:
    bool colidedBalls(Ball *ball1, Ball *ball2) const;
    void updateColisionVel(Ball *p_b1, Ball *p_b2);
    void checkColisionsBalls(std::vector<Ball*>& balls);
    void checkColisionsWalls(std::vector<Ball*>& balls);
    bool colidedWallLeft(Ball *p_b) const;
    bool colidedWallRight(Ball *p_b) const;
    bool colidedWallTop(Ball *p_b) const;
    bool colidedWallBottom(Ball *p_b) const;
};
