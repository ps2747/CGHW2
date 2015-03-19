#ifndef OBJ_TOOL_H
#define OBJ_TOOL_H

#include <glm/glm.hpp>
#include "Mesh.h"

namespace HeyRenderer
{
	void LoadObjMesh(const char *filename, Mesh &out);
	
}
/*
class Obj_Tool
{
public:
	Obj_Tool();
	void LoadObj(const char *);
	void getVertices(std::vector<glm::vec3> &);
	void getUvs(std::vector<glm::vec2> &);
	void getNormals(std::vector<glm::vec3> &);
	void getfVertexIndices(std::vector<std::vector <unsigned int >> &);

private:
	std::vector<glm::vec3> catch_vertices;
//	std::vector<glm::vec2> catch_uvs;
//	std::vector<glm::vec3> catch_normals;
	std::vector<std::vector <unsigned int >> fVertexIndices;

}*/

#endif //OBJ_TOOL_H
