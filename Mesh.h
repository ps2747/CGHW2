#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"
#include "HeyColor.h"

namespace HeyRenderer
{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<int> indices;//Vertices which construct a triangle
		
		glm::mat4 	transMat;
		//Provide a way to make Mesh stay in origin status
		glm::vec3 	worldPos;//catch backward translation
		glm::vec3	worldRot;//catch backward rotation
		glm::vec3	backOriginScale;
		std::vector<glm::vec3>	faceColor;
		float		backShear;
	};
}

#endif
