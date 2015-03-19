#include "Obj_Tool.h"

//public:

Obj_Tool::Obj_Tool()
{
	catch_fVertexIndices.resize(4);
}

void Obj_Tool::LoadObj(const char *path)
{
	printf("Loading OBJ file %s ... \n",path);
	std::vector <unsigned int > vertexIndices,uvIndices,normalIndices;
	std::vector <glm::vec3> temp_vertices;
	std::vector <glm::vec2> temp_uvs;
	std::vector <glm::vec3> temp_normals;

	FILE * file = fopen(path,"r");

	if(file == NULL){
		printf("Error load file!!\n");
		return false;
	}

	while(1){
		char lineHeader[128];
		//read the first word of the line
		int res = fscanf(file, "%s",lineHeader);
		if(res == EOF)
		break;//EOF = End of File . Quit the loop

		//else : parse lineHeader

		if(strcmp (lineHeader, "v") == 0){
			cout<<"Get v"<<endl;
			glm::vec3 vertex;
			fscanf(file , "%f %f %f\n", &vertex.x,&vertex.y,&vertex.z);
			temp_vertices.push_back(vertex);
		}
		/*else if (strcmp(lineHeader, "vt") == 0	){
			cout<<"Get vt"<<endl;
			glm::vec2 uv;
			fscanf(file,"%f %f\n",  &uv.x, &uv.y);
			uv.y = -uv.y;//Invert V coordinate since we will only use DDs texture, which are inverted .Remove if you want to use TGA or BMP loaders
			temp_uvs.push_back(uv);
		}*/
		/*else if (strcmp(lineHeader, "vn") == 0){
			cout<<"Get vn"<<endl;
			glm::vec3 normal;
			fscanf(file , "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}*/
		else if (strcmp(lineHeader , "f") == 0){
			cout<<"Get f"<<endl;
			unsigned int vertexIndex[4];
			int matches = fscanf(file, "%d %d %d %d %d\n", &vertexIndex[0], &vertexIndex[1],&vertexIndex[2], &vertexIndex[3]);

			catch_fVertexIndices.push.push_back(vertexIndex);
		}
		else {
			//Probably a comment , eat up the rest of the line
			char commentBuffer[1000];
			fgets(commentBuffer, 1000,file);
		}

	}

	//For each vertex of each triangle
/*	for( unsigned int i = 0; i < vertexIndices.size(); ++i ){
		
		//Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int normalIndex = normalIndices[i];

		//Get the attributes by index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec3 normal = temp_normals[nromalIndex - 1];

		//Put the attribute in buffers
		catch_vertices.push_back(vertex);
		catch_normals.push_back(normal);
	}*/
	
}

void Obj_Tool::getVertices(std::vector<glm::vec3> &);
void Obj_Tool::getUvs(std::vector<glm::vec2> &);
void Obj_Tool::getNormals(std::vector<glm::vec3> &);
void Obj_Tool::getfVertexIndices(std::vector<std::vector <unsigned int >> &out_fVertexIndices)
{
	out_fVertexIndices.assign(catch_fVertexIndices.begin(),catch_fVertexIndices.end());

}


















