#include "common.h"

//lantai dasar
void lantai(){
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
    glVertex3f(-1000, 0, 1000);
    glVertex3f(-1000, 0, -1000);
    glVertex3f(1000, 0, -1000);
    glVertex3f(1000, 0, 1000);
    glEnd();
}

void trotoar(float x){
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glTranslatef(0.0, 0.1,0.0);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 20);
    glVertex3f(-x, 0, -20);
    glVertex3f(x, 0, -20);
    glVertex3f(x, 0, 20);
    glEnd();
	glPopMatrix();
	
	//strip jalan 1
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(70.0, 0.11, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-x/10, 0, x/100);
    glVertex3f(-x/10, 0, -x/100);
    glVertex3f(x/10, 0, -x/100);
    glVertex3f(x/10, 0, x/100);
    glEnd();
	glPopMatrix();
	
	//strip jalan 2 
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(30.0, 0.11, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-x/10, 0, x/100);
    glVertex3f(-x/10, 0, -x/100);
    glVertex3f(x/10, 0, -x/100);
    glVertex3f(x/10, 0, x/100);
    glEnd();
	glPopMatrix();
	
	//strip jalan 3 
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-x/10, 0.11, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-x/10, 0, x/100);
    glVertex3f(-x/10, 0, -x/100);
    glVertex3f(x/10, 0, -x/100);
    glVertex3f(x/10, 0, x/100);
    glEnd();
	glPopMatrix();
	
	//strip jalan 4 
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-50.0, 0.11, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-x/10, 0, x/100);
    glVertex3f(-x/10, 0, -x/100);
    glVertex3f(x/10, 0, -x/100);
    glVertex3f(x/10, 0, x/100);
    glEnd();
	glPopMatrix();
	
	//strip jalan 5 
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-90.0, 0.11, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-x/10, 0, x/100);
    glVertex3f(-x/10, 0, -x/100);
    glVertex3f(x/10, 0, -x/100);
    glVertex3f(x/10, 0, x/100);
    glEnd();
	glPopMatrix();
}

void roadsideRight(float x){
		//sisi jalan kanan
	glPushMatrix();
	//sisi jalan kanan bawah
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0, 0.11, 20.0);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 1);
    glVertex3f(-x, 0, -1);
    glVertex3f(x, 0, -1);
    glVertex3f(x, 0, 1);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kanan atas
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glTranslatef(0.0, 1.0, 20.0);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 1);
    glVertex3f(-x, 0, -1);
    glVertex3f(x, 0, -1);
    glVertex3f(x, 0, 1);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kanan samping kiri
	glPushMatrix();
	glRotated(90, 10, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0.0, 19.0, -0.5);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 0.5);
    glVertex3f(-x, 0, -0.5);
    glVertex3f(x, 0, -0.5);
    glVertex3f(x, 0, 0.5);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kanan samping kanan
	glPushMatrix();
	glRotated(90, 10, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0.0, 21.0, -0.5);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 0.5);
    glVertex3f(-x, 0, -0.5);
    glVertex3f(x, 0, -0.5);
    glVertex3f(x, 0, 0.5);
    glEnd();
	glPopMatrix();
	//pop sisi jalan kanan
	glPopMatrix(); 
}

void roadsideLeft(float x){
	//sisi jalan kiri
	glPushMatrix();
	glTranslatef(0.0, 0.0, -40.0);
	//sisi jalan kiri bawah
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0, 0.11, 20.0);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 1);
    glVertex3f(-x, 0, -1);
    glVertex3f(x, 0, -1);
    glVertex3f(x, 0, 1);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kiri atas
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glTranslatef(0.0, 1.0, 20.0);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 1);
    glVertex3f(-x, 0, -1);
    glVertex3f(x, 0, -1);
    glVertex3f(x, 0, 1);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kiri samping kiri
	glPushMatrix();
	glRotated(90, 10, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0.0, 19.0, -0.5);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 0.5);
    glVertex3f(-x, 0, -0.5);
    glVertex3f(x, 0, -0.5);
    glVertex3f(x, 0, 0.5);
    glEnd();
	glPopMatrix();
	
	//sisi jalan kiri samping kanan
	glPushMatrix();
	glRotated(90, 10, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0.0, 21.0, -0.5);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 0.5);
    glVertex3f(-x, 0, -0.5);
    glVertex3f(x, 0, -0.5);
    glVertex3f(x, 0, 0.5);
    glEnd();
	glPopMatrix();
	//pop sisi jalan kiri
	glPopMatrix(); 
}
void Jalan()
{
    // Fungsi untuk membuat grid di "lantai"
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 10.0;
    
    
    //Push Pertama untuk lantai dasar dll agak kebawah
    glPushMatrix();
    glTranslatef(0.0, -0.5,0.0);
    
    //lantai dasar
    lantai();
    
	//Push jalan 1
	glPushMatrix();
	//
	glTranslatef(-0, 0,0);
    
	//Trotoar dan strip jalan
	trotoar(100);
	//roadside right	
	roadsideRight(100);
    //roadside left
    roadsideLeft(100);
    glPopMatrix();  
	//pop end
	glPopMatrix();       
    
}

