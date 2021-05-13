#include "common.h"

void Jalan()
{
    // Fungsi untuk membuat grid di "lantai"
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for(i=Z_MIN; i<Z_MAX; i+=gap)
    {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for(i=X_MIN; i<X_MAX; i+=gap)
    {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
	//Trotoar
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glTranslatef(0.0, 0.1,0.0);
    glBegin(GL_QUADS);
    glVertex3f(-100, 0, 20);
    glVertex3f(-100, 0, -20);
    glVertex3f(100, 0, -20);
    glVertex3f(100, 0, 20);
    glEnd();
	glPopMatrix();
	
	
	//strip jalan 1
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(70.0, 0.11, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-10, 0, 1);
    glVertex3f(-10, 0, -1);
    glVertex3f(10, 0, -1);
    glVertex3f(10, 0, 1);
    glEnd();
	glPopMatrix();
	
	//strip jalan 2 
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(30.0, 0.11, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-10, 0, 1);
    glVertex3f(-10, 0, -1);
    glVertex3f(10, 0, -1);
    glVertex3f(10, 0, 1);
    glEnd();
	glPopMatrix();
	
	//strip jalan 3 
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-10.0, 0.11, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-10, 0, 1);
    glVertex3f(-10, 0, -1);
    glVertex3f(10, 0, -1);
    glVertex3f(10, 0, 1);
    glEnd();
	glPopMatrix();
	
	//strip jalan 4 
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-50.0, 0.11, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-10, 0, 1);
    glVertex3f(-10, 0, -1);
    glVertex3f(10, 0, -1);
    glVertex3f(10, 0, 1);
    glEnd();
	glPopMatrix();
	
	//strip jalan 5 
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-90.0, 0.11, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-10, 0, 1);
    glVertex3f(-10, 0, -1);
    glVertex3f(10, 0, -1);
    glVertex3f(10, 0, 1);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kanan
	glPushMatrix();
	//sisi jalan kanan bawah
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0, 0.11, 20.0);
    glBegin(GL_QUADS);
    glVertex3f(-100, 0, 1);
    glVertex3f(-100, 0, -1);
    glVertex3f(100, 0, -1);
    glVertex3f(100, 0, 1);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kanan atas
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glTranslatef(0.0, 1.0, 20.0);
    glBegin(GL_QUADS);
    glVertex3f(-100, 0, 1);
    glVertex3f(-100, 0, -1);
    glVertex3f(100, 0, -1);
    glVertex3f(100, 0, 1);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kanan samping kiri
	glPushMatrix();
	glRotated(90, 10, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0.0, 19.0, -0.5);
    glBegin(GL_QUADS);
    glVertex3f(-100, 0, 0.5);
    glVertex3f(-100, 0, -0.5);
    glVertex3f(100, 0, -0.5);
    glVertex3f(100, 0, 0.5);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kanan samping kanan
	glPushMatrix();
	glRotated(90, 10, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0.0, 21.0, -0.5);
    glBegin(GL_QUADS);
    glVertex3f(-100, 0, 0.5);
    glVertex3f(-100, 0, -0.5);
    glVertex3f(100, 0, -0.5);
    glVertex3f(100, 0, 0.5);
    glEnd();
	glPopMatrix();
	//pop sisi jalan kanan
	glPopMatrix(); 

    //sisi jalan kiri
	glPushMatrix();
	glTranslatef(0.0, 0.0, -40.0);
	//sisi jalan kiri bawah
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0, 0.11, 20.0);
    glBegin(GL_QUADS);
    glVertex3f(-100, 0, 1);
    glVertex3f(-100, 0, -1);
    glVertex3f(100, 0, -1);
    glVertex3f(100, 0, 1);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kiri atas
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glTranslatef(0.0, 1.0, 20.0);
    glBegin(GL_QUADS);
    glVertex3f(-100, 0, 1);
    glVertex3f(-100, 0, -1);
    glVertex3f(100, 0, -1);
    glVertex3f(100, 0, 1);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kiri samping kiri
	glPushMatrix();
	glRotated(90, 10, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0.0, 19.0, -0.5);
    glBegin(GL_QUADS);
    glVertex3f(-100, 0, 0.5);
    glVertex3f(-100, 0, -0.5);
    glVertex3f(100, 0, -0.5);
    glVertex3f(100, 0, 0.5);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kiri samping kanan
	glPushMatrix();
	glRotated(90, 10, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0.0, 21.0, -0.5);
    glBegin(GL_QUADS);
    glVertex3f(-100, 0, 0.5);
    glVertex3f(-100, 0, -0.5);
    glVertex3f(100, 0, -0.5);
    glVertex3f(100, 0, 0.5);
    glEnd();
	glPopMatrix();
	//pop sisi jalan kiri
	glPopMatrix(); 
		
	//pop end
	glPopMatrix();       
    
}
