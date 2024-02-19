// Graphics Pgm 2 for Colby McClure

#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
using namespace std; 

/*****************************************************************************************

Author: Colby McClure
Program: CS 445 Program 2 
Architecture Statement: when the program first, the display event handler, 'display_func', 
will display every object along with a text prompt displayed in the middle of the screen. 
For as long as the bool 'gameBegin' remains true, the prompt that displays "Any Key Will 
Start" will remain on the screen. As soon as the user hits a key, the keyboard event 
handler, 'keyboard_input', will trigger. As soon as this keyboard event handler triggers 
for the FIRST time, it will set 'gameBegin' to false, therefore removing the beginning
prompt from the screen. From then on, the keyboard handler will be in charge of several
things. For one, if the 'h' or 'H' key get pressed, then the arrows x position will be 
subtracted by 5 units and therefore moving the arrow to the left. If the 'j' or 'J' key
gets pressed, then the arrows x position will be incremented by 5 units and therefore 
moving the arrow to the right. Something to note, when either of the movement keys get 
pressed, the 'x_pos' variable gets incremented/decremented depending on the key.
This variable gets declared globally but gets set equal to 0 in the main function. 
While the keyboard checks for that input, there will be  a timer event handler,
'arrowFall', that will be activated that is in charge for checking the position of 
the 'y_pos' variable while the arrow falls. Just like the 'x_pos' variable, the 
'y_pos' variable also gets declared globally and gets set to 0 in the main function.
But while this timer event handler is running, if the 'y_pos' variable is less than or 
equal to 550, then increment the 'y_pos' variable by 3 units then call the timer event
handler once again. For further context, the 'x_pos' and 'y_pos' variable are 
added/subtracted from the x and y positions of the arrowhead, that is their purpose. 
As soon as the 'y_pos' variable is no longer less than or equal to 550, then the 
'gameOver' bool gets set to 'true' therefore ending the game. I chose to increment the
'y_pos' variable by 3 units per 25ms because that was the best time I found in which 
the arrow hits the ground in between 4 and 5 seconds. I also chose to check if the 
'y_pos' variable to be less than 550 because that is how big the arrow is supposed to 
be. As soon as 'y_pos' is over 550, then it could be assumed that the arrow has struck
the ground no matter what. As soon as the game ends, another condition gets check, the
'x_pos' position. I have it to where as soon as the game ends, if the 'x_pos' variable 
is not in between -475 and -525, then the user wins the game and the 'gameWin' bool 
gets set to true. I chose -475 and -525 because that is the range in which 'x_pos' 
needs to be in to be on the green landing pad. The end goal of the program is for 
the user to 'land' their arrow on the green landing pad that is placed on the 
bottom right-hand side of the canvas. But as soon as the 'gameWin' bool is set to 
true, the display event handler will draw text using bitmaps indicating to the user
that they have won the game. As soon as the arrow hits the ground, then the game
freezes and text will be displayed depending on whether the user landed the arrow
on the landing pad or not. 
 
*****************************************************************************************/

// To compile and link the code: g++ mcclurePgm2.cpp -o mcclurePgm2.exe -Wall -lGL -lGLU -lglut -lGLEW 

// Initialize the global variables for the x and y position of the arrow 
int y_pos; // 550
int x_pos; //25

// Initialize the global variables for the game state 
bool gameWin = false;
bool gameBegin = true;
bool gameOver = false;

// This function draws the arrow with the arguments being the x and y coordinates  
void drawArrow(int x, int y) {

	// Set the color to orange and begin the drawing
	glColor3f(1, 0.5, 0);
	glBegin(GL_LINES);

	// Draw the arrow head  
	glVertex3i(x - 25 - x_pos, y + 25 - y_pos, -10); 
	glVertex3i(x - x_pos, y - y_pos, -10);

	glVertex3i(x - x_pos, y - y_pos, -10);
	glVertex3i(x + 25 - x_pos, y + 25 - y_pos, -10);

	glVertex3i(x - 25 - x_pos, y + 25 - y_pos, -10);
	glVertex3i(x - x_pos, y - 25 - y_pos, -10);

	glVertex3i(x + 25 - x_pos, y + 25 - y_pos, -10);
	glVertex3i(x - x_pos, y - 25 - y_pos, -10);

	// End the drawing 
	glEnd(); 
}

// This function draws the snowman using wirespheres 
void drawSnowman() {

	// Set the color to white 
	glColor3f(1, 1, 1); 

	// Translate the snowman to the correct position and draw the bottom sphere
	glTranslatef(300, 75, -10); 
	glutWireSphere(75, 20, 20);
	glLoadIdentity();

	// Translate the snowman to the correct position and draw the middle sphere
	glTranslatef(300, 187.5, -10);
	glutWireSphere(37.5, 20, 20); 
	glLoadIdentity();

	// Translate the snowman to the correct position and draw the top sphere
	glTranslatef(300, 250, -10);
	glutWireSphere(25, 20, 20);
	glLoadIdentity();

}

// This function is responsible for drawing the text when the game is won
void winText() {

	// Set the color to white and position the raster cursor
	glColor3f(1, 1, 1);
	glRasterPos3i(250, 300, -10);

	// Draw the text, "You Win"
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
}

// This function is responsible for drawing the text when the game begins 
void beginText() {

	// Set the color to white and position the raster cursor
	glColor3f(1, 1, 1);
	glRasterPos3i(200, 300, -10);

	// Draw the text, "Any Key Will Start"
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

// This function is responsible for drawing the landing pad
void drawLandingPad() {

	// Set the color of the line to green, set the line width to 2, and begin drawing
	glColor3f(0, 1, 0); 
	glLineWidth(2);
	glBegin(GL_LINES);
	
	// Draw the landing pad
	glVertex3i(500, 0, -10);
	glVertex3i(550, 0, -10);

	// End the drawing and reset line width 
	glEnd(); 
	glLineWidth(1);
}

// This is my display event handler that will draw all of the objects for the program  
void display_func() {

	// Set the background color to a dark gray
	glClearColor(0.1, 0.1, 0.1, 1); 
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the snowman, arrow, and landing pad
	drawSnowman();
	drawArrow(25, 575); 
	drawLandingPad();

	// Draw the respective text if the game has not been started yet
	if(gameBegin) {
		beginText();
	}

	// Draw the respective text if the game has been won
	if(gameWin) {
		winText();
	}

	// Flush the drawing
	glFlush(); 
}

// This is my timer event handler that handles the falling of the arrow and sets the win condition
void arrowFall(int val) {

	// If the y position of the arrow is less than 550, continue to fall
	if(y_pos <= 550) {

		// Increment the y position, post the redisplay, and call the timer function 
		y_pos += 3; 
		glutPostRedisplay();
		glutTimerFunc(20, arrowFall, 1);

	// Else, the game is over and it checks if the game has been won and calls the display function 
	} else {
		gameOver = true; 
		
		// If the arrow has landed on the landing pad, set 'gameWin' to be true
		if(x_pos < -475 && x_pos > -525) {
			gameWin = true;
			glutPostRedisplay();
		}
		
		// Call the display function when the arrow done falling
		display_func();
	}
}

// This is my keyoard event handler that is in charge of moving the arrow when 'h', 'H', 'j', or 'J' get pressed 
void keyboardInput(unsigned char key, int x, int y) {

	// If the game has not been started, set the gameBegin variable to false
	if(gameBegin) {
		gameBegin = false;
		glutTimerFunc(25, arrowFall, 1);
	} 
	
	// If the 'gameOver' bool is set to true, then leave the function 
	if(gameOver) {
		return;
	}

	// If the key is 'h' or 'H', move the arrow left
	if (key == 'h' || key == 'H') {
		x_pos += 5; 

	// If the key is 'j' or 'J', move the arrow right
	} else if (key == 'j' || key == 'J') {
		x_pos -= 5; 
	
	// Otherwise, make the arrow fall like normal 
	} else {
		glutTimerFunc(25, arrowFall, 1);
	}
	
}

// Set the canvas size to be 600 x 600 
#define canvas_Width 600
#define canvas_Height 600

// Name the canvas 
char canvas_Name[] = "Colby McClure Winter Wonderland";

// This is my driver function 
int main(int argc, char ** argv) {

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	// Set x_pos and y_pos variables to 0 
	y_pos = 0;
	x_pos = 0; 

	// Start the keyboard and display function along with the loop
	glutKeyboardFunc(keyboardInput);
	glutDisplayFunc(display_func);
	glutMainLoop();
	return 0;
}