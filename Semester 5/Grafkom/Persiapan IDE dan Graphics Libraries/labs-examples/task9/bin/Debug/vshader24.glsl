#version 150

in  vec3 vPosition;
in  vec3 vColor;
out vec4 color;
uniform mat3 mTransform;

void
main()
{
//  float angle = 0.001*time;
//	gl_Position = vec4(vPosition.x*cosAngle - vPosition.y*sinAngle, vPosition.x*sinAngle + vPosition.y*cosAngle, 0.0, 1.0);
    gl_Position = vec4(mTransform*vPosition, 1.0);
    color = vec4( vColor, 1.0 );
}
