#version 400

in vec3 VertexPosition;
in vec3 VertexColor;

uniform View
{
	matrix4x4 modelview;
	matrix4x4 projection;
};

out vec3 Color;

void main()
{
	Color = VertexColor;
	gl_Position = vec4(VertexPosition, 1.0);
}