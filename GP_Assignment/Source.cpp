
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "GP Assignment"

GLfloat gunmove = -5.0f;
GLfloat gunrotate = 270.0f;
GLfloat legmove = 2.5f;
GLfloat bodyrotate = 0;
GLfloat movex = 0.0;
GLfloat movey = 0.0;
GLfloat movez = 0.0;
GLfloat rotater2 = 0;

int triangleAmount = 400;
GLfloat twopi = 2.0f * 3.14159265359;

boolean activategun = false;
boolean rotategun = false;
int activateleg = 0;
int activatebodyrotate = 0;


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
		else if (wParam == 'N')
		{
			if (activategun == true)
			{
				activategun = false;
			}
			else
			{
				activategun = true;
			}
		}
		else if (wParam == 'M')
		{
			if (rotategun == true)
			{
				rotategun = false;
			}
			else
			{
				rotategun = true;
			}
		}
		else if (wParam == 'Z')
		{
			activateleg = 1;
		}
		else if (wParam == 'X')
		{
			activateleg = 2;
		}
		else if (wParam == 'C')
		{
			activatebodyrotate = 1;
		} 
		else if (wParam == 'V')
		{
			activatebodyrotate = 2;
		} 
		else if (wParam == 'A')
		{
			movex += 0.2;
		}
		else if (wParam == 'D')
		{
			movex -= 0.2;
		}
		else if (wParam == 'W')
		{
			movez += 0.2;
		}
		else if (wParam == 'S')
		{
			movez -= 0.2;
		}
		else if (wParam == 'Q')
		{
			rotater2 += 2;
		}
		else if (wParam == 'E')
		{
			rotater2 -= 2;
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

	GLUquadricObj* cylinderleft = NULL;
	cylinderleft = gluNewQuadric();
	glColor3f(0.4, 0.4, 0.4);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(cylinderleft, GLU_FILL);
	gluCylinder(cylinderleft, 0.5, 0.5, 1.5, 20, 5);
	gluDeleteQuadric(cylinderleft);
}

void join_cylinderright()
{
	glRotatef(90, 0, 1.0, 0);
	glTranslatef(0.0f, -1.0f, 2.3f);

	GLUquadricObj* cylinderright = NULL;
	cylinderright = gluNewQuadric();
	glColor3f(0.4, 0.4, 0.4);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(cylinderright, GLU_FILL);
	gluCylinder(cylinderright, 0.5, 0.5, 1.5, 20, 5);
	gluDeleteQuadric(cylinderright);
}

//top rectangle for leg
void rectangle_1(double h)
{
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

void rectangle_7(double h)
{
	glBegin(GL_QUADS);
	//top
	glVertex3f(-0.5f, 1.0f, -0.4f);
	glVertex3f(-0.5f, 1.0f, 0.4f);
	glVertex3f(0.5f, 1.0f, 0.4f);
	glVertex3f(0.5f, 1.0f, -0.4f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(0.5f, 1.0f, -0.4f);
	glVertex3f(-0.5f, 1.0f, -0.4f);
	glVertex3f(-0.5f, 0.0f - h, -0.4f);
	glVertex3f(0.5f, 0.0f - h, -0.4f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(0.5f, 0.0f - h, -0.4f);
	glVertex3f(0.5f, 1.0f, -0.4f);
	glVertex3f(0.5f, 1.0f, 0.4f);
	glVertex3f(0.5f, 0.0f - h, 0.4f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(0.5f, 0.0f - h, 0.4f);
	glVertex3f(0.5f, 0.0f - h, -0.4f);
	glVertex3f(-0.5f, 0.0f - h, -0.4f);
	glVertex3f(-0.5f, 0.0f - h, 0.4f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-0.5f, 0.0f - h, 0.4f);
	glVertex3f(-0.5f, 0.0f - h, -0.4f);
	glVertex3f(-0.5f, 1.0f, -0.4f);
	glVertex3f(-0.5f, 1.0f, 0.4f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-0.5f, 1.0f, 0.4f);
	glVertex3f(0.5f, 1.0f, 0.4f);
	glVertex3f(0.5f, 0.0f - h, 0.4f);
	glVertex3f(-0.5f, 0.0f - h, 0.4f);
	glEnd();
}

void quadforcenterleg()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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



//----------------------------leg thruster shape
void thrustercylinder()
{

}
//------------------------------



//-----------------------------Shapes for body
void head_sphere()
{
	glPushMatrix();
		glTranslatef(0.0f, 0.25f, 0.0f);
		glRotatef(90, 1.0, 0.0, 0.0);

		GLUquadricObj* headsphere = NULL;
		headsphere = gluNewQuadric();
		glColor3f(1, 0, 0);
		gluQuadricDrawStyle(headsphere, GLU_FILL);
		gluSphere(headsphere, 2.95, 20, 10);
		gluDeleteQuadric(headsphere);
	glPopMatrix();
}

void body_cylinder()
{
	glPushMatrix();
		glTranslatef(0.0f, 0.25f, 0.0f);
		glRotatef(90, 1.0, 0.0, 0.0);

		GLUquadricObj* bodycylinder = NULL;
		bodycylinder = gluNewQuadric();
		glColor3f(0, 0, 1);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(bodycylinder, GLU_FILL);
		gluCylinder(bodycylinder, 3.0, 3.0, 6.0, 20, 5);
		gluDeleteQuadric(bodycylinder);
	glPopMatrix();
}

void body_bottom()
{
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0.0f, 0.0f, 5.7f);

		GLUquadricObj* bodybottomcylinder = NULL;
		bodybottomcylinder = gluNewQuadric();
		glColor3f(0, 0, 1);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(bodybottomcylinder, GLU_FILL);
		gluCylinder(bodybottomcylinder, 3.0, 2.5, 1.0, 20, 5);
		gluDeleteQuadric(bodybottomcylinder);
	glPopMatrix();

	glPushMatrix();
		GLfloat bodybottomx1 = 0.0;
		GLfloat bodybottomy1 = 0.0;
		GLfloat bottomradius = 2.5;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 6.7f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.3, 0.3, 1.0);
		glVertex2f(bodybottomx1, bodybottomy1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(bodybottomx1 + (bottomradius * cos(i * twopi / triangleAmount)), bodybottomy1 + (bottomradius * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}

void center_leg_connector()
{
	glPushMatrix();
		glTranslatef(0.0f, -5.7f, 0.0f);
		glRotatef(90, 1.0, 0.0, 0.0);

		GLUquadricObj* centerlegcylinder = NULL;
		centerlegcylinder = gluNewQuadric();
		glColor3f(0.4, 0.4, 0.4);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(centerlegcylinder, GLU_FILL);
		gluCylinder(centerlegcylinder, 0.5, 0.5, 1.5, 20, 5);
		gluDeleteQuadric(centerlegcylinder);
	glPopMatrix();
}

//-------------------------------



//-----------------------------Combined Leg shapes
void left_leg()
{
	//top cylinder
	glPushMatrix();
		glRotatef(270, 0, 1.0, 0);
		glTranslatef(0.0f, -1.0f, 3.2f);

		GLUquadricObj* leftlegcylinder = NULL;
		leftlegcylinder = gluNewQuadric();
		glColor3f(1, 1, 1);
		gluQuadricDrawStyle(leftlegcylinder, GLU_FILL);
		gluCylinder(leftlegcylinder, 1, 1, 1, 20, 5);
		gluDeleteQuadric(leftlegcylinder);
	glPopMatrix();

	glPushMatrix();
		GLfloat leftx1 = 0.0;
		GLfloat lefty1 = 0.0;
		GLfloat radius1 = 1.0;
		
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -1.0f, 3.2f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(leftx1, lefty1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(leftx1 + (radius1 * cos(i * twopi / triangleAmount)), lefty1 + (radius1 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		GLfloat leftx2 = 0.0;
		GLfloat lefty2 = 0.0;
		GLfloat radius2 = 1.0;

		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -1.0f, 4.2f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(leftx2, lefty2);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(leftx2 + (radius2 * cos(i * twopi / triangleAmount)), lefty2 + (radius2 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -2.0f, 0.0f);
		glColor3f(1, 1, 1);
		rectangle_1(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -4.0f, 0.0f);
		glColor3f(1, 1, 1);
		rectangle_2();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -4.5f, 0.0f);
		glColor3f(1, 1, 1);
		rectangle_3(1.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -7.0f, 0.0f);
		glColor3f(1, 1, 1);
		rectangle_4(0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -8.0f, 0.0f);
		glColor3f(1, 1, 1);
		rectangle_5(0.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3.7f, -9.5f, 0.0f);
		glColor3f(1, 1, 1);
		rectangle_6();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4.0f, -3.0f, 0.0f);
		glColor3f(0, 0.5, 1);
		rectangle_7(2.5);
	glPopMatrix();

	glPushMatrix();
		glRotatef(270, 0, 1.0, 0);
		glTranslatef(0.0f, -8.3f, 3.4f);

		GLUquadricObj* lefttyrecylinder = NULL;
		lefttyrecylinder = gluNewQuadric();
		glColor3f(0.3, 0.3, 0.3);
		gluQuadricDrawStyle(lefttyrecylinder, GLU_FILL);
		gluCylinder(lefttyrecylinder, 0.9, 0.9, 0.9, 20, 5);
		gluDeleteQuadric(lefttyrecylinder);
	glPopMatrix();

	glPushMatrix();
		GLfloat lefttyrex1 = 0.0;
		GLfloat lefttyrey1 = 0.0;
		GLfloat radiustyre1 = 0.9;

		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -8.3f, 3.4f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(lefttyrex1, lefttyrey1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(lefttyrex1 + (radiustyre1 * cos(i * twopi / triangleAmount)), lefttyrey1 + (radiustyre1 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		GLfloat lefttyrex2 = 0.0;
		GLfloat lefttyrey2 = 0.0;
		GLfloat radiustyre2 = 0.9;

		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -8.3f, 4.3f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(lefttyrex2, lefttyrey2);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(lefttyrex2 + (radiustyre2 * cos(i * twopi / triangleAmount)), lefttyrey2 + (radiustyre2 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}

void right_leg()
{
	//top cylinder
	glPushMatrix();
		glRotatef(90, 0, 1.0, 0);
		glTranslatef(0.0f, -1.0f, 3.2f);

		GLUquadricObj* rightlegcylinder = NULL;
		rightlegcylinder = gluNewQuadric();
		glColor3f(1, 1, 1);
		gluQuadricDrawStyle(rightlegcylinder, GLU_FILL);
		gluCylinder(rightlegcylinder, 1, 1, 1, 20, 5);
		gluDeleteQuadric(rightlegcylinder);
	glPopMatrix();

	glPushMatrix();
		GLfloat rightx1 = 0.0;
		GLfloat righty1 = 0.0;
		GLfloat radius3 = 1.0;

		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -1.0f, -3.2f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(rightx1, righty1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(rightx1 + (radius3 * cos(i * twopi / triangleAmount)), righty1 + (radius3 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		GLfloat rightx2 = 0.0;
		GLfloat righty2 = 0.0;
		GLfloat radius4 = 1.0;

		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -1.0f, -4.2f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(rightx2, righty2);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(rightx2 + (radius4 * cos(i * twopi / triangleAmount)), righty2 + (radius4 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -2.0f, 0.0f);
		glColor3f(1, 1, 1);
		rectangle_1(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -4.0f, 0.0f);
		glColor3f(1, 1, 1);
		rectangle_2();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -4.5f, 0.0f);
		glColor3f(1, 1, 1);
		rectangle_3(1.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -7.0f, 0.0f);
		glRotatef(180, 0, 1, 0);
		glColor3f(1, 1, 1);
		rectangle_4(0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -8.0f, 0.0f);
		glRotatef(180, 0, 1, 0);
		glColor3f(1, 1, 1);
		rectangle_5(0.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.7f, -9.5f, 0.0f);
		glRotatef(180, 0, 1, 0);
		glColor3f(1, 1, 1);
		rectangle_6();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4.0f, -3.0f, 0.0f);
		glColor3f(0, 0.5, 1);
		rectangle_7(2.5);
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 1.0, 0);
		glTranslatef(0.0f, -8.3f, 3.4f);

		GLUquadricObj* righttyrecylinder = NULL;
		righttyrecylinder = gluNewQuadric();
		glColor3f(0.3, 0.3, 0.3);
		gluQuadricDrawStyle(righttyrecylinder, GLU_FILL);
		gluCylinder(righttyrecylinder, 0.9, 0.9, 0.9, 20, 5);
		gluDeleteQuadric(righttyrecylinder);
	glPopMatrix();

	glPushMatrix();
		GLfloat lefttyrex3 = 0.0;
		GLfloat lefttyrey3 = 0.0;
		GLfloat radiustyre3 = 0.9;

		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -8.3f, -3.4f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(lefttyrex3, lefttyrey3);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(lefttyrex3 + (radiustyre3 * cos(i * twopi / triangleAmount)), lefttyrey3 + (radiustyre3 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		GLfloat lefttyrex4 = 0.0;
		GLfloat lefttyrey4 = 0.0;
		GLfloat radiustyre4 = 0.9;

		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -8.3f, -4.3f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(lefttyrex4, lefttyrey4);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(lefttyrex4 + (radiustyre4 * cos(i * twopi / triangleAmount)), lefttyrey4 + (radiustyre4 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}

void center_leg()
{
	glPushMatrix();
		glTranslatef(0.0f, -8.0f, 0.0f);
		glColor3f(1, 1, 1);
		quadforcenterleg();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -9.5f, 0.0f);
		glColor3f(1, 1, 1);
		quadforcenterleg_2();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90.0, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -8.3f, -0.45);

		GLUquadricObj* centertyrecylinder = NULL;
		centertyrecylinder = gluNewQuadric();
		glColor3f(0.3, 0.3, 0.3);
		gluQuadricDrawStyle(centertyrecylinder, GLU_FILL);
		gluCylinder(centertyrecylinder, 0.9, 0.9, 0.9, 20, 5);
		gluDeleteQuadric(centertyrecylinder);
	glPopMatrix();

	glPushMatrix();
		GLfloat centertyrex1 = 0.0;
		GLfloat centertyrey1 = 0.0;
		GLfloat radiustyre5 = 0.9;

		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -8.3f, 0.5f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(centertyrex1, centertyrey1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(centertyrex1 + (radiustyre5 * cos(i * twopi / triangleAmount)), centertyrey1 + (radiustyre5 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		GLfloat centertyrex2 = 0.0;
		GLfloat centertyrey2 = 0.0;
		GLfloat radiustyre6 = 0.9;

		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, -8.3f, -0.5f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(centertyrex2, centertyrey2);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(centertyrex2 + (radiustyre6 * cos(i * twopi / triangleAmount)), centertyrey2 + (radiustyre6 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

}
//-----------------------------



//-----------------------------Gatling gun
void gg_mainbarrel() {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 1.5f);

	GLUquadricObj* mainbarrelcylinder = NULL;
	mainbarrelcylinder = gluNewQuadric();
	glColor3f(1, 0, 1);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(mainbarrelcylinder, GLU_FILL);
	gluCylinder(mainbarrelcylinder, 0.2, 0.2, 5, 20, 5);
	gluDeleteQuadric(mainbarrelcylinder);
	glPopMatrix();
}

void gg_sidebarrels() {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 2.0f);
	for (int i = 0; i <= 6; i++) {
		glRotatef(60, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(0.0f, 0.5f, 0.0f);
		GLUquadricObj* sidebarrelcylinder = NULL;
		sidebarrelcylinder = gluNewQuadric();
		glColor3f(1, 0.5, 1);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(sidebarrelcylinder, GLU_FILL);
		gluCylinder(sidebarrelcylinder, 0.2, 0.2, 5, 20, 5);
		gluDeleteQuadric(sidebarrelcylinder);
		glPopMatrix();
	}
	glPopMatrix();
}

void gg_barrelholder() {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 6.0f);

	GLUquadricObj* barrelholdercylinder = NULL;
	barrelholdercylinder = gluNewQuadric();
	glColor3f(1, 0, 1);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(barrelholdercylinder, GLU_FILL);
	gluCylinder(barrelholdercylinder, 0.75, 0.75, 0.5, 20, 5);
	gluDeleteQuadric(barrelholdercylinder);
	glPopMatrix();
}

void gg_barrels() {
	glPushMatrix();
		gg_mainbarrel();
		gg_sidebarrels();
		gg_barrelholder();
	glPopMatrix();
}

void gg_body() {
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 1.0f);

	GLUquadricObj* gunbodycylinder = NULL;
	gunbodycylinder = gluNewQuadric();
	glColor3f(1, 0, 1);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(gunbodycylinder, GLU_FILL);
	gluCylinder(gunbodycylinder, 0.75, 0.75, 2, 20, 5);
	gluDeleteQuadric(gunbodycylinder);
	glPopMatrix();
}

void gg_connnector() {
	glPushMatrix();

	GLUquadricObj* gunconnectorcylinder = NULL;
	gunconnectorcylinder = gluNewQuadric();
	glColor3f(1, 0, 1);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(gunconnectorcylinder, GLU_FILL);
	gluCylinder(gunconnectorcylinder, 0.5, 0.5, 2, 20, 5);
	gluDeleteQuadric(gunconnectorcylinder);
	glPopMatrix();
}

void gg_head()
{

	GLUquadricObj* gunheadsphere = NULL;
	gunheadsphere = gluNewQuadric();
	glColor3f(0, 0, 1);
	gluQuadricDrawStyle(gunheadsphere, GLU_FILL);
	gluSphere(gunheadsphere, 0.9, 20, 10);
	gluDeleteQuadric(gunheadsphere);
}

void gatlingGun() {
	glPushMatrix();
		glTranslatef(0.0f, gunmove, 0.0f);
		glRotatef(gunrotate, 1.0, 0.0, 0.0);
		gg_barrels();
		gg_body();
		gg_connnector();
		gg_head();
	glPopMatrix();
}
//-----------------------------

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		glPushMatrix();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glTranslatef(movex, movey, movez);
			glRotatef(rotater2, 0.0f, 1.0f, 0.0f);

			glPushMatrix();

				glTranslatef(0.0f, -1.0f, 0.0f);
				glRotatef(-bodyrotate, 1.0f, 0.0f, 0.0f);
				glTranslatef(0.0f, 1.0f, 0.0f);

				head_sphere();
				gatlingGun();
				body_cylinder();
				body_bottom();
			
				glPushMatrix();

					glTranslatef(0.0f, legmove, 0.0f);

					center_leg_connector();

					glPushMatrix();
						glTranslatef(0.0f, -8.0f, 0.0f);
						glRotatef(bodyrotate, 1.0f, 0.0f, 0.0f); //mmax 25
						glTranslatef(0.0f, 8.0f, 0.0f);
						center_leg();
					glPopMatrix();

				glPopMatrix();

			glPopMatrix();

			glPushMatrix();

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
	glOrtho(-12, 12, -12, 12, -20, 20);

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//gattinggun movement------------------
		if (activategun == true)
		{
			if (gunmove < 3.5f)
			{
				gunmove += 0.1;
			}
		}

		if (activategun == false)
		{
			if (rotategun == false)
			{
				if (gunmove > (-5.0f))
				{
					gunmove -= 0.1;
				}
			}
		}

		if (rotategun == true)
		{
			if (activategun == true)
			{
				if (gunrotate < 360.0f)
				{
					gunrotate += 1.0f;
				}
			}
		}

		if (rotategun == false)
		{
			if (gunrotate > 270.0f)
			{
				gunrotate -= 1.0f;
			}
		}
		//--------------------------------------

		//center leg movement-------------------
		if (activateleg == 1) {
			legmove += 0.1;
		}
		else if (activateleg == 2) {
			legmove -= 0.1;;
		}

		if (legmove >= 2.5) {
			legmove = 2.5f;
			activateleg = 0;
		}
		else if (legmove <= -0.7) {
			legmove = -0.7f;
			activateleg = 0;
		}
		//--------------------------------------

		//body movement-------------------------
		if (activatebodyrotate == 1) {
			bodyrotate += 1;
		}
		else if (activatebodyrotate == 2) {
			activateleg = 1;

			bodyrotate -= 1;
		}

		if (bodyrotate >= 25)
		{
			bodyrotate = 25;
			activatebodyrotate = 0;
			activateleg = 2;
		}
		else if (bodyrotate <= 0.1)
		{
			bodyrotate = 0;
			activatebodyrotate = 0;
		}
		//--------------------------------------


		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------