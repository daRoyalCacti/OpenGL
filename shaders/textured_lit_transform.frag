#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;

// texture samplers
uniform sampler2D t; 

uniform vec3 lightDir;

void main() {
	vec3 norm = normalize(Normal);
	vec3 dir = normalize(-lightDir);
	float diff = max(dot(norm, dir), 0.0);

	FragColor = diff*texture(t, TexCoord);
}
