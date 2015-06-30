#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <math.h>
#include "glwrapper.h"

#define abs(a) ((a)>=0?(a):-(a))

static int height ,width;

static float dot(glm::vec3 a, glm::vec3 b)
{
	return a.x*b.x +a.y * b.y +a.z *b.z;
}

static float distance(glm::vec3 pos_1 , glm::vec3 pos_2)
{
	float x = pos_2.x - pos_1.x;
	float y = pos_2.y - pos_1.y;
	float z = pos_2.z - pos_1.z;
	return std::sqrt(x * x + y * y + z * z);
}

static glm::vec3 reflect(glm::vec3 v ,glm::vec3 n)
{
	return -2*dot(n ,v )*n + v;
}

static glm::vec3 normalize(glm::vec3 in)
{
	float d = sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
	return in / d;
}

void GLWrapper::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	height =320;width = 320;
	for(int i = 0 ;i <height ; ++i)
		for(int j =0; j<width ;++j){
			zbuffer[i][j] = glm::vec3(2000.0f);
			frameBuffer[i][j] = glm::vec3(0.0f);
			normalBuffer[i][j] = glm::vec3(0.0f);
		}
}

void GLWrapper::glDrawFrame(int f_height , int f_width, Buffer c_buffer)
{
	float x, y;
	glBegin(GL_POINTS);
	for(int i = 0 ;i < f_height; ++i){
		for(int j = 0; j< f_width; ++j){
			x = (float)j/f_width*2 - 1;
			y = (float)i/f_height *2 - 1;
			
			switch(c_buffer){
				case ZBUFFER:
					glColor3f(zbuffer[i][j].x, zbuffer[i][j].y, zbuffer[i][j].z); break;
				case FBUFFER:
					glColor3f(frameBuffer[i][j].x, frameBuffer[i][j].y,frameBuffer[i][j].z );  break;
				case NBUFFER:
					glColor3f(normalBuffer[i][j].x, normalBuffer[i][j].y,normalBuffer[i][j].z );  break;
			} 
			glVertex2f(x,y);	
		}
	}
	glEnd();
}


void GLWrapper::drawPoint(glm::vec3 pos, glm::vec3 color, Buffer c_buffer)
{
	if(pos.x>=-1 && pos.x<=1 &&pos.y>=-1 &&pos.y<=1 ){
		int x = int((pos.x+1)*width/2.0f);
		int y = int((pos.y+1)*height/2.0f);
		if(-pos.z <zbuffer[y][x].x){
			zbuffer[y][x]= glm::vec3(-pos.z);
			switch(c_buffer){
				case ZBUFFER:
				case FBUFFER:
					frameBuffer[y][x] = color; break;
				case NBUFFER:
					normalBuffer[y][x] = color; break;
			}
		}
	}
}

void GLWrapper::drawLine(glm::vec3 pos_1, glm::vec3 color_1, glm::vec3 pos_2, glm::vec3 color_2,Buffer c_buffer)
{
	glm::vec2 v1((pos_1.x+1)*width/2.0f, (pos_1.y+1)*height/2.0f);
	glm::vec2 v2((pos_2.x+1)*width/2.0f, (pos_2.y+1)*height/2.0f);

	glm::vec3 slope = (pos_2 - pos_1);

	glm::vec3 curPos = pos_1;

	int widthPixels = abs(v1.x-v2.x);
	int heightPixels = abs(v2.y-v1.y);
	if(widthPixels>heightPixels){
		if(widthPixels != 0)
			slope /= (float)widthPixels;
		else 
			slope = glm::vec3(0.0f);
		for(int i = 0; i < widthPixels ; ++i){
			float ratio = (float)i/(float)widthPixels;
			drawPoint(curPos , color_1 *(1- ratio) + color_2 *ratio,c_buffer);
			//drawPoint(curPos , color_2 ,c_buffer);
			curPos += slope;
		}
	}
	else {
		if(heightPixels != 0)
			slope /= (float)heightPixels;
		else 
			slope = glm::vec3(0.0f);
		for(int i = 0; i < heightPixels ; ++i){
			float ratio =(float) i/(float)heightPixels;
			drawPoint(curPos , color_1 *(1- ratio) + color_2 *ratio,c_buffer);
			//drawPoint(curPos , color_2 ,c_buffer);
			curPos += slope;
		}
	}
}

void GLWrapper::drawTriangle(glm::vec3 pos_1, glm::vec3 color_1, glm::vec3 pos_2, glm::vec3 color_2, glm::vec3 pos_3, glm::vec3 color_3, Buffer c_buffer)
{
	glm::vec2 v2((pos_2.x+1)*width/2.0f, (pos_2.y+1)*height/2.0f);
	glm::vec2 v3((pos_3.x+1)*width/2.0f, (pos_3.y+1)*height/2.0f);

	int widthPixels = abs(v3.x-v2.x);
	int heightPixels = abs(v2.y-v3.y);
	int sample;
	if(widthPixels>heightPixels)
		sample = widthPixels + 70;
	else 
		sample = heightPixels + 70;

	for (int i = 0 ; i <sample; ++i){
		float ratio = (float)i / sample;
		glm::vec3 sColor = color_2* (1 - ratio) + color_3 * ratio;
		glm::vec3 ratioedPos = glm::vec3(pos_2.x+i*(pos_3.x-pos_2.x)/sample,pos_2.y+i*(pos_3.y-pos_2.y)/sample,pos_2.z+i*(pos_3.z-pos_2.z)/sample);
		drawLine(pos_1, color_1, ratioedPos, sColor , c_buffer);

	}
}

void GLWrapper::drawTriangle(glm::vec3 pos_1, float originZ_1, glm::vec3 color_1, glm::vec3 pos_2, float originZ_2, glm::vec3 color_2, glm::vec3 pos_3,  float originZ_3, glm::vec3 color_3, Buffer c_buffer)
{
	pos_1.z = originZ_1;
	pos_2.z = originZ_2; 
	pos_3.z = originZ_3;
	drawTriangle(pos_1, color_1, pos_2, color_2, pos_3, color_3, c_buffer);
}

void GLWrapper::litDirLight(glm::vec3 dir)
{
	//dir = normalize(dir);
	for(int i = 0 ;i <height; i++)
		for(int j  = 0 ;j < width; j++){
			if(zbuffer[i][j].x <  2000.0f){
				glm::vec3 refVec = reflect (normalize(dir) , normalBuffer[i][j]);
				glm::vec3 veiwVec = glm::vec3(0.0f,0.0f,-1.0f);
				glm::vec3 originColor= glm::vec3(0.5,0.5,0.5);
				float l_Dot_n = dot( - dir , normalBuffer[i][j]);
				float r_Dot_v = dot(refVec , veiwVec);
				if(l_Dot_n < 0) l_Dot_n = 0;
				if(r_Dot_v < 0) r_Dot_v = 0;


				glm::mat4 Coex = glm::mat4(
					1.0,1.0,1.0,0.0,
					l_Dot_n,l_Dot_n,l_Dot_n,0.0,
					r_Dot_v,r_Dot_v,r_Dot_v,0.0,
					0.0,0.0,0.0,1.0
				);

				glm::mat4 K = glm::mat4(
					ambiColor.r,ambiColor.g,ambiColor.b,0.0,
					diffColor.r,diffColor.g,diffColor.b,0.0,
					0.03,0.03,0.03,0.0,
					0.0,0.0,0.0,1.0
				);

				frameBuffer[i][j] = glm::vec3(K*Coex*glm::vec4(originColor,1.0));
			}
		}
}

void GLWrapper::litSetDiffColor(glm::vec3 in)
{
	diffColor = in;
}

void GLWrapper::litSetAmbi(float valume)
{
	ambiColor +=valume;
}
void GLWrapper::litSetDiffColor_R(float valume)
{
	diffColor.r += valume;
}

void GLWrapper::litSetDiffColor_G(float valume)
{
	diffColor.g += valume;
}
void GLWrapper::litSetDiffColor_B(float valume)
{
	diffColor.b += valume;
}