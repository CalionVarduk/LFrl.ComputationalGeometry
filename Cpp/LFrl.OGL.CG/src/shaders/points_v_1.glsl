#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in float aSize;

uniform mat4 uProjection;

out VS_OUT {
	vec4 position;
	vec4 color;
	float size;
} vs_out;

void main()
{
	vs_out.position = uProjection * vec4(aPosition, 1.0f);
	gl_Position = vs_out.position;
	vs_out.color = aColor;
	vs_out.size = aSize;
}
