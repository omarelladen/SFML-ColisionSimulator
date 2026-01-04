#include "Simulator.h"

#define MAX_TRIES 100000
#define WIN_SIZE 600


Simulator::Simulator(int num_balls):
    balls(),
    num_balls(num_balls)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int count_new_balls = 0;
    int num_tries = 0;
    while (count_new_balls < this->num_balls && num_tries < MAX_TRIES)
    {
        // Generate random values
        std::uniform_int_distribution<int> distPos(100, WIN_SIZE-100);
        std::uniform_real_distribution<float> distV(0.1f, 0.3f);

        int x = distPos(gen);
        int y = distPos(gen);

        float vx = distV(gen);
        float vy = distV(gen);

        Ball *pBall = new Ball(x, y, vx, vy);

        if (pBall)
        {
            // Push first ball
            if (balls.empty())
            {
                balls.push_back(pBall);
                count_new_balls++;
            }
            else
            {
               // Check overlap
               for (int i = 0; i < count_new_balls; i++)
               {
                   Ball *pBall_check = balls[i];
                   if (pBall_check != pBall && colided_ball(pBall, pBall_check))
                   {
                       num_tries++;
                       delete pBall;
                       pBall = nullptr;
                       break;
                   }
               }

               // Push if no overlap
               if (pBall)
               {
                   num_tries = 0;
                   balls.push_back(pBall);
                   count_new_balls++;
               }
            }
        }
    }

    if (num_tries == MAX_TRIES)
        this->num_balls = 0;
}

Simulator::~Simulator()
{
    for (int i = 0; i < num_balls; i++)
        delete balls[i];
}

int Simulator::getNumBalls()
{
    return num_balls;
}

bool Simulator::colided_ball(Ball *b1, Ball *b2)
{
    float dx = b1->getX() - b2->getX();
    float dy = b1->getY() - b2->getY();

    float d = std::sqrt(dx*dx + dy*dy);
    float d_colision = (b1->getR() + b2->getR());

    return (d <= d_colision);
}

bool Simulator::colided_wall_v(Ball *b)
{
    return (b->getX() > (WIN_SIZE - 2*b->getR()) ||
            b->getX() < 0);
}

bool Simulator::colided_wall_h(Ball *b)
{
    return (b->getY() > (WIN_SIZE - 2*b->getR()) ||
            b->getY() < 0);
}

void Simulator::update_colision_vel(Ball *b1, Ball *b2)
{
    float dx = b1->getX() - b2->getX();
    float dy = b1->getY() - b2->getY();

    float rq = dx*dx + dy*dy;

    float k1 = (b1->getVX()*dx + b1->getVY()*dy) / rq;
    float k2 = (b2->getVX()*dx + b2->getVY()*dy) / rq;

    // Vector projetion on the colision direction
    float proj_vx_1 = k1 * dx;
    float proj_vy_1 = k1 * dy;
    float proj_vx_2 = k2 * dx;
    float proj_vy_2 = k2 * dy;

    // Vector orthogonal to the colision direction
    float oproj_vx_1 = b1->getVX() - proj_vx_1;
    float oproj_vy_1 = b1->getVY() - proj_vy_1;
    float oproj_vx_2 = b2->getVX() - proj_vx_2;
    float oproj_vy_2 = b2->getVY() - proj_vy_2;

    b1->setVX(proj_vx_2 + oproj_vx_1);
    b1->setVY(proj_vy_2 + oproj_vy_1);
    b2->setVX(proj_vx_1 + oproj_vx_2);
    b2->setVY(proj_vy_1 + oproj_vy_2);
}

void Simulator::execute()
{
    // Window
    sf::RenderWindow window(
       sf::VideoMode(WIN_SIZE, WIN_SIZE),
       "SFML Colision Simulator"
    );

    // Text Font
    sf::Font font;
    font.loadFromFile("data/fonts/OpenSans-VariableFont_wdth,wght.ttf");

    // Info Text
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(12);
    text.setPosition(10,10);


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
                Ball *b1 = balls[i];
                Ball *b2 = balls[j];

                if (colided_ball(b1, b2))
                {
                    update_colision_vel(b1, b2);
                }
            }
        }

        // Check colision with walls
        for (int i = 0; i < num_balls; i++)
        {
            Ball *b = balls[i];

            if (colided_wall_v(b))
            {
                b->setVX((-1) * b->getVX());
            }
            if (colided_wall_h(b))
            {
                b->setVY((-1) * b->getVY());
            }
        }

        // Move and draw the balls
        window.clear(sf::Color::Black);
        for (int i = 0; i < num_balls; i++)
        {
            Ball *b = balls[i];
            b->move();
            window.draw(b->getBody());
        }

        // Calculate kinectic energy (m=1)
        double k = 0;
        for (int i = 0; i < num_balls; i++)
        {
            Ball *b = balls[i];
            float vx = b->getVX();
            float vy = b->getVY();
            k += vx*vx + vy*vy;
        }

        // Draw Info Text
        std::ostringstream ss;
        ss << "n=" << num_balls << std::endl
           << "r=" << balls[0]->getR() << std::endl
           << "K=" << k;
        text.setString(ss.str());
	    window.draw(text);


		window.display();
    }
}
