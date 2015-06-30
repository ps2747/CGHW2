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
glm::vec3 direction;
bool isGround = false ;
static int mode ;

HeyRenderer::Mesh my_mesh;
HeyRenderer::Mesh mesh_1;
HeyRenderer::Mesh mesh_2;
HeyRenderer::Mesh mesh_3;

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
    my_mesh = mesh_2;


    //make object farther
    HeyRenderer::TransMesh(glm::vec3(0,0,-1),my_mesh);

    //random set face color
    HW2::randSetMeshColor(my_mesh);

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
    HW2::litDirLight(glm::vec3(1.0f, 1.0f, 0.0f));
    if(isGround)	
    	HW2::drawMesh_pers_ground(-0.999, 10,my_mesh);	
    else 
    	HW2::drawMesh_pers(-0.999, 10,my_mesh);
    GLWrapper::glDrawFrame(320 , 320, GLWrapper::FBUFFER);
    //HW2::drawMesh_otho(my_mesh);
}


static void keyCallBack(GLFWwindow *window, int key , int scancode,int action,int mods);
static void ObjectCtl(GLFWwindow *window, int key , int scancode,int action,int mods)
{

	if(mode == 1){
		if(key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (0.0f,0.003f,0.0f);
			HeyRenderer::TransMesh(direction,my_mesh);
		}
		if(key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (-0.003f,0.0f,0.0f);
			HeyRenderer::TransMesh(direction,my_mesh);
		}
		if(key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (0.0f,-0.003f,0.0f);
			HeyRenderer::TransMesh(direction,my_mesh);
		}
		if(key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (0.003f,0.0f,0.0f);
			HeyRenderer::TransMesh(direction,my_mesh);
		}
		if(key == GLFW_KEY_2 && action == GLFW_RELEASE){
			mode = 2;
		}
		if(key == GLFW_KEY_3 && action == GLFW_RELEASE){
			mode = 3;
		}
		if(key == GLFW_KEY_4 && action == GLFW_RELEASE){
			HW2::setFlat(false);
			isGround = false;
		}
		if(key == GLFW_KEY_5 && action == GLFW_RELEASE){
			HW2::setFlat(true);
			isGround = false;
		}
		if(key == GLFW_KEY_6 && action == GLFW_RELEASE){
			isGround = true;
		}
	}

	if(mode == 2){
		if(key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			HeyRenderer::RotateMesh_X(0.03,my_mesh);
		}
		if(key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			HeyRenderer::RotateMesh_Y(-0.03,my_mesh);	
		}
		if(key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			HeyRenderer::RotateMesh_X(-0.03,my_mesh);
		}
		if(key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			HeyRenderer::RotateMesh_Y(0.03,my_mesh);
		}
		if(key == GLFW_KEY_1 && action == GLFW_RELEASE){
			mode = 1;
		}
		if(key == GLFW_KEY_3 && action == GLFW_RELEASE){
			mode = 3;
		}
		if(key == GLFW_KEY_4 && action == GLFW_RELEASE){
			HW2::setFlat(false);
			isGround = false;
		}
		if(key == GLFW_KEY_5 && action == GLFW_RELEASE){
			HW2::setFlat(true);
			isGround = false;
		}
		if(key == GLFW_KEY_6 && action == GLFW_RELEASE){
			isGround = true;
		}
	}

	if(mode == 3){
		if(key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (1.003f);
			HeyRenderer::ScalingMesh(direction, my_mesh);
		}
		if(key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (0.997f);
			HeyRenderer::ScalingMesh(direction, my_mesh);
		}
		if(key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (0.997f);
			HeyRenderer::ScalingMesh(direction, my_mesh);
		}
		if(key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
			direction = glm::vec3 (1.003f);
			HeyRenderer::ScalingMesh(direction, my_mesh);
		}
		if(key == GLFW_KEY_2 && action == GLFW_RELEASE){
			mode = 2;
		}
		if(key == GLFW_KEY_1 && action == GLFW_RELEASE){
			mode = 1;
		}
		if(key == GLFW_KEY_4 && action == GLFW_RELEASE){
			HW2::setFlat(false);
			isGround = false;
		}
		if(key == GLFW_KEY_5 && action == GLFW_RELEASE){
			HW2::setFlat(true);
			isGround = false;
		}
		if(key == GLFW_KEY_6 && action == GLFW_RELEASE){
			isGround = true;
		}
	}
}
