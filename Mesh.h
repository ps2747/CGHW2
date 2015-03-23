#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"

namespace HeyRenderer
{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<int> indices;//Vertices which construct a triangle
		//Provide a way to make Mesh stay in origin status
		glm::vec3 	worldPos;//catch backward translation
		glm::vec3	worldRot;//catch backward rotation
		glm::vec3	backOriginScale;
		float		backShear;
	};
}

#endif
