#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;

uniform mat4 transform;
uniform mat4 model;

void main(){
	Normal = mat3(transpose(inverse(model) )) * aNormal;
	gl_Position = transform * vec4(aPos, 1.0);
}
