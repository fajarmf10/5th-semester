/* sierpinski gasket with vertex arrays */

#include "Angel.h"

using namespace std;

const int NumTimesToSubdivide = 5;
const int NumTriangles = 6;  // 3^5 triangles generated
const int NumVertices  = 3 * NumTriangles;

GLint sinAngle, cosAngle;
GLint transform, timeParam;

vec3 points[NumVertices];
int Index = 0;

//----------------------------------------------------------------------------

void
triangle( const vec3& a, const vec3& b, const vec3& c )
{
    points[Index++] = a;
    points[Index++] = b;
    points[Index++] = c;
}

//----------------------------------------------------------------------------

void
divide_triangle( const vec3& a, const vec3& b, const vec3& c, int count )
{
    if ( count > 0 ) {
        vec3 v0 = ( a + b ) / 2.0;
        vec3 v1 = ( a + c ) / 2.0;
        vec3 v2 = ( b + c ) / 2.0;
        divide_triangle( a, v0, v1, count - 1 );
        divide_triangle( c, v1, v2, count - 1 );
        divide_triangle( b, v2, v0, count - 1 );
    }
    else {
        triangle( a, b, c );    // draw triangle at end of recursion
    }
}

//----------------------------------------------------------------------------

void
init( void )
{
    vec3 vertex[18] = {
    vec3(-0.5, -0.5, 0.0), vec3(-0.5, 0.5, 0.0), vec3(0.5, -0.5, 0.0),
    vec3(0.5, 0.5, 0.0),   vec3(0.5, -0.5, 0.0), vec3(-0.5, 0.5, 0.0),
    vec3(-0.5, -0.5, 0.0), vec3(-0.5, 0.5, 0.0), vec3(0.5, -0.5, 0.0),
    vec3(0.5, 0.5, 0.0),   vec3(0.5, -0.5, 0.0), vec3(-0.5, 0.5, 0.0),
    vec3(-0.5, -0.5, 0.0), vec3(-0.5, 0.5, 0.0), vec3(0.5, -0.5, 0.0),
    vec3(0.5, 0.5, 0.0),   vec3(0.5, -0.5, 0.0), vec3(-0.5, 0.5, 0.0)};
    triangle (vertex[0], vertex[1], vertex[2]);
    triangle (vertex[3], vertex[4], vertex[5]);
    triangle (vertex[6], vertex[7], vertex[8]);
    triangle (vertex[9], vertex[10], vertex[11]);
    triangle (vertex[12], vertex[13], vertex[14]);
    triangle (vertex[15], vertex[16], vertex[17]);

    vec3 colors[18] = {
    vec3(0,0,0), vec3(0,1,1), vec3(0,0,0),
	vec3(0,1,1), vec3(0,0,0), vec3(0,1,1),
	vec3(0,0,0), vec3(0,1,1), vec3(0,0,0),
	vec3(0,1,1), vec3(0,0,0), vec3(0,1,1),
	vec3(0,0,0), vec3(0,1,1), vec3(0,0,0),
	vec3(0,1,1), vec3(0,0,0), vec3(0,1,1)
	/*vec3(1.0, 1.0, 0.0) , vec3(0.0, 1.0, 0.0) ,vec3(1.0, 1.0, 0.0) ,
	vec3(0.0, 1.0, 0.0) , vec3(1.0, 1.0, 0.0) , vec3(0.0, 1.0, 0.0),
	vec3(1.0, 1.0, 0.0) , vec3(0.0, 1.0, 0.0) ,vec3(1.0, 1.0, 0.0) ,
	vec3(0.0, 1.0, 0.0) , vec3(1.0, 1.0, 0.0) , vec3(0.0, 1.0, 0.0),
	vec3(1.0, 1.0, 0.0) , vec3(0.0, 1.0, 0.0) ,vec3(1.0, 1.0, 0.0) ,
	vec3(0.0, 1.0, 0.0) , vec3(1.0, 1.0, 0.0) , vec3(0.0, 1.0, 0.0)*/
	};

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // First, we create an empty buffer of the size we need by passing
    //   a NULL pointer for the data values
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
		  NULL, GL_STATIC_DRAW );

    // Next, we load the real data in parts.  We need to specify the
    //   correct byte offset for placing the color data after the point
    //   data in the buffer.  Conveniently, the byte offset we need is
    //   the same as the size (in bytes) of the points array, which is
    //   returned from "sizeof(points)".
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader24.glsl", "fshader24.glsl" );
    glUseProgram( program );

    transform = glGetUniformLocation(program, "mTransform");

    // Initialize the vertex position attribute from the vertex shader
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    // Likewise, initialize the vertex color attribute.  Once again, we
    //    need to specify the starting offset (in bytes) for the color
    //    data.  Just like loading the array, we use "sizeof(points)"
    //    to determine the correct value.
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );

    glEnable( GL_DEPTH_TEST ); //hidden surface removal

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); /* white background */
}

//----------------------------------------------------------------------------

void
display( void )
{
    //glClear( GL_COLOR_BUFFER_BIT );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //hidden surface removal
    glUniform1f( timeParam, glutGet(GLUT_ELAPSED_TIME) );
    //Rotasi terhadap sumbu Z
    mat3 mTransform = mat3(cos(0.001*glutGet(GLUT_ELAPSED_TIME)), -sin(0.001*glutGet(GLUT_ELAPSED_TIME)), 0.0,
	                       sin(0.001*glutGet(GLUT_ELAPSED_TIME)),  cos(0.001*glutGet(GLUT_ELAPSED_TIME)), 0.0,
                           0.0,        0.0,         1.0);

    glUniformMatrix3fv( transform, 1, false, mTransform );

    glDrawArrays( GL_TRIANGLES, 0, 6 );

    //Rotasi terhadap sumbu X
    mat3 mTransform1 = mat3(1.0,        0.0,         0.0,
	                       0.0, cos(0.001*glutGet(GLUT_ELAPSED_TIME)), -sin(0.001*glutGet(GLUT_ELAPSED_TIME)),
	                       0.0, sin(0.001*glutGet(GLUT_ELAPSED_TIME)),  cos(0.001*glutGet(GLUT_ELAPSED_TIME)) );

    glUniformMatrix3fv( transform, 1, false, mTransform1 );

    glDrawArrays( GL_TRIANGLES, 6, 6 );

    //ROtasi terhadap sumbu Y
    mat3 mTransform2 = mat3(cos(0.001*glutGet(GLUT_ELAPSED_TIME)), 0.0, -sin(0.001*glutGet(GLUT_ELAPSED_TIME)),
                           0.0,        1.0,         0.0,
	                       -sin(0.001*glutGet(GLUT_ELAPSED_TIME)),  0.0, cos(0.001*glutGet(GLUT_ELAPSED_TIME)) );

    glUniformMatrix3fv( transform, 1, false, mTransform2 );

    glDrawArrays( GL_TRIANGLES, 12, 6 );

    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

void idle (){
    glutPostRedisplay();
}

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    //glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //hidden surface removal
    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Task 11" );

    glewInit();
    glutIdleFunc(idle);

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
