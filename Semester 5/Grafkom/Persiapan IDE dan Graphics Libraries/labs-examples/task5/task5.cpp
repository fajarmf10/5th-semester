// Two-Dimensional Sierpinski Gasket
// Generated using randomly selected vertices and bisection

#include "Angel.h"

const int NumPoints = 5000;
const int NumTriangles = 2;
const int NumVertices  = 3 * NumTriangles;

vec3 points[NumVertices] = {
    vec3(-0.5, -0.5, 0.0), vec3(-0.5, 0.5, 0.0), vec3(0.5, -0.5, 0.0),
    vec3(0.5, 0.5, 0.0),   vec3(0.5, -0.5, 0.0), vec3(-0.5, 0.5, 0.0)
};

GLint timeParam;

//----------------------------------------------------------------------------

void
init( void )
{
    vec3 points[NumVertices] = {
    vec3(0.5, -0.5, 0.0),
    vec3(-0.5, 0.5, 0.0),
    vec3(-0.5, -0.5, 0.0),
    vec3(-0.5, 0.5, 0.0),
    vec3(0.5, -0.5, 0.0),
    vec3(0.5, 0.5, 0.0)
};
    vec3 colors[NumVertices] = {
    vec3(0.0, 1.0, 1.0),
    vec3(0.0, 0.0, 0.0),
    vec3(0.0, 1.0, 1.0),
    vec3(0.0, 0.0, 1.0),
    vec3(1.0, 0.0, 1.0),
    vec3(0.0, 0.0, 0.0)
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

    timeParam = glGetUniformLocation(program, "time");

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

    //glEnable( GL_DEPTH_TEST );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); /* white background */
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    glUniform1f( timeParam, glutGet(GLUT_ELAPSED_TIME) );
    glDrawArrays( GL_TRIANGLES, 0, NumPoints );    // draw the points
    glFlush();
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

void
idle(void)
{
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );

    // If you are using freeglut, the next two lines will check if
    // the code is truly 3.2. Otherwise, comment them out

    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "NRP 15-171" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
