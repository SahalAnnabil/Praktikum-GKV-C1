#include <gl/glut.h>
#include <math.h>

void Resize(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (aspect >= 1.0) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect); 
    }

    glMatrixMode(GL_MODELVIEW);
}




void DrawGradientBackground() {
    glBegin(GL_QUADS);
        glColor3f(0.61f, 0.77f, 0.91f); glVertex2f(-2.45f, -0.9f); 
        glColor3f(0.61f, 0.77f, 0.91f); glVertex2f(2.45f, -0.9f);  
        glColor3f(0.425f, 0.685f, 0.935f); glVertex2f(2.45f, 1.0f);  
        glColor3f(0.42f, 0.68f, 0.93f); glVertex2f(-2.45f, 1.0f);   
    glEnd();
}

void DrawRoad() {
    glBegin(GL_QUADS);
        glColor3f(0.6f, 0.62f, 0.63f); glVertex2f(-2.45f, -1.0f); 
        glColor3f(0.55f, 0.578f, 0.59f); glVertex2f(2.45f, -1.0f);   
        glColor3f(0.55f, 0.578f, 0.59f); glVertex2f(2.45f, -0.44f); 
        glColor3f(0.6f, 0.62f, 0.63f); glVertex2f(-2.45f, -0.66f);
    glEnd();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glLineWidth(5.0f);
    glColor4f(0.8f, 0.8f, 0.8f, 0.4f); 
    glBegin(GL_LINES);
        glVertex2f(-2.45f, -0.66f);
        glVertex2f(2.45f, -0.44f);
    glEnd();

    glDisable(GL_BLEND);
}


void DrawGunung() {	
    glBegin(GL_POLYGON);
        glColor3f(0.45f, 0.7f, 0.85f);
        glVertex2f(-2.45f, -0.6f);
        glVertex2f(-1.95f, -0.4f);
        glVertex2f(-1.47f, -0.5f);
        glVertex2f(-0.98f, -0.3f);
        glVertex2f(-0.49f, -0.4f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(0.49f, -0.3f);
        glVertex2f(0.98f, -0.4f);
        glVertex2f(1.47f, -0.2f);
        glVertex2f(1.95f, -0.3f);
        glVertex2f(2.45f, -0.4f);
        glColor3f(1.47f, 0.85f, 1.0f);
        glVertex2f(2.45f, -1.0f);
        glVertex2f(-2.45f, -1.0f);
    glEnd();
}

void DrawMobil() {

    glBegin(GL_POLYGON);
        glColor3f(0.3f, 0.3f, 0.4f);
        glVertex2f(-0.73f, -0.5f);//E
        glVertex2f(-0.73f, -0.3f); //C
        glVertex2f(-0.49f, 0.0f); //A
        glVertex2f(0.245f, 0.0f);//B
        glVertex2f(0.49f, -0.2f);//D
        glVertex2f(0.98f, -0.3f);//F
        glVertex2f(0.98f, -0.5f);//G
        glVertex2f(0.73f, -0.55f);//I
        glVertex2f(-0.49f, -0.6f);//H
        glVertex2f(-0.73f, -0.5f);
    glEnd();
    
    glBegin(GL_POLYGON);
        glColor3f(0.42f, 0.53f, 0.7f);
        glVertex2f(-0.7f, -0.48f);//E
        glVertex2f(-0.7f, -0.3f); //C
        glVertex2f(-0.47f, -0.01f); //A
        glVertex2f(0.22f, -0.01f);//B
        glVertex2f(0.46f, -0.21f);//D
        glVertex2f(0.955f, -0.31f);//F
        glVertex2f(0.955f, -0.45f);//G
	glEnd();
	
	glBegin(GL_POLYGON);
        glColor3f(0.35f, 0.33f, 0.4f);
        glVertex2f(-0.62f, -0.25f); //C
        glVertex2f(-0.45f, -0.03f); //A
        glVertex2f(0.2f, -0.03f);//B
        glVertex2f(0.43f, -0.23f);//D
	glEnd();
	
    glLineWidth(8.0f);
    glColor3f(0.42f, 0.53f, 0.7f);

    glBegin(GL_LINES);
        glVertex2f(-0.12f, -0.03f);
        glVertex2f(-0.11f, -0.25f); 
    glEnd();
    
    glLineWidth(3.0f);
    glColor3f(0.45f, 0.57f, 0.72f);

    glBegin(GL_LINES);
        glVertex2f(-0.7f, -0.3f);
        glVertex2f(0.955f, -0.31f); 
    glEnd();

            
}

void DrawCircle(float cx, float cy) {
    const float fixedRadius = 0.13f;
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    
    #define PI 3.1415926535898
    GLint circle_points = 100;
    float angle;
    
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        for (int i = 0; i < circle_points; i++) {
            angle = 2 * PI * i / circle_points;
            float x = fixedRadius * cos(angle);
            float y = fixedRadius * sin(angle);
            glVertex2f(x, y);
        }
    glEnd();
    
    glColor3f(0.15f, 0.15f, 0.15f);
    glLineWidth(6.0f);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < circle_points; i++) {
            angle = 2 * PI * i / circle_points;
            float x = fixedRadius * cos(angle);
            float y = fixedRadius * sin(angle);
            glVertex2f(x, y);
        }
    glEnd();
    
    glPopMatrix();
}

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    DrawGradientBackground();
    DrawGunung();
    DrawRoad();
    DrawMobil();

    DrawCircle(-0.4f, -0.6f);
    DrawCircle(0.65f, -0.55f);
    
    glFlush();
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1080, 441);  
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Mobil Nanjak");  
    glutReshapeFunc(Resize); 
    glutDisplayFunc(RenderScene); 
    glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}
