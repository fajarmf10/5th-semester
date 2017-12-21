/* sierpinski gasket with vertex arrays */

#include "Angel.h"
#include "mat.h"
using namespace std;

const int NumTimesToSubdivide = 0;
const int NumTriangles = 12;  // 3^5 triangles generated
const int NumVertices  = 3 * NumTriangles;

mat4 projection = Frustum(-0.2, 0.2, -0.2, 0.2, 0.2, 2.0);

mat4 view = Translate(0.0, 0.0, -2);

GLint winheight=512, winwidth=512;

vec4 points[NumVertices]={
   vec4( -0.5, -0.5,  0.5,1.0 ), vec4(  0.5, -0.5,  0.5,1.0 ), vec4( -0.5,  0.5, 0.5,1.0 ), 	   vec4(  0.5,  0.5,  0.5,1.0 ), vec4( -0.5,  0.5,  0.5,1.0 ), vec4(  0.5, -0.5, 0.5,1.0 ),
   vec4( -0.5, -0.5, -0.5,1.0 ), vec4(  0.5, -0.5, -0.5,1.0 ), vec4( -0.5,  0.5, -0.5,1.0 ), 	   vec4(  0.5,  0.5, -0.5,1.0 ), vec4( -0.5,  0.5, -0.5,1.0 ), vec4(  0.5, -0.5, -0.5,1.0 ),
   vec4(  0.5, -0.5, -0.5,1.0 ), vec4(  0.5,  0.5, -0.5,1.0 ), vec4(  0.5, -0.5,  0.5 ,1.0), 	   vec4(  0.5,  0.5,  0.5,1.0 ), vec4(  0.5, -0.5,  0.5,1.0 ), vec4(  0.5,  0.5, -0.5,1.0 ),
   vec4( -0.5, -0.5, -0.5,1.0 ), vec4( -0.5,  0.5, -0.5,1.0 ), vec4( -0.5, -0.5,  0.5 ,1.0), 	   vec4( -0.5,  0.5,  0.5,1.0 ), vec4( -0.5, -0.5,  0.5,1.0 ), vec4( -0.5,  0.5, -0.5,1.0 ),
   vec4( -0.5,  0.5, -0.5,1.0 ), vec4( -0.5,  0.5,  0.5,1.0 ), vec4(  0.5,  0.5, -0.5 ,1.0), 	   vec4(  0.5,  0.5,  0.5,1.0 ), vec4(  0.5,  0.5, -0.5,1.0 ), vec4( -0.5,  0.5,  0.5 ,1.0),
   vec4( -0.5, -0.5, -0.5 ,1.0), vec4( -0.5, -0.5,  0.5,1.0 ), vec4(  0.5, -0.5, -0.5 ,1.0), 	   vec4(  0.5, -0.5,  0.5,1.0 ), vec4(  0.5, -0.5, -0.5,1.0 ), vec4( -0.5, -0.5,  0.5 ,1.0),
};

vec3 col_ver[6]= {
    vec3( 0.066, 0.459, 0.878),
    vec3( 0.411, 0.956, 0.625),
    vec3( 0.411, 0.956, 0.625),
    vec3( 0.411, 0.956, 0.625),
    vec3( 0.411, 0.956, 0.625),
    vec3( 0.066, 0.459, 0.878)
};

vec3 colors[NumVertices]={
    col_ver[0],col_ver[1],col_ver[2],col_ver[0],col_ver[1],col_ver[2],
    col_ver[0],col_ver[1],col_ver[2],col_ver[0],col_ver[1],col_ver[2],
    col_ver[0],col_ver[1],col_ver[2],col_ver[0],col_ver[1],col_ver[2],
    col_ver[0],col_ver[1],col_ver[2],col_ver[0],col_ver[1],col_ver[2],
    col_ver[0],col_ver[1],col_ver[2],col_ver[0],col_ver[1],col_ver[2],
    col_ver[0],col_ver[1],col_ver[2],col_ver[0],col_ver[1],col_ver[2]

};
GLint timeParam;
double sina,cosa;
GLuint multiplier;
int Index = 0;

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


//----------------------------------------------------------------------------

void
init( void )
{



    //triangle(vec3(-0.5,0.5,0.0),vec3(-0.5,-0.5,0.0),vec3(0.5,0.5,0.0),0);
    //triangle(vec3(0.5,0.5,0.0),vec3(-0.5,-0.5,0.0),vec3(0.5,-0.5,0.0),3);

   // triangle(vec3(-0.5,0.5,0.0),vec3(-0.5,-0.5,0.0),vec3(0.5,0.5,0.0),0);
    //triangle(vec3(0.5,0.5,0.0),vec3(-0.5,-0.5,0.0),vec3(0.5,-0.5,0.0),3);

    //triangle(vec3(-0.5,0.5,0.0),vec3(-0.5,-0.5,0.0),vec3(0.5,0.5,0.0),0);
    //triangle(vec3(0.5,0.5,0.0),vec3(-0.5,-0.5,0.0),vec3(0.5,-0.5,0.0),3);


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
    timeParam=glGetUniformLocation(program,"time");
    glUseProgram( program );
    multiplier=glGetUniformLocation(program,"multiplier");
    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(points)) );

    glEnable(GL_DEPTH_TEST);
    //glClearColor( 1.0, 1.0, 1.0, 1.0 );
    glClearColor( 0.0, 0.0, 0.0, 0.0 ); /* white background */

}

//----------------------------------------------------------------------------

void drawCube(mat4 model){
    glUniformMatrix4fv(multiplier,1,GL_TRUE,projection*view*model);
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
}

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    sina = sin(0.001*glutGet(GLUT_ELAPSED_TIME));
    cosa = cos(0.001*glutGet(GLUT_ELAPSED_TIME));

    mat3 roty = mat3(cosa,0,-sina,
                     0,1,0,
                     sina,0,cosa);
    mat3 rotx = mat3(1,0,0,
                      0,cosa,-sina,
                      0,sina,cosa);
    mat3 rotz = mat3(cosa,-sina,0,
                      sina,cosa,0,
                      0,0,1);
    mat3 shrinkX = mat3( vec3(0.25, 0.0, 0.0),
                        vec3(0.0, 1.0, 0.0),
                        vec3(0.0, 0.0, 1.0) );

    mat4 rot = Translate(0.5,0.5,0.5)*Scale(0.3,0.3,0.3) *RotateX(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416)*RotateY(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416);
    mat4 negrot = Translate(0.5,-0.5,0.5)*Scale(0.3,0.3,0.3) *RotateX(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416)*RotateY(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416);
    mat4 negnegrot = Translate(-0.5,-0.5,0.5)*Scale(0.3,0.3,0.3) *RotateX(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416)*RotateY(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416);
    mat4 rotneg = Translate(-0.5,0.5,0.5)*Scale(0.3,0.3,0.3) *RotateX(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416)*RotateY(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416);

    mat4 rot1 = Translate(0.6,0.6,0.6)*Scale(0.3,0.3,0.3) *RotateX(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416)*RotateY(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416);
    mat4 negrot1 = Translate(0.6,-0.6,0.6)*Scale(0.3,0.3,0.3) *RotateX(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416)*RotateY(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416);
    mat4 negnegrot1 = Translate(-0.6,-0.6,0.6)*Scale(0.3,0.3,0.3) *RotateX(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416)*RotateY(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416);
    mat4 rotneg1 = Translate(-0.6,0.6,0.6)*Scale(0.3,0.3,0.3) *RotateX(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416)*RotateY(0.001*glutGet(GLUT_ELAPSED_TIME)*180/3.1416);

    drawCube(negnegrot);
    drawCube(negrot);
    drawCube(rot);
    drawCube(rotneg);

    drawCube(negnegrot1);
    drawCube(negrot1);
    drawCube(rot1);
    drawCube(rotneg1);

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

void resep(int x, int y){
    winheight = y;
    winwidth = x;
    glViewport(0, 0, winwidth, winheight);
    projection = Frustum(-0.2*winwidth/(float)512, 0.2*winwidth/(float)512, -0.2*winheight/(float)512, 0.2*winheight/(float)512, 0.2*winheight/(float)512, 2.0);
}

void mosgerak(int mosx, int mosy){
    view = Translate(mosx/(float)512-0.5,-mosy/(float)512+0.5,-2);
}

void idling(){
    glutPostRedisplay();
}


int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize( winheight, winwidth );
    glutInitContextVersion( 3, 2 );
    glutInitContextProfile( GLUT_CORE_PROFILE );
    glutCreateWindow( "Simple GLSL example" );

    glewInit();

    init();
    glutMotionFunc(mosgerak);
    glutReshapeFunc(resep);
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutIdleFunc(idling);

    glutMainLoop();
    return 0;
}
