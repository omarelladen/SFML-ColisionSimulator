#include "Simulator.h"

#define MAX_TRIES 100000

Simulator::Simulator(int num_balls, int r, int win_w, int win_h):
    balls(),
    num_balls(num_balls),
    win_w(win_w),
    win_h(win_h)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int count_new_balls = 0;
    int num_tries = 0;
    while (count_new_balls < this->num_balls &&
           num_tries < MAX_TRIES)
    {
        // Generate random values
        std::uniform_int_distribution<int> distr_pos_x(1, win_w - 2*r - 1);
        std::uniform_int_distribution<int> distr_pos_y(1, win_h - 2*r - 1);

        std::uniform_real_distribution<float> distr_v(0.1f, 0.3f);

        int x = distr_pos_x(gen);
        int y = distr_pos_y(gen);

        float vx = distr_v(gen);
        float vy = distr_v(gen);


        Ball *p_ball = new Ball(x, y, vx, vy, r);

        if (p_ball)
        {
            // Push first ball
            if (balls.empty())
            {
                balls.push_back(p_ball);
                count_new_balls++;
            }
            else
            {
               // Check overlap
               for (int i = 0; i < count_new_balls; i++)
               {
                   Ball *p_ball_check = balls[i];
                   if (p_ball_check != p_ball &&
                       colided_ball(p_ball, p_ball_check))
                   {
                       num_tries++;
                       delete p_ball;
                       p_ball = nullptr;
                       break;
                   }
               }

               // Push if no overlap
               if (p_ball)
               {
                   num_tries = 0;
                   balls.push_back(p_ball);
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

bool Simulator::colided_ball(Ball *p_b1, Ball *p_b2)
{
    float dx = p_b1->getX() - p_b2->getX();
    float dy = p_b1->getY() - p_b2->getY();

    float d = std::sqrt(dx*dx + dy*dy);
    float d_colision = (p_b1->getR() + p_b2->getR());

    return (d <= d_colision);
}

bool Simulator::colided_wall_v(Ball *b)
{
    // Left and Right
    return (b->getX() > (win_w - 2*b->getR()) ||
            b->getX() < 0);
}

bool Simulator::colided_wall_h(Ball *b)
{
    // Top and Bottom
    return (b->getY() > (win_h - 2*b->getR()) ||
            b->getY() < 0);
}

void Simulator::update_colision_vel(Ball *p_b1, Ball *p_b2)
{
    float dx = p_b1->getX() - p_b2->getX();
    float dy = p_b1->getY() - p_b2->getY();

    float div = dx*dx + dy*dy;

    float c1 = (p_b1->getVX()*dx + p_b1->getVY()*dy) / div;
    float c2 = (p_b2->getVX()*dx + p_b2->getVY()*dy) / div;

    // Vector projetion on the colision direction
    float proj_vx_1 = c1 * dx;
    float proj_vy_1 = c1 * dy;
    float proj_vx_2 = c2 * dx;
    float proj_vy_2 = c2 * dy;

    // Vector orthogonal to the colision direction
    float oproj_vx_1 = p_b1->getVX() - proj_vx_1;
    float oproj_vy_1 = p_b1->getVY() - proj_vy_1;
    float oproj_vx_2 = p_b2->getVX() - proj_vx_2;
    float oproj_vy_2 = p_b2->getVY() - proj_vy_2;

    p_b1->setVX(proj_vx_2 + oproj_vx_1);
    p_b1->setVY(proj_vy_2 + oproj_vy_1);
    p_b2->setVX(proj_vx_1 + oproj_vx_2);
    p_b2->setVY(proj_vy_1 + oproj_vy_2);
}

void Simulator::execute()
{
    // Window
    sf::RenderWindow window(
       sf::VideoMode(win_w, win_h),
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
                Ball *p_b1 = balls[i];
                Ball *p_b2 = balls[j];

                if (colided_ball(p_b1, p_b2) &&
                    (p_b1->getPrevCol() != p_b2 ||
                     p_b2->getPrevCol() != p_b1))
                {
                    update_colision_vel(p_b1, p_b2);
                    p_b1->setPrevCol(p_b2);
                    p_b2->setPrevCol(p_b1);
                }
            }
        }

        // Check colision with walls
        for (int i = 0; i < num_balls; i++)
        {
            Ball *p_b = balls[i];

            if (colided_wall_v(p_b))
            {
                p_b->setVX((-1) * p_b->getVX());
                p_b->setPrevCol(nullptr);
            }
            if (colided_wall_h(p_b))
            {
                p_b->setVY((-1) * p_b->getVY());
                p_b->setPrevCol(nullptr);
            }
        }

        // Move and draw the balls
        window.clear(sf::Color::Black);
        for (int i = 0; i < num_balls; i++)
        {
            Ball *p_b = balls[i];
            p_b->move();
            window.draw(p_b->getBody());
        }

        // Calculate kinectic energy (m=1)
        double k = 0;
        for (int i = 0; i < num_balls; i++)
        {
            Ball *p_b = balls[i];
            float vx = p_b->getVX();
            float vy = p_b->getVY();
            k += vx*vx + vy*vy;
        }

        // Draw Info Text
        std::ostringstream ss;
        ss << "n=" << num_balls << std::endl
           << "r=" << balls[0]->getR() << std::endl
           << "w=" << win_w << std::endl
           << "h=" << win_h << std::endl
           << "K=" << std::setprecision(4) << k << std::endl;

        text.setString(ss.str());
	    window.draw(text);

		window.display();
    }
}
