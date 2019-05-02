#include<GL/glew.h>
#include<GL/glut.h>
#include<GLFW/glfw3.h>
#include<GL/freeglut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>

#define windowH 900
#define windowW 1600
#define interval 16,666666667

float PI = atanf(1.0f)*4.0f;

struct Vertices{
	int x;
	int y;
};

struct Player{
	int score;
	float paddlePos;
};

struct Player p1;
struct Player p2;

//Variables for circle drawing
GLfloat circ_pnt = 200;
GLfloat ang, Xaxis, Yaxis, ballAxis;

//position variables
struct Vertices v1;
struct Vertices v2 = {.x=50, .y=150};

//Colors
float black = 0.0f;
float white = 1.0f;
float ballColor = white;
float grey = 0.5f;

//Variables for ball colision
float a_value;
float b_value;
float c_value;
bool touch=false;

//Variables for game scale
float scaleTV = 0.75f;

void display(void);
void screen(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void mouseMovement(int x, int y);

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Circle Events");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutFullScreen();
	glutReshapeFunc(screen);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutPassiveMotionFunc(mouseMovement);
	glutMainLoop();

	return(0);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'b':
			ballColor = black;
			break;
		case 'w':
			p1.score+=1;
			p2.score+=1;
			break;
		case 's':
			break;
		case 'o':
			break;
		case 'l':
			break;
		case 27:
			glutDestroyWindow (0);
			exit(0);
			break;
	}
}

void mouseMovement(int x, int y){
	v1.x = x-(windowW/2);
	v1.y = y-(windowH/2);

	float a_value=v1.x-v2.x;
	float b_value=v1.y-v2.y;
	float c_value=sqrt((a_value*a_value)+(b_value*b_value));

	if(c_value < (ballAxis*2)){
		touch=true;
	}else{
		touch=false;
	}
}

void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    glColor3f(white,white,white);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
}

std::string int2str(int x){
	std::stringstream ss;
	ss << x;
	return ss.str( );
}

void centerLine(){
	glLineWidth(5);
	glColor3f(white,white,white);
	glBegin(GL_LINES);
		glVertex2f(0,-410);
		glVertex2f(0,440);
	glEnd();
}

void ball(){
	glColor3f(ballColor,ballColor,ballColor);
	ballAxis = 30;
	glBegin(GL_POLYGON);
		for(int i=0;i<circ_pnt;i++){
			ang=(2*PI*i)/circ_pnt;
			glVertex2f(cos(ang)*ballAxis,sin(ang)*ballAxis);
		}
	glEnd();
}

void paddle(){
	glColor3f(white,white,white);
	glBegin(GL_QUADS);
		glVertex2f(-10,60);
		glVertex2f(10,60);
		glVertex2f(10,-60);
		glVertex2f(-10,-60);
	glEnd();
}

void gameOverScreen(){
	
}

void scoreText(){
	drawText(-18,-420, int2str(p1.score) + " : " + int2str(p2.score));
}

void draw_elements(){
	glLoadIdentity();
	glPushMatrix();
		glTranslatef((windowW)/2,(windowH)/2,0);
		glScalef(scaleTV,-(scaleTV),scaleTV);
		scoreText();
		centerLine();
		glPushMatrix();
			glTranslatef(v1.x,v1.y,0);
			ballColor=white;
			ball();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-700,0,0);
			paddle();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(700,0,0);
			paddle();
		glPopMatrix();
	
		if((p1.score==10)||(p2.score==10)){
			gameOverScreen();
			glutDestroyWindow(0);
			exit(0);
		}

		glutPostRedisplay();
	glPopMatrix();
}

void display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(black,black,black,white);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0,0,windowW, windowH);
	draw_elements();

	glFlush();
}

void screen(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);

}
