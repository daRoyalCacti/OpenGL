#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "global.h"

struct transformation {
	glm::mat4 proj = glm::mat4(1.0f), view = glm::mat4(1.0f), model = glm::mat4(1.0f);
	//proj - orthonormal or projection matrix
	//view - camera style
	//model - rotations, scales, translations and similar

	transformation() {
		proj = glm::perspective(glm::radians(settings::fov), (float)settings::viewport_width / (float)settings::viewport_height, settings::near_plane, settings::far_plane);
	}


	inline glm::mat4 get_matrix() {	//the data to be passed to the shader to multiply the vertex coordinates
		return proj*view*model;
	}
};
