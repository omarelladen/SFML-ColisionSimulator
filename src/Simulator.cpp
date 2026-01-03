#include "Simulator.h"
#include <cmath>
#include <random>
#include <ctime>

#define MAX_TRIES 100000


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

float Simulator::colided(Ball* ball1, Ball* ball2)
{
    float dist_x = ball1->pos.x - ball2->pos.x;
    float dist_y = ball1->pos.y - ball2->pos.y;

    float dist = sqrt(dist_x * dist_x + dist_y * dist_y);
    float dist_colision =  (ball1->radius + ball2->radius);

    return (dist <= dist_colision);
}

void Simulator::execute()
{
    sf::RenderWindow window(
       sf::VideoMode(1000, 1000),
       "SFML Colision Simulator"
    );

    while (window.isOpen())
    {
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
                    float dist_x = balls[i]->pos.x - balls[j]->pos.x;
                    float dist_y = balls[i]->pos.y - balls[j]->pos.y;
                    float rq = dist_x * dist_x + dist_y * dist_y;

                    float k1 = (balls[i]->vel.x * dist_x + balls[i]->vel.y * dist_y) / rq;
                    float proj_1_x = k1 * dist_x;
                    float proj_1_y = k1 * dist_y;

                    float k2 = (balls[j]->vel.x * dist_x + balls[j]->vel.y * dist_y) / rq;
                    float proj_2_x = k2 * dist_x;
                    float proj_2_y = k2 * dist_y;

                    balls[i]->vel.x = proj_2_x + (balls[i]->vel.x - proj_1_x);
                    balls[i]->vel.y = proj_2_y + (balls[i]->vel.y - proj_1_y);
                    balls[j]->vel.x = proj_1_x + (balls[j]->vel.x - proj_2_x);
                    balls[j]->vel.y = proj_1_y + (balls[j]->vel.y - proj_2_y);
                }
            }
        }

        // Check colision with walls
        for (int i = 0; i < num_balls; i++)
        {
            if (balls[i]->body.getPosition().x > (1000 - 2*balls[i]->radius) || balls[i]->body.getPosition().x < 0)
            {
                balls[i]->setVel(Vector2f((-1) * balls[i]->vel.x, balls[i]->vel.y));
            }
            if (balls[i]->body.getPosition().y > (1000 - 2*balls[i]->radius) || balls[i]->body.getPosition().y < 0)
            {
                balls[i]->setVel(Vector2f(balls[i]->vel.x, (-1) * balls[i]->vel.y));
            }
        }


        // Move and draw the balls
        window.clear(); 
        for (int i = 0; i < num_balls; i++)
        {
            balls[i]->move();
            window.draw(balls[i]->body);
        }
        window.display();
    }
}
