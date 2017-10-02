// Two-Dimensional Sierpinski Gasket
// Generated using randomly selected vertices and bisection

#include "Angel.h"

const int NumPoints = 5000;

//----------------------------------------------------------------------------

void
init( void )
{
    vec2 points[NumPoints];

    vec2 vertices[3] = {
        vec2( -1.0, -1.0 ), vec2( 0.0, 1.0 ), vec2( 1.0, -1.0 )
    };

    // Select an arbitrary initial point inside of the triangle
    //BIKIN SEGITIGA KAYAK DI PPT
//    points[0] = vec2( -0.5, -0.5 );
//    points[1] = vec2( -0.5, 0.0 );
//    points[2] = vec2( 0.0, 0.5 );
//    points[3] = vec2( 0.0, -0.5 );
//    points[4] = vec2( 0.0, 0.0 );
//    points[5] = vec2( 0.5, 0.5 );
//    points[6] = vec2( 0.5, -0.5 );
//    points[7] = vec2( 0.5, 0.0 );
//    points[8] = vec2( -0.5, 0.5 );

//VARIASI SEGITIGA
    points[0] = vec2( 0.1, 0.5 );
    points[1] = vec2( -0.4, 0.0 );
    points[2] = vec2( 0.1, 0.0 );

    points[3] = vec2( 0.25, 0.1 );
    points[4] = vec2( 0.15, 0.35 );
    points[5] = vec2( 0.1, 0.0 );

    points[6] = vec2( -0.5, 0.0 );
    points[7] = vec2( -0.25, 0.5 );
    points[8] = vec2( -0.25, 0.25 );

    points[9] = vec2( -0.1, 0.0 );
    points[10] = vec2( 0.2, 0.0 );
    points[11] = vec2( 0.0, -0.5 );

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
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

    glutCreateWindow( "SEGITIGA STANGSTUNG" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
