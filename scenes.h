#pragma once

#include "mesh_list.h"
#include "shader_list.h"

#include <cmath>


namespace scenes {

	struct triangle {
		mesh_b curr_mesh;
		shader_b curr_shader;

		triangle() {
			curr_mesh = meshes::single_triangle();
			curr_shader = shaders::toy();
		}

		inline void init() {
			curr_mesh.init();
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
			glClear(GL_COLOR_BUFFER_BIT);	//want to clear the color buffer
							//also possible
							// - GL_DEPTH_BUFFER BIT
							// - GL_STENCIL_BUFFER_BIT
			curr_mesh.draw(curr_shader.program());
		}
	};


	struct rectangle {
		mesh_i curr_mesh;
		shader_b curr_shader;

		rectangle() {
			curr_mesh = meshes::rectangle();
			curr_shader = shaders::toy();
		}

		inline void init() {
			curr_mesh.init();
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
			glClear(GL_COLOR_BUFFER_BIT);	//want to clear the color buffer
							//also possible
							// - GL_DEPTH_BUFFER BIT
							// - GL_STENCIL_BUFFER_BIT
			curr_mesh.draw(curr_shader.program());
		}
	};

	struct rectangle2 {
		mesh_i curr_mesh;
		shader_b curr_shader;

		rectangle2() {
			curr_mesh = meshes::rectangle();
			curr_shader = shaders::toy1();
		}

		inline void init() {
			curr_mesh.init();
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
			glClear(GL_COLOR_BUFFER_BIT);	//want to clear the color buffer
							//also possible
							// - GL_DEPTH_BUFFER BIT
							// - GL_STENCIL_BUFFER_BIT
			curr_mesh.draw(curr_shader.program());
		}
	};

	struct two_triangles1 {
		mesh_b curr_mesh;
		shader_b curr_shader;

		two_triangles1() {
			curr_mesh = meshes::two_triangles1();
			curr_shader = shaders::toy();
		}

		inline void init() {
			curr_mesh.init();
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
			glClear(GL_COLOR_BUFFER_BIT);	//want to clear the color buffer
							//also possible
							// - GL_DEPTH_BUFFER BIT
							// - GL_STENCIL_BUFFER_BIT
			curr_mesh.draw(curr_shader.program());
		}
	};


	struct two_triangles2 {
		mesh_b mesh1;
		mesh_b mesh2;
		shader_b shader1;
		shader_b shader2;

		two_triangles2() {
			mesh1 = meshes::single_triangle1();
			mesh2 = meshes::single_triangle2();

			shader1 = shaders::toy();
			shader2 = shaders::toy1();
		}

		inline void init() {
			mesh1.init();
			mesh2.init();
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
			glClear(GL_COLOR_BUFFER_BIT);	//want to clear the color buffer
							//also possible
							// - GL_DEPTH_BUFFER BIT
							// - GL_STENCIL_BUFFER_BIT
			mesh1.draw(shader1.program());
			mesh2.draw(shader2.program());
		}
	};



	struct triangle2 {
		mesh_b curr_mesh;
		shader_b curr_shader;

		triangle2() {
			curr_mesh = meshes::single_triangle();
			curr_shader = shaders::fixed_color();
		}

		inline void init() {
			curr_mesh.init();
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
			glClear(GL_COLOR_BUFFER_BIT);	//want to clear the color buffer
							//also possible
							// - GL_DEPTH_BUFFER BIT
							// - GL_STENCIL_BUFFER_BIT
			curr_mesh.draw(curr_shader.program());
		}
	};


	struct triangle_color_varying {
		mesh_b curr_mesh;
		shader_b curr_shader;

		triangle_color_varying() {
			curr_mesh = meshes::single_triangle();
			curr_shader = shaders::color_through_uniforms();
		}

		inline void init() {
			curr_mesh.init();
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
			glClear(GL_COLOR_BUFFER_BIT);	//want to clear the color buffer
							//also possible
							// - GL_DEPTH_BUFFER BIT
							// - GL_STENCIL_BUFFER_BIT
							
			float greeValue = (sin(time) / 2.0f) + 0.5f;	//the color to set the triangle to
			int vertexColorLocation = glGetUniformLocation(curr_shader.program(), "ourColor");	//getting the uniform variable defined in the shader code

			if (vertexColorLocation == -1) {	//the uniform could not be found
				std::cerr << "could not find uniform ourColor" << std::endl;
			}

			glUseProgram(curr_shader.program());
			glUniform4f(vertexColorLocation, 0.0f, greeValue, 0.0f, 1.0f);		//setting the color value

			curr_mesh.draw(curr_shader.program());
		}
	};

};
