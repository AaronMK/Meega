#version 400

in vec3 vertColor;

void main()
{
	gl_FragColor = vec4(vertColor, 1.0);
}