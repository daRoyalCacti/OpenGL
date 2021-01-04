#pragma once

#include "shader.h"

namespace shaders {
	inline shader_b toy() {
		//vertex shader code
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main(){\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		//fragment shader code
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main(){\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";
		
		shader_b temp_shader;
		temp_shader.set_shaders(vertexShaderSource, fragmentShaderSource);
		return temp_shader;
	}

	inline shader_b toy1() {
		//vertex shader code
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main(){\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		//fragment shader code
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main(){\n"
			"   FragColor = vec4(0.74f, 0.71f, 0.0f, 1.0f);\n"
			"}\n\0";
		
		shader_b temp_shader;
		temp_shader.set_shaders(vertexShaderSource, fragmentShaderSource);
		return temp_shader;
	}

};
