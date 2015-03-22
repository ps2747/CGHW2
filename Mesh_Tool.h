#ifndef MESH_TOOL_H_
#define MESH_TOOL_H_

#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"
#include "Mesh.h"

namespace HeyRenderer
{
	void TransMesh(glm::vec3 direction, Mesh &ctlMesh);
	void RotateMesh(float rotAngle, Mesh &ctlMesh);
	void ScalingMesh(glm::vec3 scalingVal, Mesh &ctlMesh);
	void ShearMesh(float shearVal, Mesh &ctlMesh);
}


#endif
