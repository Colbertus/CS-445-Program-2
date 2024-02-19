// Graphics Pgm 1 for Colby McClure
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
using namespace std; 

// To compile and link the code: g++ mcclurePgm2.cpp -o mcclurePgm2.exe -Wall -lGL -lGLU -lglut -lGLEW 

int y_pos; // 550
int x_pos; //25

bool gameWin = false;

bool gameBegin = true;

bool gameOver = false;

void drawArrow(int x, int y) {

	glColor3f(1, 0.5, 0);
	glBegin(GL_LINES);

	glVertex2i(x - 25 - x_pos, y + 25 - y_pos); 
	glVertex2i(x - x_pos, y - y_pos);

	glVertex2i(x - x_pos, y - y_pos);
	glVertex2i(x + 25 - x_pos, y + 25 - y_pos);

	glVertex2i(x - 25 - x_pos, y + 25 - y_pos);
	glVertex2i(x - x_pos, y - 25 - y_pos);

	glVertex2i(x + 25 - x_pos, y + 25 - y_pos);
	glVertex2i(x - x_pos, y - 25 - y_pos);

	glEnd(); 
}

void drawSnowman() {

	glColor3f(1, 1, 1); 

	glTranslatef(300, 75, 0); 
	glutWireSphere(75, 20, 20);
	glLoadIdentity();

	glTranslatef(300, 187.5, 0);
	glutWireSphere(37.5, 20, 20); 
	glLoadIdentity();

	glTranslatef(300, 250, 0);
	glutWireSphere(25, 20, 20);
	glLoadIdentity();

}

void winText() {
	glColor3f(1, 1, 1);
	glRasterPos2i(250, 300);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
}

void beginText() {
	glColor3f(1, 1, 1);
	glRasterPos2i(200, 300);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'K');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');

}

void drawLandingPad() {
	glColor3f(0, 1, 0); 
	glLineWidth(2);
	glBegin(GL_LINES);
	
	glVertex2i(500, 0);
	glVertex2i(550, 0);


	glEnd(); 

	glLineWidth(1);
}

void display_func() {

	glClearColor(0.1, 0.1, 0.1, 1); 
	glClear(GL_COLOR_BUFFER_BIT);

	drawSnowman();
	drawArrow(25, 575); 
	drawLandingPad();

	if(gameBegin) {
		beginText();
	}

	if(gameWin) {
		winText();
	}

	glFlush(); 

	

}


void arrowFall(int val) {
	if(y_pos < 550) {
		y_pos += 3; 
		glutPostRedisplay();
		glutTimerFunc(35, arrowFall, 1);
	} else {

		gameOver = true; 
		display_func();
	}
}

void keyboardInput(unsigned char key, int x, int y) {
	gameBegin = false;
	if(gameOver) {
		if(x_pos > 500 && x_pos < 550) {
			gameWin = true;
			glutPostRedisplay();
		}
		return;
	}

	if (key == 'h') {
		x_pos += 30; 
		glutPostRedisplay();
	} else if (key == 'j') {
		x_pos -= 30; 
		glutPostRedisplay();
	}
	glutTimerFunc(35, arrowFall, 1);
}

// Set the canvas size to be 600 x 600 
#define canvas_Width 600
#define canvas_Height 600
char canvas_Name[] = "Colby McClure Winter Wonderland";

int main(int argc, char ** argv) {

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	y_pos = 0;
	x_pos = 0; 

	// Start the keyboard and display function along with the loop
	glutKeyboardFunc(keyboardInput);
	glutDisplayFunc(display_func);
	glutMainLoop();
	return 0;
}