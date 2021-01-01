#pragma once

#include "mesh_list.h"
#include "shader_list.h"


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

		inline void draw() {
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

		inline void draw() {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
			glClear(GL_COLOR_BUFFER_BIT);	//want to clear the color buffer
							//also possible
							// - GL_DEPTH_BUFFER BIT
							// - GL_STENCIL_BUFFER_BIT
			curr_mesh.draw(curr_shader.program());
		}
	};


};
