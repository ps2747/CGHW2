#ifndef OBJ_TOOL_H
#define OBJ_TOOL_H

#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>


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
	std::vector<glm::vec2> catch_uvs;
	std::vector<glm::vec3> catch_normals;
	std::vector<std::vector <unsigned int >> fVertexIndices;

}

#endif //OBJ_TOOL_H
