#pragma once

#include <glad/glad.h>

#include "errors.h"


//base shader class
struct shader_b {
	unsigned shaderProgram;

	shader_b() {};

	inline unsigned program() const {
		return shaderProgram;
	}

	virtual void set_shaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
		//compiling the vertex shader
		unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);	//assigning an ID to reference the vertex shader
										//GL_VERTEX_SHADER because want to create a vertexShader
		
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);	//attaching the shader source code to the sharder object
										// - first argument is the shader object to compile to
										// - second argument specifies how many strings the source code is (only 1 here)
										// - third argument is the actual source code
										// - leave forth argument blank
		
		glCompileShader(vertexShader);		//compiling the shader

		//checking for errors compiling the shader
		check_shader_compile(vertexShader);	//function defined in errors.h	



		//compiling the fragment shader
		//same as for the vertex shader but with GL_FRAGMENT_SHADER
		unsigned fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		check_shader_compile(fragmentShader);



		//Creating the shader program
		// - the linked version of multiple shaders
		// - have to activate this shader program when rendering objects
		// - the activated shader program wil be used when issueing render calls
		//
		// - links the output of each shader to the inputs of the next shader
		
		shaderProgram = glCreateProgram();	//creating the shader program and attaching it to an id (to reference the object)

		glAttachShader(shaderProgram, vertexShader);	//attach the shaders to the program (in the correct order)
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);		//link the shaders

		check_shaderProgram_linking(shaderProgram);	//defined in errors.h

		glDeleteShader(vertexShader);	//can delete the shader objects now
		glDeleteShader(fragmentShader);	//they've been link into the program object
	}	
};
