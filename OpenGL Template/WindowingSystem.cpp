//
//  WindowingSystem.c
//  IsoJetPac
//
//  Created by Cameron Gray on 01/12/2013.
//  Copyright (c) 2013 Cameron Gray. All rights reserved.
//

#include "WindowingSystem.h"

// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv) {

	// Initialize GLUT.
	glutInit(&argc, argv);

	// Set display mode with an RGB colour buffer, double buffering and a depth buffer..
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// Set OpenGL window size
	glutInitWindowSize(500,500);

	// Set position of OpenGL window upper-left corner
	glutInitWindowPosition(100, 100);

	// Create OpenGL window with title
	glutCreateWindow("OpenGL Template");

	// Initialize
	setup();

	// Register display routine
	glutDisplayFunc(drawScene);

	// Register reshape routine
	glutReshapeFunc(resize);

	// Register keyboard routine
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(keySpecial);
	glutKeyboardUpFunc(keyUp);          // Only used in play modes.
	glutSpecialUpFunc(keyUpSpecial);

	// Begin processing
	glutMainLoop();

	return 0;
}