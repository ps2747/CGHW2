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

void GLWrapper::drawPoint_Color(float x,float y,const float r,const float g,const float b)
{
	glColor3f(r,g,b);
	drawPoint(x,y);
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
	int sample=200;
	for(int i=0; i<=sample; i++)
		drawPoint(x1+i*(x2-x1)/sample, y1+i*(y2-y1)/sample);
}

void GLWrapper::drawLine_Color(float x1, float y1, float x2, float y2,const float r,const float g,const float b)
{
	int sample = 200;
	for(int i = 0; i<= sample;++i)
		drawPoint_Color(x1+i*(x2-x1)/sample, y1+i*(y2-y1)/sample,r,g,b);
}

void GLWrapper::drawTriangle(float x1,float y1,float x2,float y2,float x3,float y3,const float r,const float g,const float b)
{
	int sample = 200;
	for(int i = 0;i <= sample ; ++i){
		drawLine_Color(x1,y1,x2+i*(x3-x2)/sample,y2+i*(y3-y2)/sample,r,g,b);
	}


}
