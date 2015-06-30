#include "Obj_Tool.h"
#include <cstdio>

#define BUFFER_SIZE 128

typedef bool (*PROCESS_FUNC)(char *, HeyRenderer::Mesh &);

static bool process_v(char *linebuffer, HeyRenderer::Mesh &out);
static bool process_vn(char *linebuffer, HeyRenderer::Mesh &out);
static bool process_f(char *linebuffer, HeyRenderer::Mesh &out);

static int vnCount ;

static PROCESS_FUNC pfunc_ptr[]=
{
process_v,process_vn, process_f
};

static glm::vec3 normalize(glm::vec3 in)
{
	float d = sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
	return in / d;
}

static glm::vec3 cross(glm::vec3 a, glm::vec3 b)
{
	glm::vec3 c ;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return c;
}

static std::vector<glm::vec3> normalPool;

void HeyRenderer::LoadObjMesh(const char *filename, Mesh &out)
{
	char linebuffer[BUFFER_SIZE];
	FILE *fp = fopen(filename, "r");

	if(!fp) printf("File not found\n");
	vnCount = 0;
	while(!feof(fp))
	{
		fgets(linebuffer, BUFFER_SIZE, fp);
		for(int i=0;i<3;i++)
			if(pfunc_ptr[i](linebuffer, out))
				break;
	}

	for(int i = 0 ;i < out.vertices.size(); i ++)
		out.vertices[i].normal = normalize(out.vertices[i].normal);

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

static bool process_vn(char *linebuffer, HeyRenderer::Mesh &out)
{
	glm::vec3 vn;
	if(sscanf(linebuffer, "vn %f %f %f", &vn.x, &vn.y, &vn.z)!=3)
		return false;
	normalPool.push_back(vn);
	return true;
}

static bool process_f(char *linebuffer, HeyRenderer::Mesh &out)
{
	unsigned int o, a, b, c, on , an , bn;
	if(sscanf(linebuffer, "f %u//%u %u//%u%u//%u", &o,&on , &a, &an, &b, &bn)== 6)
	{
		out.indices.push_back(o-1);
		out.indices.push_back(a-1);
		out.indices.push_back(b-1);

		out.vertices[o - 1].normal  += normalPool[on -1];
		out.vertices[a - 1].normal += normalPool[on -1];
		out.vertices[b - 1].normal += normalPool[on -1];
		return true;
	}
	else if (sscanf(linebuffer, "f %u %u %u  %u", &o , &a, &b, &c)== 4)
	{
		out.indices.push_back(o-1);
		out.indices.push_back(a-1);
		out.indices.push_back(c-1);

		out.indices.push_back(a-1);
		out.indices.push_back(b-1);
		out.indices.push_back(c-1);

		out.vertices[o - 1].normal += cross(normalize(out.vertices[a - 1].pos - out.vertices[o - 1].pos) , normalize(out.vertices[c - 1].pos - out.vertices[o - 1].pos));
		out.vertices[a - 1].normal += cross(normalize(out.vertices[c - 1].pos - out.vertices[a - 1].pos) , normalize(out.vertices[o - 1].pos - out.vertices[a - 1].pos));
		out.vertices[c - 1].normal += cross(normalize(out.vertices[o - 1].pos - out.vertices[c - 1].pos) , normalize(out.vertices[a - 1].pos - out.vertices[c - 1].pos));

		out.vertices[a - 1].normal += cross(normalize(out.vertices[b - 1].pos - out.vertices[a - 1].pos) , normalize(out.vertices[c - 1].pos - out.vertices[a - 1].pos));
		out.vertices[b - 1].normal += cross(normalize(out.vertices[c - 1].pos - out.vertices[b - 1].pos) , normalize(out.vertices[a - 1].pos - out.vertices[b - 1].pos));
		out.vertices[c - 1].normal += cross(normalize(out.vertices[a - 1].pos - out.vertices[c - 1].pos) , normalize(out.vertices[b - 1].pos - out.vertices[c - 1].pos));
		return true;
	}
	else if(sscanf(linebuffer, "f %u %u %u", &o , &a, &b)== 3)
	{
		out.indices.push_back(o-1);
		out.indices.push_back(a-1);
		out.indices.push_back(b-1);

		out.vertices[o - 1].normal += cross(normalize(out.vertices[a - 1].pos - out.vertices[o - 1].pos) , normalize(out.vertices[b - 1].pos - out.vertices[o - 1].pos));
		out.vertices[a - 1].normal += cross(normalize(out.vertices[b - 1].pos - out.vertices[a - 1].pos) , normalize(out.vertices[o - 1].pos - out.vertices[a - 1].pos));
		out.vertices[b - 1].normal += cross(normalize(out.vertices[o - 1].pos - out.vertices[b - 1].pos) , normalize(out.vertices[a - 1].pos - out.vertices[b - 1].pos));
		return true;
	}
	return false;
}
