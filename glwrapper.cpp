#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glwrapper.h"

#define abs(a) ((a)>=0?(a):-(a))

static int height ,width;
static float zbuffer[320][320];

void GLWrapper::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	height =320;width = 320;
	for(int i = 0 ;i <height ; ++i)
		for(int j =0; j<width ;++j)
			zbuffer[i][j]= 2000.0f;
}

void GLWrapper::drawPoint(float x, float y ,float z)
{
	if(x>=-1 && x<=1 &&y>=-1 && y<=1 ){
		if(-z <zbuffer[(int)((y+1)*height/2.0f)][(int)((x+1)*width/2.0f)]){
			zbuffer[(int)((y+1)*height/2.0f)][(int)((x+1)*width/2.0f)]= -z;
			glBegin(GL_POINTS);
			glVertex2f(x, y);
			glEnd();
		}
	}
}

void GLWrapper::drawPoint_Color(float x,float y,float z,const float r,const float g,const float b)
{
	glColor3f(r,g,b);
	drawPoint(x,y,z);
}

void GLWrapper::setPointColor(float r, float g, float b)
{
	glColor3f(r, g, b);
}

void GLWrapper::drawLine( float x1, float y1,float z1,float x2,float y2,float z2)
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
			float tempZ = z1;
			z1 = z2;
			z2 = tempZ;
		}
		if((int)v2.x!=(int)v1.x)
		{
			slope=(float)(v2.y-v1.y)/(v2.x-v1.x);
			
			zSlope = (float)(z2 - z1)/(v2.x-v1.x);

			float curx=v1.x, cury=v1.y;
			while((int)cury!=(int)v2.y)
			{
				drawPoint(curx*2.0f/width-1, ((int)cury)*2.0f/height-1,z1);
				cury+=slope;
				z1 += zSlope;
				curx+=1;
			}
			while((int)curx<=(int) v2.x){
				drawPoint(curx*2.0f/width-1, ((int)cury)*2.0f/height-1,z1);
				curx+=1;
				z1 += zSlope;
			}
		}
		else{
			float curx=v1.x, cury=v1.y;
			zSlope = (float)(z2 - z1)/(v2.y-v1.y);
			while((int)cury<=(int)v2.y)
			{
				drawPoint(curx*2.0f/width-1, cury*2.0f/height-1,z1);
				cury+=1;
				z1 += zSlope;
			}
		}
	}else
	{
		
		if(v1.y>v2.y)
		{
			glm::vec2 tmp=v1;
			v1=v2;
			v2=tmp;
			float tempZ = z1;
			z1 = z2;
			z2 = tempZ;
		}
		if((int)v2.y!=(int)v1.y)
		{
			slope=(float)(v2.x-v1.x)/(v2.y-v1.y);
			zSlope = (float)(z2 - z1)/(v2.y-v1.y);
			float curx=v1.x, cury=v1.y;
			while((int)curx!=(int)v2.x)
			{
				drawPoint(((int)curx)*2.0f/width-1, cury*2.0f/height-1,z1);
				cury+=1;
				curx+=slope;
				z1 += zSlope;
			}
			while((int)cury<=(int)v2.y){
				drawPoint(((int)curx)*2.0f/width-1, cury*2.0f/height-1,z1);
				cury+=1;
				z1 += zSlope;
			}
		}
		else{
			float curx=v1.x, cury=v1.y;
			zSlope = (float)(z2 - z1)/(v2.x-v1.x);
			while((int)curx<=(int)v2.x)
			{
				drawPoint(curx*2.0f/width-1, cury*2.0f/height-1,z1);
				curx+=1;
				z1 +=zSlope;
			}
		}
	}
}

void GLWrapper::drawLine_Color(float x1, float y1,float z1, float x2, float y2, float z2,float r,float g,float b)
{
	glColor3f(r, g, b);
	drawLine(x1,y1,z1,x2,y2,z2);
}

void GLWrapper::drawTriangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,const float r,const float g,const float b)
{
	int sample = 200;
	for(int i = 0;i <= sample ; ++i){
		drawLine_Color(x1,y1,z1,x2+i*(x3-x2)/sample,y2+i*(y3-y2)/sample,z2+i*(z3-z2)/sample,r,g,b);
	}


}
