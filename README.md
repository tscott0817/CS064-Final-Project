# Traffic Light State Machine

Simulation of a two-way traffic system using C++, openGL, and GLUT. It works through a simple 
state machine made by using boolean logic switches. The flipping of these switches changes which
light is active and which colors are lit up. States include:

#### Parent States
-   Null: The base state of the lights. Only red lit.
-   Light one active: Light one begins iteration of light color states; light two kept red.
-   Light two active: Light two begins iteration of light color states; light one kept red.
-   Error: Something has broken main loop(like a car crash); both lights flash red.

#### Child States
-   Green light: Swaps active green state to false and yellow to true after set time duration.
-   Yellow light: Swaps active yellow state to false and red to true after set time duration.
-   Red light: Swaps active red state to false, deactivates current light and activates the other.