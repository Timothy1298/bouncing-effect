
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <iostream>

using namespace std;

GLuint texture;
float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;
float ySpeed = 0.02f;
float yPos = 0.0f;
bool goingUp = true;

void checkOpenGLError() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL Error: " << err << endl;
    }
}

void loadTexture(const char* filename) {
    cout << "Loading texture from: " << filename << endl;
    texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (!texture) {
        cerr << "Error: Failed to load texture!" << endl;
        exit(1);
    }
    cout << "Texture loaded successfully: " << texture << endl;
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    checkOpenGLError();
}

void drawCube() {
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    // Front Face
    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5,  0.5);
    glTexCoord2f(1, 0); glVertex3f( 0.5, -0.5,  0.5);
    glTexCoord2f(1, 1); glVertex3f( 0.5,  0.5,  0.5);
    glTexCoord2f(0, 1); glVertex3f(-0.5,  0.5,  0.5);
    

    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1, 0); glVertex3f( 0.5, -0.5, -0.5);
    glTexCoord2f(1, 1); glVertex3f( 0.5,  0.5, -0.5);
    glTexCoord2f(0, 1); glVertex3f(-0.5,  0.5, -0.5);

    // Left Face
    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1, 0); glVertex3f(-0.5, -0.5,  0.5);
    glTexCoord2f(1, 1); glVertex3f(-0.5,  0.5,  0.5);
    glTexCoord2f(0, 1); glVertex3f(-0.5,  0.5, -0.5);

    // Right Face
    glTexCoord2f(0, 0); glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1, 0); glVertex3f(0.5, -0.5,  0.5);
    glTexCoord2f(1, 1); glVertex3f(0.5,  0.5,  0.5);
    glTexCoord2f(0, 1); glVertex3f(0.5,  0.5, -0.5);

    // Top Face
    glTexCoord2f(0, 0); glVertex3f(-0.5,  0.5, -0.5);
    glTexCoord2f(1, 0); glVertex3f( 0.5,  0.5, -0.5);
    glTexCoord2f(1, 1); glVertex3f( 0.5,  0.5,  0.5);
    glTexCoord2f(0, 1); glVertex3f(-0.5,  0.5,  0.5);

    // Bottom Face
    glTexCoord2f(0, 0); glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1, 0); glVertex3f( 0.5, -0.5, -0.5);
    glTexCoord2f(1, 1); glVertex3f( 0.5, -0.5,  0.5);
    glTexCoord2f(0, 1); glVertex3f(-0.5, -0.5,  0.5);

    // Repeat for other faces (omitted for brevity)
    glEnd();
    checkOpenGLError();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, yPos, -5.0f);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleZ, 0, 0, 1);
    drawCube();
    glutSwapBuffers();
}

void update(int value) {
    if (goingUp) {
        yPos += ySpeed;
        if (yPos >= 1.0f) goingUp = false;
    } else {
        yPos -= ySpeed;
        if (yPos <= -1.0f) goingUp = true;
    }
    angleX += 1.0f;
    angleY += 1.0f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    loadTexture("/home/timothy/Desktop/boucing-effect/image.png");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bouncing Textured Cube");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}
