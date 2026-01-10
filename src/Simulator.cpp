#include "Simulator.h"

#define FONT_PATH "data/fonts/OpenSans-VariableFont_wdth,wght.ttf"
#define WIN_TITLE "SFML Colision Simulator"
#define MAX_TRIES 100000
#define FPS_LIMIT 60
#define NUM_CELLS 4


Simulator::Simulator(unsigned int num_balls,
                     float r, float m,
                     unsigned int win_w, unsigned int win_h):
    balls(),
    num_balls(0),
    win_w(win_w),
    win_h(win_h)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    balls.reserve(num_balls);

    unsigned int num_new_balls = 0;
    unsigned int num_tries = 0;
    while (num_new_balls < num_balls &&
           num_tries < MAX_TRIES)
    {
        // Generate random values
        std::uniform_int_distribution<int> distr_pos_x(1, win_w - 2*r - 1);
        std::uniform_int_distribution<int> distr_pos_y(1, win_h - 2*r - 1);
        std::uniform_real_distribution<float> distr_v(1.f, 3.f);

        unsigned int x = distr_pos_x(gen);
        unsigned int y = distr_pos_y(gen);
        float vx = distr_v(gen);
        float vy = distr_v(gen);


        Ball *p_ball = new Ball(x, y, vx, vy, r, m);

        if (p_ball)
        {
            // Push first ball
            if (balls.empty())
            {
                balls.push_back(p_ball);
                num_new_balls++;
            }
            else
            {
               // Check overlap
               for (unsigned int i = 0; i < num_new_balls; i++)
               {
                   Ball *p_ball_check = balls[i];
                   if (p_ball_check != p_ball &&
                       colidedBalls(p_ball, p_ball_check))
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
                   num_new_balls++;
               }
            }
        }
    }

    if (num_tries == MAX_TRIES)
        this->num_balls = 0;
    else
        this->num_balls = balls.size();
}

Simulator::~Simulator()
{
    for (unsigned int i = 0; i < num_balls; i++)
    {
        delete balls[i];
        balls[i] = nullptr;
    }
}

unsigned int Simulator::getNumBalls() const
{
    return num_balls;
}

bool Simulator::colidedBalls(Ball *p_b1, Ball *p_b2) const
{
    float dx = p_b1->getX() - p_b2->getX();
    float dy = p_b1->getY() - p_b2->getY();

    float d = std::sqrt(dx*dx + dy*dy);
    float d_colision = (p_b1->getR() + p_b2->getR());

    return (d <= d_colision);
}

bool Simulator::colidedWallLeft(Ball *p_b) const
{
    return (p_b->getX() < 0);
}

bool Simulator::colidedWallRight(Ball *p_b) const
{
    return (p_b->getX() > (win_w - 2*p_b->getR()));
}

bool Simulator::colidedWallTop(Ball *p_b) const
{
    return (p_b->getY() < 0);
}

bool Simulator::colidedWallBottom(Ball *p_b) const
{
    return (p_b->getY() > (win_h - 2*p_b->getR()));
}

void Simulator::updateColisionVel(Ball *p_b1, Ball *p_b2)
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

void Simulator::checkColisionsBalls(std::vector<Ball*>& balls)
{
    unsigned int num_balls = balls.size();

    // Check colision between balls
    for (unsigned int i = 0; i < num_balls; i++)
    {
        for (unsigned int j = i+1; j < num_balls; j++)
        {
            Ball *p_b1 = balls[i];
            Ball *p_b2 = balls[j];

            if (colidedBalls(p_b1, p_b2) &&
                (p_b1->getPrevCol() != p_b2 ||
                 p_b2->getPrevCol() != p_b1))
            {
                updateColisionVel(p_b1, p_b2);
                p_b1->setPrevCol(p_b2);
                p_b2->setPrevCol(p_b1);
            }
        }
    }
}

void Simulator::checkColisionsWalls(std::vector<Ball*>& balls)
{
    for (unsigned int i = 0; i < num_balls; i++)
    {
        Ball *p_b = balls[i];
        float vx = p_b->getVX();
        float vy = p_b->getVY();

        bool wall_colision = false;

        if (colidedWallLeft(p_b))
        {
            if (vx < 0)
                p_b->setVX(-vx);
            wall_colision = true;
        }
        if (colidedWallRight(p_b))
        {
            if (vx > 0)
                p_b->setVX(-vx);
            wall_colision = true;
        }
        if (colidedWallTop(p_b))
        {
            if (vy < 0)
                p_b->setVY(-vy);
            wall_colision = true;
        }
        if (colidedWallBottom(p_b))
        {
            if (vy > 0)
                p_b->setVY(-vy);
            wall_colision = true;
        }

        if (wall_colision)   
            p_b->setPrevCol(nullptr);
    }
}

void Simulator::execute()
{
    // Window
    sf::RenderWindow window(
       sf::VideoMode(win_w, win_h),
       WIN_TITLE,
       sf::Style::Close
    );
    window.setFramerateLimit(FPS_LIMIT);  // freq of main loop execution


    // Stats String
    std::ostringstream ss;
    ss << std::setprecision(3);

    // Stats Font
    sf::Font font;
    font.loadFromFile(FONT_PATH);

    // Stats Text
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(12);
    text.setPosition(10,10);


    // Clock
    sf::Clock clock;
    unsigned int t = 0;

    // Real fps
    unsigned int fps = FPS_LIMIT;
    unsigned int num_frames = 0;


    // Grid division
    float div_x = win_w / 2;
    float div_y = win_h / 2;


    // Cell balls
    std::vector<Ball*> balls_1;
    std::vector<Ball*> balls_2;
    std::vector<Ball*> balls_3;
    std::vector<Ball*> balls_4;

    balls_1.reserve(num_balls);
    balls_2.reserve(num_balls);
    balls_3.reserve(num_balls);
    balls_4.reserve(num_balls);


    while (window.isOpen())
    {
        // Check close event
        sf::Event event;
        while (window.pollEvent(event))
        {
            // X
            if (event.type == sf::Event::Closed)
                window.close();

            // Ctrl+Q
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) &&
                (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
                window.close();
        }


        // Clear cell balls
        balls_1.clear();
        balls_2.clear();
        balls_3.clear();
        balls_4.clear();

        // Insert each ball inside at least one cell
        for (unsigned int i = 0; i < num_balls; i++)
        {
            Ball *p_ball = balls[i];
            float x = p_ball->getX();
            float y = p_ball->getY();
            float r = p_ball->getR();

            if (y <= div_y)
            {
                if (x <= div_x)
                    balls_1.push_back(p_ball);
                if (x + 2*r >= div_x)
                    balls_2.push_back(p_ball);
            }
            if (y + 2*r >= div_y)
            {
                if (x <= div_x)
                    balls_3.push_back(p_ball);
                if (x + 2*r >= div_x)
                    balls_4.push_back(p_ball);
            }
        }


        // Check colision with walls
        checkColisionsWalls(balls);

        // Check colision between balls of the same grid
        checkColisionsBalls(balls_1);
        checkColisionsBalls(balls_2);
        checkColisionsBalls(balls_3);
        checkColisionsBalls(balls_4);


        // Move and draw the balls
        window.clear(sf::Color::Black);
        for (unsigned int i = 0; i < num_balls; i++)
        {
            Ball *p_b = balls[i];
            p_b->move();
            window.draw(p_b->getBody());
        }


        // Calculate stats
        double vx_total = 0;
        double vy_total = 0;
        double  m_total = 0;
        double  k_total = 0;

        for (unsigned int i = 0; i < num_balls; i++)
        {
            Ball *p_b = balls[i];

            float vx = p_b->getVX();
            float vy = p_b->getVY();
            float m = p_b->getM();

            vx_total += vx;
            vy_total += vy;
            k_total += m*(vx*vx + vy*vy);
            m_total += m;
        }
        k_total /= 2;

        float vxcm = vx_total / m_total;
        float vycm = vy_total / m_total;


        // Count time
        if (clock.getElapsedTime().asMilliseconds() >= 1000)
        {
            t++;
            clock.restart();

            fps = num_frames;
            num_frames = 0;
        }

        // Draw stats Text
        ss << "n="     << num_balls        << std::endl
           << "r="     << balls[0]->getR() << std::endl
           << "m="     << balls[0]->getM() << std::endl
           << "M="     << m_total          << std::endl
           << "Vx="    << vx_total         << std::endl
           << "Vy="    << vy_total         << std::endl
           << "K="     << k_total          << std::endl
           << "Vxcm="  << vxcm             << std::endl
           << "Vycm="  << vycm             << std::endl
           << "res="   << win_w <<"x"
                       << win_h            << std::endl
           << "cells=" << NUM_CELLS        << std::endl
           << "fps="   << fps              << std::endl
           << "t="     << t << "s"         << std::endl
           ;

        text.setString(ss.str());
        window.draw(text);
        ss.str("");
        ss.clear();


        window.display();
        num_frames++;
    }
}
