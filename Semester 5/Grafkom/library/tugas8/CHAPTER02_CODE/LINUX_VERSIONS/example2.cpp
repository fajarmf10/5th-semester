/* sierpinski gasket with vertex arrays */

#include "Angel.h"

using namespace std;

const int NumTimesToSubdivide = 5;
const int NumTriangles = 243;  // 3^5 triangles generated
const int NumVertices  = 3 * NumTriangles;

vec3 points[NumVertices];
vec3 colors[NumVertices];
//GLint timeParam;
double sine,cose;
GLuint multiplier;
int Index = 0;


vec3 col_ver[6]= {
    vec3( 0.066, 0.459, 0.878),
    vec3( 0.411, 0.956, 0.625),
    vec3( 0.411, 0.956, 0.625),
    vec3( 0.411, 0.956, 0.625),
    vec3( 0.411, 0.956, 0.625),
    vec3( 0.066, 0.459, 0.878)
};

//----------------------------------------------------------------------------

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
        triangle( a, b, c ,0);    // draw triangle at end of recursion
    }
}

//----------------------------------------------------------------------------

void
init( void )
{
    vec3 vertices[3] = {
        vec3( -1.0, -1.0, 0 ), vec3( 0.0, 1.0, 0 ), vec3( 1.0, -1.0, 0 )
    };

    // Subdivide the original triangle
    divide_triangle( vertices[0], vertices[1], vertices[2],
                     NumTimesToSubdivide );


    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
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
    //timeParam=glGetUniformLocation(program,"time");
    //sine=glGetUniformLocation(program,"sine");
    //cose=glGetUniformLocation(program,"cose");
    multiplier=glGetUniformLocation(program,"multiplier");
    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); /* white background */
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glUniform1f(timeParam,glutGet(GLUT_ELAPSED_TIME));
    //glUniform1f(sine,sin(0.001*glutGet(GLUT_ELAPSED_TIME)));
    //glUniform1f(cose,cos(0.001*glutGet(GLUT_ELAPSED_TIME)));
    sine = sin(0.001*glutGet(GLUT_ELAPSED_TIME));
    cose = cos(0.001*glutGet(GLUT_ELAPSED_TIME));
    mat3 multi_mat = mat3(cose,-sine,0.0,
                          sine,cose,0.0,
                          0.0,0.0,1.0);
    glUniformMatrix3fv(multiplier,1,false,multi_mat);
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    //glFlush();
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

void idling(){
    glutPostRedisplay();
}

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Simple GLSL example" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutIdleFunc(idling);

    glutMainLoop();
    return 0;
}
