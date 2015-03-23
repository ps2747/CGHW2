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

HeyRenderer::Mesh my_mesh;

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

    HeyRenderer::LoadObjMesh("monkey.obj", my_mesh);

    //make object farther
    HeyRenderer::TransMesh(glm::vec3(0,0,-1),my_mesh);

    //random set face color
    HW2::randSetMeshColor(my_mesh);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
	// Control Objects
	ObjectCtl();

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
    HW2::drawMesh_pers(-0.999,my_mesh);
    //HW2::drawMesh_otho(my_mesh);
}

void ObjectCtl()
{
	direction = glm::vec3 (0.001f);
	//HeyRenderer::TransMesh(direction,my_mesh);
	//HeyRenderer::ScalingMesh(direction, my_mesh);
	HeyRenderer::RotateMesh_X(0.01,my_mesh);
	//HeyRenderer::ShearMesh(0.0001,my_mesh);
}
