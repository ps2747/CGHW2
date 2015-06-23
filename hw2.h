#ifndef _HW1_H_
#define _HW1_H_


#include <glm/glm.hpp>
#include "Mesh.h"

namespace HW2
{
	static bool isFlat = 0;
	void drawCircle(float x, float y, float r, int seg);
	void drawMesh_otho(const HeyRenderer::Mesh &in);
	void drawMesh_pers(const float near, const float far ,const HeyRenderer::Mesh &in);
	void drawMesh_pers_ground(const float near, const float far ,const HeyRenderer::Mesh &in);

	void randSetMeshColor(HeyRenderer::Mesh &);
	void litDirLight(glm::vec3 dir);
	void setFlat(bool set);

	glm::vec3 pixelLighting(glm::vec3 n, glm::vec3 v);

	// design your function interface here
	// ex.
	// Mesh *loadMesh(const char *filename)
	// void drawMesh(Mesh *) or someMeshObject->draw()
	// (You need to complete Mesh class on your own)
}

#endif
