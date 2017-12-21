#version 150

in vec3 vPosition;
in vec3 vColor;
out vec4 color;
uniform float time;
void
main()
{
	float angle=0.001*time;
    gl_Position = vec4(vPosition.x*cos(angle)-vPosition.y*sin(angle),
						vPosition.x*sin(angle)+vPosition.y*cos(angle),
						0.0,
						1.0);
	color = vec4((vColor.x*sin(angle)+vColor.y*cos(angle)),
					(vColor.x*sin(angle)+vColor.y*sin(angle)),
					(vColor.x+vColor.y)*cos(angle)/5,
					1.0
					);
}
