#include "Simulator.h"


void clearCinBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void readInput(int *ptr, int default_value, const std::string title)
{
    std::cout << title << " [" << default_value << "]: ";
    if (std::cin.peek() == '\n')
    {
        *ptr = default_value;
    }
    else if (!(std::cin >> *ptr))
    {
        std::cout << "Invalid input! Using default" << std::endl;
        *ptr = default_value;
    }

    clearCinBuffer();
}


int main()
{
    // Input

    int num_balls = 0;
    readInput(&num_balls, 3, "Number of balls");
    if (num_balls < 1)
    {
        std::cout << "Minimum number is 1!" << std::endl;
        return 0;
    }

    int r;
    readInput(&r, 30, "Ball radius");
    if (r < 1)
    {
        std::cout << "Minimum radius is 1!" << std::endl;
        return 0;
    }

    int m;
    readInput(&m, 1, "Ball mass");
    if (m < 1)
    {
        std::cout << "Minimum mass is 1!" << std::endl;
        return 0;
    }

    int win_w;
    readInput(&win_w, 500, "Window width");
    if (win_w < r)
    {
        std::cout << "Minimum size is r!" << std::endl;
        return 0;
    }

    int win_h;
    readInput(&win_h, 500, "Window height");
    if (win_h < r)
    {
        std::cout << "Minimum size is r!" << std::endl;
        return 0;
    }


    if (2*r >= win_h || 2*r >= win_w)
    {
        std::cout << "Bad size!" << std::endl;
        return 0;
    }


    Simulator simulator(num_balls, r, m, win_h, win_w);

    if (simulator.getNumBalls() > 0)
        simulator.execute();
    else
        std::cout << "Bad size!" << std::endl;


    return 0;
}
