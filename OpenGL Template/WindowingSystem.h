#include <stdio.h>          // Header File For Standard Input / Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <math.h>			// Header File For Math functions.
#include <iostream>         // Header File For I/O Streams
#ifdef __APPLE__ 
#include <GL/glew.h>        // Header File For GL Extension Wrangler.
#include <GLUT/glut.h>		// Header File For GLUT library
							// ... glut.h calls gl.h and glu.h
#endif
#ifdef _WIN32
#include <gl/glew.h>
#include <gl/glut.h>
#include <Windows.h>
#endif

#include <SOIL.h>

#ifndef FALSE
#define FALSE (0)
#define TRUE (!(FALSE))
#endif

// These are the functions that you will use to create and interact with your GL scene:
void drawScene(void);
void updateScene(int value);
void resize(int w, int h);
void setup(void);
void keyInput(unsigned char key, int x, int y);
void keySpecial(int key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keyUpSpecial(int key, int x, int y);
void close(void);