#include "main.h"
#include "circle.h"
#include "rect.h"
#include <ctime>
using namespace std;

/**
 * Simple two-way traffic light system. Main logic in timer()
 */

// region Fields (Don't Need)
GLdouble width, height;
int wd;

const color baseGrey(64/255.0,64/255.0,64/255.0);
const color lightGreen(0, .8, 0);
const color lightYellow(.85, .85, 0);
const color lightRed(1, 0, 0);
const color green(0, .5, 0);
const color yellow(.45, .45, 0);
const color red(.5, 0, 0);

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
//endregion

/**
 * Fields used for states
 */
//region Fields (Need)

// All light states
bool startLights;

bool lightOneActive;
bool lightTwoActive;

bool lightOneGreenState;
bool lightOneYellowState;
bool lightOneRedState;

bool lightTwoGreenState;
bool lightTwoYellowState;
bool lightTwoRedState;


// Sets all initial values of states
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
//endregion

// region Initializations (Don't Need)
// Sets parameters to build lights with
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

void init() {
    width = 1280;
    height = 720;
    srand(time(0));
    initLights();
    initLightFields();
}

void initGL() {
    glClearColor(0, 90/255.0, 130/255.0, 1);
}

// Draws visuals in window
void display() {

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Make Light One
    lightOneBase.draw();
    lightOneGreen.draw();
    lightOneYellow.draw();
    lightOneRed.draw();

    // Make Light Two
    lightTwoBase.draw();
    lightTwoGreen.draw();
    lightTwoYellow.draw();
    lightTwoRed.draw();

    glFlush();
}
//endregion (DOnt' Need)

/**
 * SPACEBAR starts main loop
 */
 //region Initial Action (Need)
void kbd(unsigned char key, int x, int y) {

    switch(key) {
        // When space key is pressed, activate lights
        case 32: {
            startLights = true;
        }
    }
    glutPostRedisplay();
}
//endregion

/**
 *  Timer Function
 */
//region Timers (Need)
void mainLoop(int currentTime) {

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

            glutTimerFunc(3000, mainLoop, currentTime);

        }

        // Light One
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

                glutTimerFunc(3000, mainLoop, currentTime);
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

                glutTimerFunc(3000, mainLoop, currentTime);
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

                glutTimerFunc(3000, mainLoop, currentTime);
            }

        }

        // Light two
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

                glutTimerFunc(3000, mainLoop, currentTime);
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

                glutTimerFunc(3000, mainLoop, currentTime);
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

                glutTimerFunc(3000, mainLoop, currentTime);
            }
        }
    }
    else {
        glutTimerFunc(30, mainLoop, currentTime);
    }
    glutPostRedisplay();
}
//endregion (Need)

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

    glutSetCursor(GLUT_CURSOR_DESTROY);

    glutTimerFunc(0, mainLoop, 0);

    glutMainLoop();
    return 0;
}