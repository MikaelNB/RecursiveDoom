#include <windows.h>  // for MS Windows
#include <glut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 15

/* Global variables */
char title[] = "3D Shapes";
float rotationDelta = 0.0f;
float currentRotation = 0;
int mH[N][N - 1];
int mV[N - 1][N];



/* Initialize OpenGL Graphics */
void MyKeyBoardFunc(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'a': rotationDelta -= 0.1f; break;
	case 'd': rotationDelta += 0.1f; break;
	case 's': rotationDelta = 0; break;
	};


}
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	glutKeyboardFunc(MyKeyBoardFunc);
}

void RecursiveDivision(int i0, int i1, int j0, int j1)//Ingreso de Filas y columnas Iniciales y Finales
{
	if (i1 - i0 <= 1 || j1 - j0 <= 1)return; //Caso base, espacio del corredor es 1

	int h = i1 - i0; int w = j1 - j0; //h: height, w: width
	int opt;
	if (h > w) { opt = 0; } //Si h > w se hará un corte Horizontal
	else if (w > h) { opt = 1; }//Sino w < h se hará un corte Vertical
	else opt = rand() % 2;//Otro, si w == h entonces de hace un corte aleatorio V o H

	int ic, jc; //Fila de corte, columna de corte
	switch (opt)
	{
	case 0:
		/*aleatorio entre la fila siguiente a la inicial y
		la fila anterior a la final, ->
		entre (i0+1) y (i1-1). POR EJEMPLO: si i0 =2 y i1 == 7 entonces:
		rand() % (7-2-1) +2 +1 = rand() % (4)[desde 0 hasta 3] + 2 + 1 = (3,4,5,6))
		*/
		ic = rand() % (i1 - i0 - 1) + i0 + 1;

		for (int i = j0; i < j1; i++)
		{
			mH[ic][i] = 1;
		}
		mH[ic][rand() % ((j1 - j0) / 2 + 1) + j0] = 0; //Creacion de puertas
		RecursiveDivision(i0, ic, j0, j1);
		RecursiveDivision(ic, i1, j0, j1);
		break;
	case 1:
		jc = rand() % (j1 - j0 - 1) + j0 + 1;
		for (int i = i0; i < i1; i++)
		{
			mV[i][jc] = 1;
		}
		mV[rand() % ((i1 - i0) / 2 + 1) + i0][jc] = 0; //Creacion de puertas
		RecursiveDivision(i0, i1, j0, jc);
		RecursiveDivision(i0, i1, jc, j1);
		break;
	}
}



/* Handler for window-repaint event. Called back when the window first appears and
whenever the window needs to be re-painted. */
void FigurasPrimitivas()
{
	glLoadIdentity();                 // Reset the model-view matrix
	glTranslatef(0.0f, 0.0f, -20.0f);  // Move right and into the screen

	//glTranslatef(0.5f, 0.0f, -7.0f);  // Move right and into the screen
	glPushMatrix();
	glRotatef(currentRotation += 1.4f, 0.0, 1.0, 0);

	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	// Top face (y = 1.0f)
	// Define vertices in counter-clockwise (CCW) order with normal pointing out

	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();  // End of drawing color-cube
	glPopMatrix();

	// Render a pyramid consists of 4 triangles
	glLoadIdentity();                  // Reset the model-view matrix
	glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen

	glRotatef(currentRotation += 1.4f, 0.0, 1.0, 0);
	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	// Front
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left
	glColor3f(1.0f, 0.0f, 0.0f);       // Red
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);       // Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);       // Green
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();   // Done drawing the pyramid
}

void Laberinto()
{
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (mV[i][j] == 0)continue;

			glLoadIdentity();                 // Reset the model-view matrix
			glTranslatef((-N + 1)*0.5f, (-N + 1)*0.5f, -N - 3);
			glTranslatef(j, i, 0);
			glBegin(GL_QUADS);

			glColor3f(0.0f, 0.15f, 0.25f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			//glColor3f(0.5f, 0, 0);
			glVertex3f(0, 1, 0);
			glColor3f(1.0f, 0.15f, 0.25f);
			//glColor3f(0.5f, 0, 0);
			glVertex3f(0, 1, 1);

			//glColor3f(0.5f, 1, 0);
			glVertex3f(0, 0, 1);
			//glPopMatrix();
			glEnd();
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			if (mH[i][j] == 0)continue;

			glLoadIdentity();                 // Reset the model-view matrix
			//glPushMatrix();
			//glRotatef(-30, 1, 0, 0);
			glTranslatef((-N + 1)*0.5f, (-N + 1)*0.5f, -N - 3);
			glTranslatef(j, i, 0);
			glBegin(GL_QUADS);

			glColor3f(0.0f, 0.3f, 0.45f);
			glVertex3f(1, 0, 0);


			glColor3f(1.0f, 0.3f, 0.45f);
			//glColor3f(0.5f, 0.5f, 1);
			glVertex3f(1, 0, 1);

			//glColor3f(1, 0.5f, 0.5f);
			glVertex3f(0, 0, 1);
			glColor3f(0.0f, 0.3f, 0.45f);
			//glColor3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			//glPopMatrix();
			glEnd();
		}
	}
}

void Plataforma()
{
	glLoadIdentity();                 // Reset the model-view matrix
	//glPushMatrix();
	//glRotatef(-30, 1, 0, 0);
	glTranslatef((-N + 1)*0.5f, (-N + 1)*0.5f, -N - 3);
	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.25f, 0.35f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	//glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(N - 1, 0.0f, 0.0f);
	glColor3f(0.0f, 0.65f, 0.75f);
	//glColor3f(1, 0.2f, 0.2f);
	glVertex3f(N - 1, N - 1, 0.0f);

	//glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(0.0f, N - 1, 0.0f);
	//glPopMatrix();
	glEnd();
	Laberinto();

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glClearColor(0.0f, 0.2f, 0.3f, 0);
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	Plataforma();
	// Render a color-cube consisting of 6 quads with different colors


	glutPostRedisplay();
	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */



int main(int argc, char** argv) {
	srand(time(NULL));
	RecursiveDivision(0, N - 1, 0, N - 1);


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			printf("%d ", mH[i][j]);
		}
		printf("\n");
	}
	printf("\n"); printf("\n"); printf("\n");

	for (int i = 0; i < N - 1; i++)
	{
		mH[0][i] = 1;
		mV[i][0] = 1;
		mH[N - 1][i] = 1;
		mV[i][N - 1] = 1;
	}

	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", mV[i][j]);
		}
		printf("\n");
	}
	printf("\n"); printf("\n");

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			printf("-%c", mH[i][j] * 196);


		}
		printf("%c\n", 248);
		for (int j = 0; j < N; j++)
		{
			printf("%c ", mV[i][j] * 179);
		}
		printf("\n");
	}
	printf("\n"); printf("\n"); printf("\n");





	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(640, 480);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	initGL();                       // Our own OpenGL initialization	
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}