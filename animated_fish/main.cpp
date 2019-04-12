#include<GL/glew.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define windowH 400
#define windowW 600

//translation variables
float tx=0.0;
float ty=0.0;

//variables incrementation
float xStep=1;
float yStep=0.25;

void display(void);
void screen(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void anim(int value);

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Animation Test");

	glutReshapeFunc(screen);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutTimerFunc(1500,anim,1);
	glutMainLoop();

	return(0);
}

void anim(int value){
	if ((tx)>(100) || (tx) < (-100)){
		xStep= -xStep;
	}
	if ((ty)>(10) || (ty) < (-10)){
		yStep= -yStep;
	}
	tx += xStep;
	ty += yStep;

	printf("\n Top %.2f \t Bottom %.2f \t Right %.2f \t Left %.2f",((windowH)/2),(((windowH)/2)*-1),((windowW)/2),(((windowW)/2)*-1));
	printf("\n Step X %.2f Step Y %.2f", xStep, yStep);
	printf("\n TX %.2f TY %.2f", tx, ty);

	glutPostRedisplay();
	glutTimerFunc(150,anim,1);
}

void keyboard(unsigned char key, int x, int y){
	printf("\n Key %c", key);
	printf("\n1-Translate X\n2-Translate Y\nEnter: ");
	printf("\nKey %c", key);
	printf("\n Mouse position: %d x %d", x,y);
}

void fish(){
	glColor3f(0,1,0);

	glBegin(GL_POLYGON);
		glVertex2f(50, 50);
		glVertex2f(100, 75);
		glVertex2f(150, 80);
		glVertex2f(140, 110);
		glVertex2f(90, 90);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2f(150, -80);
		glVertex2f(130, -95);
		glVertex2f(90, -90);
		glVertex2f(100, -75);
	glEnd();

	glColor3f(1,0,0);

	glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(-100, 100);
		glVertex2f(-50, 0);
		glVertex2f(-100, -100);
	glEnd();

	glBegin(GL_POLYGON);		
		glVertex2f(0, 0);
		glVertex2f(50, 50);
		glVertex2f(100, 75);
		glVertex2f(150, 80);
		glVertex2f(200, 60);
		glVertex2f(230, 30);
		glVertex2f(240, 0);
		glVertex2f(230, -30);
		glVertex2f(200, -60);
		glVertex2f(150, -80);
		glVertex2f(100, -75);
		glVertex2f(50, -50);
	glEnd();
}

void draw_elements(){
	glLoadIdentity();
	//Unanimated
	glTranslatef((windowW)/2, (windowH)/2, 0);
	
	glEnd();
	//Animated
	glTranslatef(tx, ty, 0);
	fish();
}

void display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0,0, windowW, windowH);
	draw_elements();

	glFlush();
}

void screen(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);
}