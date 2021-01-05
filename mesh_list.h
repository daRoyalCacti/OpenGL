#pragma once

#include "mesh.h"

namespace meshes {
	inline mesh_b single_triangle(){
		std::vector<float> vertices = {
			-0.5f, -0.5f, 0.0f, // left  
			0.5f, -0.5f, 0.0f, // right 
			0.0f,  0.5f, 0.0f  // top   
		};

		return mesh_b(vertices);
	}

	inline mesh_i rectangle() {
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

		return mesh_i(vertices, indices);
	}

	inline mesh_b two_triangles1() {
		std::vector<float> vertices = {
			-0.75f, -0.75f, 0.0f,	//lower left1
			-0.75f,  0.25f, 0.0f,   //upper left1
			 0.25f, -0.75f, 0.0f,	//lower right1

			 0.75f,  0.75f, 0.0f, 	//upper right2
			 0.75f, -0.25f, 0.0f,	//lower right2
			 -0.25f, 0.75f, 0.0f	//upper left2
		};

		return mesh_b(vertices);
	}

	inline mesh_b single_triangle1() {
		std::vector<float> vertices = {
			-0.75f, -0.75f, 0.0f,	//lower left1
			-0.75f,  0.25f, 0.0f,   //upper left1
			 0.25f, -0.75f, 0.0f	//lower right1
		};

		return mesh_b(vertices);
	}

	inline mesh_b single_triangle2() {
		std::vector<float> vertices = {
			 0.75f,  0.75f, 0.0f, 	//upper right2
			 0.75f, -0.25f, 0.0f,	//lower right2
			 -0.25f, 0.75f, 0.0f	//upper left2
		};

		return mesh_b(vertices);

	}


	inline mesh_bc colourful_triangle() {
		std::vector<float> vertices = {
			// positions         // colors
		 	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 	
		};

		return mesh_bc(vertices);

	}

};
