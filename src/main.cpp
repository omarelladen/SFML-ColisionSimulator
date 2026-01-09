#include "Simulator.h"


void clearCinBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
void readInput(T *ptr, T default_value, T min_value, const std::string title)
{
    float tmp_value;

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
    else
    {
        if (tmp_value < 0)
	    {
	        std::cout << "Invalid input! Using default" << std::endl;
	        *ptr = default_value;
	    }
        else
        {
            *ptr = static_cast<T>(tmp_value);
            if (*ptr < min_value)
            {
                std::cout << "Minimum value is " << min_value << std::endl;
                exit(0);
            }
        }
    }

    clearCinBuffer();
}


int main()
{
    unsigned int num_balls;
    float r;
    float m;
    unsigned int win_w;
    unsigned int win_h;

    // Input
    readInput(&num_balls, 3u, 1u, "Number of balls");
    readInput(&r, 30.f, 1.f, "Ball radius");
    readInput(&m, 1.f, 1.f, "Ball mass");
    readInput(&win_w, 500u, static_cast<unsigned int>(r), "Window width");
    readInput(&win_h, 500u, static_cast<unsigned int>(r), "Window height");


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
