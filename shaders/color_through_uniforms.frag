#version 330 core

out vec4 FragColor;
uniform vec4 ourColor;	//set this value in OpenGL code (uniforms are the same for any shader stage)

void main(){
	FragColor = ourColor;
}
