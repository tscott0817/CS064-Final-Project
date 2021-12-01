#include "main.h"
#include "circle.h"
#include "rect.h"
#include <iostream>
#include <memory>
#include <vector>
#include <ctime>
using namespace std;

GLdouble width, height;
int wd;
const color grassGreen(26/255.0, 176/255.0, 56/255.0);
const color white(1, 1, 1);
const color baseYellow(2/255.0, 184/255.0, 44/255.0);
const color baseGrey(127/255.0,127/255.0,127/255.0);
const color lightGreen(49/255.0, 201/255.0, 54/255.0);
const color lightYellow(252/255.0, 252/255.0, 87/255.0);
const color lightRed(245/255.0, 80/255.0, 39/255.0);
const color green(0, .5, 0);
const color yellow(.5, .5, 0);
const color red(.5, 0, 0);


vector<unique_ptr<Shape>> clouds;
Rect grass;

// Light fields
Rect lightOneBase;
Circle lightOneGreen;
Circle lightOneYellow;
Circle lightOneRed;

Rect lightTwoBase;
Circle lightTwoGreen;
Circle lightTwoYellow;
Circle lightTwoRed;

// States that light can be
enum  lightStates{Null = 0, Green = 1, Yellow = 2, Red = 3, Error = 4};

// States
bool startLights;

bool lightOneActive;
bool lightTwoActive;

bool lightOneGreenState;
bool lightOneYellowState;
bool lightOneRedState;

bool lightTwoGreenState;
bool lightTwoYellowState;
bool lightTwoRedState;


vector<unique_ptr<Shape>> lightOne;

Rect user;

void initFields() {

    startLights = false;
    lightOneActive = true;
    lightTwoActive = false;

    lightOneGreenState = true; // Initializer
    lightOneYellowState = false;
    lightOneRedState = false;

    lightTwoGreenState = false;
    lightTwoYellowState = false;
    lightTwoRedState = false;
}

void initLights () {

    // Left Light
    lightOneBase.setSize(150, 450);
    lightOneBase.setCenter(150, 450);
    lightOneBase.setColor(baseGrey);

    lightOneGreen.setRadius(65);
    lightOneGreen.setCenter(150, 600);
    lightOneGreen.setColor(green);

    lightOneYellow.setRadius(65);
    lightOneYellow.setCenter(150, 450);
    lightOneYellow.setColor(yellow);

    lightOneRed.setRadius(65);
    lightOneRed.setCenter(150, 300);
    lightOneRed.setColor(red);

    // Right Light

    lightTwoBase.setSize(150, 450);
    lightTwoBase.setCenter(1450, 450);
    lightTwoBase.setColor(baseGrey);

    lightTwoGreen.setRadius(65);
    lightTwoGreen.setCenter(1450, 600);
    lightTwoGreen.setColor(green);

    lightTwoYellow.setRadius(65);
    lightTwoYellow.setCenter(1450, 450);
    lightTwoYellow.setColor(yellow);

    lightTwoRed.setRadius(65);
    lightTwoRed.setCenter(1450, 300);
    lightTwoRed.setColor(red);




}

void initGrass() {
    grass.setCenter(250, 450);
    grass.setSize(width, height/3);
    grass.setColor(grassGreen);
}
void initUser() {
    // TODO: Initialize the user to be a 20x20 white block
    // centered in the top left corner of the graphics window
    user.setCenter(0, 0);
    user.setSize(20, 20);
    user.setColor(white);
}

void init() {
    width = 1600;
    height = 900;
    srand(time(0));
    initLights();
    initGrass();
    initUser();
    initFields();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(.2, 0, .5, .5f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE


    // All Lights
    lightOneBase.draw();
    lightOneGreen.draw();
    lightOneYellow.draw();
    lightOneRed.draw();

    lightTwoBase.draw();
    lightTwoGreen.draw();
    lightTwoYellow.draw();
    lightTwoRed.draw();

    user.draw();

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    switch(key) {
        case 27: {
            glutDestroyWindow(wd);
            exit(0);
        }

        case 32: {
            //lightOneActive = true;
            startLights = true;
        }
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {
    user.setCenter(x, y);
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}


void timer(int dummy) {

    if(startLights) {
        if (lightOneActive) {
            //startLights = false;
            //lightOneGreenState = true;

            if (lightOneGreenState) {
                lightOneGreenState = false;
                lightOneRed.setColor(red);
                lightOneGreen.setColor(lightGreen);
                lightOneYellowState = true;
                lightTwoRed.setColor(lightRed);
                glutTimerFunc(5000, timer, dummy);
            } else if (lightOneYellowState) {
                lightOneYellowState = false;
                lightOneGreen.setColor(green);
                lightOneYellow.setColor(lightYellow);
                lightOneRedState = true;
                glutTimerFunc(5000, timer, dummy);
            } else if (lightOneRedState) {
                lightOneRedState = false;
                lightOneYellow.setColor(yellow);
                lightOneRed.setColor(lightRed);
                lightOneGreenState = true;
                lightTwoActive = true;
                lightOneActive = false;
                //lightTwoGreenState = true;
                glutTimerFunc(5000, timer, dummy);
            }

                // If other light active, keep red lit
            else {
                lightOneGreen.setColor(green);
                lightOneYellow.setColor(yellow);
                lightTwoGreenState = true;
                glutTimerFunc(5000, timer, dummy);
                //lightTwoGreenState = true;
                //lightOneRed.setColor(lightRed);
                //glutTimerFunc(1000, timer, dummy);
            }


        }

        if (lightTwoActive) {

            //lightTwoGreenState = true;
            if (lightTwoGreenState) {
                lightTwoGreenState = false;
                lightTwoGreen.setColor(lightGreen);
                lightTwoRed.setColor(red);
                lightTwoYellowState = true;
                glutTimerFunc(5000, timer, dummy);
            } else if (lightTwoYellowState) {
                lightTwoYellowState = false;
                lightTwoGreen.setColor(green);
                lightTwoYellow.setColor(lightYellow);
                lightTwoRedState = true;
                glutTimerFunc(5000, timer, dummy);
            } else if (lightTwoRedState) {
                lightTwoRedState = false;
                lightTwoYellow.setColor(yellow);
                lightTwoRed.setColor(lightRed);
                lightTwoGreenState = true;
                lightOneActive = true;
                lightTwoActive = false;
                //lightOneGreenState = true;
                glutTimerFunc(5000, timer, dummy);
            }

                // If other light active, keep red lit
            else {
                lightTwoGreen.setColor(green);
                lightTwoYellow.setColor(yellow);
                //lightTwoRed.setColor(lightRed);
                //glutTimerFunc(1000, timer, dummy);
            }
        }

    }


    else {
        glutTimerFunc(1000, timer, dummy);
    }
    glutPostRedisplay();

    //glutTimerFunc(3000, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(150, 50); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Finite State Machines Example: Traffic Lights");

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);


    // Logic


    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}