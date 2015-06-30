#include <GLFW/glfw3.h>
#include <cstdlib>
#include <glm/glm.hpp>

#include "hw2.h"
#include "glwrapper.h"
#include "Mesh.h"
#include "Obj_Tool.h"
#include "Mesh_Tool.h"


static void render();
void ObjectCtl();
bool isGround = false ;
static int mode ;

HeyRenderer::Mesh my_mesh;
HeyRenderer::Mesh mesh_1;
HeyRenderer::Mesh mesh_2;
HeyRenderer::Mesh mesh_3;

bool mesh_1_enable = false;
bool mesh_2_enable = true;
bool mesh_3_enable = false;

int rotateMode = 0;
int scalingMode = 0;


glm::vec3 direction;

static void ObjectCtl(GLFWwindow *window, int key , int scancode,int action,int mods);

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(320, 320, "CGHW2", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    //Set control  
    mode =1;
    glfwSetKeyCallback(window , ObjectCtl);
    
    HeyRenderer::LoadObjMesh("low_ICO.obj", mesh_1);
    HeyRenderer::LoadObjMesh("monkey.obj", mesh_2);
    HeyRenderer::LoadObjMesh("cube.obj", mesh_3);

    //make object farther
    HeyRenderer::TransMesh(glm::vec3(0,0,-1),mesh_1);
    HeyRenderer::TransMesh(glm::vec3(0,0,-1),mesh_2);
    HeyRenderer::TransMesh(glm::vec3(0,0,-1),mesh_3);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {

        // Render here
        render();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

static void render()
{
    GLWrapper::clearScreen();
    // Complete your code here
    // if a is press??
    //HW2::drawCircle(0, 0, 0.25, 200);
    // else draw Mode
    if(isGround)	{
    	if(mesh_1_enable)
    		HW2::drawMesh_pers_ground(-0.999, 10,mesh_1);	
    	if(mesh_2_enable)
    		HW2::drawMesh_pers_ground(-0.999, 10,mesh_2);	
    	if(mesh_3_enable)
    		HW2::drawMesh_pers_ground(-0.999, 10,mesh_3);	
    }
    else 	{
    	if(mesh_1_enable)
    		HW2::drawMesh_pers(-0.999, 10,mesh_1);
    	if(mesh_2_enable)
    		HW2::drawMesh_pers(-0.999, 10,mesh_2);
    	if(mesh_3_enable)
    		HW2::drawMesh_pers(-0.999, 10,mesh_3);
    }
    HW2::litDirLight(glm::vec3(1.0f, 1.0f, 0.0f));
    GLWrapper::glDrawFrame(320 , 320, GLWrapper::FBUFFER);
    //HW2::drawMesh_otho(my_mesh);
}


static void keyCallBack(GLFWwindow *window, int key , int scancode,int action,int mods);
static void ObjectCtl(GLFWwindow *window, int key , int scancode,int action,int mods)
{

	if(mode == 1){//Trans mode
		if(key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (0.0f,0.003f,0.0f);
		}
		if(key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (-0.003f,0.0f,0.0f);
		}
		if(key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (0.0f,-0.003f,0.0f);
		}
		if(key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (0.003f,0.0f,0.0f);
		}
		if(mesh_1_enable)
			HeyRenderer::TransMesh(direction,mesh_1);
		if(mesh_2_enable)
			HeyRenderer::TransMesh(direction,mesh_2);
		if(mesh_3_enable)
			HeyRenderer::TransMesh(direction,mesh_3);

		if(key == GLFW_KEY_2 && action == GLFW_RELEASE){
			mode = 2;
		}
		if(key == GLFW_KEY_3 && action == GLFW_RELEASE){
			mode = 3;
			scalingMode = 0;
		}
		if(key == GLFW_KEY_4 && action == GLFW_RELEASE){
			mode = 4;
		}
		if(key == GLFW_KEY_5 && action == GLFW_RELEASE){
			HW2::setFlat(false);
			isGround = false;
		}
		if(key == GLFW_KEY_6 && action == GLFW_RELEASE){
			HW2::setFlat(true);
			isGround = false;
		}
		if(key == GLFW_KEY_7 && action == GLFW_RELEASE){
			isGround = true;
		}
	}

	if(mode == 2){//Rotate mode
		if(key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			if(mesh_1_enable)
				HeyRenderer::RotateMesh_X(0.03,mesh_1);
			if(mesh_2_enable)
				HeyRenderer::RotateMesh_X(0.03,mesh_2);
			if(mesh_3_enable)
				HeyRenderer::RotateMesh_X(0.03,mesh_3);
		}
		if(key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			if(rotateMode == 0){
				if(mesh_1_enable)
					HeyRenderer::RotateMesh_Y(-0.03,mesh_1);
				if(mesh_2_enable)
					HeyRenderer::RotateMesh_Y(-0.03,mesh_2);
				if(mesh_3_enable)
					HeyRenderer::RotateMesh_Y(-0.03,mesh_3);
			}
			else{ 
				if(mesh_1_enable)
					HeyRenderer::RotateMesh_Z(-0.03,mesh_1);
				if(mesh_2_enable)
					HeyRenderer::RotateMesh_Z(-0.03,mesh_2);
				if(mesh_3_enable)
					HeyRenderer::RotateMesh_Z(-0.03,mesh_3);
			}
		}
		if(key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			if(mesh_1_enable)
				HeyRenderer::RotateMesh_X(-0.03,mesh_1);
			if(mesh_2_enable)
				HeyRenderer::RotateMesh_X(-0.03,mesh_2);
			if(mesh_3_enable)
				HeyRenderer::RotateMesh_X(-0.03,mesh_3);
		}
		if(key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			if(rotateMode == 0){
				if(mesh_1_enable)
					HeyRenderer::RotateMesh_Y(0.03,mesh_1);
				if(mesh_2_enable)
					HeyRenderer::RotateMesh_Y(0.03,mesh_2);
				if(mesh_3_enable)
					HeyRenderer::RotateMesh_Y(0.03,mesh_3);
			}
			else {
				if(mesh_1_enable)
					HeyRenderer::RotateMesh_Z(0.03,mesh_1);
				if(mesh_2_enable)
					HeyRenderer::RotateMesh_Z(0.03,mesh_2);
				if(mesh_3_enable)
					HeyRenderer::RotateMesh_Z(0.03,mesh_3);
			}
		}
		if(key == GLFW_KEY_1 && action == GLFW_RELEASE){
			mode = 1;
		}
		if(key == GLFW_KEY_2 && action == GLFW_RELEASE){
			rotateMode ++;
			rotateMode = rotateMode %2;
		}
		if(key == GLFW_KEY_3 && action == GLFW_RELEASE){
			mode = 3;
			scalingMode = 0;
		}
		if(key == GLFW_KEY_4 && action == GLFW_RELEASE){
			mode = 4;
		}
		if(key == GLFW_KEY_5 && action == GLFW_RELEASE){
			HW2::setFlat(false);
			isGround = false;
		}
		if(key == GLFW_KEY_6 && action == GLFW_RELEASE){
			HW2::setFlat(true);
			isGround = false;
		}
		if(key == GLFW_KEY_7 && action == GLFW_RELEASE){
			isGround = true;
		}
	}

	if(mode == 3){//Scaling mode
		direction = glm::vec3 (1.0f,1.0f,1.0f);
		if(key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			switch(scalingMode){
				case 0 : direction = glm::vec3 (1.012f); break;
				case 1 : direction = glm::vec3 (1.012f, 1.0f, 1.0f); break;
				case 2 : direction = glm::vec3 (1.0f, 1.012f, 1.0f); break;
				case 3 : direction = glm::vec3 (1.0f, 1.0f, 1.012f); break;
			}
		}
		if(key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			switch(scalingMode){
				case 0 : direction = glm::vec3 (0.988f); break;
				case 1 : direction = glm::vec3 (0.988f, 1.0f, 1.0f); break;
				case 2 : direction = glm::vec3 (1.0f, 0.988f, 1.0f); break;
				case 3 : direction = glm::vec3 (1.0f, 1.0f, 0.988f); break;
			}
		}
		if(key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			switch(scalingMode){
				case 0 : direction = glm::vec3 (0.988f); break;
				case 1 : direction = glm::vec3 (0.988f, 1.0f, 1.0f); break;
				case 2 : direction = glm::vec3 (1.0f, 0.988f, 1.0f); break;
				case 3 : direction = glm::vec3 (1.0f, 1.0f, 0.988f); break;
			}
		}
		if(key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			switch(scalingMode){
				case 0 : direction = glm::vec3 (1.012f); break;
				case 1 : direction = glm::vec3 (1.012f, 1.0f, 1.0f); break;
				case 2 : direction = glm::vec3 (1.0f, 1.012f, 1.0f); break;
				case 3 : direction = glm::vec3 (1.0f, 1.0f, 1.012f); break;
			}
		}

		if(mesh_1_enable)
			HeyRenderer::ScalingMesh(direction, mesh_1);
		if(mesh_2_enable)
			HeyRenderer::ScalingMesh(direction, mesh_2);
		if(mesh_3_enable)
			HeyRenderer::ScalingMesh(direction, mesh_3);
		

		if(key == GLFW_KEY_2 && action == GLFW_RELEASE){
			mode = 2;
		}
		if(key == GLFW_KEY_1 && action == GLFW_RELEASE){
			mode = 1;
		}
		if(key == GLFW_KEY_3 && action == GLFW_RELEASE){
			scalingMode ++;
			scalingMode %= 4;
		}

		if(key == GLFW_KEY_4 && action == GLFW_RELEASE){
			mode = 4;
		}

		if(key == GLFW_KEY_5 && action == GLFW_RELEASE){
			HW2::setFlat(false);
			isGround = false;
		}
		if(key == GLFW_KEY_6 && action == GLFW_RELEASE){
			HW2::setFlat(true);
			isGround = false;
		}
		if(key == GLFW_KEY_7 && action == GLFW_RELEASE){
			isGround = true;
		}
	}
	if(mode == 4){//Sheering mode
		if(key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			if(mesh_1_enable)
				ShearMesh(0.01f , mesh_1);
			if(mesh_2_enable)
				ShearMesh(0.01f , mesh_2);
			if(mesh_3_enable)
				ShearMesh(0.01f , mesh_3);
		}
		if(key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			if(mesh_1_enable)
				ShearMesh(-0.01f , mesh_1);
			if(mesh_2_enable)
				ShearMesh(-0.01f , mesh_2);
			if(mesh_3_enable)
				ShearMesh(-0.01f , mesh_3);
		}
		if(key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			if(mesh_1_enable)
				ShearMesh(-0.01f , mesh_1);
			if(mesh_2_enable)
				ShearMesh(-0.01f , mesh_2);
			if(mesh_3_enable)
				ShearMesh(-0.01f , mesh_3);
		}
		if(key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			if(mesh_1_enable)
				ShearMesh(0.01f , mesh_1);
			if(mesh_2_enable)
				ShearMesh(0.01f , mesh_2);
			if(mesh_3_enable)
				ShearMesh(0.01f , mesh_3);
		}

		if(key == GLFW_KEY_2 && action == GLFW_RELEASE){
			mode = 2;
		}
		if(key == GLFW_KEY_1 && action == GLFW_RELEASE){
			mode = 1;
		}
		if(key == GLFW_KEY_3 && action == GLFW_RELEASE){
			mode = 3;
			scalingMode = 0;
		}

		if(key == GLFW_KEY_5 && action == GLFW_RELEASE){
			HW2::setFlat(false);
			isGround = false;
		}
		if(key == GLFW_KEY_6 && action == GLFW_RELEASE){
			HW2::setFlat(true);
			isGround = false;
		}
		if(key == GLFW_KEY_7 && action == GLFW_RELEASE){
			isGround = true;
		}
	}
}
