#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include <cmath>

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




struct camera_b {
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 cameraDirection;
	glm::vec3 World_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right, up;

	virtual glm::mat4 view_matrix() {
		return glm::mat4(1.0f);
	} 
	virtual void process_inputs(GLFWwindow* window) {}
};


struct camera_rotation : public camera_b {
	float r;	//radius of rotation
	float theta = M_PI/2, phi = M_PI/2;

	float up_speed = 0.02, left_speed = 0.02, zoom_speed = 1.02;

	camera_rotation(float init_radius) : r(init_radius) {
		target = glm::vec3(0.0f, 0.0f, 0.0f);
		position = glm::vec3(0.0f, 0.0f, r);
	}

	virtual glm::mat4 view_matrix() override {
		cameraDirection = glm::normalize(position - target);	//points in the reverse dirction of the target
		right = glm::normalize(glm::cross(World_up, cameraDirection));
		up = glm::cross(cameraDirection, right);


		return glm::lookAt(position, target, up);
	}

	virtual void process_inputs(GLFWwindow* window) override {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	{
			phi -= up_speed;
			if (phi < 0.01)
				phi = 0.01;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	{
			phi += up_speed;
			if (phi > M_PI - 0.01)
				phi = M_PI - 0.01;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	{	
			theta += left_speed;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	{	
			theta -= left_speed;
		}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)	{	
			r /= zoom_speed;
		}

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)	{	
			r *= zoom_speed;
		}

		position = glm::vec3(r*cos(theta)*sin(phi), r*cos(phi), r*sin(theta)*sin(phi) );
	}

};
