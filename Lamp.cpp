// main.cpp//// This is an example of a program using glut
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>       /* sin */
class vector3{
public:
	vector3():x(0.f),y(0.f),z(0.f){}
	vector3(float xx, float yy, float zz):x(xx),y(yy),z(zz){}
	float x,y,z;
};
class vector4 : public vector3{
public:
	vector4():vector3(){
		w=0.f;
	}
	vector4(float xx, float yy, float zz, float ww):vector3(xx,yy,zz),w(ww){}
	float w;
};
float fov = 90.0f;
void drawAxes();
void RenderString(float x, float y, void *font, const char* string, vector3 const& rgb);
void drawCube(vector3 pos, vector4 rot, vector3 scale);
void drawSphere(vector3 pos, vector4 rot, vector3 scale);
void drawCone(vector3 pos, vector4 rot, vector3 scale);
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = {50.0 };
GLfloat light_position[] = {1,6.5*2+1,0, 0.0 };
void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
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
}
float forward=0.f;
float up=0.f;
int width,height;
float right = 0.f;
float rotateBody=0.f;
float yBallPos=0.f;
float angleb1=0.f;
float angleLampBase=0.f;
float angleLampBase1=0.f;
float angleLamp=0.f;
bool lockCamera=false;
bool bWireframe=false;
bool bLighting=false;
void keyboard (unsigned char key, int x, int y);
void display(void){
	if(bLighting){
		glEnable(GL_LIGHTING);
	}else{
		glDisable(GL_LIGHTING);
	}
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();  /*clear the matrix */


	if(lockCamera==true){
		// /*viewing transformation*/
		gluLookAt(right,up,forward,
	 				0.0,0.0,0.0,
	 				0.0,1.0,0.0);//y-vector is up
	}else{
//		float XTheta = cos(-right);
//		float YTheta = sin(-right);
//		float XPhi = cos(-forward);
//		float YPhi = cos(-forward);
//		float radius = 10.0f;
//		float X = XTheta * XPhi * radius;
//		float Y = YTheta * XPhi * radius;
//		float Z = YPhi * radius;
		float x=-right;
		float y = -up;
		float z = -forward;
		float radius = sqrt(x*x+y*y+z*z);
		float theta = atan2(y,x);
		float phi = acos(z / radius);
		float X = theta * phi * radius;
		float Y = theta * phi * radius;
		float Z = phi * radius;
		radius = 10.f;
//		tan(anglex) = y/radius;
//		=> y = tan(anglex)*radius;
//		cos(anglex)=z/radius;
//		=> z = cos(anglex)*radius;
		float scale = 10.f;
//		glTranslatef(tan(x/scale)*radius,tan(y/scale)*radius,-cos(y/scale)*radius -sin(x/scale)*radius);
//		glTranslatef(x,y,z);
//		float anglex = atan(y/100/radius) *180/3.1415;
		float anglex = atan(z/100/radius) *180/3.1415;
		float angley = atan(x/100/radius) *180/3.1415;
		float anglez = atan(y/100/radius) *180/3.1415;
		glTranslatef(0,0,-radius);
		glRotatef(anglex*100,1,0,0);
		glRotatef(anglez*100,0,0,1);
		glRotatef(angley*100,0,1,0);
	}

	drawAxes();

	
	//Plane
	glColor3f(0.03,0.03,0.03);
	drawCube(vector3(0,0,0), vector4(0,0,0,0), vector3(10,0.1,10));

	
	glPushMatrix();
		glRotatef(angleLampBase, 0,1,0);
		glRotatef(angleb1, 0,0,1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHT0);
		
		
		//LampBase=Sphere
		glColor3f(0.5,0.1,0);
		drawSphere(vector3(0,-0.5,0), vector4(0,0,0,0),vector3(1,1,1));

		//Base1
		glColor3f(0,0.0,0.4);
		drawSphere(vector3(0,0.5,0), vector4(0,0,0,1), vector3(0.3,0.3*10,0.3));

		//RotatorSphere1
		glColor3f(0.4,0.0,0.1);
		drawSphere(vector3(0,6.5,0), vector4(0,0,0,1), vector3(0.3,0.3,0.3));

		glPushMatrix();
			glTranslatef(0,+6.5,0);//move back where you were
			glRotatef(angleLampBase1,0,0,1);//rotate
			glTranslatef(0,-6.5,0);//move to origin
			
			//Base2
			glColor3f(0,0.0,0.6);
			drawSphere(vector3(0,6.5,0), vector4(0,0,0,1), vector3(0.3,0.3*10,0.3));

			//RotatorSphere2
			glColor3f(0.4,0.0,0.1);
			drawSphere(vector3(0,6.25*2,0), vector4(0,0,0,1), vector3(0.3,0.3,0.3));


			glPushMatrix();
				glTranslatef(0,6.2*2,0);
				glRotatef(angleLamp,0,0,1);
				glTranslatef(0,-6.2*2,0);
				
				//Arm
				glColor3f(0,0.0,0.8);
				drawSphere(vector3(0,6.5*2,0), vector4(0,0,0,1), vector3(0.3,0.3*4,0.3));
				// drawSphere(vector3(3,0,0), vector4(0,0,0,1), vector3(0.3,0.3*4,0.3));
				//Cone
				glColor3f(0.7,0.3,0.0);
				drawCone(vector3(0,6.5*2+0.3*4,0), vector4(0,0,0,1), vector3(1,1,1));
				
				// glTranslatef(1,0,0);
				
				glLightfv(GL_LIGHT0, GL_POSITION, light_position);
				drawCube(vector3( 0,0,0),vector4(0,0,0,0), vector3(1,1,1));
				// glTranslatef(-1,0,0);

			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
	
	RenderString(5.0f, 7.0f, GLUT_BITMAP_TIMES_ROMAN_24, "press:", vector3(1.0f, 1.0f, 1.0f));
	RenderString(5.0f, 7-2.0f, GLUT_BITMAP_TIMES_ROMAN_24, "z for wireframe toggle", vector3(1.0f, 0.0f, 0.0f));
	RenderString(5.0f, 7-4.0f, GLUT_BITMAP_TIMES_ROMAN_24, "c for cam lock to 0,0,0", vector3(1.0f, 0.0f, 0.0f));
	RenderString(5.0f, 7-6.0f, GLUT_BITMAP_TIMES_ROMAN_24, "l for light toggle", vector3(1.0f, 0.0f, 0.0f));
	RenderString(-10.0f, 9-2.0f, GLUT_BITMAP_TIMES_ROMAN_24, "r/R for base rotate", vector3(1.0f, 0.0f, 0.0f));
	RenderString(-10.0f, 9-4.0f, GLUT_BITMAP_TIMES_ROMAN_24, "t/T for leg rotate", vector3(1.0f, 0.0f, 0.0f));
	RenderString(-10.0f, 9-6.0f, GLUT_BITMAP_TIMES_ROMAN_24, "y/Y for arm rotate", vector3(1.0f, 0.0f, 0.0f));
	RenderString(-10.0f, 9-8.0f, GLUT_BITMAP_TIMES_ROMAN_24, "u/U for lamp rotate", vector3(1.0f, 0.0f, 0.0f));
	
	glFlush();
	glutPostRedisplay();

}
void reshape(int w, int h){
		glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);//z near=1.5, z far = 20.0
	float zoom = 10.0f;
	//glOrtho( zoom*(-1.0),   zoom*(1.0),   zoom*(-1.0),
		//zoom*(1.0),   1.5, 20.0);
	gluPerspective(fov,(float)width/(float)height,0.1,1000.0);//fov=60.0, aspect_ratio=1.0,z near=1.5, z far = 2.0
	glMatrixMode(GL_MODELVIEW);
	width=w;
	height=h;
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	glEnable(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|
		GL_LIGHTING|
		GL_COLOR_MATERIAL| GL_LIGHT1|GL_DEPTH_TEST);
    	glEnable (GL_DEPTH_TEST); // enable depth-testing
	
   
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
		case 'c':
			lockCamera=!lockCamera;
			break;
		case 'z':
			bWireframe=!bWireframe;
			break;
		case 'l':
			bLighting=!bLighting;
			break;
		case 'a':
			right-=1.f;
			break;
		case 'd':
			right+=1.f;
			break;
		case 'q':
			up+=1.f;
			break;
		case 'e':
			up-=1.f;
			break;
		case 'w':
			forward-=1.f;
			break;
		case 's':
			forward+=1.f;
			break;
		case 'b':
			yBallPos+=.1f;
			break;
		case 'B':
			yBallPos-=.1f;
			break;
		case 'r':
			std::cout<<"rotate"<<std::endl;
			rotateBody+=1.f;
			angleb1-=1.f;
			break;
		case 'R':
			rotateBody-=1.f;
			angleb1+=1.f;
			break;
		case 't':
			std::cout<<"rotate Base"<<std::endl;
			// rotateBody+=1.f;
			angleLampBase-=1.f;
			break;
		case 'T':
			// rotateBody-=1.f;
			angleLampBase+=1.f;
			break;
		case 'u':
			std::cout<<"rotate Lamp"<<std::endl;
			// rotateBody+=1.f;
			angleLamp-=1.f;
			break;
		case 'U':
			// rotateBody-=1.f;
			angleLamp+=1.f;
			break;
		case 'y':
			std::cout<<"rotate Base1"<<std::endl;
			// rotateBody+=1.f;
			angleLampBase1-=1.f;
			break;
		case 'Y':
			// rotateBody-=1.f;
			angleLampBase1+=1.f;
			break;
		case 'o':
			fov -= 1.f;
			reshape(width,height);
			break;
		case 'O':
			fov += 1.f;
			reshape(width,height);
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}
void drawCube(vector3 pos, vector4 rot, vector3 scale){
	glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		glRotatef(rot.x,rot.y,rot.z,rot.w);
		glTranslatef(0,-0.5f,0);
		glScalef(scale.x,scale.y,scale.z);
		glTranslatef(0,0.5f,0);
		if(bWireframe==false){
			glutSolidCube(1.0f);
		}else{
			glutWireCube(1.f);
		}
	glPopMatrix();
}

void drawSphere(vector3 pos, vector4 rot, vector3 scale){
	glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		glRotatef(rot.x,rot.y,rot.z,rot.w);
		glTranslatef(0,-0.5f*scale.y,0);
		glScalef(scale.x,scale.y,scale.z);
		glTranslatef(0,0.5f*scale.y,0);
		if(bWireframe==false){
			glutSolidSphere(1.0f,
                     30,30);
		}else{
			glutWireSphere(1.0f,
                     30,30);
		}
	glPopMatrix();
}

void drawCone(vector3 pos, vector4 rot, vector3 scale){
	glPushMatrix();
		glTranslatef(pos.x,pos.y,pos.z);
		glRotatef(rot.x,rot.y,rot.z,rot.w);
		glTranslatef(0,-1*scale.y,0);
		glScalef(scale.x,scale.y,scale.z);
		glTranslatef(0,1*scale.y,0);
		glRotatef(-270,1,0,0);
		if(bWireframe==false){
			glutSolidCone(1.0f,2.f,
                     30,30);
		}else{
			glutWireCone(1.0, 2.f,
                   30,30);
		}
	glPopMatrix();
}

void drawAxes(){
	glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f); //y is red
			glVertex3i(0,2,0);
			glVertex3i(0,-2,0);
		glColor3f(0.0f,1.0f,0.0f); //x is green
			glVertex3i(2,0,0);
			glVertex3i(-2,0,0);
		glColor3f(0.0f,0.0f,1.0f); //z is blue
			glVertex3i(0,0,2);
			glVertex3i(0,0,-2);
	glEnd();// The following command ensures that the drawing commands are// actually executed rather than being stored in a buffer// awaiting additional OpenGL commands        

}

void RenderString(float x, float y, void *font, const char* string, vector3 const& rgb)
{  
  char *c;

  glColor3f(rgb.x, rgb.y, rgb.z); 
  glRasterPos2f(x, y);

  glutBitmapString(font, reinterpret_cast<const unsigned char *>(string));
}
