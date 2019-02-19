//
//	glutmain.cpp - source file
//
//	David Henry - tfc_duke@hotmail.com
//


#include	<GL/glut.h>
#include	<iostream>
#include	<iomanip>

#include	"texture.h"
#include	"timer.h"
#include	"md2.h"



/////////////////////////////////////////////////
CMD2Model		Ogro;
CMD2Model		Weapon;

bool			bTextured	= true;
bool			bLighGL		= false;
bool			bAnimated	= true;
float			angle		= 0.0;
extern float	g_angle;
/////////////////////////////////////////////////



// --------------------------------------------------
// Display() - draw the main scene.
// ----------------------------------------------

void Display( void )
{
	// clear color and depth buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();


	CTimer::GetInstance()->Update();
	float timesec = CTimer::GetInstance()->GetTimeMSec() / 1000.0;

	// print fps statistics
	std::cout << "\r   fps = " << std::setprecision(4) << CTimer::GetInstance()->GetFps();


	if( g_angle > 360.0 )
		g_angle -= 360.0;

	if( g_angle < 0.0 )
		g_angle += 360.0;

	if( angle < 0.0 )
		angle += 360.0;

	if( angle > 360.0 )
		angle -= 360.0;


	glTranslatef( 0.0, 0.0, -25.0 );
	glRotatef( angle, 0.0, 1.0, 0.0 );

	// draw models
	Ogro.DrawModel( bAnimated ? timesec : 0.0 );
	Weapon.DrawModel( bAnimated ? timesec : 0.0 );


	// swap buffers and redisplay the scene
	glutSwapBuffers();
	glutPostRedisplay();
}



// --------------------------------------------------
// Reshape() - used when the window is resized.
// --------------------------------------------------

void Reshape( int width, int height )
{
	// prevent division by zero
	if( height == 0 )
		height = 1;

	glViewport( 0, 0, width, height );

	// reset projection matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0, (float)width/(float)height, 0.1, 100.0 );

	// reset model/view matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}



// --------------------------------------------------
// Init() - setup opengl.
// --------------------------------------------------

void Init( void )
{
	// color used to clear the window
	glClearColor( 0.0, 0.0, 0.0, 0.0 );

	// smoothing polygons
	glShadeModel( GL_SMOOTH );

	// enable depth test
	glEnable( GL_DEPTH_TEST );

	// enable texture mapping
	glEnable( GL_TEXTURE_2D );

	/////////////////////////////////////////////

	CTimer::GetInstance()->Initialize();
	CTextureManager::GetInstance()->Initialize();

	// load and initialize the Ogros model
	Ogro.LoadModel( "models/Ogros.md2" );
	Ogro.LoadSkin( "models/igdosh.pcx" );
//	Ogro.LoadModel( "models/grunt.md2" );
//	Ogro.LoadSkin( "models/grunt.pcx" );
//	Ogro.LoadModel( "models/cybrpnk/tris.md2" );
//	Ogro.LoadSkin( "models/cybrpnk/vicious.pcx" );
	Ogro.SetAnim( 0 );
	Ogro.ScaleModel( 0.25 );

	// load and initialize Ogros' weapon model
	Weapon.LoadModel( "models/Weapon.md2" );
	Weapon.LoadSkin( "models/Weapon.pcx" );
//	Weapon.LoadModel( "models/cybrpnk/weapon.md2" );
//	Weapon.LoadSkin( "models/cybrpnk/weapon.pcx" );
	Weapon.SetAnim( STAND );
	Weapon.ScaleModel( 0.25 );

	/////////////////////////////////////////////

	// opengl lighting initialization
	glDisable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	float lightpos[]	= { 10.0, 10.0, 100.0 };
	float lightcolor[]	= { 1.0, 1.0, 1.0, 1.0 };

	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, lightcolor );
	glLightfv( GL_LIGHT0, GL_SPECULAR, lightcolor );
}



// --------------------------------------------------
// Keyboard() - keyboard input.
// --------------------------------------------------

void Keyboard( unsigned char key, int x, int y )
{
	switch( key )
	{
		case 27:
		{
			CTimer::FreeInstance();
			CTextureManager::FreeInstance();

			exit(0);
			break;
		}

		case 'A':
		case 'a':
		{
			bAnimated = !bAnimated;
			break;
		}

		case 'L':
		case 'l':
		{
			bLighGL = !bLighGL;

			if( bLighGL )
				glEnable( GL_LIGHTING );
			else
				glDisable( GL_LIGHTING );

			break;
		}

		case 'P':
		case 'p':
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
			break;
		}

		case 'S':
		case 's':
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
		}

		case 'T':
		case 't':
		{
			bTextured = !bTextured;

			if( bTextured )
				glEnable( GL_TEXTURE_2D );
			else
				glDisable( GL_TEXTURE_2D );

			break;
		}

		case 'W':
		case 'w':
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			break;
		}
	}

}



// --------------------------------------------------
// Special() - keyboard input (special keys).
// --------------------------------------------------

void Special( int key, int x, int y )
{
	switch( key )
	{
		case GLUT_KEY_LEFT:
			angle -= 5.0;
			break;

		case GLUT_KEY_RIGHT:
			angle += 5.0;
			break;

		case GLUT_KEY_UP:
			g_angle -= 10.0;
			break;

		case GLUT_KEY_DOWN:
			g_angle += 10.0;
			break;
	}
}



// --------------------------------------------------
// main() - main function.
// --------------------------------------------------

int main( int argc, char *argv[] )
{
	// setup glut
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

	// initialize window size
	glutInitWindowSize( 640, 480 );

	// initialize window position
	glutInitWindowPosition( 100, 100 );

	// create the window
	glutCreateWindow( "Quake2's MD2 Model Loader" );

	// setup opengl
	Init();

	// callback functions
	glutKeyboardFunc( Keyboard );
	glutSpecialFunc( Special );
	glutReshapeFunc( Reshape );
	glutDisplayFunc( Display );


	std::cout << "\t+-----------------------------------------------------------+"	<< std::endl;
	std::cout << "\t|                  - Quake2's MD2 loader -                  |"	<< std::endl;
	std::cout << "\t|           by David Henry : tfc_duke@hotmail.com           |"	<< std::endl;
	std::cout << "\t|                                                           |"	<< std::endl;
	std::cout << "\t|   QUAKE II" << (char)184
			  << " is registered trademark of id Software, Inc.  |"					<< std::endl;
	std::cout << "\t+-----------------------------------------------------------+"	<< std::endl;
	std::cout << std::endl;
	std::cout << std::endl << " [controls]"											<< std::endl;
	std::cout << "   right/left:     turn right/left"								<< std::endl;
	std::cout << "   up/down:        increase/decrease light angle"					<< std::endl;
	std::cout << "   S, W, P:        render mode : smooth shaded/wireframe/points"	<< std::endl;
	std::cout << "   A:              toggle animation/pause"						<< std::endl;
	std::cout << "   L:              toggle opengl ligthing"						<< std::endl;
	std::cout << "   T:              toggle texture"								<< std::endl;
	std::cout << "   escap:          quit"											<< std::endl;
	std::cout << std::endl;


	// enter an infinite loop...
	glutMainLoop();

	return 0;
}
