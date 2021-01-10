#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include <cmath>
#include <algorithm>	//for std::clamp
#include <math.h>	//for std::fmod

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

	glm::vec3 cameraDirection;
	glm::vec3 World_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right, up;

	virtual glm::mat4 view_matrix() {
		return glm::mat4(1.0f);
	} 
	virtual void process_inputs(GLFWwindow* window, float deltaTime) {}

	virtual void process_mouse(GLFWwindow* window, double xpos, double ypos) {}
};


struct camera_rotation : public camera_b {
	float r;	//radius of rotation
	float theta = M_PI/2, phi = M_PI/2;
	glm::vec3 target;

	float up_speed = 2.0f, left_speed = 2.0f, zoom_speed = 2.0f;

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

	virtual void process_inputs(GLFWwindow* window, float deltaTime) override {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	{
			phi -= up_speed * deltaTime;
			if (phi < 0.01)
				phi = 0.01;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	{
			phi += up_speed * deltaTime;
			if (phi > M_PI - 0.01)
				phi = M_PI - 0.01;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	{	
			//theta += left_speed * deltaTime;
			theta = std::fmod(theta + left_speed*deltaTime, 360.0f);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	{	
			//theta -= left_speed * deltaTime;
			theta = std::fmod(theta - left_speed*deltaTime, 360.0f);
		}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)	{	
			r /= (1+zoom_speed * deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)	{	
			r *= (1+zoom_speed * deltaTime);
		}

		//theta = std::fmod(theta, 2*M_PI);	//stopping theta from getting very very large

		//using spherical coordinates
		position = glm::vec3(r*cos(theta)*sin(phi), r*cos(phi), r*sin(theta)*sin(phi) );
	}

};



struct camera_player : public camera_b {
	float movement_speed = 8.0f;
	float up_speed = 8.0f;	//how quickly move up
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::vec3 low_front;	//front variable used for movement

	//variables for processing the mouse movement
	bool firstMouse = true;
	double lastx, lasty;
	float mouse_sensitivity = 0.005f;
	float theta = -M_PI/2,  phi = M_PI/2;

	camera_player(glm::vec3 init_pos = glm::vec3(0.0f, 0.0f, 0.0f))  {
		position = init_pos;
	}

	virtual glm::mat4 view_matrix() override {
		right = glm::normalize(glm::cross(World_up, front));
		up = glm::cross(front, right);

		//glm::normalized doesn't work if the input vector is the 0 vector
		// - this should never be the case but checking anyway
		if (front.x == 0 || front.z == 0)
			front.x = 0.001;
		low_front = glm::normalize(glm::vec3(front.x, 0, front.z));


		return glm::lookAt(position, position + front, up);
	}

	virtual void process_inputs(GLFWwindow* window, float deltaTime) override {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	{
			position += movement_speed * low_front * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	{
			position -= movement_speed * low_front * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	{	
			position += movement_speed * right * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	{	
			position -= movement_speed * right * deltaTime;
		}


		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)	{	
			position.y += up_speed * deltaTime;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)	{	
			position.y -= up_speed * deltaTime;
		}
	}

	virtual void process_mouse(GLFWwindow* window, double xpos, double ypos) override {
		//no need for delta time because the movement is based on the change in mouse position per frame
		// - if the framerate is really hight, the mouse movement per frame will be really low
		// - not increasing a variable by a fixed ammount like in process_inputs

		if (firstMouse) {
			firstMouse = false;
			lastx = xpos;
			lasty = ypos;
			return;
		}

		float xoffset = xpos - lastx;
		float yoffset = ypos - lasty;

		xoffset *= mouse_sensitivity;	//else the screen would move way too much in one frame
		yoffset *= mouse_sensitivity;	
		

		//theta += xoffset;	//implemented in fmod below
		phi += yoffset;
		
		phi = std::clamp(phi, (float)0.01, float(M_PI-0.01));	//stopping the ability to be able to do flips with the mouse
		theta = std::fmod(theta + xoffset, 2*M_PI);	//stopping theta from getting very very large

		//using spherical coordinates
		front = glm::vec3(cos(theta)*sin(phi), cos(phi), sin(theta)*sin(phi) );

		//setting the variables for next time the function is called
		lastx = xpos;
		lasty = ypos;
	}

};
