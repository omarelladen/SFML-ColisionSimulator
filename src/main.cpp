#include "Simulator.h"


void clearCinBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void readInput(unsigned int *ptr, unsigned int default_value, const std::string title)
{
    int tmp_value;

    std::cout << title << " [" << default_value << "]: ";
    if (std::cin.peek() == '\n')
    {
        *ptr = default_value;
    }
    else if (!(std::cin >> tmp_value))
    {
        std::cout << "Invalid input! Using default" << std::endl;
        *ptr = default_value;
    }

    if (tmp_value < 0)
        *ptr = -tmp_value;
    else
        *ptr = tmp_value;

    clearCinBuffer();
}


int main()
{
    // Input

    unsigned int num_balls;
    readInput(&num_balls, 3, "Number of balls");
    if (num_balls < 1)
    {
        std::cout << "Minimum number is 1!" << std::endl;
        return 0;
    }

    unsigned int r;
    readInput(&r, 30, "Ball radius");
    if (r < 1)
    {
        std::cout << "Minimum radius is 1!" << std::endl;
        return 0;
    }

    unsigned int m;
    readInput(&m, 1, "Ball mass");
    if (m < 1)
    {
        std::cout << "Minimum mass is 1!" << std::endl;
        return 0;
    }

    unsigned int win_w;
    readInput(&win_w, 500, "Window width");
    if (win_w < r)
    {
        std::cout << "Minimum size is r!" << std::endl;
        return 0;
    }

    unsigned int win_h;
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


    Simulator simulator(num_balls, r, m, win_w, win_h);

    if (simulator.getNumBalls() > 0)
        simulator.execute();
    else
        std::cout << "Bad size!" << std::endl;


    return 0;
}
