#include "hw2.h"
#include "glwrapper.h"
#include <cmath>
#include <time.h>

#include "Mesh.h"
#include "HeyColor.h"

#ifndef M_PI
#define M_PI    3.1415926535
#endif

static glm::vec3 m_dir = glm::vec3 (0.0f);

static glm::vec3 normalize(glm::vec3 in)
{
	float d = sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
	return in / d;
}

static glm::vec3 reflect(glm::vec3 v ,glm::vec3 n)
{
	return -2*dot(n ,v )*n + v;
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

		glm::vec3 oNorm = normalize(in.vertices[in.indices[i]].normal);
		glm::vec3 aNorm = normalize(in.vertices[in.indices[i+1]].normal);
		glm::vec3 bNorm = normalize(in.vertices[in.indices[i+2]].normal);
			
		o = in.transMat * o;
		a = in.transMat * a;
		b = in.transMat * b;

		oNorm = glm::vec3(in.transMat * glm::vec4( oNorm, 1.0f));
		aNorm = glm::vec3(in.transMat * glm::vec4( aNorm, 1.0f));
		bNorm = glm::vec3(in.transMat * glm::vec4( bNorm, 1.0f));

		glm::vec4 divW_o,divW_a,divW_b;
		divW_o = mPer * o;  divW_o/= divW_o.w;
		divW_a = mPer * a;  divW_a/= divW_a.w;
		divW_b = mPer * b;  divW_b/= divW_b.w;

		oTemp = glm::vec3( divW_o);
		aTemp = glm::vec3( divW_a);
		bTemp = glm::vec3(divW_b);

		//draw edge
		//GLWrapper::drawLine(oTemp, oNorm, aTemp, aNorm,GLWrapper::NBUFFER);
		//GLWrapper::drawLine(oTemp, oNorm, bTemp, bNorm,GLWrapper::NBUFFER);
		//GLWrapper::drawLine(bTemp, bNorm, aTemp, aNorm,GLWrapper::NBUFFER);
		//drawTriangle(oTemp, o.z, normalize(oTemp), aTemp, a.z, normalize(aTemp), bTemp, b.z, normalize(bTemp), GLWrapper::FBUFFER); //Pos map
		if(!isFlat )
			drawTriangle(oTemp, o.z, oNorm, aTemp, a.z, aNorm, bTemp, b.z, bNorm, GLWrapper::NBUFFER); //Normal
		else {
			glm::vec3 flatNorm = (oNorm + aNorm + bNorm) /3.0f;
			drawTriangle(oTemp, o.z, flatNorm, aTemp, a.z, flatNorm, bTemp, b.z, flatNorm, GLWrapper::NBUFFER); //Flat Normal
		}

	}
	GLWrapper::litDirLight(m_dir);
	//GLWrapper::glDrawFrame(320 , 320, GLWrapper::NBUFFER);

}

void HW2::drawMesh_pers_ground(const float near, const float far ,const HeyRenderer::Mesh &in)
{
	glm::vec3 grondLightDir = glm::vec3 (m_dir.x, m_dir.y, -m_dir.z);
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

		drawTriangle(oTemp, o.z, pixelLighting(oNorm, grondLightDir), aTemp, a.z, pixelLighting(aNorm, grondLightDir), bTemp, b.z, pixelLighting(bNorm, grondLightDir), GLWrapper::FBUFFER); 

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

glm::vec3 HW2::pixelLighting(glm::vec3 n, glm::vec3 v)
{
	glm::vec3 refVec = reflect (v , n);
	glm::vec3 veiwVec = glm::vec3(0.0f,0.0f, -1.0f);
	glm::vec3 originColor= glm::vec3(0.5,0.5,0.5);
	float l_Dot_n = dot(v , n);
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
		0.3,0.3,0.3,0.0,
		0.5,0.5,0.5,0.0,
		0.03,0.03,0.03,0.0,
		0.0,0.0,0.0,1.0
	);

	return glm::vec3(K*Coex*glm::vec4(n,1.0f));
}

void HW2::litDirLight(glm::vec3 dir)
{
	m_dir = dir;
}

void HW2::setFlat(bool set)
{
	isFlat = set ; 
}
