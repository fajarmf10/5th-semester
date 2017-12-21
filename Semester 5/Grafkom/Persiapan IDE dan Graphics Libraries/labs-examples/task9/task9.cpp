// Two-Dimensional Sierpinski Gasket
// Generated using randomly selected vertices and bisection

#include "Angel.h"

using namespace std;

const int NumPoints = 50000;
GLint sinAngle;
GLint cosAngle;
GLint angle;
GLint multipliers;
GLint transform;
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void
init( void )
{
    vec2 points[NumPoints];

    // Specifiy the vertices for a triangle
    vec2 vertices[3] = {
        vec2( -1.0, -1.0 ), vec2( 0.0, 1.0 ), vec2( 1.0, -1.0 )
    };

    // Select an arbitrary initial point inside of the triangle
    points[0] = vec2( 0.25, 0.50 );

    // compute and store N-1 new points
    for ( int i = 1; i < NumPoints; ++i ) {
        int j = rand() % 3;   // pick a vertex at random

        // Compute the point halfway between the selected vertex
        //   and the previous point
        points[i] = ( points[i - 1] + vertices[j] ) / 2.0;
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
    GLuint program = InitShader( "vshader24.glsl", "fshader24.glsl" );
    glUseProgram( program );
    transform = glGetUniformLocation(program, "mTransform");
//    multipliers = glGetUniformLocation(program, "multipliers");

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
//    glUniform1f(sinAngle, 0.5*sin(0.001*glutGet(GLUT_ELAPSED_TIME)));
//    glUniform1f(cosAngle, 2*cos(0.001*glutGet(GLUT_ELAPSED_TIME)));
//    glUniform1f( timeParam, glutGet(GLUT_ELAPSED_TIME)) ;
    glDrawArrays( GL_POINTS, 0, NumPoints );    // draw the points
    //glFlush();


//    ROTASI Y DAN Z
    mat3 mTransform = mat3(1.0,        0.0,         0.0,
	                       0.0, cos(0.001*glutGet(GLUT_ELAPSED_TIME)), -sin(0.001*glutGet(GLUT_ELAPSED_TIME)),
	                       0.0, sin(0.001*glutGet(GLUT_ELAPSED_TIME)),  cos(0.001*glutGet(GLUT_ELAPSED_TIME)) );

//  ROTASI X DAN Z
//    mat3 mTransform = mat3(1.0, cos(0.001*glutGet(GLUT_ELAPSED_TIME)), -sin(0.001*glutGet(GLUT_ELAPSED_TIME)),
//                           0.0,         1.0, 0.0,
//	                       0.0, sin(0.001*glutGet(GLUT_ELAPSED_TIME)),  cos(0.001*glutGet(GLUT_ELAPSED_TIME)) );

//    mat2 multipliers_mat = mat2( vec2(cos(0.001*glutGet(GLUT_ELAPSED_TIME)), -sin(0.001*glutGet(GLUT_ELAPSED_TIME))),
//                               vec2(sin(0.001*glutGet(GLUT_ELAPSED_TIME)), cos(0.001*glutGet(GLUT_ELAPSED_TIME))));
//  	glUniformMatrix2fv( multipliers, 1, GL_TRUE, multipliers_mat );
  	glUniformMatrix3fv(transform, 1, false, mTransform );

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

void idle()
{
    //bisa ngerun tapi nggak bisa muter krn vshader cuman bisa baca 1x doang.
    //kalo ada idle dia membaca sampe timeparam. jadi dia bisa muter sesuai timenya itu.
    glutPostRedisplay();
}
//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    //vshader


    //asli
    glutInit( &argc, argv );
    //glutInitDisplayMode( GLUT_RGBA );
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize( 512, 512 );

    // If you are using freeglut, the next two lines will check if
    // the code is truly 3.2. Otherwise, comment them out

    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "Sierpinski Gasket" );
    glutIdleFunc(idle);
    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
