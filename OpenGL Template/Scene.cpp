#include "WindowingSystem.h"
#include <iostream>

float x = -0.95f;
float y = -2.1f;
float size = 0.4;
int numOfMovesMade = 0;
int numOfMovesToBeMade = 630;
float slowRotation = 0.0f;

void renderText(const char *text, int length, float x, float y) {
	glPushMatrix();
	glRasterPos2f(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int) text[i]);
	}
	glPopMatrix();
}

void renderSmallText(const char *text, int length, float x, float y) {
	glPushMatrix();
	glRasterPos2f(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (int)text[i]);
	}
	glPopMatrix();
}

void renderCircle(float x, float y, float size, float numOfVertices, float red, float green, float blue) {
	GLUquadric *quad;
	quad = gluNewQuadric();
	// set colour of circle
	glColor3f(red, green, blue);

	glPushMatrix();
	// Get to the location of where I want the circle to be positioned.
	glTranslatef(x, y, 1);
	// form the circle.
	// (type, inner radius, outer radius, number of edges, number of loops)
	gluDisk(quad, 0, size, numOfVertices, 1);
	// Go back to original coordinate space to prevent translation moving the circle each frame.
	glPopMatrix();
}

void placeWheelOrHeadlight(float x, float y, int type) {

	// set colour to grey or yellow depending on what is to be generated.
	if (type == 0) { // headlights
		// set colour to yellow
		glColor3f(1, 1, 0);
	}
	else { // "wheels"
		   // set colour to grey
		glColor3f(0, 0, 0);
	}

	// build component in specified colour
	glBegin(GL_QUADS);
	glVertex2f(x, y); // The bottom left corner  
	glVertex2f(x, y + 0.03); // The top left corner  
	glVertex2f(x + 0.03, y + 0.03); // The top right corner  
	glVertex2f(x + 0.03, y); // The bottom right corner  
	glEnd();
}

void rotateCar(float rotationAngle, float carX, float carY) {
	glRotatef(rotationAngle-0.05, 0.0, 0.0, 1.0);
}

void moveCar(float x, float y, float size) {

	// Apply current or new rotation:
	float middleX = (x + x + (x + size) + (x + size)) / 4;
	float middleY = (y + y + (y + size) + (y + size)) / 4;
	rotateCar(slowRotation, middleX, middleY);

	// offset for x and y in relation to the base.
	float offset = abs(x / 1.2);

	// wheels
	placeWheelOrHeadlight(x - 0.015, y + 0.025, 1); // back left
	placeWheelOrHeadlight(x - 0.015, y + 0.325, 1); // front left
	placeWheelOrHeadlight(x + 0.385, y + 0.025, 1); // back right
	placeWheelOrHeadlight(x + 0.385, y + 0.325, 1); // front right

	// headlights
	placeWheelOrHeadlight(x + 0.05, y + size - 0.01, 0); // left
	placeWheelOrHeadlight(x + 0.32, y + size - 0.01, 0); // right

	// BASE OF CAR
	// set colour to red
	glColor3f(1.0f, 0.0f, 0.0f);
	
	glBegin(GL_QUADS);
	glVertex2f(x, y); // The bottom left corner  
	glVertex2f(x, y + size); // The top left corner  
	glVertex2f(x + size, y + size); // The top right corner  
	glVertex2f(x + size, y); // The bottom right corner  
	glEnd();

	
	// set colour to black
	glColor3f(0, 0, 0);
	glLineWidth(1.0f);
	// birds eye view of the top of the car.
	glBegin(GL_LINE_LOOP);
	glVertex2f(x + 0.05, y + 0.05); // The bottom left corner 
	glVertex2f(x + 0.05, y  + (size / 2)); // The top left corner 
	glVertex2f(x - 0.05 + size, y + (size / 2)); // The top right corner  
	glVertex2f(x - 0.05 + size, y + 0.05); // The bottom right corner  
	glEnd();

	// Raycast
	glLineWidth(5.0f);
	glColor3f(1,1,0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x + (size / 2), y + 0.5); // The bottom of the first line 
	glVertex2f(x + (size / 2), y + 0.6); // The top of the first line 
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(x + (size / 2), y + 0.7); // The bottom of the second line 
	glVertex2f(x + (size / 2), y + 0.8); // The top of the second line 
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(x + (size / 2), y + 0.9); // The bottom of the second line 
	glVertex2f(x + (size / 2), y + 1.0); // The top of the second line 
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(x + (size / 2), y + 1.1); // The bottom of the second line 
	glVertex2f(x + (size / 2), y + 1.2); // The top of the second line 
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(x + (size / 2), y + 1.3); // The bottom of the second line 
	glVertex2f(x + (size / 2), y + 1.4); // The top of the second line 
	glEnd();

	// When interceptions occur!
	if (numOfMovesMade >= 150 && numOfMovesMade <= 170 || numOfMovesMade >= 325 && numOfMovesMade <= 355) {
		glLineWidth(3.0f);
		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
		// bottom left to top right of X
		glVertex2f(x + (size / 2) - 0.05, y + 1.4); // bottom left
		glVertex2f(x + (size / 2) + 0.05, y + 1.5); // top right
		glEnd();
		glBegin(GL_LINE_LOOP); 
		// bottom right to top left of X
		glVertex2f(x + (size / 2) + 0.05, y + 1.4); // bottom right
		glVertex2f(x + (size / 2) - 0.05, y + 1.5); // top left
		glEnd();
	}
}

void instantiateEnvironment() {
	// purple circle:
	renderCircle(-0.8, 1.0, 0.18, 200, 0.5, 0, 0.5);
	// blue circle:
	renderCircle(1.8, 0.55, 0.2, 100, 0, 0, 1);

	// GUI Box
	glColor3f(0,0,0);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-1, 1.4); // The bottom left corner 
	glVertex2f(-1, 1.9); // The top left corner
	glVertex2f(1.8, 1.9); // The top right corner  
	glVertex2f(1.8, 1.4); // The bottom right corner  
	glEnd();

	// GUI text
	std::string text1 = "Interception is occuring: ";
	renderText(text1.data(), text1.size(), -0.5, 1.75);

	std::string text2 = "Avoidance behaviour executing: ";
	renderText(text2.data(), text2.size(), -0.93, 1.55);

	// Bottom Left Animation Info
	if (numOfMovesMade > 75) { // once the car has passed the location.
		std::string text3 = "The animation above shows collision";
		std::string text4 = "detection and avoidance by";
		std::string text5 = "representing a car raycasting in";
		std::string text6 = "front of itself which identifies ";
		std::string text7 = "objects in front and steers away";
		std::string text8 = "from them.";
		renderSmallText(text3.data(), text3.size(), -2, -1.4);
		renderSmallText(text4.data(), text4.size(), -2, -1.5);
		renderSmallText(text5.data(), text5.size(), -2, -1.6);
		renderSmallText(text6.data(), text6.size(), -2, -1.7);
		renderSmallText(text7.data(), text7.size(), -2, -1.8);
		renderSmallText(text8.data(), text8.size(), -2, -1.9);
	}

	// GUI lights ON - first light set colour to green
	if (numOfMovesMade >= 150 && numOfMovesMade <= 170 || numOfMovesMade >= 325 && numOfMovesMade <= 355) {
		renderCircle(1.71, 1.78, 0.06, 200, 0,1,0);
	}
	else { // GUI status light OFF - first light set colour to red
		renderCircle(1.71, 1.78, 0.06, 200, 1, 0, 0);
	} 
	// GUI lights ON - second light set colour to green
	if(numOfMovesMade > 158 && numOfMovesMade < 250 || numOfMovesMade > 350 && numOfMovesMade < 435){
		renderCircle(1.71, 1.58, 0.06, 200, 0, 1, 0);
	}
	else { // GUI status light OFF - second light set colour to red
		renderCircle(1.71, 1.58, 0.06, 200, 1, 0, 0);
	}
}

void drawScene(void) {
	// Sets up what is viewed in the window 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(-0.2f, 0.0f, 0.0f);
	glOrtho(-2.5, 2.2, -2.2, 2.2, -1, 1);

	// clears what was in the window previously
	glClearColor(0.64, 0.64, 0.64, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// input the environment and GUI to the scene
	instantiateEnvironment();

	// inputs the car image onto the window in it's specified x and y position with specified size.
	glPushMatrix();
	moveCar(x, y, size);
	glPopMatrix();
	
	// if number of moves has not been achieved:
	if (numOfMovesMade < numOfMovesToBeMade) {
		//increment the number of moves made.
		numOfMovesMade += 1;
		// interval between each movement (in msecs, 1000msecs = 1sec)
		Sleep(30);
		
		// Movements.
		// movement 1
		if (numOfMovesMade <= 158){
			y += 0.01;
		}
		// movement 2 and 4 -> Rotations
		else if (numOfMovesMade > 158 && numOfMovesMade < 250 || numOfMovesMade > 350 && numOfMovesMade < 435){ // rotate from left op + 1, to right op - 1.
			slowRotation -= 1.0f;
		}
		// movement 3
		else if (numOfMovesMade >= 300 && numOfMovesMade <= 350){
			y += 0.01;
		}
		// movement 5
		else {
		// remaining frames
			y += 0.01;
		}

		// Swap buffer so you can see the content.
		glutSwapBuffers();
		// Rerun the this method.
		glutPostRedisplay();
	}
	else {
		// with the animation ended, flush.
		glFlush();
		// reset values 
		x = -0.95f;
		y = -2.1f;
		size = 0.4;
		numOfMovesMade = 0;
		slowRotation = 0.0f;
		// and then for continous loop
		glutPostRedisplay();
	}
}
void updateScene(int value) {}
void resize(int w, int h) {}
void setup(void) {}
void keyInput(unsigned char key, int x, int y) {}
void keySpecial(int key, int x, int y) {}
void keyUp(unsigned char key, int x, int y) {}
void keyUpSpecial(int key, int x, int y) {}
void close(void) {}