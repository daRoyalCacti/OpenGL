#version 330 core

layout (location = 0) in vec3 aPos;		//position of vertex
layout (location = 1) in vec3 aColor;	//color of vertex

out vec3 ourColor;		//color to pass to fragment shader

void main(){
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
}
