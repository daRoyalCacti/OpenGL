#pragma once

#include <glad/glad.h>
#include <vector>
#include "shader.h"

//base mesh class
struct mesh_b {
	std::vector<float> vertices;
	unsigned VAO;
	shader_b mesh_shader;

	mesh_b() {};
	mesh_b(const std::vector<float> v, const shader_b s) : vertices(v), mesh_shader(s) {}

	inline shader_b get_shader() {
		return mesh_shader;
	}
	
	void init(GLenum usage = GL_STATIC_DRAW) {
		//setting Vertex array Object
		// - stores glVertexAttribPointer (for vertex attribute configurations and vertex buffer objects assocated with the vertex attributes)
		glGenVertexArrays(1, &VAO);

		//bind the VAO first, then bind and set vertex buffers, then configure vertex attributes
		glBindVertexArray(VAO);




		//allocating memory and uploading the vertex data
		unsigned VBO;	//stores the id of the buffer object
					// - if want more than 1 buffer object, the can be an array of unsigned ints
					
		glGenBuffers(1, &VBO);	//Generating the ids
					// - 1 for 1 object
					// - the ids are stored in VBO
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);	//specifying the type of the buffer object
							// in this case it is a vertex buffer so GL_ARRAY_BUFFER
		
		//any buffer calls that are made from here on are referencing the bounding buffer (VBO)
		
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), usage);	//copies the vertex data to the buffers memory
												// - first argument is the type of buffer want to copy into
												// - second argument is the size of the data in bytes to pass the to the buffer
												// - third argument is the actual data
												// - forth argument specifics how to graphics card should manage the supplied data
												//   -- GL_STREAM_DRAW has the data sent once and used a few times (by the GPU)
												//   -- Gl_STATIC_DRAW has the data sent once and used many times
												//   -- GL_DYNAMIC_DRAW has the sent many times (because it is changing) and used many times

		//current have the vertex data stored on the memory of the graphics card in a vertex buffer named VBO


		
		//linking vertex attributes
		// - telling opengl how to interpret the vertex data
		//working with the current bound VBO
		mesh_shader.attribs(0).set_glVertexAttribPointer();
		glEnableVertexAttribArray(0);

	}

	virtual void draw(float time = 0, unsigned long frameCounter = 0, float deltaTime = 0) {
		glUseProgram(mesh_shader.program());	//activate the shader program
						//every shader and rendering call after use will use this program object
		
		glBindVertexArray(VAO);		//setting the vertex buffer object to draw along with its attribute pointers

		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);	//GL_TRIANGLES because drawing triangles
							// second argument specifies the starting index of the vertex array to draw
							// third argument is for how many vertices to draw
							//  - number of vertices / (coordinates per vertex)
		
		glBindVertexArray(0);		//to unbind the Vertex array
	}
};


struct mesh_i : public mesh_b {
	std::vector<unsigned> indices;

	mesh_i() {};
	mesh_i(const std::vector<float> v, const std::vector<unsigned> i, shader_b s) : indices(i) {
		vertices = v;
		mesh_shader = s;
	}


	void init(GLenum usage_v = GL_STATIC_DRAW, GLenum usage_i = GL_STATIC_DRAW) {
		//usage_v is the usage for the vertices
		//usage_i is the usage of the indices

		//setting Vertex array Object
		// - stores glVertexAttribPointer (for vertex attribute configurations and vertex buffer objects assocated with the vertex attributes)
		glGenVertexArrays(1, &VAO);

		//bind the VAO first, then bind and set vertex buffers, then configure vertex attributes
		glBindVertexArray(VAO);




		//allocating memory and uploading the vertex data
		unsigned VBO;	//stores the id of the buffer object
					// - if want more than 1 buffer object, the can be an array of unsigned ints
					
		glGenBuffers(1, &VBO);	//Generating the ids
					// - 1 for 1 object
					// - the ids are stored in VBO
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);	//specifying the type of the buffer object
							// in this case it is a vertex buffer so GL_ARRAY_BUFFER
		
		//any buffer calls that are made from here on are referencing the bounding buffer (VBO)
		
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), usage_v);	//copies the vertex data to the buffers memory
												// - first argument is the type of buffer want to copy into
												// - second argument is the size of the data in bytes to pass the to the buffer
												// - third argument is the actual data
												// - forth argument specifics how to graphics card should manage the supplied data
												//   -- GL_STREAM_DRAW has the data sent once and used a few times (by the GPU)
												//   -- Gl_STATIC_DRAW has the data sent once and used many times
												//   -- GL_DYNAMIC_DRAW has the sent many times (because it is changing) and used many times

		//current have the vertex data stored on the memory of the graphics card in a vertex buffer named VBO
		

		
		//allocating memory and uploaing the index data
		// - very similar to the vertex data
		unsigned EBO;
		glGenBuffers(1, &EBO);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), usage_i);


		
		//linking vertex attributes
		// - telling opengl how to interpret the vertex data
		//working with the current bound VBO
		mesh_shader.attribs(0).set_glVertexAttribPointer();
		glEnableVertexAttribArray(0);
	}


	virtual void draw(float time = 0, unsigned long frameCounter = 0, float deltaTime = 0) {
		glUseProgram(mesh_shader.program());	//activate the shader program
						//every shader and rendering call after use will use this program object
		
		glBindVertexArray(VAO);		//setting the vertex buffer object to draw along with its attribute pointers

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);	//GL_TRIANGLES because drawing triangles
									// second argument is the number of elements to draw
									// third argument is the type of the indices
									// last argument is an offset in the EBO
		
		glBindVertexArray(0);		//to unbind the Vertex array
	}

};



//mesh class with only a vertex array and colors for each vertex
struct mesh_bc : public mesh_b{

	mesh_bc() {};
	mesh_bc(const std::vector<float> v, shader_c s) {
		vertices = v;
		mesh_shader = s;
	}
	
	void init(GLuint v_index_in_shader = 0, GLuint c_index_in_shader = 1, GLenum usage = GL_STATIC_DRAW) {
		//setting Vertex array Object
		// - stores glVertexAttribPointer (for vertex attribute configurations and vertex buffer objects assocated with the vertex attributes)
		glGenVertexArrays(1, &VAO);

		//bind the VAO first, then bind and set vertex buffers, then configure vertex attributes
		glBindVertexArray(VAO);




		//allocating memory and uploading the vertex data
		unsigned VBO;	//stores the id of the buffer object
					// - if want more than 1 buffer object, the can be an array of unsigned ints
					
		glGenBuffers(1, &VBO);	//Generating the ids
					// - 1 for 1 object
					// - the ids are stored in VBO
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);	//specifying the type of the buffer object
							// in this case it is a vertex buffer so GL_ARRAY_BUFFER
		
		//any buffer calls that are made from here on are referencing the bounding buffer (VBO)
		
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), usage);	//copies the vertex data to the buffers memory
												// - first argument is the type of buffer want to copy into
												// - second argument is the size of the data in bytes to pass the to the buffer
												// - third argument is the actual data
												// - forth argument specifics how to graphics card should manage the supplied data
												//   -- GL_STREAM_DRAW has the data sent once and used a few times (by the GPU)
												//   -- Gl_STATIC_DRAW has the data sent once and used many times
												//   -- GL_DYNAMIC_DRAW has the sent many times (because it is changing) and used many times

		//current have the vertex data stored on the memory of the graphics card in a vertex buffer named VBO


		
		//linking vertex attributes
		// - telling opengl how to interpret the vertex data
		//working with the current bound VBO

		for (int i = 0; i < 2; i++) {
			//i = 0 -> position data
			//i = 1 -> color data
			mesh_shader.attribs(i).set_glVertexAttribPointer();
			glEnableVertexAttribArray(i);
		}

/*
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
		glEnableVertexAttribArray(1);
*/
	}
};
