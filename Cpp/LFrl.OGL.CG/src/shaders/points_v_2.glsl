#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in float aSize;

uniform vec2 uScale;

out VS_OUT {
	vec4 color;
	vec2 halfSize;
} vs_out;

void main()
{
	gl_Position = vec4(aPosition, 1.0f);
	float halfSize = aSize * 0.5f;
	vs_out.color = aColor;
	vs_out.halfSize = vec2(halfSize, halfSize) / uScale;
}
