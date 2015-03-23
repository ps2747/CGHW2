#ifndef _GLWRAPPER_H_
#define _GLWRAPPER_H_

#include <GLFW/glfw3.h>

namespace GLWrapper
{
	void clearScreen();
	void drawPoint(float, float);
	void drawPoint_Color(float,float ,const float,const float,const float);
	void setPointColor(float r, float g, float b);
	void drawLine(float x1, float y1, float x2, float y2);
	void drawLine_Color(float , float , float , float ,const float,const float,const float);
	void drawTriangle(float,float,float,float,float,float,const float,const float,const float);
}

#endif
