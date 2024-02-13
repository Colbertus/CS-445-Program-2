// Graphics Pgm 1 for Colby McClure
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
using namespace std; 

void display_func() {

}

// Set the canvas size to be 600 x 600 
#define canvas_Width 600
#define canvas_Height 600
char canvas_Name[] = "Colby McClure Winter Wonderland";

int main(int argc, char ** argv) {

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	// Start the keyboard and display function along with the loop
	glutKeyboardFunc(keyboardInput);
	glutDisplayFunc(display_func);
	glutMainLoop();
	return 0;
}