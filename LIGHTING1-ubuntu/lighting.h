// Lighting.h : main header file for the LIGHTING application
//


/////////////////////////////////////////////////////////////////////////////
// CLightingApp:
// See Lighting.cpp for the implementation of this class
//
#include <GL/freeglut.h>
#include <unistd.h>
extern float m_rotZ;
extern float m_tess;
class lighting
{
public:
	lighting();
	// Implementation
	float m_Z;
	float m_accelZ;
	float m_rotY;
	float m_rotX;
	
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightingApp)
public:
	static void OnStart();//OnInitialUpdate
	static void OnUpdate();
	static void OnUpdate2();
	static void OnUpdate3();
	//}}AFX_VIRTUAL
	static void OnKeyDown (unsigned char key, int x, int y);

	
	
};


/////////////////////////////////////////////////////////////////////////////
