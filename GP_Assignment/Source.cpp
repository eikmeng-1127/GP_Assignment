
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <mmsystem.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")
#pragma comment (lib, "winmm.lib")

#define WINDOW_TITLE "GP Assignment R2-D69 By Eik Meng & Kar Weng"

GLfloat gunmove = -5.0f;
GLfloat gunrotate = 270.0f;
GLfloat legmove = 2.5f;
GLfloat bodyrotate = 0;
GLfloat thrustermove = 0.0;
GLfloat backthrustermove = 0.0;
GLfloat rotatehead = 0;
GLfloat secondeyemove = 0;
GLfloat rotateeye = 0;
GLfloat shootgun = 0;
GLfloat rotatelighter = 0;
GLfloat rotatelighter2 = 0;
GLfloat lschambermove = 0;
GLfloat lsmove = 0;
GLfloat sawmove = 0;
GLfloat sawrotate = 90;
GLfloat armrotate = 90;
GLfloat armmove = 0;
GLfloat handmove = 0;

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
int activatethruster = 0;
int activatebackthruster = 0;
int activatesecondeye = 0;
int activatelighter = 0;
int activatelighter2 = 0;
int activatelightsaberchamber = 0;
int activatelightsaber = 0;
int activatedeathstarplan = 0;
int activatesaw = 0;
int activatearm = 0;
int activatehand = 0;
boolean selectOrtho = true;
boolean selectPerspective = false;

GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;

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
			activatesecondeye = 1;
			PlaySound("Sounds/Processing_R2D2.wav", NULL, SND_ASYNC);
		}
		else if (wParam == 'X')
		{
			activatesecondeye = 2;
		}
		else if (wParam == 'C')
		{
			activatebodyrotate = 1;
			PlaySound("Sounds/Playful_R2D2.wav", NULL, SND_ASYNC);
		} 
		else if (wParam == 'V')
		{
			activatebodyrotate = 2;
		} 
		else if (wParam == 'B')
		{
			shootgun += 20;
			PlaySound("Sounds/LAZER.wav", NULL, SND_ASYNC);
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
		else if (wParam == 'O')
		{
			activatethruster = 1;
		}
		else if (wParam == 'P')
		{
			activatethruster = 2;
		}
		else if (wParam == '9')
		{
			rotatehead += 2;
		}
		else if (wParam == '0')
		{
			rotatehead -= 2;
		}
		else if (wParam == '7')
		{
			rotateeye += 2;
		}
		else if (wParam == '8')
		{
			rotateeye -= 2;
		}
		else if (wParam == 'K')
		{
			activatelighter = 1;
		}
		else if (wParam == 'L')
		{
			activatelighter = 2;
		}
		else if (wParam == 'H')
		{
			activatelightsaberchamber = 1;
			PlaySound("Sounds/LightSaberUP.wav", NULL, SND_ASYNC);
		}
		else if (wParam == 'J')
		{
			activatelightsaber = 2;
			PlaySound("Sounds/LightSaberDOWN.wav", NULL, SND_ASYNC);
		}
		else if (wParam == VK_INSERT)
		{
			activatedeathstarplan = 0;
		}
		else if (wParam == VK_DELETE)
		{
			activatedeathstarplan = 1;
			PlaySound("Sounds/NOMOON.wav", NULL, SND_ASYNC);
		}
		else if (wParam == '1')
		{
			selectOrtho = true;
			selectPerspective = false;
		}
		else if (wParam == '2')
		{
			selectOrtho = false;
			selectPerspective = true;
		}
		else if (wParam == 'F')
		{
			activatesaw = 1;
		}
		else if (wParam == 'G')
		{
			activatesaw = 2;
		}
		else if (wParam == 'R')
		{
			sawrotate += 2;
		}
		else if (wParam == 'T')
		{
			sawrotate -= 2;
		}
		else if (wParam == '5')
		{
			armrotate += 2;
		}
		else if (wParam == '6')
		{
			armrotate -= 2;
		}
		else if (wParam == '3')
		{
			activatehand = 1;
		}
		else if (wParam == '4')
		{
			activatehand = 2;
		}
		else if (wParam == 'Y')
		{
			activatearm = 1;
		}
		else if (wParam == 'U')
		{
			activatearm = 2;
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
//1 polygon
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

//1 polygon
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

//top rectangle for leg (6 polygon)
void rectangle_1(float h)
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

//shape under rectangle_1 (6 polygon)
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

//rectangle under rectangle_2 (6 polygon)
void rectangle_3(float h)
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

//rectangle under rectangle_3 (6 polygon)
void rectangle_4(float h)
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

//rectangle under rectangle_4 (6 polygon)
void rectangle_5(float h)
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

//rectangle under rectangle_5 (6 polygon)
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

//(6 polygon)
void rectangle_7(float h)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "bluetexture.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//type of texture, what filter used?magnified?,minimize?,
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 1.0f, -0.4f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 1.0f, 0.4f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 1.0f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 1.0f, -0.4f);

	//back
	//glColor3f(1, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 1.0f, -0.4f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 1.0f, -0.4f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.0f - h, -0.4f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.0f - h, -0.4f);

	//right
	//glColor3f(0, 1, 0);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.0f - h, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 1.0f, -0.4f);
	glTexCoord2f(0, 0); glVertex3f(0.5f, 1.0f, 0.4f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.0f - h, 0.4f);

	//bottom
	//glColor3f(0, 0, 1);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.0f - h, 0.4f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.0f - h, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.0f - h, -0.4f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.0f - h, 0.4f);

	//left
	//glColor3f(1, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.0f - h, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.0f - h, -0.4f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 1.0f, -0.4f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 1.0f, 0.4f);

	//front
	//glColor3f(1, 0, 1);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 1.0f, 0.4f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 1.0f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.0f - h, 0.4f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.0f - h, 0.4f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

//(6 polygon)
void quadforcenterleg()
{
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

//(6 polygon)
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


//----------------------------Shapes for head
//1 polygon
void head_sphere()
{
	glPushMatrix();
		glTranslatef(0.0f, 0.25f, 0.0f);
		glRotatef(180, 1.0, 0.0, 0.0);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "glossysilvertexture.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP, sizeof(BMP), &BMP);
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//type of texture, what filter used?magnified?,minimize?,
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		GLUquadricObj* headsphere = NULL;
		headsphere = gluNewQuadric();
		gluQuadricTexture(headsphere, TRUE);
		glColor3f(1, 1, 1);
		gluQuadricDrawStyle(headsphere, GLU_FILL);
		gluSphere(headsphere, 2.95, 30, 30);
		gluDeleteQuadric(headsphere);

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP);
		glDeleteTextures(1, &texture);
	glPopMatrix();
}

void head_eyepiece(float h)
{
	glPushMatrix();
		glRotatef(30, -1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 2.15f);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "bluetexture.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP, sizeof(BMP), &BMP);
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//type of texture, what filter used?magnified?,minimize?,
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		//top
		glTexCoord2f(0, 0); glVertex3f(-0.6f, 1.0f, 0.0f);
		glTexCoord2f(0, 1); glVertex3f(-0.6f, 1.0f, 1.0f);
		glTexCoord2f(1, 1); glVertex3f(0.6f, 1.0f, 1.0f);
		glTexCoord2f(1, 0); glVertex3f(0.6f, 1.0f, 0.0f);

		//back
		//glColor3f(1, 0, 0);
		glTexCoord2f(1, 0); glVertex3f(0.6f, 1.0f, 0.0f);
		glTexCoord2f(0, 1); glVertex3f(-0.6f, 1.0f, 0.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, 0.0f - h, 0.0f);
		glTexCoord2f(1, 1); glVertex3f(0.6f, 0.0f - h, 0.0f);

		//right
		//glColor3f(0, 1, 0);
		glTexCoord2f(1, 1); glVertex3f(0.6f, 0.0f - h, 0.0f);
		glTexCoord2f(1, 0); glVertex3f(0.6f, 1.0f, 0.0f);
		glTexCoord2f(0, 0); glVertex3f(0.6f, 1.0f, 1.0f);
		glTexCoord2f(0, 1); glVertex3f(0.6f, 0.0f - h, 1.0f);

		//bottom
		//glColor3f(0, 0, 1);
		glTexCoord2f(0, 1); glVertex3f(0.6f, 0.0f - h, 1.0f);
		glTexCoord2f(1, 1); glVertex3f(0.6f, 0.0f - h, 0.0f);
		glTexCoord2f(1, 0); glVertex3f(-1.0f, 0.0f - h, 0.0f);
		glTexCoord2f(0, 0); glVertex3f(-1.0f, 0.0f - h, 1.0f);

		//left
		//glColor3f(1, 1, 0);
		glTexCoord2f(0, 0); glVertex3f(-1.0f, 0.0f - h, 1.0f);
		glTexCoord2f(1, 0); glVertex3f(-1.0f, 0.0f - h, 0.0f);
		glTexCoord2f(1, 1); glVertex3f(-0.6f, 1.0f, 0.0f);
		glTexCoord2f(0, 1); glVertex3f(-0.6f, 1.0f, 1.0f);

		//front
		//glColor3f(1, 0, 1);
		glTexCoord2f(0, 0); glVertex3f(-0.6f, 1.0f, 1.0f);
		glTexCoord2f(1, 1); glVertex3f(0.6f, 1.0f, 1.0f);
		glTexCoord2f(1, 0); glVertex3f(0.6f, 0.0f - h, 1.0f);
		glTexCoord2f(0, 0); glVertex3f(-1.0f, 0.0f - h, 1.0f);
		glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void head_eyesphere()
{
	glPushMatrix();
		glTranslatef(0.0f, 2.0f, 2.4f);
		GLUquadricObj* eyesphere = NULL;
		eyesphere = gluNewQuadric();
		glColor3f(0, 0, 0);
		gluQuadricDrawStyle(eyesphere, GLU_FILL);
		gluSphere(eyesphere, 0.35, 20, 10);
		gluDeleteQuadric(eyesphere);
	glPopMatrix();
}

void head_secondeyecylinder()
{
	GLUquadricObj* thrustercylinder = NULL;
	thrustercylinder = gluNewQuadric();
	glColor3f(0.4, 0.4, 0.4);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(thrustercylinder, GLU_FILL);
	gluCylinder(thrustercylinder, 0.2, 0.2, 1.5, 20, 5);
	gluDeleteQuadric(thrustercylinder);
}

void head_secondeyequad()
{
	glBegin(GL_QUADS);
		//top
		glColor3f(0, 0, 1);
		glVertex3f(-1.0f, 0.6f, -0.6f);
		glVertex3f(-0.5f, 1.5f, 0.6f);
		glVertex3f(0.5f, 1.5f, 0.6f);
		glVertex3f(1.0f, 0.6f, -0.6f);

		//back
		glColor3f(0.9, 0.9, 0.9);
		glVertex3f(1.0f, 0.6f, -0.6f);
		glVertex3f(-1.0f, 0.6f, -0.6f);
		glVertex3f(-1.0f, 0.0f, -0.6f);
		glVertex3f(1.0f, 0.0f, -0.6f);

		//right
		glColor3f(0.9, 0.9, 0.9);
		glVertex3f(1.0f, 0.0f, -0.6f);
		glVertex3f(1.0f, 0.6f, -0.6f);
		glVertex3f(0.5f, 1.5f, 0.6f);
		glVertex3f(0.5f, 0.0f, 0.6f);

		//bottom
		glColor3f(0, 0, 1);
		glVertex3f(0.5f, 0.0f, 0.6f);
		glVertex3f(1.0f, 0.0f, -0.6f);
		glVertex3f(-1.0f, 0.0f, -0.6f);
		glVertex3f(-0.5f, 0.0f, 0.6f);

		//left
		glColor3f(0.9, 0.9, 0.9);
		glVertex3f(-0.5f, 0.0f, 0.6f);
		glVertex3f(-1.0f, 0.0f, -0.6f);
		glVertex3f(-1.0f, 0.6f, -0.6f);
		glVertex3f(-0.5f, 1.5f, 0.6f);

		//front
		glColor3f(0.9, 0.9, 0.9);
		glVertex3f(-0.5f, 1.5f, 0.6f);
		glVertex3f(0.5f, 1.5f, 0.6f);
		glVertex3f(0.5f, 0.0f, 0.6f);
		glVertex3f(-0.5f, 0.0f, 0.6f);
	glEnd();
}

void head_secondeyesphere()
{
	GLUquadricObj* eyesphere = NULL;
	eyesphere = gluNewQuadric();
	glColor3f(0, 0, 0);
	gluQuadricDrawStyle(eyesphere, GLU_FILL);
	gluSphere(eyesphere, 0.35, 20, 10);
	gluDeleteQuadric(eyesphere);
}

void head_eyecone()
{
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.2f);
		GLUquadricObj* thrustercylinder = NULL;
		thrustercylinder = gluNewQuadric();
		glColor3f(1, 1, 0.0);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(thrustercylinder, GLU_FILL);
		gluCylinder(thrustercylinder, 0.3, 0.25, 0.5, 20, 5);
		gluDeleteQuadric(thrustercylinder);
	glPopMatrix();

	glPushMatrix();
		GLfloat circlex2 = 0.0;
		GLfloat circley2 = 0.0;
		GLfloat circlerad2 = 0.25;

		glTranslatef(0.0f, 0.0f, 0.6f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(circlex2, circley2);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(circlex2 + (circlerad2 * cos(i * twopi / triangleAmount)), circley2 + (circlerad2 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}

void head_eyecylinder1()
{
	glPushMatrix();
		GLUquadricObj* thrustercylinder = NULL;
		thrustercylinder = gluNewQuadric();
		glColor3f(1, 1, 0);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(thrustercylinder, GLU_FILL);
		gluCylinder(thrustercylinder, 0.35, 0.35, 0.3, 20, 5);
		gluDeleteQuadric(thrustercylinder);
	glPopMatrix();

	glPushMatrix();
		GLfloat circlex1 = 0.0;
		GLfloat circley1 = 0.0;
		GLfloat circlerad = 0.35;

		glTranslatef(0.0f, 0.0f, 0.3f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(circlex1, circley1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(circlex1 + (circlerad * cos(i * twopi / triangleAmount)), circley1 + (circlerad * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}

void head_rectangle()
{
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	//top
		glVertex3f(-0.5f, 0.8f, -0.3f);
		glVertex3f(-0.5f, 0.8f, 0.3f);
		glVertex3f(0.5f, 0.8f, 0.3f);
		glVertex3f(0.5f, 0.8f, -0.3f);

		//back
		//glColor3f(1, 0, 0);
		glVertex3f(0.5f, 0.8f, -0.3f);
		glVertex3f(-0.5f, 0.8f, -0.3f);
		glVertex3f(-0.5f, 0.0f, -0.3f);
		glVertex3f(0.5f, 0.0f, -0.3f);

		//right
		//glColor3f(0, 1, 0);
		glVertex3f(0.5f, 0.0f, -0.3f);
		glVertex3f(0.5f, 0.8f, -0.3f);
		glVertex3f(0.5f, 0.8f, 0.3f);
		glVertex3f(0.5f, 0.0f, 0.3f);

		//bottom
		//glColor3f(0, 0, 1);
		glVertex3f(0.5f, 0.0f, 0.3f);
		glVertex3f(0.5f, 0.0f, -0.3f);
		glVertex3f(-0.5f, 0.0f, -0.3f);
		glVertex3f(-0.5f, 0.0f, 0.3f);

		//left
		//glColor3f(1, 1, 0);
		glVertex3f(-0.5f, 0.0f, 0.3f);
		glVertex3f(-0.5f, 0.0f, -0.3f);
		glVertex3f(-0.5f, 0.8f, -0.3f);
		glVertex3f(-0.5f, 0.8f, 0.3f);

		//front
		//glColor3f(1, 0, 1);
		glVertex3f(-0.5f, 0.8f, 0.3f);
		glVertex3f(0.5f, 0.8f, 0.3f);
		glVertex3f(0.5f, 0.0f, 0.3f);
		glVertex3f(-0.5f, 0.0f, 0.3f);
	glEnd();
}

void head_colourchangingsphere()
{
	glPushMatrix();
		GLUquadricObj* eyesphere = NULL;
		eyesphere = gluNewQuadric();
		glColor3f(1, 0, 0);
		gluQuadricDrawStyle(eyesphere, GLU_FILL);
		gluSphere(eyesphere, 0.30, 20, 10);
		gluDeleteQuadric(eyesphere);
	glPopMatrix();
}


void head_lightsaberchamber()
{
	glBegin(GL_QUADS);
	//top
	glColor3f(0, 0, 1);
	glVertex3f(-1.0f, 0.6f, -0.6f);
	glVertex3f(-0.5f, 1.0f, 0.6f);
	glVertex3f(0.5f, 1.0f, 0.6f);
	glVertex3f(1.0f, 0.6f, -0.6f);

	//back
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(1.0f, 0.6f, -0.6f);
	glVertex3f(-1.0f, 0.6f, -0.6f);
	glVertex3f(-1.0f, 0.0f, -0.6f);
	glVertex3f(1.0f, 0.0f, -0.6f);

	//right
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(1.0f, 0.0f, -0.6f);
	glVertex3f(1.0f, 0.6f, -0.6f);
	glVertex3f(0.5f, 1.0f, 0.6f);
	glVertex3f(0.5f, 0.0f, 0.6f);

	//bottom
	glColor3f(0, 0, 1);
	glVertex3f(0.5f, 0.0f, 0.6f);
	glVertex3f(1.0f, 0.0f, -0.6f);
	glVertex3f(-1.0f, 0.0f, -0.6f);
	glVertex3f(-0.5f, 0.0f, 0.6f);

	//left
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-0.5f, 0.0f, 0.6f);
	glVertex3f(-1.0f, 0.0f, -0.6f);
	glVertex3f(-1.0f, 0.6f, -0.6f);
	glVertex3f(-0.5f, 1.0f, 0.6f);

	//front
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-0.5f, 1.0f, 0.6f);
	glVertex3f(0.5f, 1.0f, 0.6f);
	glVertex3f(0.5f, 0.0f, 0.6f);
	glVertex3f(-0.5f, 0.0f, 0.6f);
	glEnd();
}
//----------------------------


//----------------------------leg thruster shape
void thrustercylinder()
{
	GLUquadricObj* thrustercylinder = NULL;
	thrustercylinder = gluNewQuadric();
	glColor3f(0.4, 0.4, 0.4);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(thrustercylinder, GLU_FILL);
	gluCylinder(thrustercylinder, 0.2, 0.2, 1.5, 20, 5);
	gluDeleteQuadric(thrustercylinder);
}

void thrustercone() 
{
	GLUquadricObj* thrustercone = NULL;
	thrustercone = gluNewQuadric();
	glColor3f(0.4, 0.4, 0.4);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(thrustercone, GLU_FILL);
	gluCylinder(thrustercone, 0.2, 0.15, 0.3, 20, 5);
	gluDeleteQuadric(thrustercone);
}

//6 polygon
void thrusterjoint1()
{
	glBegin(GL_QUADS);
	//top
	glVertex3f(-0.3f, 0.3f, -0.1f);
	glVertex3f(-0.3f, 0.3f, 0.1f);
	glVertex3f(0.3f, 0.3f, 0.1f);
	glVertex3f(0.3f, 0.3f, -0.1f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(0.3f, 0.3f, -0.1f);
	glVertex3f(-0.3f, 0.3f, -0.1f);
	glVertex3f(-0.3f, 0.0f, -0.1f);
	glVertex3f(0.3f, 0.0f, -0.1f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(0.3f, 0.0f, -0.1f);
	glVertex3f(0.3f, 0.3f, -0.1f);
	glVertex3f(0.3f, 0.3f, 0.1f);
	glVertex3f(0.3f, 0.0f, 0.1f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(0.3f, 0.0f, 0.1f);
	glVertex3f(0.3f, 0.0f, -0.1f);
	glVertex3f(-0.3f, 0.0f, -0.1f);
	glVertex3f(-0.3f, 0.0f, 0.1f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-0.3f, 0.0f, 0.1f);
	glVertex3f(-0.3f, 0.0f, -0.1f);
	glVertex3f(-0.3f, 0.3f, -0.1f);
	glVertex3f(-0.3f, 0.3f, 0.1f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-0.3f, 0.3f, 0.1f);
	glVertex3f(0.3f, 0.3f, 0.1f);
	glVertex3f(0.3f, 0.0f, 0.1f);
	glVertex3f(-0.3f, 0.0f, 0.1f);
	glEnd();
}

//left thruster joint (6 polygon)
void thrusterjoint2()
{
	glBegin(GL_QUADS);
	//top
	glVertex3f(-0.3f, 0.3f, -0.1f);
	glVertex3f(-0.3f, 0.3f, 0.1f);
	glVertex3f(0.3f, -0.3f, 0.1f);
	glVertex3f(0.3f, -0.3f, -0.1f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(0.3f, -0.3f, -0.1f);
	glVertex3f(-0.3f, 0.3f, -0.1f);
	glVertex3f(-0.3f, 0.0f, -0.1f);
	glVertex3f(0.3f, -0.6f, -0.1f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(0.3f, -0.6f, -0.1f);
	glVertex3f(0.3f, -0.3f, -0.1f);
	glVertex3f(0.3f, -0.3f, 0.1f);
	glVertex3f(0.3f, -0.6f, 0.1f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(0.3f, -0.6f, 0.1f);
	glVertex3f(0.3f, -0.6f, -0.1f);
	glVertex3f(-0.3f, 0.0f, -0.1f);
	glVertex3f(-0.3f, 0.0f, 0.1f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-0.3f, 0.0f, 0.1f);
	glVertex3f(-0.3f, 0.0f, -0.1f);
	glVertex3f(-0.3f, 0.3f, -0.1f);
	glVertex3f(-0.3f, 0.3f, 0.1f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-0.3f, 0.3f, 0.1f);
	glVertex3f(0.3f, -0.3f, 0.1f);
	glVertex3f(0.3f, -0.6f, 0.1f);
	glVertex3f(-0.3f, 0.0f, 0.1f);
	glEnd();
}

//right thruster joint (6 polygon)
void thrusterjoint3()
{
	glBegin(GL_QUADS);
	//top
	glVertex3f(-0.3f, -0.3f, -0.1f);
	glVertex3f(-0.3f, -0.3f, 0.1f);
	glVertex3f(0.3f, 0.3f, 0.1f);
	glVertex3f(0.3f, 0.3f, -0.1f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(0.3f, 0.3f, -0.1f);
	glVertex3f(-0.3f, -0.3f, -0.1f);
	glVertex3f(-0.3f, -0.6f, -0.1f);
	glVertex3f(0.3f, 0.0f, -0.1f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(0.3f, 0.0f, -0.1f);
	glVertex3f(0.3f, 0.3f, -0.1f);
	glVertex3f(0.3f, 0.3f, 0.1f);
	glVertex3f(0.3f, 0.0f, 0.1f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(0.3f, 0.0f, 0.1f);
	glVertex3f(0.3f, 0.0f, -0.1f);
	glVertex3f(-0.3f, -0.6f, -0.1f);
	glVertex3f(-0.3f, -0.6f, 0.1f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-0.3f, -0.6f, 0.1f);
	glVertex3f(-0.3f, -0.6f, -0.1f);
	glVertex3f(-0.3f, -0.3f, -0.1f);
	glVertex3f(-0.3f, -0.3f, 0.1f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-0.3f, -0.3f, 0.1f);
	glVertex3f(0.3f, 0.3f, 0.1f);
	glVertex3f(0.3f, 0.0f, 0.1f);
	glVertex3f(-0.3f, -0.6f, 0.1f);
	glEnd();
}
//------------------------------

//----------------------------back thruster
void backpackthruster(float h)
{
	glColor3f(0.0f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	//top
	glVertex3f(-1.5f, 1.0f, -1.0f);
	glVertex3f(-1.5f, 1.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, -1.0f);

	//back
	//glColor3f(1, 0, 0);
	glVertex3f(1.5f, 1.0f, -1.0f);
	glVertex3f(-1.5f, 1.0f, -1.0f);
	glVertex3f(-1.5f, 0.0f - h, -1.0f);
	glVertex3f(1.5f, 0.0f - h, -1.0f);

	//right
	//glColor3f(0, 1, 0);
	glVertex3f(1.5f, 0.0f - h, -1.0f);
	glVertex3f(1.5f, 1.0f, -1.0f);
	glVertex3f(1.5f, 1.0f, 1.0f);
	glVertex3f(1.5f, 0.0f - h, 1.0f);

	//bottom
	//glColor3f(0, 0, 1);
	glVertex3f(1.5f, 0.0f - h, 1.0f);
	glVertex3f(1.5f, 0.0f - h, -1.0f);
	glVertex3f(-1.5f, 0.0f - h, -1.0f);
	glVertex3f(-1.5f, 0.0f - h, 1.0f);

	//left
	//glColor3f(1, 1, 0);
	glVertex3f(-1.5f, 0.0f - h, 1.0f);
	glVertex3f(-1.5f, 0.0f - h, -1.0f);
	glVertex3f(-1.5f, 1.0f, -1.0f);
	glVertex3f(-1.5f, 1.0f, 1.0f);

	//front
	//glColor3f(1, 0, 1);
	glVertex3f(-1.5f, 1.0f, 1.0f);
	glVertex3f(1.5f, 1.0f, 1.0f);
	glVertex3f(1.5f, 0.0f - h, 1.0f);
	glVertex3f(-1.5f, 0.0f - h, 1.0f);
	glEnd();
}

void backpackthrustercone()
{
	GLUquadricObj* backthrustercone = NULL;
	backthrustercone = gluNewQuadric();
	glColor3f(0.4, 0.4, 0.4);
	//gluQuadricTexture(cylinder, TRUE);
	gluQuadricDrawStyle(backthrustercone, GLU_FILL);
	gluCylinder(backthrustercone, 0.5, 0.4, 0.3, 20, 5);
	gluDeleteQuadric(backthrustercone);
}
//----------------------------


//-----------------------------Gatling gun
//1 polygon
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

//6 polygon
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

//1 polygon
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
		glRotatef(shootgun, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
			gg_mainbarrel();
			gg_sidebarrels();
			gg_barrelholder();
		glPopMatrix();
	glPopMatrix();
}

//1 polygon
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

//1 polygon
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

//1 polygon
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

//-----------------------------Lighter
void lightercylinder()
{
	glPushMatrix();
		glRotatef(90.0, 0.0f, 1.0f, 0.0f);
		glTranslatef(-2.1f, -0.5f, -1.6f);

		GLUquadricObj* thrustercylinder = NULL;
		thrustercylinder = gluNewQuadric();
		glColor3f(0.4, 0.4, 0.4);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(thrustercylinder, GLU_FILL);
		gluCylinder(thrustercylinder, 0.1, 0.1, 3.2, 20, 5);
		gluDeleteQuadric(thrustercylinder);
	glPopMatrix();
}

void lighterhead()
{
	glPushMatrix();
		glTranslatef(1.3f, -0.5f, 2.1f);
		glColor3f(1, 0, 0);
		glBegin(GL_QUADS);
			//top
			glVertex3f(-0.3f, 0.2f, -0.1f);
			glVertex3f(-0.3f, 0.2f, 0.1f);
			glVertex3f(0.3f, 0.2f, 0.1f);
			glVertex3f(0.3f, 0.2f, -0.1f);

			//back
			//glColor3f(1, 0, 0);
			glVertex3f(0.3f, 0.2f, -0.1f);
			glVertex3f(-0.3f, 0.2f, -0.1f);
			glVertex3f(-0.3f, 0.0f, -0.1f);
			glVertex3f(0.3f, 0.0f, -0.1f);

			//right
			//glColor3f(0, 1, 0);
			glVertex3f(0.3f, 0.0f, -0.1f);
			glVertex3f(0.3f, 0.2f, -0.1f);
			glVertex3f(0.3f, 0.2f, 0.1f);
			glVertex3f(0.3f, 0.0f, 0.1f);

			//bottom
			//glColor3f(0, 0, 1);
			glVertex3f(0.3f, 0.0f, 0.1f);
			glVertex3f(0.3f, 0.0f, -0.1f);
			glVertex3f(-0.3f, 0.0f, -0.1f);
			glVertex3f(-0.3f, 0.0f, 0.1f);

			//left
			//glColor3f(1, 1, 0);
			glVertex3f(-0.3f, 0.0f, 0.1f);
			glVertex3f(-0.3f, 0.0f, -0.1f);
			glVertex3f(-0.3f, 0.2f, -0.1f);
			glVertex3f(-0.3f, 0.2f, 0.1f);

			//front
			//glColor3f(1, 0, 1);
			glVertex3f(-0.3f, 0.2f, 0.1f);
			glVertex3f(0.3f, 0.2f, 0.1f);
			glVertex3f(0.3f, 0.0f, 0.1f);
			glVertex3f(-0.3f, 0.0f, 0.1f);
		glEnd();
	glPopMatrix();
}
//-----------------------------

//-----------------------------Saw
void sawcylinder() {
	glPushMatrix();
		//glTranslatef(1.4f, -3.4f, 2.0f);

		GLUquadricObj* sawcylinder = NULL;
		sawcylinder = gluNewQuadric();
		glColor3f(0.4, 0.4, 0.4);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(sawcylinder, GLU_FILL);
		gluCylinder(sawcylinder, 0.1, 0.1, 2.5, 20, 5);
		gluDeleteQuadric(sawcylinder);
	glPopMatrix();
}

void saw_head()
{
	glPushMatrix();
		glTranslatef(0.0f, -0.2f, 2.5f);
		glColor3f(1, 1, 0);
		glBegin(GL_QUADS);
			//top
			glVertex3f(-0.3f, 0.4f, -0.3f);
			glVertex3f(-0.3f, 0.4f, 0.3f);
			glVertex3f(0.3f, 0.4f, 0.3f);
			glVertex3f(0.3f, 0.4f, -0.3f);

			//back
			//glColor3f(1, 0, 0);
			glVertex3f(0.3f, 0.4f, -0.3f);
			glVertex3f(-0.3f, 0.4f, -0.3f);
			glVertex3f(-0.3f, 0.0f, -0.3f);
			glVertex3f(0.3f, 0.0f, -0.3f);

			//right
			//glColor3f(0, 1, 0);
			glVertex3f(0.3f, 0.0f, -0.3f);
			glVertex3f(0.3f, 0.4f, -0.3f);
			glVertex3f(0.3f, 0.4f, 0.3f);
			glVertex3f(0.3f, 0.0f, 0.3f);

			//bottom
			//glColor3f(0, 0, 1);
			glVertex3f(0.3f, 0.0f, 0.3f);
			glVertex3f(0.3f, 0.0f, -0.3f);
			glVertex3f(-0.3f, 0.0f, -0.3f);
			glVertex3f(-0.3f, 0.0f, 0.3f);

			//left
			//glColor3f(1, 1, 0);
			glVertex3f(-0.3f, 0.0f, 0.3f);
			glVertex3f(-0.3f, 0.0f, -0.3f);
			glVertex3f(-0.3f, 0.4f, -0.3f);
			glVertex3f(-0.3f, 0.4f, 0.3f);

			//front
			//glColor3f(1, 0, 1);
			glVertex3f(-0.3f, 0.4f, 0.3f);
			glVertex3f(0.3f, 0.4f, 0.3f);
			glVertex3f(0.3f, 0.0f, 0.3f);
			glVertex3f(-0.3f, 0.0f, 0.3f);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 1.0f, 0.0f, 0.0f);	
		glTranslatef(0.0f, 2.5f, -0.5f);

		GLUquadricObj* sawheadcylinder = NULL;
		sawheadcylinder = gluNewQuadric();
		glColor3f(0, 0, 1);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(sawheadcylinder, GLU_FILL);
		gluCylinder(sawheadcylinder, 0.1, 0.1, 0.4, 20, 5);
		gluDeleteQuadric(sawheadcylinder);
	glPopMatrix();

	glPushMatrix();
		GLfloat sawheadcapx = 0.0;
		GLfloat sawheadcapy = 0.0;
		GLfloat sawheadcaprad = 0.1;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 2.5f, -0.5f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(sawheadcapx, sawheadcapy);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(sawheadcapx + (sawheadcaprad * cos(i * twopi / triangleAmount)), sawheadcapy + (sawheadcaprad * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		GLfloat sawheadx = 0.0;
		GLfloat sawheady = 0.0;
		GLfloat sawheadrad = 1.0;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 2.5f, -0.3f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(sawheadx, sawheady);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(sawheadx + (sawheadrad * cos(i * twopi / triangleAmount)), sawheady + (sawheadrad * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}
//-----------------------------

//-----------------------------Arm
void armcylinder() {
	glPushMatrix();
		GLUquadricObj* sawcylinder = NULL;
		sawcylinder = gluNewQuadric();
		glColor3f(0.4, 0.4, 0.4);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(sawcylinder, GLU_FILL);
		gluCylinder(sawcylinder, 0.1, 0.1, 3.2, 20, 5);
		gluDeleteQuadric(sawcylinder);
	glPopMatrix();
}

void armhand()
{
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 3.2f);
		GLUquadricObj* eyesphere = NULL;
		eyesphere = gluNewQuadric();
		glColor3f(1, 0, 0);	
		gluQuadricDrawStyle(eyesphere, GLU_FILL);
		gluSphere(eyesphere, 0.15, 20, 10);
		gluDeleteQuadric(eyesphere);
	glPopMatrix();
}

void armquad()
{
	glPushMatrix();
		glBegin(GL_QUADS);
			//top
			glVertex3f(-0.2f, 0.6f, -0.3f);
			glVertex3f(-0.5f, 0.6f, 0.3f);
			glVertex3f(-0.3f, 0.6f, 0.3f);
			glVertex3f(0.0f, 0.6f, -0.3f);

			//back
			//glColor3f(1, 0, 0);
			glVertex3f(0.0f, 0.6f, -0.3f);
			glVertex3f(-0.2f, 0.6f, -0.3f);
			glVertex3f(-0.2f, 0.0f, -0.3f);
			glVertex3f(0.0f, 0.0f, -0.3f);

			//right
			//glColor3f(0, 1, 0);
			glVertex3f(0.0f, 0.0f, -0.3f);
			glVertex3f(0.0f, 0.6f, -0.3f);
			glVertex3f(-0.3f, 0.6f, 0.3f);
			glVertex3f(-0.3f, 0.0f, 0.3f);

			//bottom
			//glColor3f(0, 0, 1);
			glVertex3f(-0.3f, 0.0f, 0.3f);
			glVertex3f(0.0f, 0.0f, -0.3f);
			glVertex3f(-0.2f, 0.0f, -0.3f);
			glVertex3f(-0.5f, 0.0f, 0.3f);

			//left
			//glColor3f(1, 1, 0);
			glVertex3f(-0.5f, 0.0f, 0.3f);
			glVertex3f(-0.2f, 0.0f, -0.3f);
			glVertex3f(-0.2f, 0.6f, -0.3f);
			glVertex3f(-0.5f, 0.6f, 0.3f);

			//front
			//glColor3f(1, 0, 1);
			glVertex3f(-0.5f, 0.6f, 0.3f);
			glVertex3f(-0.3f, 0.6f, 0.3f);
			glVertex3f(-0.3f, 0.0f, 0.3f);
			glVertex3f(-0.5f, 0.0f, 0.3f);
		glEnd();
	glPopMatrix();
}

void armquad2()
{
	glPushMatrix();
		
		glBegin(GL_QUADS);
		//top
		glVertex3f(-0.5f, 0.6f, -0.3f);
		glVertex3f(-0.2f, 0.6f, 0.3f);
		glVertex3f(0.0f, 0.6f, 0.3f);
		glVertex3f(-0.3f, 0.6f, -0.3f);

		//back
		//glColor3f(1, 0, 0);
		glVertex3f(-0.3f, 0.6f, -0.3f);
		glVertex3f(-0.5f, 0.6f, -0.3f);
		glVertex3f(-0.5f, 0.0f, -0.3f);
		glVertex3f(-0.3f, 0.0f, -0.3f);

		//right
		//glColor3f(0, 1, 0);
		glVertex3f(-0.3f, 0.0f, -0.3f);
		glVertex3f(-0.3f, 0.6f, -0.3f);
		glVertex3f(0.0f, 0.6f, 0.3f);
		glVertex3f(0.0f, 0.0f, 0.3f);

		//bottom
		//glColor3f(0, 0, 1);
		glVertex3f(0.0f, 0.0f, 0.3f);
		glVertex3f(-0.3f, 0.0f, -0.3f);
		glVertex3f(-0.5f, 0.0f, -0.3f);
		glVertex3f(-0.2f, 0.0f, 0.3f);

		//left
		//glColor3f(1, 1, 0);
		glVertex3f(-0.2f, 0.0f, 0.3f);
		glVertex3f(-0.5f, 0.0f, -0.3f);
		glVertex3f(-0.5f, 0.6f, -0.3f);
		glVertex3f(-0.2f, 0.6f, 0.3f);

		//front
		//glColor3f(1, 0, 1);
		glVertex3f(-0.2f, 0.6f, 0.3f);
		glVertex3f(0.0f, 0.6f, 0.3f);
		glVertex3f(0.0f, 0.0f, 0.3f);
		glVertex3f(-0.2f, 0.0f, 0.3f);
		glEnd();
	glPopMatrix();
}

void armquad3()
{
	glPushMatrix();
		glBegin(GL_QUADS);
			//top
			glVertex3f(0.2f, 0.6f, -0.3f);
			glVertex3f(0.5f, 0.6f, 0.3f);
			glVertex3f(0.3f, 0.6f, 0.3f);
			glVertex3f(0.0f, 0.6f, -0.3f);

			//back
			//glColor3f(1, 0, 0);
			glVertex3f(0.0f, 0.6f, -0.3f);
			glVertex3f(0.2f, 0.6f, -0.3f);
			glVertex3f(0.2f, 0.0f, -0.3f);
			glVertex3f(0.0f, 0.0f, -0.3f);

			//right
			//glColor3f(0, 1, 0);
			glVertex3f(0.0f, 0.0f, -0.3f);
			glVertex3f(0.0f, 0.6f, -0.3f);
			glVertex3f(0.3f, 0.6f, 0.3f);
			glVertex3f(0.3f, 0.0f, 0.3f);

			//bottom
			//glColor3f(0, 0, 1);
			glVertex3f(0.3f, 0.0f, 0.3f);
			glVertex3f(0.0f, 0.0f, -0.3f);
			glVertex3f(0.2f, 0.0f, -0.3f);
			glVertex3f(0.5f, 0.0f, 0.3f);

			//left
			//glColor3f(1, 1, 0);
			glVertex3f(0.5f, 0.0f, 0.3f);
			glVertex3f(0.2f, 0.0f, -0.3f);
			glVertex3f(0.2f, 0.6f, -0.3f);
			glVertex3f(0.5f, 0.6f, 0.3f);

			//front
			//glColor3f(1, 0, 1);
			glVertex3f(0.5f, 0.6f, 0.3f);
			glVertex3f(0.3f, 0.6f, 0.3f);
			glVertex3f(0.3f, 0.0f, 0.3f);
			glVertex3f(0.5f, 0.0f, 0.3f);
		glEnd();
	glPopMatrix();
}

void armquad4()
{
	glPushMatrix();

		glBegin(GL_QUADS);
			//top
			glVertex3f(0.5f, 0.6f, -0.3f);
			glVertex3f(0.2f, 0.6f, 0.3f);
			glVertex3f(0.0f, 0.6f, 0.3f);
			glVertex3f(0.3f, 0.6f, -0.3f);

			//back
			//glColor3f(1, 0, 0);
			glVertex3f(0.3f, 0.6f, -0.3f);
			glVertex3f(0.5f, 0.6f, -0.3f);
			glVertex3f(0.5f, 0.0f, -0.3f);
			glVertex3f(0.3f, 0.0f, -0.3f);

			//right
			//glColor3f(0, 1, 0);
			glVertex3f(0.3f, 0.0f, -0.3f);
			glVertex3f(0.3f, 0.6f, -0.3f);
			glVertex3f(0.0f, 0.6f, 0.3f);
			glVertex3f(0.0f, 0.0f, 0.3f);

			//bottom
			//glColor3f(0, 0, 1);
			glVertex3f(0.0f, 0.0f, 0.3f);
			glVertex3f(0.3f, 0.0f, -0.3f);
			glVertex3f(0.5f, 0.0f, -0.3f);
			glVertex3f(0.2f, 0.0f, 0.3f);

			//left
			//glColor3f(1, 1, 0);
			glVertex3f(0.2f, 0.0f, 0.3f);
			glVertex3f(0.5f, 0.0f, -0.3f);
			glVertex3f(0.5f, 0.6f, -0.3f);
			glVertex3f(0.2f, 0.6f, 0.3f);

			//front
			//glColor3f(1, 0, 1);
			glVertex3f(0.2f, 0.6f, 0.3f);
			glVertex3f(0.0f, 0.6f, 0.3f);
			glVertex3f(0.0f, 0.0f, 0.3f);
			glVertex3f(0.2f, 0.0f, 0.3f);
		glEnd();
	glPopMatrix();
}
//-----------------------------

//-----------------------------Lightsaber
void lightsaber_main()
{
	glPushMatrix();
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -1.5f);

		GLUquadricObj* lsmain = NULL;
		lsmain = gluNewQuadric();
		glColor3f(1, 1, 0);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(lsmain, GLU_FILL);
		gluCylinder(lsmain, 0.15, 0.15, 3.5, 20, 5);
		gluDeleteQuadric(lsmain);
	glPopMatrix();
}

void lightsaber_grip()
{
	glPushMatrix();
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 0.1f);

		GLUquadricObj* lsgrip = NULL;
		lsgrip = gluNewQuadric();
		glColor3f(0, 1, 0);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(lsgrip, GLU_FILL);
		gluCylinder(lsgrip, 0.2, 0.2, 2.0, 20, 5);
		gluDeleteQuadric(lsgrip);
	glPopMatrix();

	glPushMatrix();
		GLfloat circlex1 = 0.0;
		GLfloat circley1 = 0.0;
		GLfloat circlerad = 0.2;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 2.1f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(circlex1, circley1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(circlex1 + (circlerad * cos(i * twopi / triangleAmount)), circley1 + (circlerad * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		GLfloat circlex2 = 0.0;
		GLfloat circley2 = 0.0;
		GLfloat circlerad2 = 0.2;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 0.1f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(circlex2, circley2);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(circlex2 + (circlerad2 * cos(i * twopi / triangleAmount)), circley2 + (circlerad2 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}

void lightsaber_cap()
{
	glPushMatrix();
		glRotatef(270.0, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 1.0f);

		GLUquadricObj* lscap = NULL;
		lscap = gluNewQuadric();
		glColor3f(0, 1, 0);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(lscap, GLU_FILL);
		gluCylinder(lscap, 0.2, 0.3, 0.5, 20, 5);
		gluDeleteQuadric(lscap);
	glPopMatrix();

	glPushMatrix();
		GLfloat circlex1 = 0.0;
		GLfloat circley1 = 0.0;
		GLfloat circlerad = 0.3;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -1.5f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(circlex1, circley1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(circlex1 + (circlerad * cos(i * twopi / triangleAmount)), circley1 + (circlerad * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}

void lightsaber_centergrip()
{
	glPushMatrix();
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -0.9f);

		GLUquadricObj* lsgrip = NULL;
		lsgrip = gluNewQuadric();
		glColor3f(0, 1, 0);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(lsgrip, GLU_FILL);
		gluCylinder(lsgrip, 0.2, 0.2, 0.2, 20, 5);
		gluDeleteQuadric(lsgrip);
	glPopMatrix();

	glPushMatrix();
		GLfloat circleupperx1 = 0.0;
		GLfloat circleuppery1 = 0.0;
		GLfloat circlerad = 0.2;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -0.9f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(circleupperx1, circleuppery1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(circleupperx1 + (circlerad * cos(i * twopi / triangleAmount)), circleuppery1 + (circlerad * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		GLfloat circlelowerx1 = 0.0;
		GLfloat circlelowery1 = 0.0;
		GLfloat circlerad2 = 0.2;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -0.7f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(circlelowerx1, circlelowery1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(circlelowerx1 + (circlerad2 * cos(i * twopi / triangleAmount)), circlelowery1 + (circlerad2 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}

void lightsaber_centergrip2()
{
	glPushMatrix();
		glRotatef(90.0, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -0.6f);

		GLUquadricObj* lsgrip2 = NULL;
		lsgrip2 = gluNewQuadric();
		glColor3f(0, 1, 0);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(lsgrip2, GLU_FILL);
		gluCylinder(lsgrip2, 0.2, 0.2, 0.2, 20, 5);
		gluDeleteQuadric(lsgrip2);
	glPopMatrix();

	glPushMatrix();
		GLfloat circleupperx1 = 0.0;
		GLfloat circleuppery1 = 0.0;
		GLfloat circlerad = 0.2;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -0.6f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(circleupperx1, circleuppery1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(circleupperx1 + (circlerad * cos(i * twopi / triangleAmount)), circleuppery1 + (circlerad * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		GLfloat circlelowerx1 = 0.0;
		GLfloat circlelowery1 = 0.0;
		GLfloat circlerad2 = 0.2;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, -0.4f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(circlelowerx1, circlelowery1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(circlelowerx1 + (circlerad2 * cos(i * twopi / triangleAmount)), circlelowery1 + (circlerad2 * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}

void lightsaber_combined()
{
	glPushMatrix();
		lightsaber_main();
		lightsaber_grip();
		lightsaber_centergrip();
		lightsaber_centergrip2();
		lightsaber_cap();
	glPopMatrix();
}
//-----------------------------


//-----------------------------Shapes for body
void head_combined()
{
	glPushMatrix();
		glPushMatrix();
			head_sphere();
			head_eyesphere();
			head_eyepiece(0.0);
			glPushMatrix();
				glTranslatef(0.05f, 0.4f, 2.8f);
				glPushMatrix();
				glRotatef(-10, 1.0f, 0.0f, 0.0f);
					glPushMatrix();
						head_rectangle();
						glPushMatrix();
						glTranslatef(0.1f, 0.4f, 0.2f);
							head_colourchangingsphere();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(1.1f, 1.0f, 2.5f);
				glPushMatrix();
				glRotatef(-10, 1.0f, 0.0f, 0.0f);
					glPushMatrix();
					glRotatef(15, 0.0f, 1.0f, 0.0f);
						head_eyecylinder1();
						head_eyecone();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glRotatef(190, 0.0f, 1.0f, 0.0f);
				glTranslatef(1.1f, 1.0f, 2.5f);
				glPushMatrix();
					glRotatef(-10, 1.0f, 0.0f, 0.0f);
					glPushMatrix();
						glRotatef(15, 0.0f, 1.0f, 0.0f);
						head_eyecylinder1();
						head_eyecone();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, secondeyemove, 0.0f);
				glPushMatrix();
					glRotatef(90, 1.0f, 0.0f, 0.0f);
					glTranslatef(0.0f, -1.3f, -1.0f);
					head_secondeyecylinder();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, -1.3f, -1.3f);
					glRotatef(rotateeye, 0.0f, 1.0f, 0.0f);
					glTranslatef(0.0f, 1.3f, 1.3f);
					glPushMatrix();
						glTranslatef(0.0f, 1.0f, -1.3f);
						head_secondeyequad();
					glPopMatrix();
					glPushMatrix();
						glTranslatef(0.0f, 1.7f, -0.85f);
						head_secondeyesphere();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.8f, lschambermove, 0.8f);
				glPushMatrix();
					glRotatef(225, 0.0f, 1.0f, 0.0f);
					head_lightsaberchamber();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0.8f, lsmove, 0.8f);
				lightsaber_combined();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

//1 polygon
void body_cylinder()
{
	glPushMatrix();
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f, 5.75f, 0.0f);
		glRotatef(90, 1.0, 0.0, 0.0);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "r2d2_torso.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP, sizeof(BMP), &BMP);
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//type of texture, what filter used?magnified?,minimize?,
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		GLUquadricObj* bodycylinder = NULL;
		bodycylinder = gluNewQuadric();
		glColor3f(1, 1, 1);
		gluQuadricTexture(bodycylinder, TRUE);
		gluQuadricDrawStyle(bodycylinder, GLU_FILL);
		gluCylinder(bodycylinder, 3.0, 3.0, 6.0, 40, 5);
		gluDeleteQuadric(bodycylinder);
		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP);
		glDeleteTextures(1, &texture);
	glPopMatrix();

	glPopMatrix();
}

//2 polygon
void body_bottom()
{
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0.0f, 0.0f, 5.7f);

		GLUquadricObj* bodybottomcylinder = NULL;
		bodybottomcylinder = gluNewQuadric();
		glColor3f(0.75, 0.75, 0.75);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(bodybottomcylinder, GLU_FILL);
		gluCylinder(bodybottomcylinder, 3.0, 2.5, 1.0, 20, 5);
		gluDeleteQuadric(bodybottomcylinder);
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0.0f, 0.0f, 5.7f);

		GLUquadricObj* bodybottomcylinderline = NULL;
		bodybottomcylinderline = gluNewQuadric();
		glColor3f(0, 0, 0);
		//gluQuadricTexture(cylinder, TRUE);
		gluQuadricDrawStyle(bodybottomcylinderline, GLU_LINE);
		gluCylinder(bodybottomcylinderline, 3.0, 2.5, 1.0, 20, 1);
		gluDeleteQuadric(bodybottomcylinderline);
	glPopMatrix();

	glPushMatrix();
		GLfloat bodybottomx1 = 0.0;
		GLfloat bodybottomy1 = 0.0;
		GLfloat bottomradius = 2.5;

		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 6.7f);
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.75, 0.75, 0.75);
		glVertex2f(bodybottomx1, bodybottomy1);
		for (int i = 0; i <= triangleAmount; i++) {
			glVertex2f(bodybottomx1 + (bottomradius * cos(i * twopi / triangleAmount)), bodybottomy1 + (bottomradius * sin(i * twopi / triangleAmount)));
		}
		glEnd();
	glPopMatrix();
}

void backthruster_combined() 
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -(backthrustermove));
		glPushMatrix();
		glTranslatef(0.0f, -1.5f, -0.0f);
			backpackthruster(2.0);
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.8f, -0.3f, 3.5f);
			backpackthrustercone();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			glTranslatef(-0.8f, -0.3f, 3.5f);
			backpackthrustercone();
		glPopMatrix();
	glPopMatrix();
}

void lighter_combined()
{
	glPushMatrix();
		glTranslatef(-1.5f, -0.5f, 2.0f);
		glRotatef(-rotatelighter, 0.0f, 1.0f, 0.0f);
		glTranslatef(1.5f, 0.5f, -2.0f);
		glPushMatrix();
				lightercylinder();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.5f, -0.5f, 2.0f);
			glRotatef(-rotatelighter2, 0.0f, 0.0f, 1.0f);
			glTranslatef(-1.5f, 0.5f, -2.0f);
			lighterhead();
		glPopMatrix();
	glPopMatrix();
}

void saw_combined()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, sawmove);
		glPushMatrix();
		glTranslatef(1.4f, -3.1f, -1.0f);
			glPushMatrix();
				sawcylinder();
			glPopMatrix();
			glPushMatrix();
			glRotatef(sawrotate, 0.0f, 0.0f, 1.0f);
				saw_head();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void arm_combined()
{
	glPushMatrix();
	glTranslatef(2.4f, -1.0f, 0.80f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
		glPushMatrix();
			glPushMatrix();
				glPointSize(6);
				glColor3f(1, 1, 0);
				glBegin(GL_POINTS);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glEnd();
			glPopMatrix();
			glRotatef(-armmove, 1.0f, 0.0f, 0.0f);
			glPushMatrix();
				armcylinder();
			glPopMatrix();
			glPushMatrix();
				glRotatef(armrotate, 0.0f, 0.0f, 1.0f);
				armhand();

				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 3.2f);
					glRotatef(-(handmove), 0.0f, 1.0f, 0.0f);
					glTranslatef(0.0f, 0.0f, -2.8f);
					glPushMatrix();
						glTranslatef(0.0f, -0.3f, 3.0f);
						glPushMatrix();
							armquad();
							glPushMatrix();
								glTranslatef(0.0f, 0.0f, 0.6f);
								armquad2();
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 3.2f);
					glRotatef((handmove), 0.0f, 1.0f, 0.0f);
					glTranslatef(0.0f, 0.0f, -2.8f);
					glPushMatrix();
						glTranslatef(0.0f, -0.3f, 3.0f);
						glPushMatrix();
							armquad3();
							glPushMatrix();
								glTranslatef(0.0f, 0.0f, 0.6f);
								armquad4();
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

//1 polygon
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
//6 polygon + 42 polygon
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
		rectangle_7(2.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-(thrustermove), 0.0f, 0.0f);
		glPushMatrix();
			glRotatef(90.0, 1.0f, 0.0f, 0.0f);
			glTranslatef(-4.1f, 0.0f, 2.7f);
			thrustercylinder();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0, 1.0f, 0.0f, 0.0f);
			glTranslatef(-4.1f, 0.0f, 4.2f);
			thrustercone();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-3.6f, -3.1f, 0.0f);
			thrusterjoint1();
			glPopMatrix();
		glPushMatrix();
			glTranslatef(-3.6f, -3.7f, 0.0f);
			thrusterjoint2();
		glPopMatrix();
	glPopMatrix();

	//--------tyre------------
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
	//------------------------
}

//6 polygon + 42 polygon
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
		rectangle_7(2.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(thrustermove, 0.0f, 0.0f);
		glPushMatrix();
			glRotatef(90.0, 1.0f, 0.0f, 0.0f);
			glTranslatef(4.1f, 0.0f, 2.7f);
			thrustercylinder();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0, 1.0f, 0.0f, 0.0f);
			glTranslatef(4.1f, 0.0f, 4.2f);
			thrustercone();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3.6f, -3.1f, 0.0f);
			thrusterjoint1();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3.6f, -3.7f, 0.0f);
			thrusterjoint3();
		glPopMatrix();
	glPopMatrix();

	//----------------tyre----------------
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
	//------------------------------------
}

//3 polygon + 12 polygon
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

//----------------------------deathstar plan
void display_deathstarplan()
{
	glPushMatrix();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "deathstarplan.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP, sizeof(BMP), &BMP);
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//type of texture, what filter used?magnified?,minimize?,
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
			glTexCoord2f(1, 1); glVertex3f(-10, 6, 10);
			glTexCoord2f(0, 1); glVertex3f(10, 6, 10);
			glTexCoord2f(0, 0); glVertex3f(10, -6, 10);
			glTexCoord2f(1, 0); glVertex3f(-10, -6, 10);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP);
		glDeleteTextures(1, &texture);
	glPopMatrix();
}
//----------------------------

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
				
				glPushMatrix();
					glRotatef(rotatehead, 0.0f, 1.0f, 0.0f);
					head_combined();
					gatlingGun();
					if (activatedeathstarplan == 1)
					{
						display_deathstarplan();
					}
				glPopMatrix();

				body_cylinder();
				body_bottom();
				backthruster_combined();
				lighter_combined();
				saw_combined();
				arm_combined();
			
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

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (selectOrtho == true) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-12, 12, -12, 12, -20, 20);
		}

		if (selectPerspective == true) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//glScalef(0.5, 0.5, 0.5);
			gluPerspective(100.0, 1.0, 1, 100);
			//glFrustum(-10, 10, -10, 10, 10, 100);
			glTranslatef(0.0f, 0.0f, -12.0f);
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

		//thruster movement---------------------
		if (activatethruster == 1) {
			thrustermove += 0.1;
			activatebackthruster = 1;
		}
		else if (activatethruster == 2) {
			thrustermove -= 0.1;
			activatebackthruster = 2;
		}

		if (activatebackthruster == 1)
		{
			backthrustermove += 0.1;
		}
		else if (activatebackthruster == 2)
		{
			backthrustermove -= 0.1;
		}

		if (thrustermove >= 1.1)
		{
			thrustermove = 1.1;
			activatethruster = 0;
		}
		else if (thrustermove <= 0.1)
		{
			thrustermove = 0;
			activatethruster = 0;
		}
		
		if (backthrustermove >= 3.5)
		{
			backthrustermove = 3.5;
			activatebackthruster = 0;
		}
		else if (backthrustermove <= 0.1)
		{
			backthrustermove = 0.0;
			activatebackthruster = 0;
		}
		//--------------------------------------

		//Second eye movement-------------------
		if (activatesecondeye == 1)
		{
			secondeyemove += 0.1;
		}
		else if (activatesecondeye == 2)
		{
			secondeyemove -= 0.1;
		}

		if (secondeyemove >= 3.0)
		{
			secondeyemove = 3.0;
			activatesecondeye = 0;
		}
		else if (secondeyemove <= 0.1)
		{
			secondeyemove -= 0;
			activatesecondeye = 0;
		}
		//--------------------------------------

		//Head rotate sound---------------------
		if (rotatehead == 46) {
			PlaySound("Sounds/R2D2a.wav", NULL, SND_ASYNC);
		}
		else if (rotatehead == -46){
			PlaySound("Sounds/R2D2c.wav", NULL, SND_ASYNC);
		}
		//--------------------------------------

		//lighter move--------------------------
		if (activatelighter == 1)
		{
			rotatelighter += 2;
			activatelighter2 = 1;
		}
		else if (activatelighter == 2)
		{
			rotatelighter -= 2;
			activatelighter2 = 2;
		}

		if (activatelighter2 == 1)
		{
			rotatelighter2 += 2;
		}
		else if (activatelighter2 == 2)
		{
			rotatelighter2 -= 2;
		}

		if (rotatelighter >= 90)
		{
			rotatelighter = 90;
			activatelighter = 0;
		}
		else if (rotatelighter <= 0.1)
		{
			rotatelighter = 0;
			activatelighter = 0;
		}

		if (rotatelighter2 >= 90)
		{
			rotatelighter2 = 90;
			activatelighter2 = 0;
		}
		else if (rotatelighter2 <= 0.1)
		{
			rotatelighter2 = 0;
			activatelighter2 = 0;
		}
		//--------------------------------------

		//lightsaber----------------------------
		if (activatelightsaber == 1)
		{
			lsmove += 0.1;
		}
		else if (activatelightsaber == 2)
		{
			lsmove -= 0.1;
		}

		if (lsmove >= 3.5)
		{
			lsmove = 3.5;
			activatelightsaber = 0;
		}
		else if (lsmove <= 0.1 && activatelightsaber == 2)
		{
			lsmove = 0;
			activatelightsaberchamber = 2;
			activatelightsaber = 0;
		}

		if (activatelightsaberchamber == 1)
		{
			lschambermove += 0.1;
		}
		else if (activatelightsaberchamber == 2)
		{
			lschambermove -= 0.1;
		}

		if (lschambermove >= 2.2 && activatelightsaberchamber == 1)
		{
			lschambermove = 2.2;
			activatelightsaber = 1;
			activatelightsaberchamber = 0;
		}
		else if (lschambermove <= 0.1)
		{
			lschambermove = 0;
			activatelightsaberchamber = 0;
		}
		//--------------------------------------

		//saw-----------------------------------
		if (activatesaw == 1) 
		{
			sawmove += 0.1;
		}
		else if (activatesaw == 2)
		{
			sawmove -= 0.1;
		}

		if (sawmove >= 3.5)
		{
			sawmove = 3.5;
			activatesaw = 0;
		}
		else if (sawmove <= 0.1)
		{
			sawmove = 0;
			activatesaw = 0;
		}
		//--------------------------------------

		//arm-----------------------------------
		if (activatearm == 1) {
			armmove += 2;
		}
		else if (activatearm == 2)
		{
			armmove -= 2;
		}

		if (armmove >= 90)
		{
			armmove = 90;
			activatearm = 0;
		}
		else if (armmove <= 0.1)
		{
			armmove = 0;
			activatearm = 0;
		}

		if (activatehand == 1) {
			handmove += 1;
		}
		else if (activatehand == 2)
		{
			handmove -= 1;
		}

		if (handmove >= 45)
		{
			handmove = 45;
			activatehand = 0;
		}
		else if (handmove <= 0.1)
		{
			handmove = 0;
			activatehand = 0;
		}
		//--------------------------------------

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------