#pragma once

#include <glad/glad.h>
#include <iostream>

inline void print_num_vertex_attribtes() {
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum number of vertex attributes supported : " << nrAttributes << std::endl;
}
