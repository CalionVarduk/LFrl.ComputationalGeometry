#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in float in_size;

uniform mat4 u_projection;
uniform mat4 u_model;

out vec4 v_position;
out vec4 v_color;
out float v_size;

void main()
{
	v_position = u_projection * u_model * vec4(in_position, 1.0f);
	gl_Position = v_position;
	v_color = in_color;
	v_size = in_size;
}
