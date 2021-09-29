#version 330 core


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


layout (location = 0) in vec4 aPos;

layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;


void main()
{
	//gl_Position = vec4(aPos, 1.0);
    vec4 outPos = proj * view * model * aPos;
    gl_Position = outPos;
	//gl_Position = aPos;

	ourColor = aColor;
    TexCoord = aTexCoord * 1.0;
}
