#pragma once

#include <iostream>
#include <glad/glad.h>
#include <string>


inline void check_shader_compile(const unsigned Shader, const std::string pre_error = "") {
	//pre_error is any information that should be printed before the errors message
	int success;
	char infoLog[512];	//holds the error information	

	//checking if the compilation is successful
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);

	if (!success) {	//if the compilation failed
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);	//retrieving the error message
		std::cout << pre_error << "\nShader Compilation failed\n" << infoLog << std::endl;
	}
}


inline void check_shaderProgram_linking(const unsigned shaderProgram, const std::string pre_error = "") {
	//pre_error is any information that should be printed before the errors message
	int success;
	char infoLog[512];	//holds the error information	

	//checking if the compilation is successful
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {	//if the compilation failed
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);	//retrieving the error message
		std::cout << pre_error << "\nShader Compilation failed\n" << infoLog << std::endl;
	}
}
