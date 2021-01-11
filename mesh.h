#pragma once

#include <glad/glad.h>
#include <vector>
#include "shader.h"
#include "texture.h"

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>





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

		for (int i = 0; i < mesh_shader.attribs_size(); i++) {
			glEnableVertexAttribArray(i);
			mesh_shader.attribs(i).set_glVertexAttribPointer();
		}


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
		mesh_b::init(usage_v);

		//allocating memory and uploaing the index data
		// - very similar to the vertex data
		unsigned EBO;
		glGenBuffers(1, &EBO);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), usage_i);
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

};


struct mesh_ic : public mesh_bc {

	std::vector<unsigned> indices;

	mesh_ic() {};
	mesh_ic(const std::vector<float> v, const std::vector<unsigned> i, shader_c s) {
		vertices = v;
		indices = i;
		mesh_shader = s;
	}
	
	void init(GLenum usage_v = GL_STATIC_DRAW, GLenum usage_i = GL_STATIC_DRAW) {
		mesh_bc::init(usage_v);

		//allocating memory and uploaing the index data
		// - very similar to the vertex data
		unsigned EBO;
		glGenBuffers(1, &EBO);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), usage_i);
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



struct mesh_btc : public mesh_bc {	//mesh with texture and colours
	texture_b tex;

	mesh_btc() {};
	mesh_btc(const std::vector<float> v, texture_b t, shader_tc s) {
		vertices = v;
		mesh_shader = s;
		tex = t;
	}

	virtual void draw(float time = 0, unsigned long frameCounter = 0, float deltaTime = 0) {
		glUseProgram(mesh_shader.program());	//activate the shader program
						//every shader and rendering call after use will use this program object
		
		glActiveTexture(GL_TEXTURE0);	//activate the texture before binding it
		tex.bind();

		glBindVertexArray(VAO);		//setting the vertex buffer object to draw along with its attribute pointers

		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);	//GL_TRIANGLES because drawing triangles
							// second argument specifies the starting index of the vertex array to draw
							// third argument is for how many vertices to draw
							//  - number of vertices / (coordinates per vertex)
		
		glBindVertexArray(0);		//to unbind the Vertex array
	}
};



struct mesh_itc : public mesh_btc {	//mesh with texture

	unsigned *a,b;	//need these 2 for some reason???
	std::vector<unsigned> indices;

	mesh_itc() {};
	mesh_itc(const std::vector<float> v, std::vector<unsigned> i, texture_b t, shader_tc s) {
		vertices = v;
		tex = t;
		mesh_shader = s;

		indices = i;
	}
	
	void init(GLenum usage_v = GL_STATIC_DRAW, GLenum usage_i = GL_STATIC_DRAW) {
		mesh_btc::init(usage_v);

		//allocating memory and uploaing the index data
		// - very similar to the vertex data
		unsigned EBO;
		glGenBuffers(1, &EBO);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), usage_i);

	}


	virtual void draw(float time = 0, unsigned long frameCounter = 0, float deltaTime = 0) {

		glUseProgram(mesh_shader.program());	//activate the shader program
						//every shader and rendering call after use will use this program object
		
		glActiveTexture(GL_TEXTURE0);	//activate the texture before binding it
		tex.bind();

		glBindVertexArray(VAO);		//setting the vertex buffer object to draw along with its attribute pointers
		
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);	//GL_TRIANGLES because drawing triangles
									// second argument is the number of elements to draw
									// third argument is the type of the indices
									// last argument is an offset in the EBO
		
		glBindVertexArray(0);		//to unbind the Vertex array
	}

};






struct mesh_bt : public mesh_b {	//mesh with texture and colours
	texture_b tex;

	mesh_bt() {};
	mesh_bt(const std::vector<float> v, texture_b t, shader_t s) {
		vertices = v;
		mesh_shader = s;
		tex = t;
	}

	virtual void draw(float time = 0, unsigned long frameCounter = 0, float deltaTime = 0) {
		glUseProgram(mesh_shader.program());	//activate the shader program
						//every shader and rendering call after use will use this program object
		
		glActiveTexture(GL_TEXTURE0);	//activate the texture before binding it
		tex.bind();

		glBindVertexArray(VAO);		//setting the vertex buffer object to draw along with its attribute pointers

		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);	//GL_TRIANGLES because drawing triangles
							// second argument specifies the starting index of the vertex array to draw
							// third argument is for how many vertices to draw
							//  - number of vertices / (coordinates per vertex)
		
		glBindVertexArray(0);		//to unbind the Vertex array
	}
};



struct mesh_it : public mesh_bt {	//mesh with texture

	std::vector<unsigned> indices;

	mesh_it() {};
	mesh_it(const std::vector<float> v, std::vector<unsigned> i, texture_b t, shader_t s) {
		vertices = v;
		tex = t;
		mesh_shader = s;

		indices = i;
	}
	
	void init(GLenum usage_v = GL_STATIC_DRAW, GLenum usage_i = GL_STATIC_DRAW) {
		mesh_bt::init(usage_v);

		//allocating memory and uploaing the index data
		// - very similar to the vertex data
		unsigned EBO;
		glGenBuffers(1, &EBO);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), usage_i);

	}


	virtual void draw(float time = 0, unsigned long frameCounter = 0, float deltaTime = 0) {

		glUseProgram(mesh_shader.program());	//activate the shader program
						//every shader and rendering call after use will use this program object
		
		glActiveTexture(GL_TEXTURE0);	//activate the texture before binding it
		tex.bind();

		glBindVertexArray(VAO);		//setting the vertex buffer object to draw along with its attribute pointers
		
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);	//GL_TRIANGLES because drawing triangles
									// second argument is the number of elements to draw
									// third argument is the type of the indices
									// last argument is an offset in the EBO
		
		glBindVertexArray(0);		//to unbind the Vertex array
	}

};












void processMesh(aiMesh *mesh, const aiScene *scene, std::vector<float> &vertices, std::vector<unsigned> &indices, std::vector<float> &uvs, std::vector<std::string> &tex_paths, std::vector<float> &norms) {
	
	for (unsigned i = 0; i < mesh->mNumVertices; i++) {
		//process vertex positions, normals and texture coordinates

		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		norms.push_back(mesh->mNormals[i].x);
		norms.push_back(mesh->mNormals[i].y);
		norms.push_back(mesh->mNormals[i].z);
		
		if (mesh->mTextureCoords[0]) {	//does the mesh contiain texture coords
			uvs.push_back(mesh->mTextureCoords[0][i].x);
			uvs.push_back(mesh->mTextureCoords[0][i].y);
		} else {
			uvs.push_back(0.0f);
			uvs.push_back(0.0f);
		}
	}

	for (unsigned i = 0; i < mesh->mNumFaces; i++) {
		//assimp defines eah mesh as having an array of faces
		// - aiProcess_Triangulate means these faces are always triangles
		//Iterate over all the faces and store the face's indices

		const aiFace face = mesh->mFaces[i];
		for (unsigned j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}


	if (mesh->mMaterialIndex >= 0) {
		//currently only processes diffuse textures

		//retribve the aiMaterial object from the scene
		aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
		//saying that want all diffuse textures
		const aiTextureType type = aiTextureType_DIFFUSE;
	
				//actually loading the textures
		for (unsigned i = 0; i < mat->GetTextureCount(type); i++) {
			aiString str;
			mat->GetTexture(type, i , &str);
			std::string path = str.C_Str();

			bool already_loaded = false;
			for (int i = 0; i < tex_paths.size(); i++) {
				if (path == tex_paths[i]) {
					already_loaded = true;
					break;
				}
			}
			if (!already_loaded) {
				tex_paths.push_back(path);	
			}

		}
	}

}


void processNode(aiNode *node, const aiScene *scene, std::vector<float> &vertices, std::vector<unsigned> &indices, std::vector<float> &uvs, std::vector<std::string> &tex_paths, std::vector<float> &norms) {
	//process all the node's meshes
	for (unsigned i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene, vertices, indices, uvs, tex_paths, norms);
	}

	//process the meshes of all the nodes children
	for (unsigned i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, vertices, indices, uvs, tex_paths, norms);
	}
}



mesh_it generate_model(const std::string file_name, shader_t shad, const bool load_normals = true, const bool flip_uvs = true) {
	//https://learnopengl.com/Model-Loading/Model	
	
	std::vector<float> vertices;
	std::vector<unsigned> indices;
	std::vector<float> uvs;
	std::vector<float> norms;
	std::vector<std::string> tex_paths;

	unsigned assimp_settings = aiProcess_Triangulate | aiProcess_GenNormals;


	if (flip_uvs)
		assimp_settings |= aiProcess_FlipUVs;

	
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(file_name, assimp_settings);	
			//aiProcess_Triangulate tells assimp to make the model entirely out of triangles
			//aiProcess_GenNormals creates normal vectors for each vertex
			//aiProcess_FlipUVS flips the texture coordinates on the y-axis

	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Assimp Error:\n\t" << importer.GetErrorString() << std::endl;
	}

	processNode(scene->mRootNode, scene, vertices, indices, uvs, tex_paths, norms);

	//creating the vertex array correctly
	std::vector<float> vert;
	//vert.resize(vertices.size() + uvs.size() + norms.size());
	
	//std::cout << vertices.size() << std::endl;

	for (int i = 0; i < vertices.size(); i+=3) {
		vert.push_back(vertices[i]);
		vert.push_back(vertices[i+1]);
		vert.push_back(vertices[i+2]);
	
		if (load_normals) {
			vert.push_back(norms[i]);
			vert.push_back(norms[i+1]);
			vert.push_back(norms[i+2]);
		}

		vert.push_back(uvs[i/3*2]);
		vert.push_back(uvs[i/3*2+1]);
	}
	//std::cout << vert.size() << std::endl;

	//finding the texture path correctly
	std::string file_dir = file_name.substr(0, file_name.find_last_of('/') );
	file_dir.append("/");
	

	/*
	for (int i = 0; i < vertices.size(); i+=3)
		std::cout << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << std::endl;
	*/


	return mesh_it(vert, indices, texture_b(file_dir.append(tex_paths[0])), shad);
}















struct mesh_2it : public mesh_b {	//mesh with texture

	unsigned *a,b,*c;	//need these 2 for some reason???
	std::vector<unsigned> indices;

	texture_b tex1, tex2;

	mesh_2it() {};
	mesh_2it(const std::vector<float> v, std::vector<unsigned> i, texture_b &t1, texture_b &t2, shader_t s) {
		vertices = v;
		tex1 = t1;
		tex2 = t2;
		mesh_shader = s;
		
		indices = i;
	}
	
	void init(GLenum usage_v = GL_STATIC_DRAW, GLenum usage_i = GL_STATIC_DRAW) {
		mesh_b::init(usage_v);

		//allocating memory and uploaing the index data
		// - very similar to the vertex data
		unsigned EBO;
		glGenBuffers(1, &EBO);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), usage_i);

	}


	virtual void draw(float time = 0, unsigned long frameCounter = 0, float deltaTime = 0) {

		glUseProgram(mesh_shader.program());	//activate the shader program
						//every shader and rendering call after use will use this program object
		
		glActiveTexture(GL_TEXTURE0);	//activate the texture before binding it
		tex1.bind();
		glActiveTexture(GL_TEXTURE1);
		tex2.bind();

		glBindVertexArray(VAO);		//setting the vertex buffer object to draw along with its attribute pointers
		
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);	//GL_TRIANGLES because drawing triangles
									// second argument is the number of elements to draw
									// third argument is the type of the indices
									// last argument is an offset in the EBO
		
		glBindVertexArray(0);		//to unbind the Vertex array
	}

};
