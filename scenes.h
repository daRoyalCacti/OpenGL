#pragma once

#include "mesh_list.h"
#include "shader_list.h"
#include "texture_list.h"
#include "camera.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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

			curr_mesh.draw();
		}
	};


	struct textured_colourful_rectangle {
		mesh_itc curr_mesh;

		textured_colourful_rectangle() {
			shader_tc temp_shader = shaders::textured_coloured();
			texture_b temp_tex = textures::container();
			curr_mesh = meshes::textured_colourful_rectangle(temp_tex, temp_shader);
		}

		inline void init() {
			curr_mesh.init();			
			curr_mesh.get_shader().set_uniform_int("t", 0);
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color


			curr_mesh.draw();
		}
	};
	

	struct textured_colourful_triangle {
		mesh_btc curr_mesh;

		textured_colourful_triangle() {
			shader_tc temp_shader = shaders::textured_coloured();
			texture_b temp_tex = textures::container();
			curr_mesh = meshes::textured_colourful_triangle(temp_tex, temp_shader);
		}

		inline void init() {
			curr_mesh.init();			
			curr_mesh.get_shader().set_uniform_int("t", 0);
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
	

			curr_mesh.draw();
		}
	};


	
	struct textured_rectangle {
		mesh_it curr_mesh;

		textured_rectangle() {
			shader_t temp_shader = shaders::textured();
			texture_b temp_tex = textures::container();
			curr_mesh = meshes::textured_rectangle(temp_tex, temp_shader);
		}

		inline void init() {
			curr_mesh.init();			
			curr_mesh.get_shader().set_uniform_int("t", 0);
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
	

			curr_mesh.draw();
		}
	};
	

	struct textured_triangle {
		mesh_bt curr_mesh;

		textured_triangle() {
			shader_t temp_shader = shaders::textured();
			texture_b temp_tex = textures::container();
			curr_mesh = meshes::textured_triangle(temp_tex, temp_shader);
		}

		inline void init() {
			curr_mesh.init();			
			curr_mesh.get_shader().set_uniform_int("t", 0);
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color


			curr_mesh.draw();
		}
	};



	struct textured_rectangle2 {
		mesh_2it curr_mesh;

		textured_rectangle2() {
			shader_t temp_shader = shaders::two_textures();

			texture_b temp_tex1 = textures::container();
			texture_b temp_tex2 = textures::face();


			curr_mesh = meshes::textured_rectangle2(temp_tex1, temp_tex2, temp_shader);
		}

		inline void init() {
			curr_mesh.init();			
			curr_mesh.get_shader().set_uniform_int("texture1", 0);
			curr_mesh.get_shader().set_uniform_int("texture2", 1);
			curr_mesh.get_shader().set_uniform_float("mix_per", 0.2);
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color


			curr_mesh.draw();
		}
	};


	struct transformed_textured_rectangle {
		mesh_it curr_mesh;

		transformed_textured_rectangle() {
			shader_t temp_shader = shaders::textured_transformed();
			texture_b temp_tex = textures::container();
			curr_mesh = meshes::textured_rectangle(temp_tex, temp_shader);
		}

		inline void init() {
			curr_mesh.init();

			glm::mat4 temp_transform = glm::mat4(1.0f);
			temp_transform = glm::rotate(temp_transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f) );
			temp_transform = glm::scale(temp_transform, glm::vec3(0.5f, 0.5f, 0.5f) );


			curr_mesh.get_shader().set_uniform_mat4("transform", temp_transform);
			curr_mesh.get_shader().set_uniform_int("t", 0);
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color


			curr_mesh.draw();
		}
	};


	struct transformed_colored_rectangle {
		mesh_i curr_mesh;
		glm::mat4 trans;

		transformed_colored_rectangle() {
			shader_b temp_shader = shaders::colored_transformed();
			curr_mesh = meshes::rectangle(temp_shader);
		}

		inline void init() {
			curr_mesh.init();
			curr_mesh.get_shader().set_uniform_vec4("ourColor", 1.0f, 0.0f, 0.0f, 1.0f);
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color
		

			trans = glm::mat4(1.0f);
			trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f) );
			trans = glm::rotate(trans, time, glm::vec3(0.0f, 0.0f, 1.0f) );	//continuous rotating about the z-axis


			curr_mesh.get_shader().set_uniform_mat4("transform", trans);
			curr_mesh.draw();
		}
	};


	struct transformed_textured_cube {
		mesh_bt curr_mesh;
		transformation trans;

		transformed_textured_cube() {
			shader_t temp_shader = shaders::textured_transformed();
			texture_b temp_tex = textures::container();
			curr_mesh = meshes::textured_cube(temp_tex, temp_shader);
		}

		inline void init() {
			curr_mesh.init();

			trans.view = glm::translate(trans.view, glm::vec3(0.0f, 0.0f, -3.0f) );	//moving away from the object

			//curr_mesh.get_shader().set_uniform_mat4("transform", temp_transform);
			curr_mesh.get_shader().set_uniform_int("t", 0);
		}

		inline void draw(float time, unsigned long frameCounter, float deltaTime) {
			//clearing the screen (so don't see the results from the previous  frame)
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//setting the clear color


			trans.model = glm::mat4(1.0f);
			trans.model = glm::rotate(trans.model, time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f) );

			curr_mesh.get_shader().set_uniform_mat4("transform", trans.get_matrix());

			curr_mesh.draw();
		}
	};

};	//end namespace
