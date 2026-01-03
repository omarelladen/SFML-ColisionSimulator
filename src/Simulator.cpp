#include "Simulator.h"
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>


Simulator::Simulator(int num_balls):
    balls(),
    num_balls(num_balls)
{

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < num_balls; i++)
    {
        Ball* pBall = new Ball(gen);
        if (pBall)
        {
        	cout << i << endl;

            balls.push_back(pBall);
            pBall = nullptr;
        }
    }

    /*this->*/Execute();
}

Simulator::~Simulator()
{
}

float Simulator::Colided(Ball* ball1, Ball* ball2)
{
    float dist_x = ball1->pos.x - ball2->pos.x;
    float dist_y = ball1->pos.y - ball2->pos.y;

    return (sqrt(dist_x * dist_x + dist_y * dist_y) <= (ball1->radius + ball2->radius));
}

void Simulator::Execute()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Colision Simulator!");  // window = new RenderWindow(VideoMode(1000, 900), "Jogo");

    // CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    
    // balls[0]->pos = Vector2f(600, 400);  /////////
    // balls[0]->body.setPosition(balls[0]->pos);
    // balls[0]->body.setFillColor(sf::Color::Green);  ///////////

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();


        // shape.move(0.07, 0);

        // Move/Update the positions
		for (int i = 0; i < num_balls; i++)
		{
            balls[i]->execute();
        }

        // Check colision with the walls


        // Check colision between the balls
		for (int i = 0; i < num_balls; i++)
		{
		    for (int j = i+1; j < num_balls; j++)
	        {
	        	if (Colided(balls[i], balls[j]))
	        	{
		            cout << "colided " << i << j << endl;

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


        /*
        float pos_x_1 = balls[0]->body.getPosition().x;
        float pos_y_1 = balls[0]->body.getPosition().y;
        float pos_x_2 = balls[1]->body.getPosition().x;
        float pos_y_2 = balls[1]->body.getPosition().y;
        */

        for (int i = 0; i < num_balls; i++)
        {
            if (balls[i]->body.getPosition().x > (1000 - 2*balls[i]->radius) || balls[i]->body.getPosition().x < 0)
            {
                // balls[i]->body.setPosition(500, pos_x_1);
                balls[i]->setVel(Vector2f((-1) * balls[i]->vel.x, balls[i]->vel.y));
            }
            else if (balls[i]->body.getPosition().y > (1000 - 2*balls[i]->radius) || balls[i]->body.getPosition().y < 0)
            {
                // balls[i]->body.setPosition(500, pos_x_1);
                balls[i]->setVel(Vector2f(balls[i]->vel.x, (-1) * balls[i]->vel.y));
            }
        }


        window.clear();
        // window.draw(shape);

        // Draw the balls
        for (int i = 0; i < num_balls; i++)
        {
            window.draw(balls[i]->body);
        }
        window.display();
    }
}
