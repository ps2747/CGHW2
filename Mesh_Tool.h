#ifndef MESH_TOOL_H_
#define MESH_TOOL_H_

#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"
#include "Mesh.h"

namespace HeyRenderer
{
	//static access Matrices
	static glm::mat4 transMat,rotateMat_X,rotateMat_Y,rotateMat_Z,scalingMat,shearMat;


	//Clear the matrices to default
	void ClearMat();

	//generate transform matrices
	void TransMat(glm::vec3 direction);
	void RotateMat_X(float rotAngle);
	void RotateMat_Y(float rotAngle);
	void RotateMat_Z(float rotAngle);
	void ScalingMat(glm::vec3 scalingVal);
	void ShearMat(float shearVal);

	//Matrices apply to Mesh vertices
	void TransMesh(glm::vec3 direction, Mesh &ctlMesh);
	void RotateMesh_X(float rotAngle, Mesh &ctlMesh);
	void RotateMesh_Y(float rotAngle, Mesh &ctlMesh);
	void RotateMesh_Z(float rotAngle, Mesh &ctlMesh);
	void ScalingMesh(glm::vec3 scalingVal, Mesh &ctlMesh);
	void ShearMesh(float shearVal, Mesh &ctlMesh);
}


#endif
