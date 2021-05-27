#include "common.h"

//lantai dasar
void lantai(){
	glColor3f(0.2, 0.56, 0.10);
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

    //strip pembatas jalan
    //panjang 40, lebar 4, jarak antar strip 10
    int i;
    glPushMatrix();
    glColor3f(1, 1, 1);
    for(i = -x+10; i < x-50; i+= 50){
        glBegin(GL_QUADS);
        glVertex3f(i, 0.2, 2);
        glVertex3f(i, 0.2, -2);
        glVertex3f(i+40, 0.2, -2);
        glVertex3f(i+40, 0.2, 2);
        glEnd();
    }
    //strip terakhir dibuat lebih pendek jadinya tidak melebihi trotoar
    glBegin(GL_QUADS);
    glVertex3f(i, 0.2, 2);
    glVertex3f(i, 0.2, -2);
    glVertex3f(x-10, 0.2, -2);
    glVertex3f(x-10, 0.2, 2);
    glEnd();
    glPopMatrix();

	/*
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
	*/
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

    //push jalan 3
    glPushMatrix();
    glTranslatef(-680.0, 0.0, -400.0);
    trotoar(320);
    //pop jalan 3
    glPopMatrix();

	//push jalan 1
    glPushMatrix();
    glTranslatef(-680.0, 0.0, 400.0);
    trotoar(320);
    //pop jalan 1
    glPopMatrix();

    //Push jalan 2
	glPushMatrix();
	//rotasi ke kanan
	glRotated(90, 0, 1, 0);
	glTranslatef(0.0, 0.0, -340.0);
	//Trotoar dan strip jalan
	trotoar(1000);
	//pop jalan 2
	glPopMatrix();

    //push jalan 4
    glPushMatrix();
    glTranslatef(-170.0, 0.0, -200.0);
    trotoar(150);
    //pop jalan 4
    glPopMatrix();

	//push jalan 5
    glPushMatrix();
    glTranslatef(-170.0, 0.0, 400.0);
    trotoar(150);
    //pop jalan 5
    glPopMatrix();

	//Push jalan 6
	glPushMatrix();
	//rotasi ke kanan
	glRotated(90, 0, 1, 0);
	//Trotoar dan strip jalan
	trotoar(1000);
	//roadside right
	//roadsideRight(100);
    //roadside left
    //roadsideLeft(100);
    glPopMatrix();

    //push jalan 7
    glPushMatrix();
    glTranslatef(170.0, 0.0, -300.0);
    trotoar(150);
    //pop jalan 7
    glPopMatrix();

	//push jalan 8
    glPushMatrix();
    glTranslatef(170.0, 0.0, 300.0);
    trotoar(150);
    //pop jalan 8
    glPopMatrix();

	 //Push jalan 9
	glPushMatrix();
	//rotasi ke kanan
	glRotated(90, 0, 1, 0);
	glTranslatef(0.0, 0.0, 340.0);
	//Trotoar dan strip jalan
	trotoar(1000);
	//pop jalan 9
	glPopMatrix();


	//push jalan 10
    glPushMatrix();
    glTranslatef(610.0, 0.0, -400.0);
    trotoar(250);
    //pop jalan 10
    glPopMatrix();

	//push jalan 11
    glPushMatrix();
    glTranslatef(610.0, 0.0, 400.0);
    trotoar(250);
    //pop jalan 11
    glPopMatrix();

    //Push jalan 12
	glPushMatrix();
	//rotasi ke kanan
	glRotated(90, 0, 1, 0);
	glTranslatef(0.0, 0.0, 880.0);
	//Trotoar dan strip jalan
	trotoar(1000);
	//pop jalan 12
	glPopMatrix();

	//push jalan 13
    glPushMatrix();
    glTranslatef(950.0, 0.0, -200.0);
    trotoar(50);
    //pop jalan 13
    glPopMatrix();

	//push jalan 14
    glPushMatrix();
    glTranslatef(950.0, 0.0, 200.0);
    trotoar(50);
    //pop jalan 14
    glPopMatrix();


	//pop end
	glPopMatrix();

}

