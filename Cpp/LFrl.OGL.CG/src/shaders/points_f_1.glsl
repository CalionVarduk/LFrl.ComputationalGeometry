#version 330 core

in GS_OUT {
	vec4 color;
} fs_in;

out vec4 fColor;

void main()
{
	fColor = fs_in.color;
}
