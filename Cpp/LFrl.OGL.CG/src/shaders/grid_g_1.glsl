#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in VS_OUT {
	vec4 color;
	vec2 halfSize;
} gs_in[];

uniform mat4 uProjection;

out GS_OUT {
	out vec4 color;
} gs_out;

void BuildVertex(vec4 position, vec2 offset)
{
	gl_Position = uProjection * (position + vec4(offset, 0.0f, 0.0f));
	EmitVertex();
}

void main()
{
	vec4 position = gl_in[0].gl_Position;
	vec2 halfSize = gs_in[0].halfSize;
	gs_out.color = gs_in[0].color;

	BuildVertex(position, vec2(-halfSize.x, halfSize.y));
	BuildVertex(position, vec2(halfSize.x, halfSize.y));
	BuildVertex(position, vec2(-halfSize.x, -halfSize.y));
	BuildVertex(position, vec2(halfSize.x, -halfSize.y));

	EndPrimitive();
}
