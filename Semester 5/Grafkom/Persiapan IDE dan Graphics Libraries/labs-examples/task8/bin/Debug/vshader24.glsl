#version 150

in  vec2 vPosition;
in  vec3 vColor;
out vec4 color;
uniform mat2 multipliers;

void
main()
{
//  float angle = 0.001*time;
//	gl_Position = vec4(vPosition.x*cosAngle - vPosition.y*sinAngle, vPosition.x*sinAngle + vPosition.y*cosAngle, 0.0, 1.0);
    gl_Position = vec4(multipliers*vPosition, 0.0, 1.0);
    color = vec4( vColor, 1.0 );
}
