#pragma once

namespace settings {
	//setting attributes for the main window
	constexpr unsigned window_width = 800;
	constexpr unsigned window_height = 600;
	const char* window_name = "OpenGL Window";

	//derived from other settings
	//==========================================
	
	//attributes for the viewport used for the main window
	constexpr unsigned viewport_ll = 0;
	constexpr unsigned viewport_lr = 0;
	constexpr unsigned viewport_width = window_width;
	constexpr unsigned viewport_height = window_height;
};
