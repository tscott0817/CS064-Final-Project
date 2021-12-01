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
const color baseGrey(64/255.0,64/255.0,64/255.0);
const color lightGreen(0, .8, 0);
const color lightYellow(.85, .85, 0);
const color lightRed(1, 0, 0);
const color green(0, .5, 0);
const color yellow(.45, .45, 0);
const color red(.5, 0, 0);


vector<unique_ptr<Shape>> clouds;
Rect grass;

// Light one components
Rect lightOneBase;
Circle lightOneGreen;
Circle lightOneYellow;
Circle lightOneRed;

// Light two components
Rect lightTwoBase;
Circle lightTwoGreen;
Circle lightTwoYellow;
Circle lightTwoRed;

// States that light can be (not using currently)
enum  lightStates{Null, Green, Yellow, Red, Error};

// States
bool startLights;

// Switches which light is active
bool lightOneActive;
bool lightTwoActive;

// Sets the state for the color of the lights
bool lightOneGreenState;
bool lightOneYellowState;
bool lightOneRedState;

bool lightTwoGreenState;
bool lightTwoYellowState;
bool lightTwoRedState;

Rect user;

void initLightFields() {

    startLights = false;
    lightOneActive = false;
    lightTwoActive = false;

    lightOneGreenState = false;
    lightOneYellowState = false;
    lightOneRedState = false;

    lightTwoGreenState = false;
    lightTwoYellowState = false;
    lightTwoRedState = false;
}

void initLights () {

    // Left Light
    lightOneBase.setSize(150, 450);
    lightOneBase.setCenter(395, 360);
    lightOneBase.setColor(baseGrey);

    lightOneGreen.setRadius(65);
    lightOneGreen.setCenter(395, 510);
    lightOneGreen.setColor(green);

    lightOneYellow.setRadius(65);
    lightOneYellow.setCenter(395, 360);
    lightOneYellow.setColor(yellow);

    lightOneRed.setRadius(65);
    lightOneRed.setCenter(395, 210);
    lightOneRed.setColor(lightRed);

    // Right Light
    lightTwoBase.setSize(150, 450);
    lightTwoBase.setCenter(885, 360);
    lightTwoBase.setColor(baseGrey);

    lightTwoGreen.setRadius(65);
    lightTwoGreen.setCenter(885, 510);
    lightTwoGreen.setColor(green);

    lightTwoYellow.setRadius(65);
    lightTwoYellow.setCenter(885, 360);
    lightTwoYellow.setColor(yellow);

    lightTwoRed.setRadius(65);
    lightTwoRed.setCenter(885, 210);
    lightTwoRed.setColor(lightRed);




}

void initGrass() {
    grass.setCenter(250, 450);
    grass.setSize(width, height/3);
    grass.setColor(grassGreen);
}
void initUser() {

    user.setCenter(0, 0);
    user.setSize(20, 20);
    user.setColor(white);
}

void init() {
    width = 1280;
    height = 720;
    srand(time(0));
    initLights();
    initGrass();
    //initUser();
    initLightFields();
}

void initGL() {
    glClearColor(0, 90/255.0, 130/255.0, 1);
}

void display() {

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    switch(key) {
        case 27: {
            glutDestroyWindow(wd);
            exit(0);
        }

        // When space key is pressed change bool to activate lights
        case 32: {

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

        // Starts lights at red
        if (!lightOneActive && !lightTwoActive) {

            // Light One
            lightOneGreen.setColor(green);
            lightOneYellow.setColor(yellow);
            lightOneRed.setColor(lightRed);

            // Light Two
            lightTwoGreen.setColor(green);
            lightTwoYellow.setColor(yellow);
            lightTwoRed.setColor(lightRed);

            // Activate state of first light to start loop
            lightOneActive = true;
            lightOneGreenState = true;

            glutTimerFunc(5000, timer, dummy);

        }

        else if (lightOneActive) {

            if (lightOneGreenState) {

                // Change states
                lightOneGreenState = false;
                lightOneYellowState = true;

                // Light One
                lightOneGreen.setColor(lightGreen);
                lightOneYellow.setColor(yellow);
                lightOneRed.setColor(red);

                // Light Two
                lightTwoGreen.setColor(green);
                lightTwoYellow.setColor(yellow);
                lightTwoRed.setColor(lightRed);

                glutTimerFunc(3000, timer, dummy);
            }

            else if (lightOneYellowState) {

                // Change States
                lightOneYellowState = false;
                lightOneRedState = true;

                // Light One
                lightOneGreen.setColor(green);
                lightOneYellow.setColor(lightYellow);
                lightOneRed.setColor(red);

                // Light Two
                lightTwoGreen.setColor(green);
                lightTwoYellow.setColor(yellow);
                lightTwoRed.setColor(lightRed);

                glutTimerFunc(3000, timer, dummy);
            }

            else if (lightOneRedState) {

                // Change states
                lightOneRedState = false;
                lightTwoGreenState = true;
                lightTwoActive = true;
                lightOneActive = false;

                // Light One
                lightOneGreen.setColor(green);
                lightOneYellow.setColor(yellow);
                lightOneRed.setColor(lightRed);

                // Light Two
                lightTwoGreen.setColor(green);
                lightTwoYellow.setColor(yellow);
                lightTwoRed.setColor(lightRed);

                glutTimerFunc(3000, timer, dummy);
            }

        }

        else if (lightTwoActive) {

            if (lightTwoGreenState) {

                // Change States
                lightTwoGreenState = false;
                lightTwoYellowState = true;

                // Change light colors
                lightTwoGreen.setColor(lightGreen);
                lightTwoYellow.setColor(yellow);
                lightTwoRed.setColor(red);

                // Light One
                lightOneGreen.setColor(green);
                lightOneYellow.setColor(yellow);
                lightOneRed.setColor(lightRed);

                glutTimerFunc(3000, timer, dummy);
            }

            else if (lightTwoYellowState) {

                // Change States
                lightTwoYellowState = false;
                lightTwoRedState = true;

                // Change light colors
                lightTwoGreen.setColor(green);
                lightTwoYellow.setColor(lightYellow);
                lightTwoRed.setColor(red);

                // Light One
                lightOneGreen.setColor(green);
                lightOneYellow.setColor(yellow);
                lightOneRed.setColor(lightRed);

                glutTimerFunc(3000, timer, dummy);
            }

            else if (lightTwoRedState) {

                // Change states
                lightTwoRedState = false;
                lightOneGreenState = true;
                lightOneActive = true;
                lightTwoActive = false;

                // Change light colors
                lightTwoGreen.setColor(green);
                lightTwoYellow.setColor(yellow);
                lightTwoRed.setColor(lightRed);

                // Light One
                lightOneGreen.setColor(green);
                lightOneYellow.setColor(yellow);
                lightOneRed.setColor(lightRed);

                glutTimerFunc(3000, timer, dummy);
            }

        }

    }


    else {
        glutTimerFunc(30, timer, dummy);
    }
    glutPostRedisplay();

}

int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(300, 150);
    wd = glutCreateWindow("Finite State Machines Example: Traffic Lights");

    glutDisplayFunc(display);

    initGL();

    glutKeyboardFunc(kbd);

    glutSpecialFunc(kbdS);

    glutPassiveMotionFunc(cursor);

    glutMouseFunc(mouse);


    // Logic


    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}