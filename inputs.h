#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"

namespace key_presses {
	bool x = false;
}

namespace input_vars {
	bool draw_line = settings::polygon_fill_mode == GL_LINE ? 0 : 1;
}


void processInput(GLFWwindow* window, camera_b *cam, float delta_time) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	{	//if the escaped key is pressed, close the window
									//if the key is not pressed glfwGetKey returns GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);	//saying the window should close
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && !key_presses::x) {
		key_presses::x = true;
		if (input_vars::draw_line) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		input_vars::draw_line = !input_vars::draw_line;
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) {
		key_presses::x = false;
		//input_vars::draw_line = !input_vars::draw_line;
	}

	cam->process_inputs(window, delta_time);
}
