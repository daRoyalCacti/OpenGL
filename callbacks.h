#pragma once

#include <GLFW/glfw3.h>
#include "global.h"

#include "camera.h"

//what happens when the user resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	const float change_x = width / float(settings::window_width);
	const float change_y = height / float(settings::window_height);

	//changing the viewport
	// - keeping the viewport the same proportion of the screen as was originally set
	glViewport(change_x * settings::viewport_ll, change_y * settings::viewport_lr, change_x * settings::window_width, change_y * settings::window_height);
}

namespace mouse_callback {
	camera_b *cam;

	void callback(GLFWwindow* window, double xpos, double ypos) {
		cam->process_mouse(window, xpos, ypos);
	}


}
