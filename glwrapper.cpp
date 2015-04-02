#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glwrapper.h"

#define abs(a) ((a)>=0?(a):-(a))

static int height ,width;

void GLWrapper::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	height =320;width = 320;
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

void GLWrapper::drawLine(const float x1,const  float y1,const  float x2,const  float y2)
{
		// Complete your code here, you can only use GLWrapper::drawPoint

	//GLFWwindow *window;
	//glfwGetWindowSize(window, &width, &height);
	//width = 320; height = 320;
	glm::vec2 v1((x1+1)*width/2.0f, (y1+1)*height/2.0f);
	glm::vec2 v2((x2+1)*width/2.0f, (y2+1)*height/2.0f);
	float slope,zSlope;

	if(abs(v1.x-v2.x)>abs(v2.y-v1.y)){
		//x changes faster than y
		if(v1.x>v2.x)
		{
			glm::vec2 tmp=v1;
			v1=v2;
			v2=tmp;
		}
		if((int)v2.x!=(int)v1.x)
		{
			slope=(float)(v2.y-v1.y)/(v2.x-v1.x);
			float curx=v1.x, cury=v1.y;
			while((int)cury!=(int)v2.y)
			{
				drawPoint(curx*2.0f/width-1, ((int)cury)*2.0f/height-1);
				cury+=slope;
				curx+=1;
			}
			while((int)curx<=(int) v2.x){
				drawPoint(curx*2.0f/width-1, ((int)cury)*2.0f/height-1);
				curx+=1;
			}
		}
		else{
			float curx=v1.x, cury=v1.y;
			while((int)cury<=(int)v2.y)
			{
				drawPoint(curx*2.0f/width-1, cury*2.0f/height-1);
				cury+=1;
			}
		}
	}else
	{
		
		if(v1.y>v2.y)
		{
			glm::vec2 tmp=v1;
			v1=v2;
			v2=tmp;
		}
		if((int)v2.y!=(int)v1.y)
		{
			slope=(float)(v2.x-v1.x)/(v2.y-v1.y);
			float curx=v1.x, cury=v1.y;
			while((int)curx!=(int)v2.x)
			{
				drawPoint(((int)curx)*2.0f/width-1, cury*2.0f/height-1);
				cury+=1;
				curx+=slope;
			}
			while((int)cury<=(int)v2.y){
				drawPoint(((int)curx)*2.0f/width-1, cury*2.0f/height-1);
				cury+=1;
			}
		}
		else{
			float curx=v1.x, cury=v1.y;
			while((int)curx<=(int)v2.x)
			{
				drawPoint(curx*2.0f/width-1, cury*2.0f/height-1);
				curx+=1;
			}
		}
	}
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
