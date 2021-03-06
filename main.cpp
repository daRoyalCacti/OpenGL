#include "iostream"

//glad must be included before GLWF
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "callbacks.h"
#include "global.h"
#include "inputs.h"
#include "errors.h"

#include "scenes.h"
#include "debug.h"




int main() {
	//init
	//=========================================================================================================================================
	glfwInit();	//intitalising GLFW
	//configuring GLFW
	//glfwWindowHint(<what option to configure (takes some enums)>, <integer that sets the value>)
	//https://www.glfw.org/docs/latest/window.html#window_hints	(for options)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);		//telling GLFW the opengl version want to use
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);		//in this case 4.6
								// - GLFW makes proper arrangements when creating the OpenGl context
								// - GLFW failes if whne the user does not have the proper version of OpenGl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//we want to use core-profiling
									// - gets access to a small amount of OpenGl features 
	
	//creating a window object
	GLFWwindow* window = glfwCreateWindow(settings::window_width, settings::window_height, settings::window_name, NULL, NULL);
	if (window == NULL)	//if the window failed to create
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);	//making the windows the main context on the current thread

	//intialising GLAD
	// - required before calling any OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}  

	//tell OpenGL the size and positioning of the viewport inside the window	
	glViewport(settings::viewport_ll, settings::viewport_lr, settings::viewport_width, settings::viewport_height);

	//tell GLFW what to do on window resize
	// - also gets called when the window is first displayed
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	camera_b* cam = new camera_player(glm::vec3(0.0f, 0.0f, 3.0f));
	//camera_b* cam = new camera_rotation(3);

	scenes::cup curr_scene(cam);
	curr_scene.init();



	glEnable(GL_DEPTH_TEST);	//turning on the depth buffer
	glfwSetInputMode(window, GLFW_CURSOR, settings::has_cursor);


	mouse_callback::cam = cam;	//this needs to be set first
	glfwSetCursorPosCallback(window, mouse_callback::callback);



	//render
	//===================================================================================================================================
	
	glPolygonMode(GL_FRONT_AND_BACK, settings::polygon_fill_mode);

	float currTime, prevTime = -1;
	unsigned long frameCounter = 0;
	float deltaTime;

	//the render loop
	// - keeps running until the user says to stop
	while (!glfwWindowShouldClose(window)) {	//was the window instructed to close (e.g. by pressing the 'x')
		currTime = glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		processInput(window, cam, deltaTime);		//processing keyboard and mouse inputs

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//want to clear the color buffer and the depth buffer
							//also possible : GL_STENCIL_BUFFER_BIT


		curr_scene.draw(currTime, frameCounter, deltaTime);
		


		glfwSwapBuffers(window);	//swaps the color buffer (2D buffer that contains color values for each pixel in the window)
						// - shows the output to the screen
						// - has double buffering because single buffering can cause flickering

		glfwPollEvents();		//checks if any events were triggered (e.g. keyboard and mouse inputs)
						// - updates the window states
						// - calls corresponding functions register via callbacks
	}





	//cleanup
	//=================================================================================================================================
	
	glfwTerminate();	//clean/delete all of GLFW's resources that were allocated


	return 0;
}
