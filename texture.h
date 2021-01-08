#pragma once

#include <glad/glad.h>
#include "stb_image_ne.h"
#include <string>
#include <iostream>

struct texture_settings  {
	GLint wrap_s;	//options: GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
	GLint wrap_t;	//same options as wrap_s
	GLint min_filt;	//options: GL_LINEAR, GL_NEAREST, <mipmap settings>
	GLint mag_filt;	//same options as min_filt less <mipmap settings>

	//<mipmap settings>
	// - GL_NEAREST_MIPMAP_NEAREST
	// - GL_LINEAR_MIPMAP_NEAREST
	// - GL_NEAREST_MIPMAP_LINEAR
	// - GL_LINEAR_MIPMAP_LINEAR
};



struct texture_b {
	unsigned texture_z = 0;
	texture_settings t_set = {GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR};

	inline unsigned id() {
		return texture_z;
	}

	inline void bind() {
		glBindTexture(GL_TEXTURE_2D, texture_z);
	}


	texture_b() {}

	void init(unsigned char* &data, const int &w, const int &h, const int &Chan) {
		glGenTextures(1, &texture_z);	//generating the id to reference the texture
						//1 because only want 1 texture

		glBindTexture(GL_TEXTURE_2D, texture_z);	//binding the texture so so any subsequent texture commands refer to this texture
							//texture is 2D so GL_TEXTURE_2D

		GLenum format;
		if(Chan == 1) {
			format = GL_RED;
		} else if (Chan == 3) {
			format = GL_RGB;
		} else if (Chan == 4) {
			format = GL_RGBA;
		} else {
			std::cerr << "image has a strange number of channels" << std::endl;
		}


		//generating the texture
		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);	//1 : texture target
														//	- will generate a texture on the bound texture object at the same target
														//	  (GL_TEXTURE_1D or GL_TEXTURE_3D will not be affected)
														//2 : the mipmap level (only for setting mipmaps manually)
														//	- current generating mipmaps automatically so 0
														//3 : the kind of format to store the texture
														//	- only have RGB textures (currently)
														//4 : width of texture
														//5 : height of texture
														//6 : always 0 (only there for legacy stuff)
														//7 : format of the source image
														//8 : datatype of the source image
														//	- stored as unsigned bytes
														//9 : actual image data
		glGenerateMipmap(GL_TEXTURE_2D);	//automatically generating the mipmap textures


		//setting texture settings
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, t_set.wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_set.wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, t_set.min_filt);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, t_set.mag_filt);

	}

	texture_b(unsigned char* &data, const int &w, const int &h, const int &Chan, texture_settings set) {
		std::cout << "using untested constructor" << std::endl;
		t_set = set;
		init(data, w, h, Chan);
	}

	texture_b(const std::string file, texture_settings set) {
		std::cout << "using untested constructor" << std::endl;
		t_set = set;
		texture_b(file.c_str());
	}

	texture_b(const std::string file_loc) {
		stbi_set_flip_vertically_on_load(true);

		int w, h, Chan;
		unsigned char* data = stbi_load(file_loc.c_str(), &w, &h, &Chan, 0);

		if (!data) {
			std::cerr << "Failed to load texture " << file_loc << std::endl;
		}

		init(data, w, h, Chan);

		//done with the texture
		stbi_image_free(data);
	}

};
