#include <GLFW/glfw3.h>
#include "glwrapper.h"

#define abs(a) ((a)>=0?(a):-(a))

void GLWrapper::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLWrapper::drawPoint(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void GLWrapper::setPointColor(float r, float g, float b)
{
	glColor3f(r, g, b);
}

void GLWrapper::drawLine(float x1, float y1, float x2, float y2)
{
	// Complete your code here, you can only use GLWrapper::drawPoint

	/*float dx=x2-x1;
	float dy=y2-y1;
*/
	int samples=200;
	for(int i=0; i<=samples; i++)
		drawPoint(x1+i*(x2-x1)/samples, y1+i*(y2-y1)/samples);
}
