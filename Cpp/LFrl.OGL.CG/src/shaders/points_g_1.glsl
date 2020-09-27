#version 330 core

layout(points) in;
layout(line_strip, max_vertices = 3) out;

in VS_OUT {
	vec4 color;
	float halfSize;
} gs_in[];

uniform mat4 uProjection;

out GS_OUT {
	out vec4 color;
} gs_out;

void main()
{
	vec4 position = gl_in[0].gl_Position;
	float halfSize = gs_in[0].halfSize;
	gs_out.color = gs_in[0].color;
	
	gl_Position = uProjection * (position - vec4(halfSize, 0.0f, 0.0f, 0.0f));
	EmitVertex();
	gl_Position = uProjection * position;
	EmitVertex();
	gl_Position = uProjection * (position + vec4(halfSize, halfSize, 0.0f, 0.0f));
	EmitVertex();

	EndPrimitive();
}
