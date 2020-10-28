#include "include.h"

static Spherical camera(3.0f, 0.2f, 1.2f);
static float fieldOfView = 25.0;

void reshapeScreen(sf::Vector2u screenSize)
{
    glViewport(0, 0, static_cast<GLsizei>(screenSize.x), static_cast<GLsizei>(screenSize.y));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fieldOfView, screenSize.x / screenSize.y, 0.2, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void initOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Spherical north_of_camera(camera.getDistance(), camera.getTheta() + 0.01f, camera.getFi());
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              north_of_camera.getX(), north_of_camera.getY(), north_of_camera.getZ());

    // draw a box
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(3.0);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            glVertex3f(-0.3 + 0.6 * (i ^ j), -0.3 + 0.6 * j, -0.3);
            glVertex3f(-0.3 + 0.6 * (i ^ j), -0.3 + 0.6 * j, 0.3);
            glVertex3f(-0.3, -0.3 + 0.6 * (i ^ j), -0.3 + 0.6 * j);
            glVertex3f(0.3, -0.3 + 0.6 * (i ^ j), -0.3 + 0.6 * j);
            glVertex3f(-0.3 + 0.6 * (i ^ j), -0.3, -0.3 + 0.6 * j);
            glVertex3f(-0.3 + 0.6 * (i ^ j), 0.3, -0.3 + 0.6 * j);
        }
    }

    glEnd();
    glFlush();
}