#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2; 
uniform float mix_per;

void main()
{
	//the last argument of mix should be an alpha mask source -- not doing it properly here
	//https://www.khronos.org/opengl/wiki/Multitexture_with_GLSL
	FragColor = mix( texture(texture1, TexCoord), texture(texture2, TexCoord), texture(texture2, TexCoord).a*mix_per);
}
