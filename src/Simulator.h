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
    int num_balls;
    int win_w;
    int win_h;

public:
    Simulator(int num_balls,
              float r, float m,
              int win_w, int win_h);
    ~Simulator();

    int getNumBalls();

    void execute();

private:
    bool colided_ball(Ball *ball1, Ball *ball2);
    void update_colision_vel(Ball *b1, Ball *b2);
    bool colided_wall_v(Ball *b);
    bool colided_wall_h(Ball *b);
};
