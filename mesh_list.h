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

};
