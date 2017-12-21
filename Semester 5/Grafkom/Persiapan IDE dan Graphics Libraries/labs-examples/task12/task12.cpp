/* sierpinski gasket with vertex arrays */

#include "Angel.h"

const int NumTriangles = 12;  // 4 triangles / tetrahedron
const int NumVertices = 3 * NumTriangles;      // 3 vertices / triangle
//GLuint timeParam;
GLint sinAngle, cosAngle, angle;
GLint multipliers;
GLint timeParam;
GLint transform;

vec3 points[NumVertices] = {
   vec3( -0.5, -0.5,  0.5 ), vec3(  0.5, -0.5,  0.5 ), vec3( -0.5,  0.5, 0.5 ),  vec3(  0.5,  0.5,  0.5 ), vec3( -0.5,  0.5,  0.5 ), vec3(  0.5, -0.5, 0.5 ),
   vec3( -0.5, -0.5, -0.5 ), vec3(  0.5, -0.5, -0.5 ), vec3( -0.5,  0.5, -0.5 ), vec3(  0.5,  0.5, -0.5 ), vec3( -0.5,  0.5, -0.5 ), vec3(  0.5, -0.5, -0.5 ),
   vec3(  0.5, -0.5, -0.5 ), vec3(  0.5,  0.5, -0.5 ), vec3(  0.5, -0.5,  0.5 ), vec3(  0.5,  0.5,  0.5 ), vec3(  0.5, -0.5,  0.5 ), vec3(  0.5,  0.5, -0.5 ),
   vec3( -0.5, -0.5, -0.5 ), vec3( -0.5,  0.5, -0.5 ), vec3( -0.5, -0.5,  0.5 ), vec3( -0.5,  0.5,  0.5 ), vec3( -0.5, -0.5,  0.5 ), vec3( -0.5,  0.5, -0.5 ),
   vec3( -0.5,  0.5, -0.5 ), vec3( -0.5,  0.5,  0.5 ), vec3(  0.5,  0.5, -0.5 ), vec3(  0.5,  0.5,  0.5 ), vec3(  0.5,  0.5, -0.5 ), vec3( -0.5,  0.5,  0.5 ),
   vec3( -0.5, -0.5, -0.5 ), vec3( -0.5, -0.5,  0.5 ), vec3(  0.5, -0.5, -0.5 ), vec3(  0.5, -0.5,  0.5 ), vec3(  0.5, -0.5, -0.5 ), vec3( -0.5, -0.5,  0.5 ),
};


vec3 colors[NumVertices] = {
    vec3(0,1,1), vec3(0,0,0), vec3(0,1,0), vec3(0,0,1), vec3(0,1,0), vec3(0,0,0),
    vec3(0,1,1), vec3(0,0,0), vec3(0,1,0), vec3(0,0,1), vec3(0,1,0), vec3(0,0,0),
    vec3(0,1,1), vec3(0,0,0), vec3(0,1,0), vec3(0,0,1), vec3(0,1,0), vec3(0,0,0),
    vec3(0,1,1), vec3(0,0,0), vec3(0,1,0), vec3(0,0,1), vec3(0,1,0), vec3(0,0,0),
    vec3(0,1,1), vec3(0,0,0), vec3(0,1,0), vec3(0,0,1), vec3(0,1,0), vec3(0,0,0),
	vec3(0,1,1), vec3(0,0,0), vec3(0,1,0), vec3(0,0,1), vec3(0,1,0), vec3(0,0,0)
};

int  Index = 0;

//----------------------------------------------------------------------------

void
triangle( const vec3& a, const vec3& b, const vec3& c, const int color )
{
    static vec3  base_colors[] = {
	vec3( 1.0, 0.0, 0.0 ),
	vec3( 0.0, 1.0, 0.0 ),
	vec3( 0.0, 0.0, 1.0 ),
	vec3( 0.0, 0.0, 0.0 )
    };

    points[Index] = a;  colors[Index] = base_colors[color];  Index++;
    points[Index] = b;  colors[Index] = base_colors[color];  Index++;
    points[Index] = c;  colors[Index] = base_colors[color];  Index++;
}
//----------------------------------------------------------------------------

void
init( void )
{
    /*vec3 vertices[4] = {
	vec3( 0.0, 0.0, -1.0 ),
	vec3( 0.0, 0.942809, 0.333333 ),
	vec3( -0.816497, -0.471405, 0.333333 ),
	vec3( 0.816497, -0.471405, 0.333333 )
    };*/

    // Subdivide the original tetrahedron
    //divide_tetra( vertices[0], vertices[1], vertices[2], vertices[3],NumTimesToSubdivide );

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
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW );

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
    //timeParam = glGetUniformLocation(program, "time");
    //multipliers = glGetUniformLocation(program, "mTransform");
    multipliers = glGetUniformLocation(program, "mTransform2");
    //multipliers = glGetUniformLocation(program, "mTransform3");

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

    glEnable( GL_DEPTH_TEST );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); /* white background */
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glUniform1f( timeParam, glutGet(GLUT_ELAPSED_TIME) );
    /***** rotasi thd sumbu x *****/
    /*mat3 mTransform = mat3(1.0,        0.0,         0.0,
                          0.0, cos(0.001*glutGet(GLUT_ELAPSED_TIME)), -sin(0.001*glutGet(GLUT_ELAPSED_TIME)),
                          0.0, sin(0.001*glutGet(GLUT_ELAPSED_TIME)), cos(0.001*glutGet(GLUT_ELAPSED_TIME)));
    */
    //rotasi terhadap sumbu y
    mat3 mTransform = mat3(cos(0.003*glutGet(GLUT_ELAPSED_TIME)),  0.0,     -sin(0.003*glutGet(GLUT_ELAPSED_TIME)),
                           0.0,                                    1.0,     0.0,
                           sin(0.003*glutGet(GLUT_ELAPSED_TIME)),  0.0,     cos(0.003*glutGet(GLUT_ELAPSED_TIME)));

  	/***** rotasi thd sumbu z *****/
    /*mat3 mTransform3 = mat3(cos(0.001*glutGet(GLUT_ELAPSED_TIME)), -sin(0.001*glutGet(GLUT_ELAPSED_TIME)), 0.0,
                           sin(0.001*glutGet(GLUT_ELAPSED_TIME)), cos(0.001*glutGet(GLUT_ELAPSED_TIME)), 0.0,
                           0.0, 0.0, 1.0);
    */
    //glUniformMatrix3fv( transform, 1, false, mTransform );
    //glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    glUniformMatrix3fv( transform, 1, false, mTransform );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    //glUniformMatrix3fv( transform, 1, false, mTransform3 );
    //glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    //glFlush();
    glutSwapBuffers();
}
void
idle(){
    glutPostRedisplay();
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
    //glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH );
    glutInitDisplayMode( GLUT_DOUBLE );
    glutInitWindowSize( 512, 512 );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Tugas 12" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutIdleFunc(idle);
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}

