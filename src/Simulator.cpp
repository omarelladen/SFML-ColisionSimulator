#include "Simulator.h"

#define FONT_PATH "data/fonts/OpenSans-VariableFont_wdth,wght.ttf"
#define WIN_TITLE "SFML Colision Simulator"
#define MAX_TRIES 100000
#define FPS_LIMIT 60


Simulator::Simulator(int num_balls,
                     float r, float m,
                     int win_w, int win_h):
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

        std::uniform_real_distribution<float> distr_v(1.f, 3.f);

        int x = distr_pos_x(gen);
        int y = distr_pos_y(gen);

        float vx = distr_v(gen);
        float vy = distr_v(gen);


        Ball *p_ball = new Ball(x, y, vx, vy, r, m);

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

bool Simulator::colidedBalls(Ball *p_b1, Ball *p_b2)
{
    float dx = p_b1->getX() - p_b2->getX();
    float dy = p_b1->getY() - p_b2->getY();

    float d = std::sqrt(dx*dx + dy*dy);
    float d_colision = (p_b1->getR() + p_b2->getR());

    return (d <= d_colision);
}

bool Simulator::colidedWallV(Ball *b)
{
    // Left and Right
    return (b->getX() > (win_w - 2*b->getR()) ||
            b->getX() < 0);
}

bool Simulator::colidedWallH(Ball *b)
{
    // Top and Bottom
    return (b->getY() > (win_h - 2*b->getR()) ||
            b->getY() < 0);
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
    for (int i = 0; i < num_balls; i++)
    {
        Ball *p_b = balls[i];

        if (colidedWallV(p_b))
        {
            p_b->setVX((-1) * p_b->getVX());
            p_b->setPrevCol(nullptr);
        }
        if (colidedWallH(p_b))
        {
            p_b->setVY((-1) * p_b->getVY());
            p_b->setPrevCol(nullptr);
        }
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
    window.setFramerateLimit(FPS_LIMIT);  // frequency of main loop execution


    // Text Font
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
    int t = 0;

    // Real fps
    int fps = FPS_LIMIT;
    int frames = 0;


    // Grid division
    float div_x = win_w / 2;
    float div_y = win_h / 2;

    // Grid balls
    std::vector<Ball*> balls_1;
    std::vector<Ball*> balls_2;
    std::vector<Ball*> balls_3;
    std::vector<Ball*> balls_4;


    while (window.isOpen())
    {
        // Check close event
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();


        // Clear grid
        balls_1.clear();
        balls_2.clear();
        balls_3.clear();
        balls_4.clear();

        // Separate balls (each ball inside at least one)
        for (int i = 0; i < num_balls; i++)
        {
            Ball *p_ball = balls[i];
            if (p_ball->getY() - p_ball->getR() <= div_y)
            {
                if (p_ball->getX() - p_ball->getR() <= div_x)
                    balls_1.push_back(p_ball);
                if (p_ball->getX() + p_ball->getR() >= div_x)
                    balls_2.push_back(p_ball);
            }
            if (p_ball->getY() + p_ball->getR() >= div_y)
            {
                if (p_ball->getX() - p_ball->getR() <= div_x)
                    balls_3.push_back(p_ball);
                if (p_ball->getX() + p_ball->getR() >= div_x)
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
        for (int i = 0; i < num_balls; i++)
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

        for (int i = 0; i < num_balls; i++)
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

            fps = frames;
            frames = 0;
        }

        // Draw stats Text
        std::ostringstream ss;
        ss << "n=" << num_balls << std::endl
           << "r=" << balls[0]->getR() << std::endl
           << "m=" << balls[0]->getM() << std::endl
           << "M=" << m_total << std::endl
           << "Vx=" << std::setprecision(3) << vx_total << std::endl
           << "Vy=" << std::setprecision(3) << vy_total << std::endl
           << "K=" << std::setprecision(3) << k_total << std::endl
           << "Vxcm=" << std::setprecision(3) << vxcm << std::endl
           << "Vycm=" << std::setprecision(3) << vycm << std::endl
           << "res=" << win_w << "x" << win_h << std::endl
           << "fps=" << fps << std::endl
           << "t=" << t << "s" << std::endl
           ;

        text.setString(ss.str());
        window.draw(text);


        window.display();
        frames++;
    }
}
