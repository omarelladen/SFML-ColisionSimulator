#include "Simulator.h"


void clearCinBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void readInput(int *p, int d, const std::string s)
{
    std::cout << s << " [" << d << "]: ";
    if (std::cin.peek() == '\n')
        *p = d;
    else if (!(std::cin >> *p))
        std::cout << "Invalid input.\n";

    clearCinBuffer();
}

int main()
{
    // Input

    int num_balls = 0;
    readInput(&num_balls, 3, "Number of balls");

    int r = 0;
    readInput(&r, 30, "Ball radius");

    int win_w = 0;
    readInput(&win_w, 600, "Window width");

    int win_h = 0;
    readInput(&win_h, 600, "Window height");


    Simulator simulator(num_balls, r, win_h, win_w);

    if (simulator.getNumBalls() > 0)
    {
        simulator.execute();
    }
    else
    {
        std::cout << "Error: Bad number of balls!" << std::endl;
    }

    return 0;
}
