#ifndef _GLWRAPPER_H_
#define _GLWRAPPER_H_

#include <GLFW/glfw3.h>

namespace GLWrapper
{
	enum Buffer {  
		ZBUFFER,
		FBUFFER,
		NBUFFER
	};
	static glm::vec3 zbuffer[320][320];
	static glm::vec3 frameBuffer[320][320];
	static glm::vec3 normalBuffer[320][320];

	static glm::vec3 ambiColor = glm::vec3(0.3f,0.3f,0.3f);
	static glm::vec3 diffColor = glm::vec3(0.5f,0.5f,0.5f);

	void clearScreen();
	void glDrawFrame(int f_height , int f_width, Buffer c_buffer);
	void drawPoint(glm::vec3 pos, glm::vec3 color, Buffer c_buffer);
	void drawLine(glm::vec3 pos_1, glm::vec3 color_1, glm::vec3 pos_2, glm::vec3 color_2,Buffer c_buffer);
	void drawTriangle(glm::vec3 pos_1, glm::vec3 color_1, glm::vec3 pos_2, glm::vec3 color_2, glm::vec3 pos_3, glm::vec3 color_3, Buffer c_buffer);
	void drawTriangle(glm::vec3 pos_1, float originZ_1, glm::vec3 color_1, glm::vec3 pos_2, float originZ_2, glm::vec3 color_2, glm::vec3 pos_3,  float originZ_3, glm::vec3 color_3, Buffer c_buffer);
	glm::vec3 getBufferElement (int i,int j, Buffer c_buffer);
	void setBufferElement (int i,int j, glm::vec3 input, Buffer c_buffer);
	void litDirLight(glm::vec3 dir);
	void litSetAmbi(float);
	void litSetDiffColor(glm::vec3 );
	void litSetDiffColor_R(float);
	void litSetDiffColor_G(float);
	void litSetDiffColor_B(float);
}
	

#endif
