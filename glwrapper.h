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

	void clearScreen();
	void glDrawFrame(int f_height , int f_width, Buffer c_buffer);
	void drawPoint(glm::vec3 pos, glm::vec3 color, Buffer c_buffer);
	void drawLine(glm::vec3 pos_1, glm::vec3 color_1, glm::vec3 pos_2, glm::vec3 color_2,Buffer c_buffer);
	void drawTriangle(glm::vec3 pos_1, glm::vec3 color_1, glm::vec3 pos_2, glm::vec3 color_2, glm::vec3 pos_3, glm::vec3 color_3, Buffer c_buffer);
	void drawTriangle(glm::vec3 pos_1, float originZ_1, glm::vec3 color_1, glm::vec3 pos_2, float originZ_2, glm::vec3 color_2, glm::vec3 pos_3,  float originZ_3, glm::vec3 color_3, Buffer c_buffer);
	
}
	

#endif
