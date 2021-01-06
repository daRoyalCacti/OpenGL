#pragma once

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
	int width, height, nrChannels;
	unsigned texture;
	texture_settings t_set = {GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR};

	texture_b() {}

	texture_b(unsigned char* data, const int w, const int h, const int Chan) : width(w), height(h), nrChannels(Chan) {
		glGenTextures(1, &texture);	//generating the id to reference the texture
						//1 because only want 1 texture

		glBindTexture(GL_TEXTURE_2D, texture);	//binding the texture so so any subsequent texture commands refer to this texture
							//texture is 2D so GL_TEXTURE_2D

		//setting texture settings
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, t_set.wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_set.wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, t_set.min_filt);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, t_set.mag_filt);



		//generating the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);	//1 : texture target
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
														//	- currently RGB
														//8 : datatype of the source image
														//	- stored as unsigned bytes
														//9 : actual image data
		glGenerateMipmap(GL_TEXTURE_2D);	//automatically generating the mipmap textures

		//done with the texture
		stbi_image_free(data);

	}

	texture_b(unsigned char* data, const int w, const int h, const int Chan, texture_settings set) {
		t_set = set;
		texture_b(data, w, h, Chan);
	}

	texture_b(const std::string file, texture_settings set) {
		t_set = set;
		texture_b(file.c_str());
	}

	texture_b(const std::string file_loc) {
		int w, h, Chan;
		unsigned char* data = stbi_load(file_loc.c_str(), &w, &h, &Chan, 0);

		if (!data) {
			std::cerr << "Failed to load texture " << file_loc << std::endl;
		}

		texture_b(data, w, h, Chan);
	}

};
