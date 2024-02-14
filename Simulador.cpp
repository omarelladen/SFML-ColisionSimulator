#include "Simulador.h"

Simulador::Simulador():
    bolas()
{
    for (int i = 0; i < 2; i++)
    {
        Bola* pBola = new Bola();
        if (pBola)
        {
            bolas.push_back(pBola);
            pBola = nullptr;
            //printf("Bola criada\n");
        }
    }

    /*this->*/Executar();
}

Simulador::~Simulador()
{
}

float Simulador::Colidiu(Bola* bola1, Bola* bola2)
{
    float dist_x = bola1->pos.x - bola2->pos.x;
    float dist_y = bola1->pos.y - bola2->pos.y;


    return (sqrt(dist_x * dist_x + dist_y * dist_y) <= (bola1->raio + bola2->raio));
}

void Simulador::Executar()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!"); //janela = new RenderWindow(VideoMode(1000, 900), "Jogo");

    //CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    
    bolas[0]->pos = Vector2f(600, 400);/////////
    bolas[0]->corpo.setPosition(bolas[0]->pos);
    bolas[0]->corpo.setFillColor(sf::Color::Green);///////////
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }



        //shape.move(0.07, 0);

        // Move/Atualiza as posições
        bolas[0]->executar();
        bolas[1]->executar();

        



        // Verifica colisao com as paredes


        // Verifica colisao entre as bolas
        if (Colidiu(bolas[0], bolas[1]))
        {
            //printf("Colidiu!\n");

        


            float dist_x = bolas[0]->pos.x - bolas[1]->pos.x;
            float dist_y = bolas[0]->pos.y - bolas[1]->pos.y;
            float rq = dist_x * dist_x + dist_y * dist_y;


            float k1 = (bolas[0]->vel.x * dist_x + bolas[0]->vel.y * dist_y) / rq;
            float proj_1_x = k1 * dist_x;
            float proj_1_y = k1 * dist_y;

            float k2 = (bolas[1]->vel.x * dist_x + bolas[1]->vel.y * dist_y) / rq;
            float proj_2_x = k2 * dist_x;
            float proj_2_y = k2 * dist_y;




            bolas[0]->vel.x = proj_2_x + (bolas[0]->vel.x - proj_1_x);
            bolas[0]->vel.y = proj_2_y + (bolas[0]->vel.y - proj_1_y);
            bolas[1]->vel.x = proj_1_x + (bolas[1]->vel.x - proj_2_x);
            bolas[1]->vel.y = proj_1_y + (bolas[1]->vel.y - proj_2_y);
        }


        /*float pos_x_1 = bolas[0]->corpo.getPosition().x;
        float pos_y_1 = bolas[0]->corpo.getPosition().y;
        float pos_x_2 = bolas[1]->corpo.getPosition().x;
        float pos_y_2 = bolas[1]->corpo.getPosition().y;*/

        for (int i = 0; i < 2; i++)
        {
            if (bolas[i]->corpo.getPosition().x > (1000 - bolas[i]->raio) || bolas[i]->corpo.getPosition().x < 0)
            {
                //bolas[i]->corpo.setPosition(500, pos_x_1);
                bolas[i]->setVel(Vector2f((-1) * bolas[i]->vel.x, bolas[i]->vel.y));
            }
            else if (bolas[i]->corpo.getPosition().y > (1000 - 200) || bolas[i]->corpo.getPosition().y < 0)
            {
                //bolas[i]->corpo.setPosition(500, pos_x_1);
                bolas[i]->setVel(Vector2f(bolas[i]->vel.x, (-1) * bolas[i]->vel.y));
            }
        }
        
 





        window.clear();
        //window.draw(shape);
        // Desenha as bolas
        window.draw(bolas[0]->corpo);
        window.draw(bolas[1]->corpo);
        window.display();
    }
}
