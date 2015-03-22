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
		glm::vec3 	backTrans;//catch backward translation
		glm::vec2	backRot;//catch backward rotation
		glm::vec3	backScale;//catch backward scale
		std::vector 	backShear;//catch backward Shear
	};
}

#endif
