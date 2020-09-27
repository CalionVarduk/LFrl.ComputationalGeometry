#version 330 core

layout(points) in;
layout(points, max_vertices = 1) out;

in VS_OUT {
	vec4 position;
	vec4 color;
	float size;
} gs_in[];

out GS_OUT {
	out vec4 color;
} gs_out;

void main()
{
	vec4 position = gl_in[0].gl_Position;
	gs_out.color = gs_in[0].color;
	
	gl_Position = position;
	EmitVertex();

	EndPrimitive();
}
