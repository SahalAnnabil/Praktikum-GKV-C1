// Nama : Muhamad Sahal Annabil
// NIM	: 24060123130088
// Kelas: GKV C
// Tugas: Proyeksi objek 3D

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstring>

// Window size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Global variables
char projectionName[50]; // Current projection name
int projectionType = 0;  // 0=Perspective, 1=Orthographic
int orthoMode = 0;       // Projection mode (1-9)
float ratio;             // Aspect ratio

// Camera variables
float angle = 0.0f;
float x = 0.0f, y = 2.0f, z = 15.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;

// Rotation variables
float rotationX = 0.0f;
float rotationY = 0.0f;

// Color definitions
const GLfloat GOLD_COLOR[3] = {0.85f, 0.65f, 0.13f};
const GLfloat ROYAL_PURPLE_COLOR[3] = {0.5f, 0.0f, 0.5f};
const GLfloat RED_VELVET_COLOR[3] = {0.8f, 0.05f, 0.05f};
const GLfloat SILVER_COLOR[3] = {0.75f, 0.75f, 0.75f};
const GLfloat BLACK_COLOR[3] = {0.0f, 0.0f, 0.0f};

// Function to set color
void setColor(const GLfloat color[3]) {
    glColor3f(color[0], color[1], color[2]);
}

//display text
void renderText(float x, float y, void *font, const char *string) {
    glColor3f(1.0f, 1.0f, 1.0f); // White text color
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

//  draw grid
void drawGrid() {
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_LINES);
    for (double i = Z_MIN; i < Z_MAX; i += gap) {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for (double i = X_MIN; i < X_MAX; i += gap) {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

// Draw cube
void drawCube(float width, float height, float depth) {
    float w = width / 2.0f;
    float h = height / 2.0f;
    float d = depth / 2.0f;
    
    // Draw filled faces
    setColor(GOLD_COLOR);
    glBegin(GL_QUADS);
    // Front face
    glVertex3f(-w, -h, d);
    glVertex3f(w, -h, d);
    glVertex3f(w, h, d);
    glVertex3f(-w, h, d);
    
    // Back face
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, -h, -d);
    
    // Top face
    glVertex3f(-w, h, -d);
    glVertex3f(-w, h, d);
    glVertex3f(w, h, d);
    glVertex3f(w, h, -d);
    
    // Bottom face
    glVertex3f(-w, -h, -d);
    glVertex3f(w, -h, -d);
    glVertex3f(w, -h, d);
    glVertex3f(-w, -h, d);
    
    // Right face
    glVertex3f(w, -h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, h, d);
    glVertex3f(w, -h, d);
    
    // Left face
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, -h, d);
    glVertex3f(-w, h, d);
    glVertex3f(-w, h, -d);
    glEnd();
    
    // Draw edges in black
    glLineWidth(2.0f); // Set line width
    setColor(BLACK_COLOR);
    
    // Front face outline
    glBegin(GL_LINE_LOOP);
    glVertex3f(-w, -h, d);
    glVertex3f(w, -h, d);
    glVertex3f(w, h, d);
    glVertex3f(-w, h, d);
    glEnd();
    
    // Back face outline
    glBegin(GL_LINE_LOOP);
    glVertex3f(-w, -h, -d);
    glVertex3f(-w, h, -d);
    glVertex3f(w, h, -d);
    glVertex3f(w, -h, -d);
    glEnd();
    
    // Top face outline
    glBegin(GL_LINE_LOOP);
    glVertex3f(-w, h, -d);
    glVertex3f(-w, h, d);
    glVertex3f(w, h, d);
    glVertex3f(w, h, -d);
    glEnd();
    
    // Bottom face outline
    glBegin(GL_LINE_LOOP);
    glVertex3f(-w, -h, -d);
    glVertex3f(w, -h, -d);
    glVertex3f(w, -h, d);
    glVertex3f(-w, -h, d);
    glEnd();
    
    // Connect remaining edges
    glBegin(GL_LINES);
    // Connect front to back (left side)
    glVertex3f(-w, -h, d);
    glVertex3f(-w, -h, -d);
    
    glVertex3f(-w, h, d);
    glVertex3f(-w, h, -d);
    
    // Connect front to back (right side)
    glVertex3f(w, -h, d);
    glVertex3f(w, -h, -d);
    
    glVertex3f(w, h, d);
    glVertex3f(w, h, -d);
    glEnd();
    
    glLineWidth(1.0f); // Reset line width
}

// Draw a cylinder with outline
void drawCylinder(float radius, float height, int slices) {
	setColor(SILVER_COLOR);
    GLUquadricObj *cylinder = gluNewQuadric();
    
    // Draw filled cylinder
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricTexture(cylinder, GL_TRUE);
    gluCylinder(cylinder, radius, radius, height, slices, 1);
    
    // Draw the top cap
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(cylinder, 0.0f, radius, slices, 1);
    glPopMatrix();
    
    // Draw the bottom cap
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(cylinder, 0.0f, radius, slices, 1);
    glPopMatrix();
    
    // Draw the outline
    setColor(BLACK_COLOR);
    
    // Set to line drawing for outlines
    gluQuadricDrawStyle(cylinder, GLU_LINE);
    gluCylinder(cylinder, radius, radius, height, slices, 1);
    
    // Outline for top cap
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(cylinder, 0.0f, radius, slices, 1);
    glPopMatrix();
    
    // Outline for bottom cap
    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(cylinder, 0.0f, radius, slices, 1);
    glPopMatrix();
    
    gluDeleteQuadric(cylinder);
}

// Draw a cushion
void drawCushion(float x, float y, float z, float width, float depth, bool isBackrest) {
    glPushMatrix();
    glTranslatef(x, y, z);
    
    if (isBackrest) {
        setColor(ROYAL_PURPLE_COLOR);
    } else {
        setColor(RED_VELVET_COLOR);
    }
    

    glPushMatrix();
    glScalef(width, 0.5f, depth);
    glutSolidCube(1.0f);
    
    // Draw outline
    setColor(BLACK_COLOR);
    glLineWidth(1.5f);
    glutWireCube(1.0f);
    glLineWidth(1.0f);
    
    glPopMatrix();
    
    glPopMatrix();
}

// Draw throne
void drawThrone() {
    // Base platform
    setColor(GOLD_COLOR);
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    drawCube(4.0f, 0.5f, 4.0f);
    glPopMatrix();
    
    // Seat
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    drawCube(3.0f, 0.5f, 3.0f);
    glPopMatrix();
    
    // Backrest base top
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, -1.25f);
    drawCube(3.0f, 2.5f, 0.5f);
    glPopMatrix();
    
    // Backrest
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, -1.25f);
    drawCube(3.5f, 1.5f, 0.5f);

    glPopMatrix();
    
    // Armrests
    setColor(GOLD_COLOR);
    glPushMatrix();
    glTranslatef(-1.5f, -0.2f, 0.0f);
    drawCube(0.5f, 1.0f, 3.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.5f, -0.2f, 0.0f);
    drawCube(0.5f, 1.0f, 3.0f);
    glPopMatrix();

    // Legs
    setColor(SILVER_COLOR);
    
    float legPositions[4][2] = {
        {-1.25f, 1.25f}, // Front left
        {1.25f, 1.25f},  // Front right
        {-1.25f, -1.25f}, // Back left
        {1.25f, -1.25f}   // Back right
    };
    
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(legPositions[i][0], -2.25f, legPositions[i][1]);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        drawCylinder(0.3f, 1.0f, 8);
        glPopMatrix();
    }
    
    // Seat cushion
    drawCushion(0.0f, -0.7f, 0.0f, 2.5f, 2.5f, false);
    
    // Back cushion
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, -0.9f);
    glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
    drawCushion(0.0f, 0.0f, 0.0f, 2.5f, 1.5f, true);
    glPopMatrix();

}

// Set projection
void setProjection(int projNum) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    switch (projNum) {
        // Perspective Projections (1-3)
        case 1: // 1-point perspective
            strcpy(projectionName, "Perspective: 1-Point");
            projectionType = 0;
            gluPerspective(45.0f, ratio, 0.1f, 1000.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(0.0f, 5.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
            break;
            
        case 2: // 2-point perspective
            strcpy(projectionName, "Perspective: 2-Point");
            projectionType = 0;
            gluPerspective(45.0f, ratio, 0.1f, 1000.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(15.0f, 5.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
            break;
            
        case 3: // 3-point perspective
            strcpy(projectionName, "Perspective: 3-Point");
            projectionType = 0;
            gluPerspective(45.0f, ratio, 0.1f, 1000.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(15.0f, 10.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.577f, 0.577f, 0.577f);
            break;
            
        // Orthographic Projections (4-9)
        case 4: // Plan view (top)
            strcpy(projectionName, "Orthographic: Plan View (Top)");
            projectionType = 1;
            glOrtho(-20, 20, -15, 15, 0.1, 1000);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(0, 20, 0, 0, 0, 0, 0, 0, -1);
            break;
            
        case 5: // Front view
            strcpy(projectionName, "Orthographic: Front View");
            projectionType = 1;
            glOrtho(-20, 20, -15, 15, 0.1, 1000);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
            break;
            
        case 6: // Side view
            strcpy(projectionName, "Orthographic: Side View");
            projectionType = 1;
            glOrtho(-20, 20, -15, 15, 0.1, 1000);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(20, 0, 0, 0, 0, 0, 0, 1, 0);
            break;
            
        case 7: // Isometric
            strcpy(projectionName, "Orthographic: Isometric");
            projectionType = 1;
            glOrtho(-20, 20, -15, 15, 0.1, 1000);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);
            break;
            
        case 8: // Dimetric
            strcpy(projectionName, "Orthographic: Dimetric");
            projectionType = 1;
            glOrtho(-20, 20, -15, 15, 0.1, 1000);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(15, 10, 15, 0, 0, 0, 0, 1, 0);
            break;
            
        case 9: // Trimetric
            strcpy(projectionName, "Orthographic: Trimetric");
            projectionType = 1;
            glOrtho(-20, 20, -15, 15, 0.1, 1000);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(10, 15, 20, 0, 0, 0, 0, 1, 0);
            break;
            
        default: // Default camera (interactive view)
            strcpy(projectionName, "Interactive View");
            projectionType = 0;
            gluPerspective(70.0f, ratio, 0.1f, 1000.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            
            // Apply interactive rotations
            gluLookAt(0.0f, 3.0f, 8.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f);
            glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
            glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
            break;
    }
}

// Reshape function
void reshape(int w, int h) {
    if (h == 0) h = 1;
    ratio = 1.0f * w / h;
    glViewport(0, 0, w, h);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    setProjection(orthoMode);
    
    drawGrid();
    
    glTranslatef(0.0f, 2.5f, 0.0f);
    drawThrone();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Render projection info text
    renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 20, GLUT_BITMAP_HELVETICA_12, projectionName);
    renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 40, GLUT_BITMAP_HELVETICA_12, "Press 1-9 to change projection");
    renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 60, GLUT_BITMAP_HELVETICA_12, "Use w/s/a/d to rotate in interactive view (0)");
    renderText(10, glutGet(GLUT_WINDOW_HEIGHT) - 80, GLUT_BITMAP_HELVETICA_12, "Press r to reset rotation");
    

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glutSwapBuffers();
}

// Keyboard function
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '0': // Interactive view
        case '1': // 1-point perspective
        case '2': // 2-point perspective
        case '3': // 3-point perspective
        case '4': // Plan view (top)
        case '5': // Front view
        case '6': // Side view
        case '7': // Isometric
        case '8': // Dimetric
        case '9': // Trimetric
            // Convert ASCII to integer (0-9)
            orthoMode = key - '0';
            glutPostRedisplay();
            break;
            
        // Interactive view control
        case 'w':
            if (orthoMode == 0)
                rotationX -= 5.0f;
            glutPostRedisplay();
            break;
        case 's':
            if (orthoMode == 0)
                rotationX += 5.0f;
            glutPostRedisplay();
            break;
        case 'a':
            if (orthoMode == 0)
                rotationY -= 5.0f;
            glutPostRedisplay();
            break;
        case 'd':
            if (orthoMode == 0)
                rotationY += 5.0f;
            glutPostRedisplay();
            break;
        case 'r':
            rotationX = 0.0f;
            rotationY = 0.0f;
            glutPostRedisplay();
            break;
        case 27: // ESC key
            exit(0);
            break;
    }
}


void init() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    strcpy(projectionName, "Interactive View");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("3D Throne");
    
    // Initialize
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}
