#include <bits/stdc++.h>
#include<iostream>
#include<string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SDL2/SDL.h>
#include<stdlib.h>
#include "game.h"
using namespace std;
#define COLUMNS 40
#define ROWS 40
#define FPS 10
 

extern short sDirection;
bool gameOver=false;

int score=0;

void reverse(char str[], int length) 
{ 
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    { 
        swap(*(str+start), *(str+end)); 
        start++; 
        end--; 
    } 
} 

char* itoa(int num, char* str, int base) 
{ 
    int i = 0; 
    bool isNegative = false; 

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 

    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) 
    { 
        isNegative = true; 
        num = -num; 
    } 

    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 

    // If number is negative, append '-' 
    if (isNegative) 
        str[i++] = '-'; 

    str[i] = '\0'; // Append string terminator 

    // Reverse the string 
    reverse(str, i); 

    return str; 
} 

void timer_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,timer_callback,0);
}

void display_callback()
{   
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	drawSnake();
    drawFood();
	glutSwapBuffers();
	if(gameOver)
	{  
        char _score[10];
        itoa(score,_score,10);
        char text[50]= "Your Score: ";
        strcat(text,_score);
       // string tex ="Your Score :";
        //string _score=to_string(score);

       
        //text.append(_score);
      int y =SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
                         "GAME OVER",
                         text,
                         NULL);
      exit(0);

	}
}

void keyboard_callback(int key,int,int)
{
     switch(key)
     {
     	case GLUT_KEY_UP:
     	    if(sDirection!=DOWN)
     	      sDirection=UP;
     	    break;
        case GLUT_KEY_DOWN:
            if(sDirection!=UP)
              sDirection=DOWN;
            break;
        case GLUT_KEY_RIGHT:
            if(sDirection!=LEFT)
              sDirection=RIGHT;
            break;
        case GLUT_KEY_LEFT:
            if(sDirection!=RIGHT)
              sDirection=LEFT;
            break;

     }
}

void reshape_callback(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);

}

void init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	initGrid(COLUMNS,ROWS);
}

int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(200,100);
	glutInitWindowSize(500,500);


	glutCreateWindow("Snake");
	glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);

    glutTimerFunc(0,timer_callback,0);
    glutSpecialFunc(keyboard_callback);

	init();

	glutMainLoop();
}