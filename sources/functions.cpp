#include "include.h"

Spherical camera(3.0f, 0.2f, 1.8f);
float fieldOfView = 45.0;
extern Cube *cube;
extern bool running;
extern pthread_mutex_t mutex;
extern bool light;

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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_ambient_global[4] = {0.5, 0.4, 0.3, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_global);

} //

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Spherical north_of_camera(camera.getDistance(), camera.getTheta() + 0.01f, camera.getFi());
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              north_of_camera.getX(), north_of_camera.getY(), north_of_camera.getZ());

    if (light)
        glEnable(GL_LIGHT0);

    // draw a box
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(3.0);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            glVertex3f(-0.5 + 1 * (i ^ j), -0.5 + 1 * j, -0.5);
            glVertex3f(-0.5 + 1 * (i ^ j), -0.5 + 1 * j, 0.5);
            glVertex3f(-0.5, -0.5 + 1 * (i ^ j), -0.5 + 1 * j);
            glVertex3f(0.5, -0.5 + 1 * (i ^ j), -0.5 + 1 * j);
            glVertex3f(-0.5 + 1 * (i ^ j), -0.5, -0.5 + 1 * j);
            glVertex3f(-0.5 + 1 * (i ^ j), 0.5, -0.5 + 1 * j);
        }
    }
    glEnd();

    GLUquadricObj *qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    int size = cube->getSize();

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                int state = cube->getCube()[i][j][k].getState();
                int age = cube->getCube()[i][j][k].getAge();

                if (!state)
                {
                    continue;
                }

                glPushMatrix();
                glColor3f((i * 8.5) / 255.0, (j * 8.5) / 255.0, (k * 8.5) / 255.0);
                glTranslatef(static_cast<float>(i) / 30.0 - 0.5, static_cast<float>(j) / 30.0 - 0.5, static_cast<float>(k) / 30.0 - 0.5);
                gluSphere(qobj, age / 10.0 * 0.015, 10, 5);
                glPopMatrix();
            }
        }
    }

    if (light)
        glDisable(GL_LIGHT0);

    glEnd();
    glFlush();
}
