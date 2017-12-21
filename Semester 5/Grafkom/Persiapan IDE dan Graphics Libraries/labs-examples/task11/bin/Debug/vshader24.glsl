#version 150

in  vec3 vPosition;
in  vec3 vColor;
out vec4 color;
uniform mat3 mTransform;

void
main()
{
    //gl_Position.xyz = mTransform*vPosition.xyz;
	gl_Position = vec4(mTransform*vPosition, 1.0);
    color = vec4( vColor, 1.0 );
}
