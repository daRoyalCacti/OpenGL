#pragma once

#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	{	//if the escaped key is pressed, close the window
									//if the key is not pressed glfwGetKey returns GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);	//saying the window should close
	}
}
