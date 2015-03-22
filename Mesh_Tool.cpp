#include "Mesh_Tool.h"

void HeyRenderer::TransMesh(glm::vec3 direction, Mesh &ctlMesh)
{
	glm::vec4 position ;
	glm::mat4 transMod = glm::vec4(0.0,0.0,0.0,0.0) ;
	transMod[0][3] = direction[0];
	transMod[1][3] = direction[1];
	transMod[2][3] = direction[2];
	transMod[0][0] = 1.0;transMod[1][1] = 1.0;transMod[2][2] = 1.0;transMod[3][3] = 1.0;
	for(int i = 0; i <ctlMesh.pos.size(); ++i){
		position = glm::vec4(ctlMesh.vertices[i].pos,1.0);
		position = transMod*position;
		ctlMesh.vertices[i].pos = position.xyz();
	}
	ctlMesh.backShift = -direction;
}
void HeyRenderer::RotateMesh(glm::vec2 rotAngle, Mesh &ctlMesh)
{
	
}
void HeyRenderer::ScalingMesh(glm::vec3 scalingVal, Mesh &ctlMesh)
void HeyRenderer::ShearMesh(std::vector shearVal, Mesh &ctlMesh)
