#include "Obj_Tool.h"
#include <cstdio>

#define BUFFER_SIZE 128

typedef bool (*PROCESS_FUNC)(char *, HeyRenderer::Mesh &);

static bool process_v(char *linebuffer, HeyRenderer::Mesh &out);
static bool process_f(char *linebuffer, HeyRenderer::Mesh &out);

static PROCESS_FUNC pfunc_ptr[]=
{
process_v, process_f
};

void HeyRenderer::LoadObjMesh(const char *filename, Mesh &out)
{
	char linebuffer[BUFFER_SIZE];
	FILE *fp = fopen(filename, "r");

	while(!feof(fp))
	{
		fgets(linebuffer, BUFFER_SIZE, fp);
		for(int i=0;i<2;i++)
			if(pfunc_ptr[i](linebuffer, out))
				break;
	}

	fclose(fp);
}

static bool process_v(char *linebuffer, HeyRenderer::Mesh &out)
{
	HeyRenderer::Vertex v;
	if(sscanf(linebuffer, "v %f %f %f", &v.pos.x, &v.pos.y, &v.pos.z)!=3)
		return false;
	
	out.vertices.push_back(v);

	return true;
}
static bool process_f(char *linebuffer, HeyRenderer::Mesh &out)
{
	unsigned int o, a, b;
	if(sscanf(linebuffer, "f %u %u %u", &o, &a, &b)==3)
	{
		out.indices.push_back(o-1);
		out.indices.push_back(a-1);
		out.indices.push_back(b-1);
		return true;
	}
	return false;
}
