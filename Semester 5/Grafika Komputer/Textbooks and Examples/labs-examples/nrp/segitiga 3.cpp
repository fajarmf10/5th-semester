// Two-Dimensional Sierpinski Gasket
// Generated using randomly selected vertices and bisection

#include "Angel.h"


const int NumPoints = 5000;

//----------------------------------------------------------------------------

void
init( void )
{
    vec2 points[NumPoints];

//0.3 sampe -0.1

// angka 1

    float verright0=0.3;
    for(int i=240;i<279;i++)
    {
        points[i] = vec2 (-0.7, verright0);
        verright0-=0.01;
    }
//angka 5
float hortop5=-0.45;
    for(int i=100;i<119;i++)
    {
        points[i] = vec2 (hortop5, 0.3 );
        hortop5+=0.01;
    }

    float verleft5=0.3;
    for(int i=120;i<139;i++)
    {
        points[i] = vec2 (-0.45,verleft5);
        verleft5-=0.01;
    }
    float hormid5 = -0.45;
    for(int i=150;i<169;i++)
    {
        points[i] = vec2 (hormid5, 0.11 );
        hormid5+=0.01;
    }

float verright5=0.11;
    for(int i=170;i<189;i++)
    {
        points[i] = vec2 (-0.26,verright5);
        verright5-=0.01;
    }
float horbot5 = -0.45;
    for(int i=190;i<209;i++)
    {
        points[i] = vec2 (horbot5, -0.08 );
        horbot5+=0.01;
    }

// angka 7
    float hortop7=-0.1;
    for(int i=384;i<403;i++)
    {
        points[i] = vec2 (hortop7, 0.3 );
        hortop7+=0.01;
    }

    float verright7=0.3;
    for(int i=403;i<442;i++)
    {
        points[i] = vec2 (0.09,verright7);
        verright7-=0.01;
    }

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
    glDrawArrays( GL_POINTS, 0, NumPoints );    // draw the points
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

    glutCreateWindow( "Fajar Maulana Firdaus" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}

