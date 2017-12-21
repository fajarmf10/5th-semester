/* sierpinski gasket with vertex arrays */

#include "Angel.h"

using namespace std;

const int NumTimesToSubdivide = 0;
const int NumTriangles = 2;  // 3^5 triangles generated
const int NumVertices  = 3 * NumTriangles;

vec3 points[NumVertices];
vec3 colors[NumVertices];
int Index = 0;

//----------------------------------------------------------------------------

vec3 col_ver[6]= {
    vec3( 0.066, 0.459, 0.878),
    vec3( 0.411, 0.956, 0.325),
    vec3( 0.647, 0.780, 1.0),
    vec3( 0.878, 0.459, 0.066),
    vec3( 0.674, 0.956, 0.411),
    vec3( 1.0, 0.780, 0.647)
};


void
triangle( const vec3& a, const vec3& b, const vec3& c,int i)
{
    colors[Index]=col_ver[i];
    points[Index++] = a;
    colors[Index]=col_ver[i+1];
    points[Index++] = b;
    colors[Index]=col_ver[i+2];
    points[Index++] = c;
}

//----------------------------------------------------------------------------


//----------------------------------------------------------------------------

void
init( void )
{

    triangle(vec3(-0.5,0.5,0.0),vec3(-0.5,-0.5,0.0),vec3(0.5,0.5,0.0),0);
    triangle(vec3(0.5,-0.5,0.0),vec3(-0.5,-0.5,0.0),vec3(0.5,0.5,0.0),3);


    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );


    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
                  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );


    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader22.glsl", "fshader22.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );

    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    //glClearColor( 0.0, 0.0, 0.0, 0.0 ); /* white background */
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
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
    glutInitWindowSize( 256, 256 );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Simple GLSL example" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}
