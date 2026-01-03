#include "Simulator.h"
#include <cmath>
#include <random>
#include <ctime>

#define MAX_TRIES 100000
#define WIN_SIZE 1000

Simulator::Simulator(int num_balls):
    balls(),
    num_balls(num_balls)
{

    std::random_device rd;
    std::mt19937 gen(rd());

    int count_num_balls = 0;
    int num_tries = 0;
    while (count_num_balls < this->num_balls && num_tries < MAX_TRIES)
    {
        // Generate random values
        std::uniform_int_distribution<int> distPos(200, 900);
        std::uniform_real_distribution<float> distVel(0.2f, 0.6f);

        int x = distPos(gen);
        int y = distPos(gen);

        float vx = distVel(gen);
        float vy = distVel(gen);

        Ball* pBall = new Ball(x, y, vx, vy);

        if (pBall)
        {
            // Push first ball
            if (balls.empty())
            {
                balls.push_back(pBall);
                count_num_balls++;
            }
            else
            {
               // Check overlap
               for (int i = 0; i < count_num_balls; i++)
               {
                   Ball* pBall_check = balls[i];
                   if (pBall_check != pBall && colided(pBall, pBall_check))
                   {
                       num_tries++;
                       delete pBall;
                          pBall = nullptr;
                          break;
                   }
               }

               // No colision
               if (pBall)
               {
                   num_tries = 0;
                   balls.push_back(pBall);
                   count_num_balls++;
               }
            }
        }
    }

    if (num_tries == MAX_TRIES)
    {
        this->num_balls = 0;
    }
}

Simulator::~Simulator()
{
}

int Simulator::getNumBalls()
{
    return num_balls;
}

bool Simulator::colided(Ball* ball1, Ball* ball2)
{
    float dist_x = ball1->getPosX() - ball2->getPosX();
    float dist_y = ball1->getPosY() - ball2->getPosY();

    float dist = sqrt(dist_x * dist_x + dist_y * dist_y);
    float dist_colision = (ball1->getRadius() + ball2->getRadius());

    return (dist <= dist_colision);
}

void Simulator::execute()
{
    sf::RenderWindow window(
       sf::VideoMode(WIN_SIZE, WIN_SIZE),
       "SFML Colision Simulator"
    );

    while (window.isOpen())
    {
        // Check close window event
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();


        // Check colision between balls
        for (int i = 0; i < num_balls; i++)
        {
            for (int j = i+1; j < num_balls; j++)
            {
                if (colided(balls[i], balls[j]))
                {
                    float dist_x = balls[i]->getPosX() - balls[j]->getPosX();
                    float dist_y = balls[i]->getPosY() - balls[j]->getPosY();
                    float rq = dist_x * dist_x + dist_y * dist_y;

                    float k1 = (balls[i]->getVelX() * dist_x + balls[i]->getVelY() * dist_y) / rq;
                    float proj_1_x = k1 * dist_x;
                    float proj_1_y = k1 * dist_y;

                    float k2 = (balls[j]->getVelX() * dist_x + balls[j]->getVelY() * dist_y) / rq;
                    float proj_2_x = k2 * dist_x;
                    float proj_2_y = k2 * dist_y;

                    balls[i]->setVelX(proj_2_x + (balls[i]->getVelX() - proj_1_x));
                    balls[i]->setVelY(proj_2_y + (balls[i]->getVelY() - proj_1_y));
                    balls[j]->setVelX(proj_1_x + (balls[j]->getVelX() - proj_2_x));
                    balls[j]->setVelY(proj_1_y + (balls[j]->getVelY() - proj_2_y));
                }
            }
        }

        // Check colision with walls
        for (int i = 0; i < num_balls; i++)
        {
            if (balls[i]->getPosX() > (WIN_SIZE - 2*balls[i]->getRadius()) || balls[i]->getPosX() < 0)
            {
                balls[i]->setVelX((-1) * balls[i]->getVelX());
            }
            if (balls[i]->getPosY() > (WIN_SIZE - 2*balls[i]->getRadius()) || balls[i]->getPosY() < 0)
            {
                balls[i]->setVelY((-1) * balls[i]->getVelY());
            }
        }


        // Move and draw the balls
        window.clear(); 
        for (int i = 0; i < num_balls; i++)
        {
            balls[i]->move();
            window.draw(balls[i]->getBody());
        }
        window.display();
    }
}
