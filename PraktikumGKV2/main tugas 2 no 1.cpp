#include <GL/glut.h>
#include <math.h>

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glPushMatrix();
    #define PI 3.1415926535898
    GLint circle_points = 100;
    int i;
    float angle;
    glColor3f(0.5f, 0.8f, 0.7f);
    glBegin(GL_LINE_LOOP);
        for (i = 0; i < circle_points; i++) {
            angle = 2 * PI * i / circle_points;
            glVertex2f(cos(angle), sin(angle));
        }
    glEnd();
    glPopMatrix();
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Lingkaran");
    glutDisplayFunc(RenderScene);
    glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
    glutMainLoop();
    return 0;
}

