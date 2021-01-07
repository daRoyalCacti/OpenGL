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
		//vertex shader code
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main(){\n"
			"   gl_Position = vec4(aPos, 1.0);\n"
			"}\0";

		//fragment shader code
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"uniform vec4 ourColor;\n"	//set this value in OpenGL code (uniforms are the same for any shader stage)
			"void main(){\n"
			"   FragColor = ourColor;\n"
			"}\n\0";
		
		return shader_b(vertexShaderSource, fragmentShaderSource);
	}


	inline shader_c vertex_colors() {	//example of passing info from the vertex shader to the fragment shader
		//vertex shader code
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"		//position of vertex
			"layout (location = 1) in vec3 aColor;\n"	//color of vertex
			"out vec3 ourColor;\n"		//color to pass to fragment shader
			"void main(){\n"
			"   gl_Position = vec4(aPos, 1.0);\n"
			"   ourColor = aColor;\n"
			"}\0";

		//fragment shader code
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec3 ourColor;\n"
			"void main(){\n"
			"   FragColor =vec4(ourColor, 1.0);\n"
			"}\n\0";
		
		return shader_c(vertexShaderSource, fragmentShaderSource);
	}


	inline shader_tc textured_coloured() {	//example of passing info from the vertex shader to the fragment shader
		//vertex shader code
		const char *vertexShaderSource = "#version 420 core\n"
			"layout (location = 0) in vec3 aPos;\n"		//position of vertex
			"layout (location = 1) in vec3 aColor;\n"	//color of vertex
			"layout (location = 2) in vec2 aTexCoord;\n"
			"out vec3 ourColor;\n"
			"out vec2 TexCoord;\n"
			"void main(){\n"
			"   gl_Position = vec4(aPos, 1.0);\n"
			"   ourColor = aColor;\n"
			"   TexCoord = vec2(aTexCoord.x, aTexCoord.y);//aTexCoord;\n"
			"}\0";

		//fragment shader code
		const char *fragmentShaderSource = "#version 420 core\n"
			"out vec4 FragColor;\n"
			"in vec3 ourColor;\n"
			"in vec2 TexCoord;\n"
			"uniform sampler2D t;\n"
			"void main(){\n"
			"   FragColor = texture(t, TexCoord) * vec4(ourColor, 1.0);\n"
			"}\n\0";
		
		return shader_tc(vertexShaderSource, fragmentShaderSource);
	}

};
