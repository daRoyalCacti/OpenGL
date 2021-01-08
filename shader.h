#pragma once

#include <glad/glad.h>

#include "errors.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct vertex_attributes {
	GLuint attribute;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	GLvoid *start;

	inline void set_glVertexAttribPointer() {
		glVertexAttribPointer(attribute, size, type, normalized, stride, start);	//first parameter specifices what attribute to configure
												// - position in the vertex shader is set by location = <attribute>
												//second parameter specifies the size of the vertex attribute
												// - e.g. vertex attribute is a vec3 so its is composed of 3 values
												//third argument specifies the type of the data
												// - e.g. GL_FLOAT size a vec in GLSL consists of floating point values
												//fourth argument specifies if the data should be normalised
												// - Should be true if inputting integer data (generally not so normally GL_FALSE)
												//firth argument is the stride (space between consecutive vertex attributes)
												// - e.g. for tightly packed data, the next position is located 3 floats away
												//last argument is the offset (where the data begins in the buffer)
												// - e.g. the data is at the start of the data so 0
												// - requires the weird cast to a void*
	}
};



std::string shader_from_file(const std::string file) {
	std::string code;
	std::ifstream shaderFile;

	//ensure ifstream objects can throw exceptions
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	//try to open file
	try {
		std::stringstream shaderStream;
		shaderFile.open(file);
		//read file's buffer constents into streams
		shaderStream << shaderFile.rdbuf();
		//close the file
		shaderFile.close();
		//convert stream into string
		code = shaderStream.str();
	} catch (const std::ifstream::failure& e) {
		std::cerr << "Failed to read shader file " << file << std::endl;
	}

	return code;
}



//base shader class
struct shader_b {
	std::vector<vertex_attributes> attributes; 
	unsigned shaderProgram;

	shader_b() {};
	
	shader_b(const char* vertexShaderSource, const char* fragmentShaderSource) {
		set_shaders(vertexShaderSource, fragmentShaderSource);
		attributes = {vertex_attributes{0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0}};
	}

	shader_b(const char* vertexShaderSource, const char* fragmentShaderSource, std::vector<vertex_attributes> attrib) {
		set_shaders(vertexShaderSource, fragmentShaderSource);

		if (attrib.size() != 1) {
			std::cerr << "shader_b requires attrib to be of size 1" << std::endl;
		}

		attributes = attrib;
	}


	inline unsigned program() const {
		return shaderProgram;
	}

	inline vertex_attributes attribs(int index) const {
		return attributes[index];
	}

	inline size_t attribs_size() const {
		return attributes.size();
	}

	virtual void set_shaders(const char* vertexShaderSource, const char* fragmentShaderSource) {

		//compiling the vertex shader
		unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);	//assigning an ID to reference the vertex shader
										//GL_VERTEX_SHADER because want to create a vertexShader
		
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);	//attaching the shader source code to the shader object
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



	inline void set_uniform_bool(const std::string &unif_name, bool value) const {
		int Location = glGetUniformLocation(shaderProgram, unif_name.c_str());
		if (Location == -1) {	//the uniform could not be found
			std::cerr << "could not find uniform " << unif_name << std::endl;
		}

		glUseProgram(shaderProgram);
		glUniform1i(Location, (int)value);		//setting the color value
	}

	inline void set_uniform_int(const std::string &unif_name, int value) const {
		int Location = glGetUniformLocation(shaderProgram, unif_name.c_str());
		if (Location == -1) {	//the uniform could not be found
			std::cerr << "could not find uniform " << unif_name << std::endl;
		}

		glUseProgram(shaderProgram);
		glUniform1i(Location, value);		//setting the color value
	}

	inline void set_uniform_float(const std::string &unif_name, float value) const {
		int Location = glGetUniformLocation(shaderProgram, unif_name.c_str());
		if (Location == -1) {	//the uniform could not be found
			std::cerr << "could not find uniform " << unif_name << std::endl;
		}

		glUseProgram(shaderProgram);
		glUniform1f(Location, value);		//setting the color value
	}

	inline void set_uniform_vec2(const std::string &unif_name, float x, float y) const {
		int Location = glGetUniformLocation(shaderProgram, unif_name.c_str());
		if (Location == -1) {	//the uniform could not be found
			std::cerr << "could not find uniform " << unif_name << std::endl;
		}

		glUseProgram(shaderProgram);
		glUniform2f(Location, x, y);		//setting the color value
	}
	
	inline void set_uniform_vec3(const std::string &unif_name, float x, float y, float z) const {
		int Location = glGetUniformLocation(shaderProgram, unif_name.c_str());
		if (Location == -1) {	//the uniform could not be found
			std::cerr << "could not find uniform " << unif_name << std::endl;
		}

		glUseProgram(shaderProgram);
		glUniform3f(Location, x, y, z);		//setting the color value
	}
	
	inline void set_uniform_vec4(const std::string &unif_name, float x, float y, float z, float w) const {
		int Location = glGetUniformLocation(shaderProgram, unif_name.c_str());
		if (Location == -1) {	//the uniform could not be found
			std::cerr << "could not find uniform " << unif_name << std::endl;
		}

		glUseProgram(shaderProgram);
		glUniform4f(Location, x, y, z, y);		//setting the color value
	}
};



//struct to hold shaders that have colors per vertices
struct shader_c : public shader_b {


	shader_c() {}
	shader_c(const char* vertexShaderSource, const char* fragmentShaderSource) {
		set_shaders(vertexShaderSource, fragmentShaderSource);
		attributes = {vertex_attributes{0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0}, 
				vertex_attributes{1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float) )  } };

	}

	shader_c(const char* vertexShaderSource, const char* fragmentShaderSource, std::vector<vertex_attributes> attrib) {
		set_shaders(vertexShaderSource, fragmentShaderSource);

		if (attrib.size() != 2) {
			std::cerr << "shader_c requires attrib to be of size 2" << std::endl;
		}

		attributes = attrib;
	}


};


//struct to hold shaders that have textures and vertex colours
struct shader_tc : public shader_c {


	shader_tc() {}
	shader_tc(const char* vertexShaderSource, const char* fragmentShaderSource) {
		set_shaders(vertexShaderSource, fragmentShaderSource);
		attributes = {  vertex_attributes{0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0}, 
				vertex_attributes{1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float) )  },
	       			vertex_attributes{2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float) ) } };

	}

	shader_tc(const char* vertexShaderSource, const char* fragmentShaderSource, std::vector<vertex_attributes> attrib) {
		set_shaders(vertexShaderSource, fragmentShaderSource);

		if (attrib.size() != 3) {
			std::cerr << "shader_c requires attrib to be of size 3" << std::endl;
		}

		attributes = attrib;
	}


};


//struct to hold shaders that have textures
struct shader_t : public shader_b {


	shader_t() {}
	shader_t(const char* vertexShaderSource, const char* fragmentShaderSource) {
		set_shaders(vertexShaderSource, fragmentShaderSource);
		attributes = {  vertex_attributes{0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0}, 
	       			vertex_attributes{1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float) ) } };

	}

	shader_t(const char* vertexShaderSource, const char* fragmentShaderSource, std::vector<vertex_attributes> attrib) {
		set_shaders(vertexShaderSource, fragmentShaderSource);

		if (attrib.size() != 3) {
			std::cerr << "shader_c requires attrib to be of size 2" << std::endl;
		}

		attributes = attrib;
	}


};
