#define GLM_SWIZZLE //for use of glm::vec4 .xyz();

#include "Mesh_Tool.h"
#include <math.h>


void HeyRenderer::TransMesh(glm::vec3 direction, Mesh &ctlMesh)
{
	glm::vec4 position ;
	glm::mat4 transMod (0.0f) ;
	transMod[0][3] = direction[0];
	transMod[1][3] = direction[1];
	transMod[2][3] = direction[2];
	transMod[0][0] = 1.0;transMod[1][1] = 1.0;transMod[2][2] = 1.0;transMod[3][3] = 1.0;
	for(int i = 0; i <ctlMesh.vertices.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position = transMod*position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.backTrans = -direction;
}
void HeyRenderer::RotateMesh(float rotAngle, Mesh &ctlMesh)
{
	glm::vec4 position ;
	glm::mat4 rotMod (0.0f) ;
	rotMod[0][0] = cos(rotAngle);	rotMod[0][1] = -sin(rotAngle);
	rotMod[1][0] = sin(rotAngle); 	rotMod[1][1] = cos(rotAngle);
	rotMod[2][2] = 1.0;		rotMod[3][3] = 1.0;
	for(int i = 0; i< ctlMesh.vertices.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position =  rotMod * position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.backRot = - rotAngle;

}
void HeyRenderer::ScalingMesh(glm::vec3 scalingVal, Mesh &ctlMesh)
{
	glm::vec4 position ; 
	glm::mat4 scaleMod (0.0f) ;
	scaleMod[0][0] = scalingVal.x;
	scaleMod[1][1] = scalingVal.y;
	scaleMod[2][2] = scalingVal.z;
	scaleMod[3][3] = 1.0;
	for(int i = 0; i< ctlMesh.vertices.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position =  scaleMod * position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.backScale = - scalingVal;

}
void HeyRenderer::ShearMesh(float shearVal, Mesh &ctlMesh)
{
	glm::vec4 position ;
	glm::mat4 shearMod (0.0f) ;
	shearMod[0][1] = tan(M_PI_2 - shearVal);
	shearMod[0][0] = 1.0;
	shearMod[1][1] = 1.0;
	shearMod[2][2] = 1.0;
	shearMod[3][3] = 1.0;

	for(int i = 0; i< ctlMesh.vertices.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position =  shearMod * position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.backShear = -shearVal;
}
