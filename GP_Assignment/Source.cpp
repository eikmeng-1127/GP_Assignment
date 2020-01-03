
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "GP Assignment"


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) 
			PostQuitMessage(0);
		else if (wParam == VK_SPACE)
		{
			glLoadIdentity();
		}
		else if (wParam == VK_UP)
		{
			glRotatef(5, -1.0, 0.0, 0.0);
		}
		else if (wParam == VK_DOWN)
		{
			glRotatef(5, 1.0, 0.0, 0.0);
		}
		else if (wParam == VK_LEFT)
		{
			glRotatef(5, 0.0, -1.0, 0.0);
		}
		else if (wParam == VK_RIGHT)
		{
			glRotatef(5, 0.0, 1.0, 0.0);
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//----------------------------- Shapes for legs
void join_cylinderleft()
{
	glRotatef(270, 0, 1.0, 0);
	glTranslatef(0.0f, -1.0f, 2.3f);

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(0, 1, 0);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.5, 0.5, 1.5, 20, 5);
	gluDeleteQuadric(cylinder);
}

void join_cylinderright()
{
	glRotatef(90, 0, 1.0, 0);
	glTranslatef(0.0f, -1.0f, 2.3f);

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(0, 1, 0);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.5, 0.5, 1.5, 20, 5);
	gluDeleteQuadric(cylinder);
}

//top rectangle for leg
void rectangle_1(double h) 
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	//top
	glVertex3f(-0.5f, 1.0f, -1.0f);
	glVertex3f(-0.5f, 1.0f, 1.0f);
	glVertex3f(0.5f, 1.0f, 1.0f);
	glVertex3f(0.5f, 1.0f, -1.0f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(0.5f, 1.0f, -1.0f);
	glVertex3f(-0.5f, 1.0f, -1.0f);
	glVertex3f(-0.5f, 0.0f - h, -1.0f);
	glVertex3f(0.5f, 0.0f - h, -1.0f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(0.5f, 0.0f - h, -1.0f);
	glVertex3f(0.5f, 1.0f, -1.0f);
	glVertex3f(0.5f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.0f - h, 1.0f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(0.5f, 0.0f - h, 1.0f);
	glVertex3f(0.5f, 0.0f - h, -1.0f);
	glVertex3f(-0.5f, 0.0f - h, -1.0f);
	glVertex3f(-0.5f, 0.0f - h, 1.0f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-0.5f, 0.0f - h, 1.0f);
	glVertex3f(-0.5f, 0.0f - h, -1.0f);
	glVertex3f(-0.5f, 1.0f, -1.0f);
	glVertex3f(-0.5f, 1.0f, 1.0f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-0.5f, 1.0f, 1.0f);
	glVertex3f(0.5f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.0f - h, 1.0f);
	glVertex3f(-0.5f, 0.0f - h, 1.0f);
	glEnd();
}

//shape under rectangle_1
void rectangle_2()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	//top
		glVertex3f(-0.5f, 1.0f, -1.0f);
		glVertex3f(-0.5f, 1.0f, 1.0f);
		glVertex3f(0.5f, 1.0f, 1.0f);
		glVertex3f(0.5f, 1.0f, -1.0f);

	//back
	//glColor3f(1, 0, 0);
		glVertex3f(0.5f, 1.0f, -1.0f);
		glVertex3f(-0.5f, 1.0f, -1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);

	//right
	//glColor3f(0, 1, 0);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 1.0f, -1.0f);
		glVertex3f(0.5f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

	//bottom
	//glColor3f(0, 0, 1);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

	//left
	//glColor3f(1, 1, 0);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 1.0f, -1.0f);
		glVertex3f(-0.5f, 1.0f, 1.0f);

	//front
	//glColor3f(1, 0, 1);
		glVertex3f(-0.5f, 1.0f, 1.0f);
		glVertex3f(0.5f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();
}

//rectangle under rectangle_2
void rectangle_3(double h)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	//top
	glVertex3f(-0.5f, 1.0f, -0.5f);
	glVertex3f(-0.5f, 1.0f, 0.5f);
	glVertex3f(0.5f, 1.0f, 0.5f);
	glVertex3f(0.5f, 1.0f, -0.5f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(0.5f, 1.0f, -0.5f);
	glVertex3f(-0.5f, 1.0f, -0.5f);
	glVertex3f(-0.5f, 0.0f - h, -0.5f);
	glVertex3f(0.5f, 0.0f - h, -0.5f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(0.5f, 0.0f - h, -0.5f);
	glVertex3f(0.5f, 1.0f, -0.5f);
	glVertex3f(0.5f, 1.0f, 0.5f);
	glVertex3f(0.5f, 0.0f - h, 0.5f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(0.5f, 0.0f - h, 0.5f);
	glVertex3f(0.5f, 0.0f - h, -0.5f);
	glVertex3f(-0.5f, 0.0f - h, -0.5f);
	glVertex3f(-0.5f, 0.0f - h, 0.5f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-0.5f, 0.0f - h, 0.5f);
	glVertex3f(-0.5f, 0.0f - h, -0.5f);
	glVertex3f(-0.5f, 1.0f, -0.5f);
	glVertex3f(-0.5f, 1.0f, 0.5f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-0.5f, 1.0f, 0.5f);
	glVertex3f(0.5f, 1.0f, 0.5f);
	glVertex3f(0.5f, 0.0f - h, 0.5f);
	glVertex3f(-0.5f, 0.0f - h, 0.5f);
	glEnd();
}

//rectangle under rectangle_3
void rectangle_4(double h)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	//top
	glVertex3f(-0.6f, 1.0f, -0.6f);
	glVertex3f(-0.6f, 1.0f, 0.6f);
	glVertex3f(0.5f, 1.0f, 0.6f);
	glVertex3f(0.5f, 1.0f, -0.6f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(0.5f, 1.0f, -0.6f);
	glVertex3f(-0.6f, 1.0f, -0.6f);
	glVertex3f(-0.6f, 0.0f - h, -0.6f);
	glVertex3f(0.5f, 0.0f - h, -0.6f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(0.5f, 0.0f - h, -0.6f);
	glVertex3f(0.5f, 1.0f, -0.6f);
	glVertex3f(0.5f, 1.0f, 0.6f);
	glVertex3f(0.5f, 0.0f - h, 0.6f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(0.5f, 0.0f - h, 0.6f);
	glVertex3f(0.5f, 0.0f - h, -0.6f);
	glVertex3f(-0.6f, 0.0f - h, -0.6f);
	glVertex3f(-0.6f, 0.0f - h, 0.6f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-0.6f, 0.0f - h, 0.6f);
	glVertex3f(-0.6f, 0.0f - h, -0.6f);
	glVertex3f(-0.6f, 1.0f, -0.6f);
	glVertex3f(-0.6f, 1.0f, 0.6f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-0.6f, 1.0f, 0.6f);
	glVertex3f(0.5f, 1.0f, 0.6f);
	glVertex3f(0.5f, 0.0f - h, 0.6f);
	glVertex3f(-0.6f, 0.0f - h, 0.6f);
	glEnd();
}

//rectangle under rectangle_4
void rectangle_5(double h)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	//top
	glVertex3f(-0.6f, 1.0f, -0.6f);
	glVertex3f(-0.6f, 1.0f, 0.6f);
	glVertex3f(0.5f, 1.0f, 0.6f);
	glVertex3f(0.5f, 1.0f, -0.6f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(0.5f, 1.0f, -0.6f);
	glVertex3f(-0.6f, 1.0f, -0.6f);
	glVertex3f(-1.0f, 0.0f - h, -1.5f);
	glVertex3f(0.5f, 0.0f - h, -1.5f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(0.5f, 0.0f - h, -1.5f);
	glVertex3f(0.5f, 1.0f, -0.6f);
	glVertex3f(0.5f, 1.0f, 0.6f);
	glVertex3f(0.5f, 0.0f - h, 1.5f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(0.5f, 0.0f - h, 1.5f);
	glVertex3f(0.5f, 0.0f - h, -1.5f);
	glVertex3f(-1.0f, 0.0f - h, -1.5f);
	glVertex3f(-1.0f, 0.0f - h, 1.5f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-1.0f, 0.0f - h, 1.5f);
	glVertex3f(-1.0f, 0.0f - h, -1.5f);
	glVertex3f(-0.6f, 1.0f, -0.6f);
	glVertex3f(-0.6f, 1.0f, 0.6f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-0.6f, 1.0f, 0.6f);
	glVertex3f(0.5f, 1.0f, 0.6f);
	glVertex3f(0.5f, 0.0f - h, 1.5f);
	glVertex3f(-1.0f, 0.0f - h, 1.5f);
	glEnd();
}

//rectangle under rectangle_5
void rectangle_6()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	//top
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glVertex3f(-1.0f, 1.0f, 1.5f);
	glVertex3f(0.5f, 1.0f, 1.5f);
	glVertex3f(0.5f, 1.0f, -1.5f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(0.5f, 1.0f, -1.5f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glVertex3f(-0.8f, 0.6f, -1.2f);
	glVertex3f(0.5f, 0.6f, -1.2f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(0.5f, 0.6f, -1.2f);
	glVertex3f(0.5f, 1.0f, -1.5f);
	glVertex3f(0.5f, 1.0f, 1.5f);
	glVertex3f(0.5f, 0.6f, 1.2f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(0.5f, 0.6f, 1.2f);
	glVertex3f(0.5f, 0.6f, -1.2f);
	glVertex3f(-0.8f, 0.6f, -1.2f);
	glVertex3f(-0.8f, 0.6f, 1.2f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-0.8f, 0.6f, 1.2f);
	glVertex3f(-0.8f, 0.6f, -1.2f);
	glVertex3f(-1.0f, 1.0f, -1.5f);
	glVertex3f(-1.0f, 1.0f, 1.5f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-1.0f, 1.0f, 1.5f);
	glVertex3f(0.5f, 1.0f, 1.5f);
	glVertex3f(0.5f, 0.6f, 1.2f);
	glVertex3f(-0.8f, 0.6f, 1.2f);
	glEnd();
}

void quadforcenterleg()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	//top
	glVertex3f(-0.8f, 1.0f, -0.8f);
	glVertex3f(-0.8f, 1.0f, 0.8f);
	glVertex3f(0.8f, 1.0f, 0.8f);
	glVertex3f(0.8f, 1.0f, -0.8f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(0.8f, 1.0f, -0.8f);
	glVertex3f(-0.8f, 1.0f, -0.8f);
	glVertex3f(-1.0f, -0.5f, -1.2f);
	glVertex3f(1.0f, -0.5f, -1.2f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(1.0f, -0.5f, -1.2f);
	glVertex3f(0.8f, 1.0f, -0.8f);
	glVertex3f(0.8f, 1.0f, 0.8f);
	glVertex3f(1.0f, -0.5f, 1.2f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(1.0f, -0.5f, 1.2f);
	glVertex3f(1.0f, -0.5f, -1.2f);
	glVertex3f(-1.0f, -0.5f, -1.2f);
	glVertex3f(-1.0f, -0.5f, 1.22f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-1.0f, -0.5f, 1.2f);
	glVertex3f(-1.0f, -0.5f, -1.2f);
	glVertex3f(-0.8f, 1.0f, -0.8f);
	glVertex3f(-0.8f, 1.0f, 0.8f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-0.8f, 1.0f, 0.8f);
	glVertex3f(0.8f, 1.0f, 0.8f);
	glVertex3f(1.0f, -0.5f, 1.2f);
	glVertex3f(-1.0f, -0.5f, 1.2f);
	glEnd();
}

void quadforcenterleg_2()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	//top
	glVertex3f(-1.0f, 1.0f, -1.2f);
	glVertex3f(-1.0f, 1.0f, 1.2f);
	glVertex3f(1.0f, 1.0f, 1.2f);
	glVertex3f(1.0f, 1.0f, -1.2f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(1.0f, 1.0f, -1.2f);
	glVertex3f(-1.0f, 1.0f, -1.2f);
	glVertex3f(-0.8f, 0.6f, -0.8f);
	glVertex3f(0.8f, 0.6f, -0.8f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(0.8f, 0.6f, -0.8f);
	glVertex3f(1.0f, 1.0f, -1.2f);
	glVertex3f(1.0f, 1.0f, 1.2f);
	glVertex3f(0.8f, 0.6f, 0.8f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(0.8f, 0.6f, 0.8f);
	glVertex3f(0.8f, 0.6f, -0.8f);
	glVertex3f(-0.8f, 0.6f, -0.8f);
	glVertex3f(-0.8f, 0.6f, 0.8f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-0.8f, 0.6f, 0.8f);
	glVertex3f(-0.8f, 0.6f, -0.8f);
	glVertex3f(-1.0f, 1.0f, -1.2f);
	glVertex3f(-1.0f, 1.0f, 1.2f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-1.0f, 1.0f, 1.2f);
	glVertex3f(1.0f, 1.0f, 1.2f);
	glVertex3f(0.8f, 0.6f, 0.8f);
	glVertex3f(-0.8f, 0.6f, 0.8f);
	glEnd();
}
//------------------------------



//-----------------------------Shapes for body
void head_sphere()
{
	glTranslatef(0.0f, 0.25f, 0.0f);
	glRotatef(90, 1.0, 0.0, 0.0);

	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	glColor3f(0, 0, 1);
	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, 2.95, 20, 10);
	gluDeleteQuadric(sphere);
}

void body_cylinder()
{
	glTranslatef(0.0f, 0.25f, 0.0f);
	glRotatef(90, 1.0, 0.0, 0.0);

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(1, 0, 0);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 3.0, 3.0, 6.0, 20, 5);
	gluDeleteQuadric(cylinder);
}

void body_bottom()
{
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.0f, 0.0f, 5.7f);

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(1, 0, 0);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 3.0, 2.5, 1.0, 20, 5);
	gluDeleteQuadric(cylinder);
}

void center_leg_connector()
{
	glTranslatef(0.0f, -6.0f, 0.0f);
	glRotatef(90, 1.0, 0.0, 0.0);

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(1, 0, 1);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.5, 0.5, 1.5, 20, 5);
	gluDeleteQuadric(cylinder);
}

//-------------------------------



//-----------------------------Combined Leg shapes
void left_leg()
{
	//top cylinder
	glPushMatrix();
		glRotatef(270, 0, 1.0, 0);
		glTranslatef(0.0f, -1.0f, 3.2f);

		GLUquadricObj* cylinder = NULL;
		cylinder = gluNewQuadric();
		glColor3f(0, 1, 0);
		gluQuadricDrawStyle(cylinder, GLU_LINE);
		gluCylinder(cylinder, 1, 1, 1, 20, 5);
		gluDeleteQuadric(cylinder);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -2.0f, 0.0f);
		rectangle_1(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -4.0f, 0.0f);
		rectangle_2();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -4.5f, 0.0f);
		rectangle_3(1.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -7.0f, 0.0f);
		rectangle_4(0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -8.0f, 0.0f);
		rectangle_5(0.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -9.5f, 0.0f);
		rectangle_6();
	glPopMatrix();

	glPushMatrix();
		glRotatef(270, 0, 1.0, 0);
		glTranslatef(0.0f, -8.3f, 3.4f);

		GLUquadricObj* cylinder2 = NULL;
		cylinder2 = gluNewQuadric();
		glColor3f(0, 1, 0);
		gluQuadricDrawStyle(cylinder2, GLU_LINE);
		gluCylinder(cylinder2, 0.9, 0.9, 0.9, 20, 5);
		gluDeleteQuadric(cylinder2);
	glPopMatrix();
}

void right_leg()
{
	//top cylinder
	glPushMatrix();
		glRotatef(90, 0, 1.0, 0);
		glTranslatef(0.0f, -1.0f, 3.2f);

		GLUquadricObj* cylinder = NULL;
		cylinder = gluNewQuadric();
		glColor3f(0, 1, 0);
		gluQuadricDrawStyle(cylinder, GLU_LINE);
		gluCylinder(cylinder, 1, 1, 1, 20, 5);
		gluDeleteQuadric(cylinder);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -2.0f, 0.0f);
		rectangle_1(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -4.0f, 0.0f);
		rectangle_2();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -4.5f, 0.0f);
		rectangle_3(1.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -7.0f, 0.0f);
		glRotatef(180, 0, 1, 0);
		rectangle_4(0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -8.0f, 0.0f);
		glRotatef(180, 0, 1, 0);
		rectangle_5(0.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -9.5f, 0.0f);
		glRotatef(180, 0, 1, 0);
		rectangle_6();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 1.0, 0);
		glTranslatef(0.0f, -8.3f, 3.4f);

		GLUquadricObj* cylinder2 = NULL;
		cylinder2 = gluNewQuadric();
		glColor3f(0, 1, 0);
		gluQuadricDrawStyle(cylinder2, GLU_LINE);
		gluCylinder(cylinder2, 0.9, 0.9, 0.9, 20, 5);
		gluDeleteQuadric(cylinder2);
	glPopMatrix();
}

void center_leg()
{
	glPushMatrix();
		glTranslatef(0.0f, -8.0f, 0.0f);
		quadforcenterleg();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -9.5f, 0.0f);
		quadforcenterleg_2();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90.0, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -8.3f, -0.45);

		GLUquadricObj* cylinder2 = NULL;
		cylinder2 = gluNewQuadric();
		glColor3f(0, 1, 0);
		gluQuadricDrawStyle(cylinder2, GLU_LINE);
		gluCylinder(cylinder2, 0.9, 0.9, 0.9, 20, 5);
		gluDeleteQuadric(cylinder2);
	glPopMatrix();
}
//-----------------------------



void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

	//head
	glPushMatrix();
		head_sphere();
	glPopMatrix();

	//body
	glPushMatrix();
		body_cylinder();
	glPopMatrix();

	glPushMatrix();
		body_bottom();
	glPopMatrix();

	glPushMatrix();
		center_leg_connector();
	glPopMatrix();

	glPushMatrix();
		center_leg();
	glPopMatrix();

	//kaki
	glPushMatrix();
		glPushMatrix();
			join_cylinderleft();
		glPopMatrix();

		glPushMatrix();
			left_leg();
		glPopMatrix();

		glPushMatrix();
			join_cylinderright();
		glPopMatrix();

		glPushMatrix();
			right_leg();
		glPopMatrix();

	glPopMatrix();


	//Show direction
	glPushMatrix();
		// draw our axes
		glBegin(GL_LINES);
		// draw line for x axis
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0.0);
		// draw line for y axis
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
		// draw line for Z axis
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 10.0);
		glEnd();
		// load the previous matrix
	glPopMatrix();

}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*gluPerspective(40.0, 1.0, 1, 5000);
	glFrustum(-2, 2, -2, 2, 1, 5000);*/
	glOrtho(-12, 12, -12, 12, -12, 12);

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------