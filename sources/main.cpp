#include "include.h"

extern Spherical camera;
extern float fieldOfView;

int main()
{
    bool running = true;
    sf::ContextSettings context(16, 0, 0, 4, 5);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cellurar3d", 7U, context);
    // window.setVerticalSyncEnabled(true);
    reshapeScreen(window.getSize());
    initOpenGL();
    sf::Vector2i mousePosition(0, 0);

    sf::Clock clck;

    Cube cube = Cube(Rules(Range<>(13,18), Range<>(10,20), Range<>(6,23)));

    while (running)
    {
        clck.restart();
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
        }

        drawScene();
        window.display();
        cube.evolve();

        float currentTime = clck.restart().asSeconds();
        float fps = 1.f / (currentTime);
        std::cout << fps << std::endl;
    }
}