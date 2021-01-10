#pragma once

#include <glad/glad.h>

namespace settings {
	//consts
	//=======================================
	//setting attributes for the main window
	constexpr unsigned window_width = 800;
	constexpr unsigned window_height = 600;
	const char* window_name = "OpenGL Window";

	//when the window is cleared (likely every frame) what color should the window become
	/*constexpr float window_clear_color_r = 0.2f;
	constexpr float window_clear_color_g = 0.3f;
	constexpr float window_clear_color_b = 0.3f;
	constexpr float window_clear_color_a = 1.0f;*/

	constexpr GLenum polygon_fill_mode = GL_FILL;	//possibilities:
							// - GL_LINE for wireframe
							// - GL_FILL for regular filled triangles
	
	constexpr float near_plane = 0.1f;
	constexpr float far_plane = 100.0f;
	constexpr float fov = 45.0f;

	constexpr int has_cursor = GLFW_CURSOR_DISABLED;

	//derived from other settings
	//==========================================
	
	//attributes for the viewport used for the main window
	constexpr unsigned viewport_ll = 0;
	constexpr unsigned viewport_lr = 0;
	constexpr unsigned viewport_width = window_width;
	constexpr unsigned viewport_height = window_height;
};
