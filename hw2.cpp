#include "hw2.h"
#include "glwrapper.h"
#include <cmath>
#include <time.h>

#include "Mesh.h"
#include "HeyColor.h"

#ifndef M_PI
#define M_PI    3.1415926535
#endif

void HW2::drawCircle(float x, float y, float r, int seg)
{
    // Complete your code here
}

void HW2::drawMesh_otho(const HeyRenderer::Mesh &in)
{
	for(int i=0; i<in.indices.size(); i+=3)
	{
		const glm::vec3 &o=in.vertices[in.indices[i]].pos;
		const glm::vec3 &a=in.vertices[in.indices[i+1]].pos;
		const glm::vec3 &b=in.vertices[in.indices[i+2]].pos;
		GLWrapper::drawLine(o.x, o.y,o.z, a.x, a.y,a.z);
		GLWrapper::drawLine(o.x, o.y,o.z, b.x, b.y,b.z);
		GLWrapper::drawLine(b.x, b.y,b.z, a.x, a.y,a.z);
	}
}

void HW2::drawMesh_pers(const float d,const HeyRenderer::Mesh &in)
{
	glm::vec3 oTemp,aTemp,bTemp;
	srand((unsigned ) time(NULL));
	for(int i=0; i<in.indices.size(); i+=3){
		glm::vec4 o(in.vertices[in.indices[i]].pos,1.0f);
		glm::vec4 a(in.vertices[in.indices[i+1]].pos,1.0f);
		glm::vec4 b(in.vertices[in.indices[i+2]].pos,1.0f);
			
		o = in.transMat * o;
		a = in.transMat * a;
		b = in.transMat * b;

		oTemp.x = o.x/(o.z/d);oTemp.y = o.y/(o.z/d);oTemp.z = o.z/(o.z/d);
		bTemp.x = b.x/(b.z/d);bTemp.y = b.y/(b.z/d);bTemp.z = b.z/(b.z/d);
		aTemp.x = a.x/(a.z/d);aTemp.y = a.y/(a.z/d);aTemp.z = a.z/(a.z/d);

		//draw face
		GLWrapper::drawTriangle(oTemp.x,oTemp.y,o.z,aTemp.x,aTemp.y,a.z,bTemp.x,bTemp.y,b.z,in.faceColor[i/3].r,in.faceColor[i/3].g,in.faceColor[i/3].b);

		//draw edge
		GLWrapper::drawLine(oTemp.x, oTemp.y,o.z, aTemp.x, aTemp.y,a.z);
		GLWrapper::drawLine(oTemp.x, oTemp.y,o.z, bTemp.x, bTemp.y,b.z);
		GLWrapper::drawLine(bTemp.x, bTemp.y,b.z, aTemp.x, aTemp.y,a.z);
	}

}

void HW2::randSetMeshColor(HeyRenderer::Mesh &mesh){
	glm::vec3 tempColor;
	for(int i = 0;i<mesh.indices.size(); i+=3){
		tempColor.r = (float) rand()/(RAND_MAX+1.0);
		tempColor.g = (float) rand()/(RAND_MAX+1.0);
		tempColor.b = (float) rand()/(RAND_MAX+1.0);
		mesh.faceColor.push_back(tempColor);
	}

}
