/* sierpinski gasket with vertex arrays */

#include "Angel.h"

using namespace std;

const int NumTimesToSubdivide = 5;
const int NumTriangles = 243;  // 3^5 triangles generated
const int NumVertices  = 12 * NumTriangles;

vec2 points[NumVertices];
vec4 colors[NumVertices];
int Index = 0;

//----------------------------------------------------------------------------

vec4 col_ver[3]= {
    vec4( 0.066, 0.459, 0.878, 0.25 ),
    vec4( 0.411, 0.674, 0.956, 0.25 ),
    vec4( 0.647, 0.780, 1.0, 0.25 )
};


void
triangle( const vec2& a, const vec2& b, const vec2& c,int i)
{
    colors[Index]=col_ver[i];
    points[Index++] = a;
    colors[Index]=col_ver[i];
    points[Index++] = b;
    colors[Index]=col_ver[i];
    points[Index++] = c;
}

//----------------------------------------------------------------------------

void
divide_triangle( const vec2& a, const vec2& b, const vec2& c, int count )
{
    if ( count > 0 ) {
        vec2 v0 = ( a + b ) / 2.0;
        vec2 v1 = ( a + c ) / 2.0;
        vec2 v2 = ( b + c ) / 2.0;
        divide_triangle( a, v0, v1, count - 1 );
        divide_triangle( c, v1, v2, count - 1 );
        divide_triangle( b, v2, v0, count - 1 );
    }
    else {
        triangle( a, b, c ,1);    // draw triangle at end of recursion
    }
}

//----------------------------------------------------------------------------

void
init( void )
{

    triangle(vec2(-0.40,-0.20),vec2(0.22,0.45),vec2(0.18,0.25),2);
    triangle(vec2(0.18,0.25),vec2(0.16,0.15),vec2(0.10,0.24),2);
    triangle(vec2(0.10,0.24),vec2(0.16,0.15),vec2(0.07,-0.30),2);
    triangle(vec2(0.10,0.24),vec2(0.07,-0.30),vec2(0.00,-0.23),2);
    triangle(vec2(0.07,-0.30),vec2(0.04,-0.45),vec2(-0.37,0.18),2);

    triangle(vec2(-0.60,-0.10),vec2(0.02,0.55),vec2(-0.02,0.35),1);
    triangle(vec2(-0.02,0.35),vec2(-0.04,0.25),vec2(-0.10,0.34),1);
    triangle(vec2(-0.10,0.34),vec2(-0.04,0.25),vec2(-0.13,-0.20),1);
    triangle(vec2(-0.10,0.34),vec2(-0.13,-0.20),vec2(-0.20,-0.13),1);
    triangle(vec2(-0.13,-0.20),vec2(-0.16,-0.35),vec2(-0.57,0.28),1);

    triangle(vec2(-0.80,0.0),vec2(-0.18,0.65),vec2(-0.22,0.45),0);
    triangle(vec2(-0.22,0.45),vec2(-0.24,0.35),vec2(-0.3,0.44),0);
    triangle(vec2(-0.3,0.44),vec2(-0.24,0.35),vec2(-0.33,-0.1),0);
    triangle(vec2(-0.3,0.44),vec2(-0.33,-0.1),vec2(-0.4,-0.03),0);
    triangle(vec2(-0.33,-0.1),vec2(-0.36,-0.25),vec2(-0.77,0.37),0);





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
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );

    //glClearColor( 1.0, 1.0, 1.0, 1.0 );
    glClearColor( 0.0, 0.0, 0.0, 0.0 ); /* white background */
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
