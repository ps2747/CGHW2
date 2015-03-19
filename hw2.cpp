#include "hw2.h"
#include "glwrapper.h"
#include <cmath>
#include "Mesh.h"

#ifndef M_PI
#define M_PI    3.1415926535
#endif

void HW2::drawCircle(float x, float y, float r, int seg)
{
    // Complete your code here
}

void HW2::drawMesh(const HeyRenderer::Mesh &in)
{
	for(int i=0; i<in.indices.size(); i+=3)
	{
		const glm::vec3 &o=in.vertices[in.indices[i]].pos;
		const glm::vec3 &a=in.vertices[in.indices[i+1]].pos;
		const glm::vec3 &b=in.vertices[in.indices[i+2]].pos;
		GLWrapper::drawLine(o.x, o.y, a.x, a.y);
		GLWrapper::drawLine(o.x, o.y, b.x, b.y);
		GLWrapper::drawLine(b.x, b.y, a.x, a.y);
	}
}
