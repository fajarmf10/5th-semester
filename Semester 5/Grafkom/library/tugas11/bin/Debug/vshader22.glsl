#version 150

in vec3 vPosition;
in vec3 vColor;
out vec4 color;
uniform mat3 multiplier;
void
main()
{
	vec3 temp = multiplier * vPosition;
    gl_Position = vec4(temp,1.0);
	color = vec4(vColor,1.0);
}
