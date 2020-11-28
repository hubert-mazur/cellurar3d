#include "include.h"
#include <unistd.h>
extern Spherical camera;
extern float fieldOfView;
Cube *cube;

bool running = true;
bool light = true;

int main()
{
    srand(time(NULL));
    sf::ContextSettings context(16, 0, 0, 4, 5);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cellurar3d", 7U, context);
    window.setVerticalSyncEnabled(true);
    reshapeScreen(window.getSize());
    initOpenGL();
    sf::Vector2i mousePosition(0, 0);
    // sf::Clock clock;
    // float time = 0.0;
    Range<> bornRule(7, 10);
    Range<> suriveRule(10, 17);
    Rules rules(bornRule, suriveRule, 0);

    cube = new Cube(rules);
    cube->initRandomData();

    while (running)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        sf::Event event;

        // start catching events
        while (window.pollEvent(event))
        {
            // case when window is resized
            if (event.type == sf::Event::Resized)
                reshapeScreen(window.getSize());

            // case for program exit
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                running = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                camera.setFi(camera.getFi() - 0.01);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                camera.setFi(camera.getFi() + 0.01);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                camera.setTheta(camera.getTheta() + 0.01);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                camera.setTheta(camera.getTheta() - 0.01);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                mousePosition = sf::Mouse::getPosition();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                float scaleFactor = 40000.0;
                sf::Vector2i currentMousePosition = sf::Mouse::getPosition();
                camera.setFi(camera.getFi() - (currentMousePosition.x - mousePosition.x) / scaleFactor);
                camera.setTheta(camera.getTheta() - (currentMousePosition.y - mousePosition.y) / scaleFactor);
            }

            if (event.type == sf::Event::MouseWheelMoved)
            {
                fieldOfView -= static_cast<float>(event.mouseWheel.delta);
                reshapeScreen(window.getSize());
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
            {
                cube->initRandomData();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            {
                cube->initRandomData(false);
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
            {
                light = !light;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad1)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) && sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                {   
                    cube->rules.getBornRule().setLower(cube->rules.getBornRule().getLower() + 1);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) && sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
                {
                    cube->rules.getBornRule().setLower(cube->rules.getBornRule().getLower() - 1);
                }
                std::cout << "Born: <" << cube->rules.getBornRule().getLower()<< ", " << cube->rules.getBornRule().getUpper() << ">\n";
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad2)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                {
                    cube->rules.getBornRule().setUpper(cube->rules.getBornRule().getUpper() + 1);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
                {
                    cube->rules.getBornRule().setUpper(cube->rules.getBornRule().getUpper() - 1);
                }
                std::cout << "Born: <" << cube->rules.getBornRule().getLower()<< ", " << cube->rules.getBornRule().getUpper() << ">\n";
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad4)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                {
                    cube->rules.getSurviveRule().setLower(cube->rules.getSurviveRule().getLower() + 1);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
                {
                    cube->rules.getSurviveRule().setLower(cube->rules.getSurviveRule().getLower() - 1);
                }
                std::cout << "Survive: <" << cube->rules.getSurviveRule().getLower()<< ", " << cube->rules.getSurviveRule().getUpper() << ">\n";
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Numpad5)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) && sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                {
                    cube->rules.getSurviveRule().setUpper(cube->rules.getSurviveRule().getUpper() + 1);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) && sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
                {
                    cube->rules.getSurviveRule().setUpper(cube->rules.getSurviveRule().getUpper() - 1);
                }
                std::cout << "Survive: <" << cube->rules.getSurviveRule().getLower()<< ", " << cube->rules.getSurviveRule().getUpper() << ">\n";
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)
            {
                if (cube->rules.getNeighbourhoodRule() == 0)
                    cube->rules.setNeighbourhood(1);
                else
                    cube->rules.setNeighbourhood(0);

                std::cout<<"Neighbourhood: "<<(cube->rules.getNeighbourhoodRule() ? "von Neumann" : "Moore")<<std::endl;
            }
        }

        drawScene();
        window.display();
        // time = clock.restart().asSeconds();

        Cube *tmp;
        tmp = cube;
        cube = cube->evolve();
        delete tmp;
    }
    cube->~Cube();
}