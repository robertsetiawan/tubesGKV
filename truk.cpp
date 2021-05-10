#include "common.h"

//berisi render buat seluruh bagian truk
//saat ini truk masih jadi satu objek,
//kalau sempet tolong dipisah
//jgn lupa untuk semua bagian truk dimasukin
//ke fungsi display() di main.cpp juga

void wheel(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	for (int j = 0; j <= 360; j++)
	{
		glPushMatrix();
		glTranslatef(0, 0, -0.5);
		glRotated(90, 1, 0, 0);
		glRotated(j, 0, 1, 0);
		glTranslatef(0, 3, 1);
		glColor3f(0.3, 0.3, 0.3);
		glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(0.3, 0, 0);
		glVertex3f(0.3, 0.6, 0);
		glVertex3f(0, 0.6, 0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();

	//pelek ban
	float th;
	glPushMatrix();
	glTranslatef(0, 0, 3.1);
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_POLYGON);
	for(int i=0; i<360; i++)
	{
		th = i * M_PI / 180;
		glVertex3f(cos(th), sin(th), 0);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 2.5);
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_POLYGON);
	for(int i=0; i<360; i++)
	{
		th = i * M_PI / 180;
		glVertex3f(cos(th), sin(th), 0);
	}
	glEnd();
	glPopMatrix();

	glPopMatrix();
}


void Truk(float x, float y, float z){
    //tolong diedit dan dipisah antara truk dan container
    //wheel depan juga
    //glLoadIdentity();
    glTranslatef(x, y, z);
    glPushMatrix();
        //container belakang
        glPushMatrix();
        glTranslatef(-3.0, 2.0, 0.0);
        glScalef(2.5, 1.0, 1.0);
        glutSolidCube(3.0f);
        glPopMatrix();

        //container depan
        glPushMatrix();
        glTranslatef(4.0, 2.0, 0.0);
        glScalef(2.0, 1.0, 1.0);
        glutSolidCube(3.0f);
        glPopMatrix();

        //truck depan
        /*
        glPushMatrix();
        glTranslatef(8.75, 1.7, 0.0);
        glScalef(1.0, 0.8, 1.0);
        glutSolidCube(3.0f);
        glPopMatrix();
        */
        //depan
        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        glColor3d(255.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f(-1.5f,-1.25f,0.0f); //kiri bawah
        glVertex3f(1.5f,-1.25f,0.0f); //kanan bawah
        glVertex3f(1.5f,0.35f,0.0f); //kanan atas
        glVertex3f(0.25f,0.65f,0.0f); //tengah kanan atas
        glVertex3f(-0.0f,1.25f,0.0f); //tengah kiri atas
        glVertex3f(-1.5f,1.5f,0.0f); //kiri atas
        glEnd();
        //glEnable(GL_DEPTH_TEST);
        glPopMatrix();
        //belakang
        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        glColor3d(0.0f, 255.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex3f(-1.5f,-1.25f,-3.0f); //kiri bawah
        glVertex3f(1.5f,-1.25f,-3.0f); //kanan bawah
        glVertex3f(1.5f,0.35f,-3.0f); //kanan atas
        glVertex3f(0.25f,0.65f,-3.0f); //tengah kanan atas
        glVertex3f(-0.0f,1.25f,-3.0f); //tengah kiri atas
        glVertex3f(-1.5f,1.5f,-3.0f); //kiri atas
        glEnd();
        glPopMatrix();
        //tutup kiri
        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        glColor3d(0.0f,0.0f, 255.0f);
        glBegin(GL_QUADS);
        glVertex3f(-1.5f,-1.25f,-3.0f); //kiri bawah
        glVertex3f(-1.5f,1.5f,-3.0f); //kiri atas
        glVertex3f(-1.5f,1.5f,0.0f); //kiri atas
        glVertex3f(-1.5f,-1.25f,0.0f); //kiri bawah
        glEnd();
        glPopMatrix();
        //tutup bawah
        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        glColor3d(128.0f, 128.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-1.5f,-1.25f,0.0f); //kiri bawah
        glVertex3f(1.5f,-1.25f,0.0f); //kanan bawah
        glVertex3f(1.5f,-1.25f,-3.0f); //kanan bawah
        glVertex3f(-1.5f,-1.25f,-3.0f); //kiri bawah
        glEnd();
        glPopMatrix();
        //tutup depan
        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        glColor3d(0.0f, 128.0f, 128.0f);
        glBegin(GL_QUADS);
        glVertex3f(1.5f,0.35f,-3.0f); //kanan atas
        glVertex3f(1.5f,-1.25f,-3.0f); //kanan bawah
        glVertex3f(1.5f,-1.25f,0.0f); //kanan bawah
        glVertex3f(1.5f,0.35f,0.0f); //kanan atas
        glEnd();
        glPopMatrix();
        //tutup atas
        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        glColor3d(64.0f, 64.0f, 64.0f);
        glBegin(GL_QUADS);
        glVertex3f(1.5f,0.35f,-3.0f); //kanan atas
        glVertex3f(1.5f,0.35f,0.0f); //kanan atas
        glVertex3f(0.25f,0.65f,0.0f); //tengah kanan atas
        glVertex3f(0.25f,0.65f,-3.0f); //tengah kanan atas
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        glColor3d(64.0f, 64.0f, 64.0f);
        glBegin(GL_QUADS);
        glVertex3f(-0.0f,1.25f,-3.0f); //tengah kiri atas
        glVertex3f(-0.0f,1.25f,0.0f); //tengah kiri atas
        glVertex3f(-1.5f,1.5f,0.0f); //kiri atas
        glVertex3f(-1.5f,1.5f,-3.0f); //kiri atas
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        glColor3d(128.0f, 128.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(0.25f,0.65f,0.0f); //tengah kanan atas
        glVertex3f(-0.0f,1.25f,0.0f); //tengah kiri atas
        glVertex3f(-0.0f,1.25f,-3.0f); //tengah kiri atas
        glVertex3f(0.25f,0.65f,-3.0f); //tengah kanan atas
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glScalef(0.65,0.65,0.65);
        //roda kanan
        wheel(13.5,0.75,-0.75); //depan kanan
        wheel(13.5,0.75,-4.85); //belakang kanan

        //roda tengah
        wheel(6.5,0.75,-0.75); //depan kanan
        wheel(6.5,0.75,-4.85); //belakang kanan
        wheel(8.5,0.75,-0.75); //depan kanan
        wheel(8.5,0.75,-4.85); //belakang kanan
        wheel(-1.0,0.75,-0.75); //depan kanan
        wheel(-1.0,0.75,-4.85); //belakang kanan

        //roda kiri
        wheel(-8.0,0.75,-0.75); //depan kiri
        wheel(-8.0,0.75,-4.85); //belakang kanan
        wheel(-6.0,0.75,-0.75); //depan kiri
        wheel(-6.0,0.75,-4.85); //belakang kanan
        glEnd();
        glPopMatrix();

    glPopMatrix();

}