#version 150

in vec3 vPosition;
in vec3 vColor;
out vec4 color;

uniform float sine;
uniform float cose;
void
main()
{
    gl_Position = vec4(vPosition.x*cose-vPosition.y*sine,
						vPosition.x*sine+vPosition.y*cose,
						0.0,
						1.0);
	color = vec4(vColor,1.0);
}
