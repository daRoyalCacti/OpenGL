#version 330 core
out vec4 FragColor;

uniform vec4 ourColor;	//set this value in OpenGL code (uniforms are the same for any shader stage)
uniform vec3 lightDir;

in vec3 Normal;

void main(){
	vec3 norm = normalize(Normal);
	vec3 dir = normalize(-lightDir);
	float diff = max(dot(norm, dir), 0.0);

	FragColor = diff * ourColor;
}
