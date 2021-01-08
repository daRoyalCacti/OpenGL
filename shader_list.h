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
		
		return shader_b(vertexShaderSource, fragmentShaderSource);
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
		
		return shader_b(vertexShaderSource, fragmentShaderSource);
	}

	inline shader_b fixed_color() {	//example of passing info from the vertex shader to the fragment shader
		//vertex shader code
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"out vec4 vertexColor;\n"	//specify a color output to the fragment shader
			"void main(){\n"
			"   gl_Position = vec4(aPos, 1.0);\n"
			"   vertexColor = vec4(0.5, 0.0, 0.0, 1.0f);"
			"}\0";

		//fragment shader code
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec4 vertexColor;\n"	//from the vertex shader (same name and type)
			"void main(){\n"
			"   FragColor = vertexColor;\n"
			"}\n\0";
		
		return shader_b(vertexShaderSource, fragmentShaderSource);
	}


	inline shader_b color_through_uniforms() {	//example of passing info from the vertex shader to the fragment shader
	
		return shader_b(shader_from_file("../shaders/color_through_uniforms.vert").c_str(), shader_from_file("../shaders/color_through_uniforms.frag").c_str());
	}


	inline shader_c vertex_colors() {	//example of passing info from the vertex shader to the fragment shader
		
		return shader_c	(shader_from_file("../shaders/vertex_colors.vert").c_str(), shader_from_file("../shaders/vertex_colors.frag").c_str());
	}


	inline shader_tc textured_coloured() {	//example of passing info from the vertex shader to the fragment shader
	
		return shader_tc(shader_from_file("../shaders/textured_coloured.vert").c_str(), shader_from_file("../shaders/textured_coloured.frag").c_str());
	}

	inline shader_t textured() {	//example of passing info from the vertex shader to the fragment shader
	
		return shader_t(shader_from_file("../shaders/textured.vert").c_str(), shader_from_file("../shaders/textured.frag").c_str());
	}

	inline shader_t two_textures() {
		return shader_t(shader_from_file("../shaders/2_textures.vert").c_str(), shader_from_file("../shaders/2_textures.frag").c_str());
	}


};
