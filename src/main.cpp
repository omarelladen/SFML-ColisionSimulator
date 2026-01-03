#include "Simulator.h"
#include <iostream>


int main()
{
    // Input
    int num_balls = 0;
    std::cout << "Enter the number of balls: ";
    std::cin >> num_balls;

    Simulator simulator(num_balls);

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
