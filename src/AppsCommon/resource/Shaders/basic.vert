#version 400

uniform vec3 Color;
uniform mat4x4 modelview;
uniform mat4x4 projection;

in vec3 VertexPosition;
out vec3 vertColor;

void main()
{
	gl_Position = projection * modelview * vec4(VertexPosition, 1.0);
	vertColor = Color;
}