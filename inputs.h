#pragma once

#include <GLFW/glfw3.h>
#include "camera.h"

void processInput(GLFWwindow* window, camera_b *cam, float delta_time) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	{	//if the escaped key is pressed, close the window
									//if the key is not pressed glfwGetKey returns GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);	//saying the window should close
	}

	cam->process_inputs(window, delta_time);
}
