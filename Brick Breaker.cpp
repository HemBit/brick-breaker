#include"header.h"
#include<stdlib.h>
#include <GL/glut.h>
#include<stdio.h>
#include<string.h>
#include <math.h>
#include <map>
#include <string>
#include <stack>



void initialize()	//To set the initial co-ordinates of the objects on the screen
{
	int n = 0, x = 4, y = 390;
	while (n < 45)
	{
		if (x > 560)
		{
			x = 4;
			y -= 25;
		}
		b[n].x = x;
		b[n].y = y;
		b[n].w = 60;
		b[n].h = 20;
		b[n].alive = true;
		n++, x += 66;
	}

	block.myx = 300;
	block.myy = 0;
	block.width = 80;
	block.height = 20;
	block.lft = false;
	block.rgt = false;

	breaker.breakerx = 300;
	breaker.breakery = 200;
	breaker.breakerwh = 30;
	breaker.velx = 0.35;
	breaker.vely = 0.35;

	red1 = 0.73;
	green1 = 0.16;
	blue1 = 0.96;
	red2 = 0.435294;
	green2 = 0.258824;
	blue2 = 0.258824;

	breaker.red = 1.0f;
	breaker.green = 1.0f;
	breaker.blue = 0.0f;

	block.red = 0.0f;
	block.green = 0.0f;
	block.blue = 1.0f;

}
bool check_collision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) //Function for checking collision
{
	if (Ay + Ah < By) return false; //if A is more to the lft than B
	else if (Ay > By + Bh) return false; //if A is more to rgt than B
	else if (Ax + Aw < Bx) return false; //if A is higher than B
	else if (Ax > Bx + Bw) return false; //if A is lower than B
	
	return true; //There is a collision because none of above returned false
}

void reshape()		//Modify the co-ordinates according to the key-presses and collisions
{
	if (block.myx < 0)
		block.myx = 0;
	if (block.myx + block.width > 680)
		block.myx = 520;
	if (block.lft == true)
		block.myx = block.myx - 0.05;
	if (block.rgt == true)
		block.myx = block.myx + 0.05;



	breaker.breakerx += 0.05 * breaker.velx;
	breaker.breakery += 0.05 * breaker.vely;

	int n = 0;
	while (n < 45)
	{
		if (b[n].alive == true)
		{
			if (check_collision(breaker.breakerx, breaker.breakery, breaker.breakerwh, breaker.breakerwh, b[n].x, b[n].y, b[n].w, b[n].h) == true)
			{
				breaker.vely = -breaker.vely;
				b[n].alive = false;
				breaker.down = true;
				breaker.up = false;
				
				break;
			}
		}
		n++;
	}
	if (breaker.breakerx < 0)
	{
		breaker.velx = -breaker.velx;
		breaker.right = true;
		breaker.left = false;
	}
	if (breaker.breakerx + breaker.breakerwh > 600)
	{
		breaker.right = false;
		breaker.left = true;
		breaker.velx = -breaker.velx;
	}
	if (breaker.breakery + breaker.breakerwh > 400)
		breaker.vely = -breaker.vely;
	else if (breaker.breakery < 0)
		exit(0);

	if (check_collision(breaker.breakerx, breaker.breakery, breaker.breakerwh, breaker.breakerwh, block.myx, block.myy, block.width, block.height) == true)
	{
		breaker.vely = -breaker.vely;
		breaker.up = true;
		breaker.down = false;
		
	}
	draw();
}

void specialUp(int key, int x, int y)
{
	switch (key)
	{
	case (GLUT_KEY_LEFT): block.lft = false; break;
	case (GLUT_KEY_RIGHT): block.rgt = false; break;
	}
}
void specialDown(int key, int x, int y)
{
	switch (key)
	{
	case (GLUT_KEY_LEFT): block.lft = true; break;
	case (GLUT_KEY_RIGHT): block.rgt = true; break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) 		//27 corresponds to the esc key
	{
		breaker.velx = 0;
		breaker.vely = 0;	//To stop the breaker from moving

	}

}
void myinit()
{
	glViewport(0, 0, 600, 400);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 600, 0, 400);
}
void draw()		//Render the objects on the screen using the latest updated co-ordinates 
{



	int i = 0;
	while (i < 45)
	{
		if (b[i].alive == true)
		{
			if (i % 2 == 0) glColor3f(red1, green1, blue1);
			else glColor3f(red2, green2, blue2);
			glBegin(GL_POLYGON);
			glVertex2f(b[i].x, b[i].y);
			glVertex2f(b[i].x + b[i].w, b[i].y);
			glVertex2f(b[i].x + b[i].w, b[i].y + b[i].h);
			glVertex2f(b[i].x, b[i].y + b[i].h);
			glEnd();
		}
		i++;
	}



	glColor3f(block.red, block.green, block.blue);
	glBegin(GL_POLYGON);
	glVertex2f(block.myx, block.myy);
	glVertex2f(block.myx + block.width, block.myy);
	glVertex2f(block.myx + block.width, block.myy + block.height);
	glVertex2f(block.myx, block.myy + block.height);
	glEnd();

	glColor3f(breaker.red, breaker.green, breaker.blue);
	glBegin(GL_POLYGON);
	glVertex2f(breaker.breakerx, breaker.breakery);
	glVertex2f(breaker.breakerx + breaker.breakerwh, breaker.breakery);
	glVertex2f(breaker.breakerx + breaker.breakerwh, breaker.breakery + breaker.breakerwh);
	glVertex2f(breaker.breakerx, breaker.breakery + breaker.breakerwh);
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red, green, blue, 1);
	glDisable(GL_DEPTH_TEST);
	
	glFlush();
	reshape();
}

void revert()
{
	breaker.velx = 0.35;
	breaker.vely = 0.35;
	if (breaker.up == true)
	{
		if (breaker.right == true)
		{
			breaker.velx = breaker.velx;
			breaker.vely = breaker.vely;
		}
		else if (breaker.left == true)
		{
			breaker.velx = -breaker.velx;
			breaker.vely = breaker.vely;
		}
	}
	else if (breaker.down == true)
	{
		if (breaker.right == true)
		{
			breaker.velx = breaker.velx;
			breaker.vely = -breaker.vely;
		}
		else if (breaker.left == true)
		{
			breaker.velx = -breaker.velx;
			breaker.vely = -breaker.vely;
		}
	}
}

//change background color
void change_background_color(int opt)
{

	switch (opt)
	{
	case RED:	red = 1.0;
		green = 0.0;
		blue = 0.0;
		display();
		break;
	case GREEN:	red = 0.0;
		green = 1.0;
		blue = 0.0;
		display();
		break;
	case BLUE:	red = 0.0;
		green = 0.0;
		blue = 1.0;
		display();
		break;
	case BLACK:	red = 0.0;
		green = 0.0;
		blue = 0.0;
		display();
		break;
	}
}

//change breaker color
void change_breaker_color(int opt)
{
	switch (opt)
	{
	case PINK:	breaker.red = 0.737255;
		breaker.green = 0.560784;
		breaker.blue = 0.560784;
		break;

	case SCARLET:	breaker.red = 0.55;
		breaker.green = 0.09;
		breaker.blue = 0.09;
		break;

	case YELLOW:	breaker.red = 1,0;
		breaker.green = 1.0;
		breaker.blue = 0.0;
		break;
	}
}

//change breaker speed
void change_breaker_speed(int opt)
{

	switch (opt)
	{
	case INC:
		breaker.velx++;
		breaker.vely++;
		break;
	case DEC:
		breaker.velx -=0.25;
		breaker.vely -=0.25;
		break;

	}
}

//change paddle size
void change_paddle_size(int opt)
{

	switch (opt)
	{
	case PDINC:
		if (block.width < 160)
		{
			block.width += 20;
		}
		break;
	case PDDEC:
		if (block.width > 20)
		{
			block.width -= 20;
		}
		break;

	}
}

//handle menu
void handle_menu(int opt)
{

}

//change brick color
void change_brick_color(int opt)
{
	switch (opt)
	{
	case C1:
		red1 = 0.72;
		green1 = 0.45;
		blue1 = 0.20;
		red2 = 0.42;
		green2 = 0.26;
		blue2 = 0.15;
		break;
	case C2:
		red1 = 0.858824;
		green1 = 0.858824;
		blue1 = 0.439216;
		red2 = 0.90;
		green2 = 0.91;
		blue2 = 0.98;
		break;
	case C3:
		red1 = 0.184314;
		green1 = 0.309804;
		blue1 = 0.184314;
		red2 = 0.196078;
		green2 = 0.8;
		blue2 = 0.196078;
		break;
	case ORIGINAL:
		red1 = 0.73;
		green1 = 0.16;
		blue1 = 0.96;
		red2 = 0.435294;
		green2 = 0.258824;
		blue2 = 0.258824;
		break;
	}
}

//handle paddle color
void change_paddle_color(int opt)
{
	switch (opt)
	{
	case ORANGE:
		block.red = 1.0;
		block.green = 0.5;
		block.blue = 0.0;
		break;
	case WHITE:
		block.red = 1;
		block.green = 1;
		block.blue = 1;
		break;
	case BLUE2:
		block.red = 0.0f;
		block.green = 0.0f;
		block.blue = 1.0f;
		break;
	}
}

//Options
void ContQuit(int opt)
{
	switch (opt)
	{
	case CONTINUE: revert();
		break;
	case QUIT: exit(0);
	}
}

//add menu
void addMenu()
{


	int submenu1 = glutCreateMenu(change_background_color);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("default", BLACK);

	int submenu2 = glutCreateMenu(change_breaker_color);
	glutAddMenuEntry("Pink", PINK);
	glutAddMenuEntry("Scarlet", SCARLET);
	glutAddMenuEntry("default", YELLOW);

	int submenu4 = glutCreateMenu(change_brick_color);
	glutAddMenuEntry("Combination 1", C1);
	glutAddMenuEntry("Combination 2", C2);
	glutAddMenuEntry("Combination 3", C3);
	glutAddMenuEntry("default", ORIGINAL);

	int submenu3 = glutCreateMenu(change_breaker_speed);
	glutAddMenuEntry("Increase", INC);
	glutAddMenuEntry("Decrease", DEC);

	int submenu5 = glutCreateMenu(change_paddle_color);
	glutAddMenuEntry("Orange", ORANGE);
	glutAddMenuEntry("White", WHITE);
	glutAddMenuEntry("default", BLUE2);

	int submenu6 = glutCreateMenu(change_paddle_size);
	glutAddMenuEntry("Increase", PDINC);
	glutAddMenuEntry("Decrease", PDDEC);

	int submenu7 = glutCreateMenu(ContQuit);
	glutAddMenuEntry("Continue", CONTINUE);
	glutAddMenuEntry("Quit Game", QUIT);

	glutCreateMenu(handle_menu);
	glutAddSubMenu("Background Color", submenu1);
	glutAddSubMenu("Breaker Color", submenu2);
	glutAddSubMenu("Brick Color", submenu4);
	glutAddSubMenu("Paddle Color", submenu5);
	glutAddSubMenu("Breaker Speed", submenu3);
	glutAddSubMenu("Paddle Size", submenu6);
	glutAddSubMenu("Options", submenu7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Brick Breaker");
	initialize();
	myinit();
	draw();
	glutDisplayFunc(display);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(reshape);
	
	
	addMenu();
	glutMainLoop();
	return 0;
}
