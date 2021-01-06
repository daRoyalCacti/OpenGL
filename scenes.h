#pragma once

#include "mesh_list.h"
#include "shader_list.h"
#include "texture_list.h"

#include <cmath>


namespace scenes {

	struct triangle {
		mesh_b curr_mesh;

		triangle() {
			shader_b temp_shader = shaders::toy();
			curr_mesh = meshes::single_triangle(temp_shader);	
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
			curr_mesh.draw();
		}
	};


	struct rectangle {
		mesh_i curr_mesh;

		rectangle() {
			shader_b temp_shader = shaders::toy();
			curr_mesh = meshes::rectangle(temp_shader);
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
			curr_mesh.draw();
		}
	};

	struct rectangle2 {
		mesh_i curr_mesh;

		rectangle2() {
			shader_b temp_shader = shaders::toy1();
			curr_mesh = meshes::rectangle(temp_shader);
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
			curr_mesh.draw();
		}
	};

	struct two_triangles1 {
		mesh_b curr_mesh;

		two_triangles1() {
			shader_b temp_shader = shaders::toy();
			curr_mesh = meshes::two_triangles1(temp_shader);
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
			curr_mesh.draw();
		}
	};


	struct two_triangles2 {
		mesh_b mesh1;
		mesh_b mesh2;

		two_triangles2() {
			shader_b temp_shader = shaders::toy();
			mesh1 = meshes::single_triangle1(temp_shader);

			temp_shader = shaders::toy1();
			mesh2 = meshes::single_triangle2(temp_shader);
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
			mesh1.draw();
			mesh2.draw();
		}
	};



	struct triangle2 {
		mesh_b curr_mesh;

		triangle2() {
			shader_b temp_shader = shaders::fixed_color();
			curr_mesh = meshes::single_triangle(temp_shader);
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
			curr_mesh.draw();
		}
	};


	struct triangle_color_varying {
		mesh_b curr_mesh;

		triangle_color_varying() {
			shader_b temp_shader = shaders::color_through_uniforms();
			curr_mesh = meshes::single_triangle(temp_shader);
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
							
			float greenValue = (sin(time) / 2.0f) + 0.5f;	//the color to set the triangle to
	
			curr_mesh.get_shader().set_uniform_vec4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

			curr_mesh.draw();
		}
	};

	struct colourful_triangle {
		mesh_bc curr_mesh;

		colourful_triangle() {
			shader_c temp_shader = shaders::vertex_colors();
			curr_mesh = meshes::colourful_triangle(temp_shader);
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
			curr_mesh.draw();
		}
	};


	
	struct colourful_rectangle {
		mesh_ic curr_mesh;

		colourful_rectangle() {
			shader_c temp_shader = shaders::vertex_colors();
			curr_mesh = meshes::colourful_rectangle(temp_shader);
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
			curr_mesh.draw();
		}
	};
	

};	//end namespace
