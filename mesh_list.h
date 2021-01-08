#pragma once

#include "mesh.h"

namespace meshes {
	inline mesh_b single_triangle(shader_b shad){
		std::vector<float> vertices = {
			-0.5f, -0.5f, 0.0f, // left  
			0.5f, -0.5f, 0.0f, // right 
			0.0f,  0.5f, 0.0f  // top   
		};

		return mesh_b(vertices, shad);
	}

	inline mesh_i rectangle(shader_b shad) {
		std::vector<float> vertices = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		std::vector<unsigned> indices = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		return mesh_i(vertices, indices, shad);
	}

	inline mesh_b two_triangles1(shader_b shad) {
		std::vector<float> vertices = {
			-0.75f, -0.75f, 0.0f,	//lower left1
			-0.75f,  0.25f, 0.0f,   //upper left1
			 0.25f, -0.75f, 0.0f,	//lower right1

			 0.75f,  0.75f, 0.0f, 	//upper right2
			 0.75f, -0.25f, 0.0f,	//lower right2
			 -0.25f, 0.75f, 0.0f	//upper left2
		};

		return mesh_b(vertices, shad);
	}

	inline mesh_b single_triangle1(shader_b shad) {
		std::vector<float> vertices = {
			-0.75f, -0.75f, 0.0f,	//lower left1
			-0.75f,  0.25f, 0.0f,   //upper left1
			 0.25f, -0.75f, 0.0f	//lower right1
		};

		return mesh_b(vertices, shad);
	}

	inline mesh_b single_triangle2(shader_b shad) {
		std::vector<float> vertices = {
			 0.75f,  0.75f, 0.0f, 	//upper right2
			 0.75f, -0.25f, 0.0f,	//lower right2
			 -0.25f, 0.75f, 0.0f	//upper left2
		};

		return mesh_b(vertices, shad);

	}


	inline mesh_bc colourful_triangle(shader_c shad) {
		std::vector<float> vertices = {
			// positions         // colors
		 	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 	
		};

		return mesh_bc(vertices, shad);

	}


	inline mesh_ic colourful_rectangle(shader_c shad) {
		std::vector<float> vertices = {
			// positions          // colors           
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   	// top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   	// bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,		// bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f	 	// top left	
		};

		std::vector<unsigned> indices = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		return mesh_ic(vertices, indices, shad);

	}

	inline mesh_btc textured_colourful_triangle(texture_b tex, shader_tc shad) {
		std::vector<float> vertices = {
			 // positions          // colors           // texture coords
			  0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			  0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			 -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		};


		return mesh_btc(vertices, tex, shad);
	}

	inline mesh_itc textured_colourful_rectangle(texture_b &tex, shader_tc shad) {
		std::vector<float> vertices = {
			 // positions          // colors           // texture coords
			  0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			  0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			 -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			 -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left	
		};

		std::vector<unsigned> indices = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		return mesh_itc(vertices, indices, tex, shad);
	}


	inline mesh_bt textured_triangle(texture_b tex, shader_t shad) {
		std::vector<float> vertices = {
			 // positions          // texture coords
			  0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
			  0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
			 -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
		};


		return mesh_bt(vertices, tex, shad);
	}


	inline mesh_it textured_rectangle(texture_b &tex, shader_t shad) {
		std::vector<float> vertices = {
			 // positions          // texture coords
			  0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
			  0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
			 -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
			 -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left	
		};

		std::vector<unsigned> indices = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		return mesh_it(vertices, indices, tex, shad);
	}


	inline mesh_2it textured_rectangle2(texture_b &tex1, texture_b &tex2, shader_t shad) {
		std::vector<float> vertices = {
			 // positions          // texture coords
			  0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
			  0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
			 -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
			 -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left	
		};

		std::vector<unsigned> indices = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		return mesh_2it(vertices, indices, tex1, tex2, shad);
	}




};
