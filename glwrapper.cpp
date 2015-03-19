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
	float tangle = (y2-y1)/(x2-x1);
	for(float i = x1; i <x2; i+=0.01){
		drawPoint(i,i*tangle);
	}
	drawPoint(x2,y2);

	// Complete your code here, you can only use GLWrapper::drawPoint
	// To determine how many samples you want, You may need to calculate the pixel width
}
