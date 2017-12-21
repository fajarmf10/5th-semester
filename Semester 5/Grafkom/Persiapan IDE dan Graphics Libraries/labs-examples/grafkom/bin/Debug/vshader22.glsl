#version 150

in vec4 vPosition;
in vec3 vColor;
out vec4 color;
uniform mat4 multiplier;
void
main()
{
	
    gl_Position = multiplier * vPosition;
	color = vec4(vColor,1.0);
}
