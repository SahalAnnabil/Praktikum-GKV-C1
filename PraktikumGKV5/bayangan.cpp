// Nama		: Muhamad Sahal Annabil
// NIM		: 24060123130088
// Tanggal	: 24 Maret 2025



#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

double rx = 0.0, ry = 0.0;
float l[] = {0.0, 80.0, 0.0}; // Sumber cahaya
float n[] = {0.0, -40.0, 0.0};
float e[] = {0.0, -60.0, 0.0};

void help();

// Manual donut (torus) implementation with two colors
void drawDonut() {
    const int numMajor = 24;  // Number of major segments (around the ring)
    const int numMinor = 18;  // Number of minor segments (around the tube)
    const float majorRadius = 15.0f;  // Distance from center of torus to center of tube
    const float minorRadius = 10.0f;   // Radius of the tube
    
    int i, j;
    float majorStep = 2.0f * M_PI / numMajor;
    float minorStep = 2.0f * M_PI / numMinor;
    
    for (i = 0; i < numMajor; ++i) {
        float a0 = i * majorStep;
        float a1 = (i + 1) * majorStep;
        float x0 = cos(a0);
        float y0 = sin(a0);
        float x1 = cos(a1);
        float y1 = sin(a1);
        
        // Set color based on position
        if (i < numMajor / 2) {
            glColor3f(0.984, 0.2, 0.67); // Pink
        } else {
            glColor3f(0.9, 0.634, 0.32); // Brown
        }
        
        glBegin(GL_TRIANGLE_STRIP);
        for (j = 0; j <= numMinor; ++j) {
            float b = j * minorStep;
            float c = cos(b);
            float r = minorRadius * c + majorRadius;
            float z = minorRadius * sin(b);
            
            // First point
            glNormal3f(x0 * c, y0 * c, sin(b));
            glVertex3f(x0 * r, y0 * r, z);
            
            // Second point
            glNormal3f(x1 * c, y1 * c, sin(b));
            glVertex3f(x1 * r, y1 * r, z);
        }
        glEnd();
    }
}

// Function to draw shadow donut (one color)
void drawShadowDonut() {
    const int numMajor = 24;  // Number of major segments (around the ring)
    const int numMinor = 18;  // Number of minor segments (around the tube)
    const float majorRadius = 15.0f;  // Distance from center of torus to center of tube
    const float minorRadius = 10.0f;   // Radius of the tube
    
    int i, j;
    float majorStep = 2.0f * M_PI / numMajor;
    float minorStep = 2.0f * M_PI / numMinor;
    
    for (i = 0; i < numMajor; ++i) {
        float a0 = i * majorStep;
        float a1 = (i + 1) * majorStep;
        float x0 = cos(a0);
        float y0 = sin(a0);
        float x1 = cos(a1);
        float y1 = sin(a1);
        
        glBegin(GL_TRIANGLE_STRIP);
        for (j = 0; j <= numMinor; ++j) {
            float b = j * minorStep;
            float c = cos(b);
            float r = minorRadius * c + majorRadius;
            float z = minorRadius * sin(b);
            
            // First point
            glNormal3f(x0 * c, y0 * c, sin(b));
            glVertex3f(x0 * r, y0 * r, z);
            
            // Second point
            glNormal3f(x1 * c, y1 * c, sin(b));
            glVertex3f(x1 * r, y1 * r, z);
        }
        glEnd();
    }
}

// Replace the draw function to use our manual donut
void draw() {
    drawDonut();
}

// Draw shadow with consistent color
void drawShadow() {
    drawShadowDonut();
}

// Membuat proyeksi bayangan
void glShadowProjection(float *l, float *e, float *n) {
    float d = n[0] * l[0] + n[1] * l[1] + n[2] * l[2];
    float c = e[0] * n[0] + e[1] * n[1] + e[2] * n[2] - d;
    float mat[16] = {
        l[0] * n[0] + c,  n[0] * l[1],       n[0] * l[2],       n[0],
        n[1] * l[0],      l[1] * n[1] + c,   n[1] * l[2],       n[1],
        n[2] * l[0],      n[2] * l[1],       l[2] * n[2] + c,   n[2],
        -l[0] * c - l[0] * d, -l[1] * c - l[1] * d, -l[2] * c - l[2] * d, -d
    };
    glMultMatrixf(mat);
}

void render() {
    // Pink background
    glClearColor(1.0, 0.8, 0.9, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLightfv(GL_LIGHT0, GL_POSITION, l);
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
        glVertex3f(l[0], l[1], l[2]);
    glEnd();
    
    // Floor color (light pink)
    glColor3f(0.87, 0.24, 0.55);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-1300.0, e[1] - 0.1, 1300.0);
        glVertex3f(1300.0, e[1] - 0.1, 1300.0);
        glVertex3f(1300.0, e[1] - 0.1, -1300.0);
        glVertex3f(-1300.0, e[1] - 0.1, -1300.0);
    glEnd();
    
    glPushMatrix();
        glRotatef(ry, 0, 1, 0);
        glRotatef(rx, 1, 0, 0);
        glEnable(GL_LIGHTING);
        // Donut color is set within the drawDonut() function
        draw();
    glPopMatrix();
    
    
    glPushMatrix();
        glShadowProjection(l, e, n);
        glRotatef(ry, 0, 1, 0);
        glRotatef(rx, 1, 0, 0);
        glDisable(GL_LIGHTING);
        glColor3f(0.68, 0.05, 0.36);
        drawShadow();
    glPopMatrix();
    
    
    glutSwapBuffers();
}

void keypress(unsigned char c, int a, int b) {
    if (c == 27) exit(0);
    else if (c == 's') l[1] -= 5.0;
    else if (c == 'w') l[1] += 5.0;
    else if (c == 'a') l[0] -= 5.0;
    else if (c == 'd') l[0] += 5.0;
    else if (c == 'q') l[2] -= 5.0;
    else if (c == 'e') l[2] += 5.0;
    else if (c == 'h') help();
}

void help() {
    printf("Proyeksi contoh bayangan sebuah obyek donut \n");
}

void idle() {
    rx += 0.1;
    ry += 0.1;
    render();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(300, 30);
    glutCreateWindow("Proyeksi Bayangan");
    glutReshapeFunc(resize);
    glutReshapeWindow(400, 400);
    glutKeyboardFunc(keypress);
    glutDisplayFunc(render);
    glutIdleFunc(idle);
    
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.0, 1.0, 400.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -150.0);
    
    glutMainLoop();
    return 0;
}
