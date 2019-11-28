/////////////////////////////////////////////////////////////////////////////
//
// LightingView.cpp : implementation of the CLightingView class
//
/////////////////////////////////////////////////////////////////////////////



#include "lighting.h"


#include <math.h> // for fabs()

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLightingView


/////////////////////////////////////////////////////////////////////////////
// CLightingView construction/destruction

/////////////////////////////////////////////////////////////////////////////
lighting::lighting()
{
	// TODO: add construction code here

	// set the initial position & rotation
	m_Z = -9.0;
	m_rotY = 35.0;
	m_rotX = 25.0f;
	m_tess=4;
	
	

}

/////////////////////////////////////////////////////////////////////////////
// Control the animation


/////////////////////////////////////////////////////////////////////////////
// Set up the material properties here
void lighting::OnStart() 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	float fov = 90.0f;
	
	glEnable(GL_LIGHT0);
	glViewport(0, 0, (GLsizei) 100, (GLsizei) 100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);//z near=1.5, z far = 20.0
	float zoom = 10.0f;
	//glOrtho( zoom*(-1.0),   zoom*(1.0),   zoom*(-1.0),
		//zoom*(1.0),   1.5, 20.0);
	gluPerspective(fov,1.0,0.1,1000.0);//fov=60.0, aspect_ratio=1.0,z near=1.5, z far = 2.0
	glMatrixMode(GL_MODELVIEW);
	

	// TODO: Add your specialized code here and/or call the base class

	// Set the the material properties
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat position[] = { 0.0f, 5.0f, 0.0f, 0.0f };

	// enable all the lighting & depth effects
    ::glEnable( GL_DEPTH_TEST );
    ::glDepthFunc( GL_LESS );
    ::glEnable( GL_LIGHT0 );

    ::glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
    ::glLightfv( GL_LIGHT0, GL_POSITION, position );
    ::glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );

	//::glEnable( GL_LIGHTING ); // turn lighting on
}


/////////////////////////////////////////////////////////////////////////////
void lighting::OnUpdate(  )
{
	// set up arrays of various properties
	// placed here for convenience
	GLfloat materialSpecular[4][4] = {
		{ 0.1f,  0.1f,  0.1f, 1.0f },
		{ 0.33f, 0.33f, 0.33f, 1.0f },
		{ 0.67f, 0.67f, 0.67f, 1.0f },
		{ 0.9f,  0.9f,  0.9f,  1.0f },
		};

	GLfloat materialAmbDiff[4][4] ={
		{ 0.0f, 0.0f, 0.12f, 1.0f },
		{ 0.0f, 0.0f, 0.25f, 1.0f },
		{ 0.0f, 0.0f, 0.50f, 1.0f },
		{ 0.0f, 0.0f, 1.00f, 1.0f },
		};

	GLfloat materialShininess[4][1] = {
		{ 0.0f },
		{ 5.0f },
		{ 25.0f },
		{ 125.0f }
		};
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();  /*clear the matrix */

glTranslatef(0,0,-10);
	//Use Color Material to simplify Text Setup
	// ::glEnable(GL_COLOR_MATERIAL);
	// ::glEnable(GL_NORMALIZE);
	::glColor3f( 0.8f, 0.8f, 0.2f ); // yellow text


glRotatef(m_rotZ,0,1,1);
m_rotZ+=1;
	// along the X axis
	::glPushMatrix();
	::glTranslatef( -1.5f, 2.0f, -1.5f );
	::glScalef( 0.4f, 0.6f, 0.5f );
	
	::glPopMatrix();

	// along the Y axis
	::glPushMatrix();
	::glTranslatef( -1.5f, -1.5f, -1.5f );
	::glRotatef( 90.0f, 0.0f, 0.0f, 1.0f );
	::glTranslatef( 0.0f, 0.5f, 0.0f );
	::glScalef( 0.4f, 0.6f, 0.5f );
	
	::glPopMatrix();

	// along the Z axis
	::glPushMatrix();
	::glTranslatef( 2.0f, 2.0f, -1.5f );
	::glRotatef( -90.0f, 0.0f, 1.0f, 0.0f );
	::glScalef( 0.4f, 0.6f, 0.5f );
	
	::glPopMatrix();

	::glDisable(GL_NORMALIZE);
	::glDisable(GL_COLOR_MATERIAL);

	GLUquadricObj *sphere = gluNewQuadric();
	// now draw the matrix of spheres
	::glPushMatrix();
	for (int z = 0 ; z < 4 ; z++)
		{
		::glMaterialfv( GL_FRONT, GL_SPECULAR, materialSpecular[z] );
		for (int y = 0 ; y < 4 ; y++)
			{
			::glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialAmbDiff[y] );
			for ( int x = 0 ; x < 4 ; x++ )
				{
				::glMaterialfv( GL_FRONT, GL_SHININESS, materialShininess[x] );
				::glPushMatrix();
				::glTranslatef( -1.5f+(float)x, -1.5f+(float)y, -1.5f+(float)z );
				//::auxWireSphere( 0.25f );
				gluSphere(sphere,0.25, 4*4, 4*4);
				::glPopMatrix();
				}
			}
		}
	::glPopMatrix();
	::glFlush();
	usleep(10000);
	glutSwapBuffers();
	// glutPostRedisplay();
	gluDeleteQuadric(sphere);
	
}

/////////////////////////////////////////////////////////////////////////////
// OnKeyDown
// This routine runs the local keyboard interface.
// Most of the keys accepted are from the numeric keypad
// Unhandled keys are passed to the parent in the last line
// Multiply/Divide: increase, decrease sphere tesselation (# of polygons)

void OnKeyDown (unsigned char key, int x, int y){

	// TODO: Add your message handler code here and/or call default
	// bool ctrl = 0x8000 & GetKeyState( VK_CONTROL );
	// bool shift= 0x8000 & GetKeyState( VK_SHIFT );

	// switch ( nChar )
	// {
	// 	case VK_MULTIPLY:
	// 		m_tess *= 2;
	// 		return;
	// 	case VK_DIVIDE:
	// 		m_tess = (m_tess != 1) ? m_tess/2 : 1;

	// }


}

