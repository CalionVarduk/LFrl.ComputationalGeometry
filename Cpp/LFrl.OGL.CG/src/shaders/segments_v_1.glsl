#version 330 core

layout(location = 0) in vec3 aStart;
layout(location = 1) in vec2 aDirection;
layout(location = 2) in float aLength;
layout(location = 3) in float aSize;
layout(location = 4) in vec4 aColor;

uniform vec2 uScale;

out VS_OUT {
	vec4 color;
	vec4 end;
	vec2 halfSize;
} vs_out;

void main()
{
	vec3 end = aStart + vec3(aDirection, 0.0f) * aLength;
	vec2 perpendicular = vec2(-aDirection.y, aDirection.x);

	gl_Position = vec4(aStart, 1.0f);
	
	vs_out.end = vec4(end, 1.0f);
	vs_out.color = aColor;
	vs_out.halfSize = vec2(-aDirection.y, aDirection.x) * (aSize * 0.5f) / uScale;
}
