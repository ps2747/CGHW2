#define GLM_SWIZZLE //for use of glm::vec4 .xyz();

#include "Mesh_Tool.h"
#include <math.h>
#include <cstdio>


void HeyRenderer::ClearMat()
{
	transMat = glm::mat4 (0.0f);
	rotateMat_X = glm::mat4 (0.0f);
	rotateMat_Y = glm::mat4 (0.0f);
	rotateMat_Z = glm::mat4 (0.0f);
	scalingMat = glm::mat4 (0.0f);
	shearMat = glm::mat4 (0.0f);

}

void HeyRenderer::TransMat(const glm::vec3 direction)
{
	transMat = glm::mat4 (0.0f) ;
	transMat[3][0] = direction.x;
	transMat[3][1] = direction.y;
	transMat[3][2] = direction.z;
	transMat[0][0] = 1.0f;transMat[1][1] = 1.0f;transMat[2][2] = 1.0f;transMat[3][3] = 1.0f;
}

void HeyRenderer::RotateMat_X(const float rotAngle)
{
	rotateMat_X = glm::mat4 (0.0f) ;
	rotateMat_X[1][1] = cos(rotAngle);   rotateMat_X[1][2] = sin(rotAngle);
	rotateMat_X[2][1] = -sin(rotAngle);  rotateMat_X[2][2] = cos(rotAngle);
	rotateMat_X[0][0] = 1.0f;            rotateMat_X[3][3] = 1.0f;
}

void HeyRenderer::RotateMat_Y(const float rotAngle)
{
	rotateMat_Y = glm::mat4 (0.0f) ;
	rotateMat_Y[0][0] = cos(rotAngle);   rotateMat_Y[0][2] = -sin(rotAngle);
	rotateMat_Y[2][0] = sin(rotAngle);   rotateMat_Y[2][2] = cos(rotAngle);
	rotateMat_Y[1][1] = 1.0f;            rotateMat_Y[3][3] = 1.0f;

}

void HeyRenderer::RotateMat_Z(const float rotAngle)
{
	rotateMat_Z = glm::mat4 (0.0f) ;
	rotateMat_Z[0][0] = cos(rotAngle);   rotateMat_Z[0][1] = sin(rotAngle);
	rotateMat_Z[1][0] = -sin(rotAngle);  rotateMat_Z[1][1] = cos(rotAngle);
	rotateMat_Z[2][2] = 1.0f;            rotateMat_Z[3][3] = 1.0f;

}

void HeyRenderer::ScalingMat(const glm::vec3 scalingVal)
{
	scalingMat = glm::mat4(0.0f) ;
        scalingMat[0][0] = scalingVal.x;
        scalingMat[1][1] = scalingVal.y;
        scalingMat[2][2] = scalingVal.z;
        scalingMat[3][3] = 1.0f;

}

void HeyRenderer::ShearMat(const float shearVal)
{
	shearMat = glm::mat4 (0.0f) ;
        shearMat[1][0] = tan(M_PI_2 - shearVal);
        shearMat[0][0] = 1.0f;
        shearMat[1][1] = 1.0f;
        shearMat[2][2] = 1.0f;
        shearMat[3][3] = 1.0f;

}


//
void HeyRenderer::TransMesh(glm::vec3 direction, Mesh &ctlMesh)
{
	glm::vec4 position ;
	TransMat(direction);
	for(int i = 0; i <ctlMesh.vertices.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position =  transMat * position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.worldPos += direction;
}

void HeyRenderer::RotateMesh_X(float rotAngle, Mesh &ctlMesh)
{
	glm::vec4 position ;
	
	//move back to world center then rotate
	TransMat(-ctlMesh.worldPos);
	RotateMat_X(rotAngle);
	rotateMat_X = rotateMat_X * transMat;
	TransMat(ctlMesh.worldPos);
	rotateMat_X = transMat * rotateMat_X;

	for(int i = 0; i< ctlMesh.vertices.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position =  rotateMat_X * position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.worldRot.x =  rotAngle;
	
}

void HeyRenderer::RotateMesh_Y(float rotAngle, Mesh &ctlMesh)
{
	glm::vec4 position ;

	//move back to world center then rotate
	TransMat(-ctlMesh.worldPos);
	RotateMat_Y(rotAngle);
	rotateMat_Y = rotateMat_Y * transMat;
	TransMat(ctlMesh.worldPos);
	rotateMat_Y = transMat * rotateMat_Y;

	RotateMat_Y(rotAngle);
	for(int i = 0; i< ctlMesh.vertices.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position =  rotateMat_Y * position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.worldRot.y =  rotAngle;
}

void HeyRenderer::RotateMesh_Z(float rotAngle, Mesh &ctlMesh)
{
	glm::vec4 position ;

	//move back to world center then rotate
	TransMat(-ctlMesh.worldPos);
	RotateMat_Z(rotAngle);
	rotateMat_Z = rotateMat_Z * transMat;
	TransMat(ctlMesh.worldPos);
	rotateMat_Z = transMat * rotateMat_Z;

	for(int i = 0; i< ctlMesh.vertices.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position =  rotateMat_Z * position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.worldRot.z =  rotAngle;
}
void HeyRenderer::ScalingMesh(glm::vec3 scalingVal, Mesh &ctlMesh)
{
	glm::vec4 position ;
	ScalingMat(scalingVal);
	for(int i = 0; i< ctlMesh.vertices.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position =  scalingMat * position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.backOriginScale -= scalingVal;

}
void HeyRenderer::ShearMesh(float shearVal, Mesh &ctlMesh)
{
	glm::vec4 position ;
	ShearMat(shearVal);
	for(int i = 0; i< ctlMesh.vertices.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position =  shearMat * position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.backShear = -shearVal;
}
