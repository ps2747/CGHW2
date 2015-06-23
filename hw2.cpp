#include "hw2.h"
#include "glwrapper.h"
#include <cmath>
#include <time.h>

#include "Mesh.h"
#include "HeyColor.h"

#ifndef M_PI
#define M_PI    3.1415926535
#endif

static glm::vec3 normalize(glm::vec3 in)
{
	float d = sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
	return in / d;
}

void HW2::drawCircle(float x, float y, float r, int seg)
{
    // Complete your code here
}

void HW2::drawMesh_otho(const HeyRenderer::Mesh &in)
{
	glm::vec3 oTemp,aTemp,bTemp;
	for(int i=0; i<in.indices.size(); i+=3)
	{
		glm::vec4 o(in.vertices[in.indices[i]].pos,1.0f);
		glm::vec4 a(in.vertices[in.indices[i+1]].pos,1.0f);
		glm::vec4 b(in.vertices[in.indices[i+2]].pos,1.0f);

		glm::vec3 oNorm = in.vertices[in.indices[i]].normal;
		glm::vec3 aNorm = in.vertices[in.indices[i+1]].normal;
		glm::vec3 bNorm = in.vertices[in.indices[i+2]].normal;
			
		oTemp = glm::vec3(in.transMat * o);
		aTemp = glm::vec3(in.transMat * a);
		bTemp = glm::vec3(in.transMat * b);

		oNorm = glm::vec3(in.transMat * glm::vec4( oNorm, 1.0f));
		aNorm = glm::vec3(in.transMat * glm::vec4( aNorm, 1.0f));
		bNorm = glm::vec3(in.transMat * glm::vec4( bNorm, 1.0f));

		//GLWrapper::drawLine(o, normalize(o), a, normalize (a),GLWrapper::FBUFFER);
		//GLWrapper::drawLine(o, normalize(o), b, normalize(b),GLWrapper::FBUFFER);
		//GLWrapper::drawLine(b, normalize(b), a, normalize(a),GLWrapper::FBUFFER);

		drawTriangle(oTemp, normalize(oTemp), aTemp, normalize(aTemp), bTemp, normalize(bTemp), GLWrapper::FBUFFER);
		drawTriangle(oTemp, oNorm, aTemp, aNorm, bTemp, bNorm, GLWrapper::NBUFFER);
	}
	GLWrapper::glDrawFrame(320 , 320, GLWrapper::FBUFFER);
}

void HW2::drawMesh_pers(const float near, const float far ,const HeyRenderer::Mesh &in)
{
	glm::vec3 oTemp,aTemp,bTemp;
	glm::mat4 mPer(
		- near, 0.0f, 0.0f, 0.0f,
		0.0f, - near, 0.0f, 0.0f,
		0.0f, 0.0f,  (near + far)/(near - far), (-2 *near * far) / (near - far),
		0.0f, 0.0f, -1, 0.0f
	);
	for(int i=0; i<in.indices.size(); i+=3){
		glm::vec4 o(in.vertices[in.indices[i]].pos,1.0f);
		glm::vec4 a(in.vertices[in.indices[i+1]].pos,1.0f);
		glm::vec4 b(in.vertices[in.indices[i+2]].pos,1.0f);

		glm::vec3 oNorm = in.vertices[in.indices[i]].normal;
		glm::vec3 aNorm = in.vertices[in.indices[i+1]].normal;
		glm::vec3 bNorm = in.vertices[in.indices[i+2]].normal;
			
		o = in.transMat * o;
		a = in.transMat * a;
		b = in.transMat * b;

		oNorm = glm::vec3(in.transMat * glm::vec4( oNorm, 1.0f));
		aNorm = glm::vec3(in.transMat * glm::vec4( aNorm, 1.0f));
		bNorm = glm::vec3(in.transMat * glm::vec4( bNorm, 1.0f));

		oTemp = glm::vec3(mPer * o);
		aTemp = glm::vec3(mPer * a);
		bTemp = glm::vec3(mPer * b);

		//draw edge
		//GLWrapper::drawLine(oTemp, oNorm, aTemp, aNorm,GLWrapper::NBUFFER);
		//GLWrapper::drawLine(oTemp, oNorm, bTemp, bNorm,GLWrapper::NBUFFER);
		//GLWrapper::drawLine(bTemp, bNorm, aTemp, aNorm,GLWrapper::NBUFFER);
		//drawTriangle(oTemp, o.z, normalize(oTemp), aTemp, a.z, normalize(aTemp), bTemp, b.z, normalize(bTemp), GLWrapper::FBUFFER); //Pos map
		if(!false )
			drawTriangle(oTemp, o.z, oNorm, aTemp, a.z, aNorm, bTemp, b.z, bNorm, GLWrapper::NBUFFER); //Normal
		else {
			glm::vec3 flatNorm = (oNorm + aNorm + bNorm) /3.0f;
			drawTriangle(oTemp, o.z, flatNorm, aTemp, a.z, flatNorm, bTemp, b.z, flatNorm, GLWrapper::NBUFFER); //Flat Normal
		}

	}
	//GLWrapper::glDrawFrame(320 , 320, GLWrapper::NBUFFER);

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
