#include "common.h"
#include "truk.h"

//berisi render buat seluruh bagian truk
//saat ini truk masih jadi satu objek,
//kalau sempet tolong dipisah
//jgn lupa untuk semua bagian truk dimasukin
//ke fungsi display() di main.cpp juga

//redefinition variable collision point
float cpDepanX, cpDepanZ, cpBelakangX, cpBelakangZ;

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
		glColor3f(0.2, 0.2, 0.2);
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
	glColor3f(0.2, 0.2, 0.2);
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
	glColor3f(0.2, 0.2, 0.2);
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

/*posisi 0 = container paling depan (pertama)
ukuran container pertama lebih pendek dibanding container dibelakangnya*/
void container(int posisi, float x, float y, float z) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glPushMatrix();
	        glTranslatef(0, 2.0, 0.0);
	        if(posisi == 0){
	        	glScalef(2.0,1.0,1.0);
			}else{
				glScalef(2.5, 1.0, 1.0);
			}
	        glutSolidCube(3.0f);
	    glPopMatrix();

	    //atur roda buat container
	    glScalef(0.65,0.65,0.65);
	    if(posisi == 0){
	//        wheel(3.5,0.75,-0.75);
	//        wheel(3.5,0.75,-4.85);
	        wheel(-2.5,0.75,-0.75); //kanan
	        wheel(-2.5,0.75,-4.85); //kiri
		}
		else{
	    	wheel(4.0,0.75,-0.75); //depan kanan
	        wheel(4.0,0.75,-4.85); //depan kiri
	//      wheel(-8.0,0.75,-0.75);
	//		wheel(-8.0,0.75,-4.85);
			wheel(-3.5,0.75,-0.75); //belakang kanan
			wheel(-3.5,0.75,-4.85); //belakang kiri
		}
    glPopMatrix();

}

void wheelDepan(float x, float y, float z) {
	glPushMatrix();
		glScalef(0.65,0.65,0.65);
		wheel(x,y,-0.75+z); //wheel kanan
		wheel(x,y,-4.85+z); //wheel kiri
	glPopMatrix();
}


void collisionBox(float putaran, float tx, float ty, float tz) {
    putaran = putaran - 90;
    cpDepanX = tx + -10.0*sin(putaran*M_PI/180);
    cpDepanZ = tz + -10.0*cos(putaran*M_PI/180);

    cpBelakangX = tx + 5.0*sin(putaran*M_PI/180);
    cpBelakangZ = tz + 5.0*cos(putaran*M_PI/180);

    //buat visualisasi tempat collisionnya aja
    //titik nya pas ditengah cube nya (jangan dihapus buat debug)
//    glPushMatrix();
//    glColor3f(1,1,1);
//    glTranslatef(cpDepanX, ty, cpDepanZ);
//    glRotatef(putaran, 0.0, 1.0, 0.0);
//    glutSolidCube(3.0f);
//    glPopMatrix();
//
//    glPushMatrix();
//    glColor3f(1,1,1);
//    glTranslatef(cpBelakangX, ty, cpBelakangZ);
//    glRotatef(putaran, 0.0, 1.0, 0.0);
//    glutSolidCube(3.0f);
//    glPopMatrix();
}


void Truk(float putaran, float x, float y, float z){
    //glLoadIdentity();
    collisionBox(putaran, x, y, z);
    glTranslatef(x, y, z);

    glPushMatrix();
    glRotated(putaran, 0.0f, 1.0f, 0.0f);

    glColor3f(0.65,0.65,0.65); //warna container
    container(0,4,0,0); //depan
    
    	//Depan
    	glPushMatrix();
		//Hiasan 1
    	glPushMatrix();
    	glColor3f(0,0.16,0.631);
    	glTranslatef(1.5,2,1.51);
    	glRectf(5.5, 0.5, -0.5, -0.5);
    	glPopMatrix();
    
    	//hiasan 2
    	glPushMatrix();
    	glColor3f(0,0.16,0.631);
    	glTranslatef(1.5,2,-1.51);
    	glRectf(5.5, 0.5, -0.5, -0.5);
    	glPopMatrix();
    	glPopMatrix();
    
    	//belakang
    	glPushMatrix();
    	glTranslatef(-6.2, 0, 0);
		//Hiasan 1
    	glPushMatrix();
    	glColor3f(0,0.16,0.631);
    	glTranslatef(1.5,2,1.51);
    	glRectf(5.5, 0.5, -2.0, -0.5);
    	glPopMatrix();
    
    	//hiasan 2
    	glPushMatrix();
    	glColor3f(0,0.16,0.631);
    	glTranslatef(1.5,2,-1.51);
    	glRectf(5.5, 0.5, -2.0, -0.5);
    	glPopMatrix();
    	glPopMatrix();
    	
    	//hiasan biru belakang
    	glPushMatrix();
		glTranslatef(-8.3, 0, -1.5);
		//Hiasan 1
    	glPushMatrix();
    	glColor3f(0,0.16,0.631);
    	glTranslatef(1.5,2,1.51);
    	glRotatef(90, 0, 1, 0);
    	glRectf(1.5, 0.5, -1.5, -0.5);
    	glPopMatrix();
    	glPopMatrix();
    	
    	
    	//lampu kiri kuning
    	glPushMatrix();
		glTranslatef(-8.3, -1.2, -2.55);
		//Hiasan 1
    	glPushMatrix();
    	glColor3f(0.89,0.02,0.01);
    	glTranslatef(1.5,2,1.51);
    	glRotatef(90, 0, 1, 0);
    	glRectf(0.225, 0.125, -0.225, -0.125);
    	glPopMatrix();
    	glPopMatrix();
    	
    	//lampu kiri kuning
    	glPushMatrix();
		glTranslatef(-8.3, -1.2, -2.1);
		//Hiasan 1
    	glPushMatrix();
    	glColor3f(0.89,0.82,0.01);
    	glTranslatef(1.5,2,1.51);
    	glRotatef(90, 0, 1, 0);
    	glRectf(0.225, 0.125, -0.225, -0.125);
    	glPopMatrix();
    	glPopMatrix();
    	
    	
    	
    	////lampu kanan kuning
    	glPushMatrix();
		glTranslatef(-8.3, -1.2, -0.9);
		//Hiasan 1
    	glPushMatrix();
    	glColor3f(0.89,0.82,0.01);
    	glTranslatef(1.5,2,1.51);
    	glRotatef(90, 0, 1, 0);
    	glRectf(0.225, 0.125, -0.225, -0.125);
    	glPopMatrix();
    	glPopMatrix();
    	
    	////lampu kanan kuning
    	glPushMatrix();
		glTranslatef(-8.3, -1.2, -0.5);
		//Hiasan 1
    	glPushMatrix();
    	glColor3f(0.89,0.02,0.01);
    	glTranslatef(1.5,2,1.51);
    	glRotatef(90, 0, 1, 0);
    	glRectf(0.225, 0.125, -0.225, -0.125);
    	glPopMatrix();
    	glPopMatrix();
    	
    glColor3f(0.45,0.45,0.45); //warna container
    container(1,-3,0,0); //belakang
        //truck depan
//
//        glPushMatrix();
//        glTranslatef(8.75, 1.7, 0.0);
//        glScalef(1.0, 0.8, 1.0);
//        glutSolidCube(3.0f);
//        glPopMatrix();


        //depan
        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);

        //glColor3d(128.0f, 32.0f, 32.0f);
        //glColor3d(255.0f, 128.0f, 128.0f);
        glColor3f(0.25,0.25,0.75);
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
        //glColor3d(0.0f, 255.0f, 0.0f);
        glColor3f(0.25,0.25,0.75);
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
        //glColor3d(0.0f,0.0f, 255.0f);
        glColor3f(0.25,0.25,0.75);
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
        //glColor3d(128.0f, 128.0f, 0.0f);
        glColor3f(0.25,0.25,0.75);
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
        //glColor3d(0.0f, 128.0f, 128.0f);
        glColor3f(0.25,0.25,0.75);
        glBegin(GL_QUADS);
        glVertex3f(1.5f,0.35f,-3.0f); //kanan atas
        glVertex3f(1.5f,-1.25f,-3.0f); //kanan bawah
        glVertex3f(1.5f,-1.25f,0.0f); //kanan bawah
        glVertex3f(1.5f,0.35f,0.0f); //kanan atas
        glEnd();
        glPopMatrix();
        
		//cerobong kanan
        glPushMatrix();
        GLUquadricObj *pObj;
        pObj = gluNewQuadric();
    	gluQuadricNormals(pObj, GLU_SMOOTH);
    	glPushMatrix();
    		glColor3f(0.75,0.75,0.75);
    		glRotated(270, 1, 0, 0);
    		glTranslatef(7, 1.2, 0.6);
    		gluCylinder(pObj, 0.2, 0.2, 4, 10, 10);
		glPopMatrix();
		glPopMatrix();
		
		//cerobong kiri
    	glPushMatrix();
    		glColor3f(0.75,0.75,0.75);
    		glRotated(270, 1, 0, 0);
    		glTranslatef(7, -1.2, 0.5);
    		gluCylinder(pObj, 0.2, 0.2, 4, 10, 10);
		glPopMatrix();
		
        //plat
        glPushMatrix();
        glTranslatef(10.3,1,0);
        //glColor3d(0.0f, 128.0f, 128.0f);
        glRotatef(90,0,1,0);
		glColor3f(0.75,0.75,0.75);
        glRectf(0.5,0.25,-0.5,-0.25);
        glPopMatrix();
        
        
        //lampu kiri kuning
        glPushMatrix();
        glTranslatef(10.32, 1.8, 1.0);
        //glColor3d(0.0f, 128.0f, 128.0f);
        glRotatef(90,0,1,0);
		glColor3f(0.89,0.81,0.02);
        glRectf(0.25,0.125,-0.25,-0.125);
        glPopMatrix();
        
        //lampu kiri putih
        glPushMatrix();
        glTranslatef(10.3, 1.8, 1.1);
        //glColor3d(0.0f, 128.0f, 128.0f);
        glRotatef(90,0,1,0);
		glColor3f(0.9,0.9,0.9);
        glRectf(0.35,0.175,-0.35,-0.175);
        glPopMatrix();
        
        //lampu kanan kuning
        glPushMatrix();
        glTranslatef(10.32, 1.8, -1.0);
        //glColor3d(0.0f, 128.0f, 128.0f);
        glRotatef(90,0,1,0);
		glColor3f(0.89,0.81,0.02);
        glRectf(0.25,0.125,-0.25,-0.125);
        glPopMatrix();
        
        //lampu kanan putih
        glPushMatrix();
        glTranslatef(10.3, 1.8, -1.0);
        //glColor3d(0.0f, 128.0f, 128.0f);
        glRotatef(90,0,1,0);
		glColor3f(0.9,0.9,0.9);
        glRectf(0.35,0.175,-0.35,-0.175);
        glPopMatrix();
        
        //tutup atas
        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        //glColor3d(64.0f, 64.0f, 64.0f);
        glColor3f(0.25,0.25,0.75);
        glBegin(GL_QUADS);
        glVertex3f(1.5f,0.35f,-3.0f); //kanan atas
        glVertex3f(1.5f,0.35f,0.0f); //kanan atas
        glVertex3f(0.25f,0.65f,0.0f); //tengah kanan atas
        glVertex3f(0.25f,0.65f,-3.0f); //tengah kanan atas
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        //glColor3d(64.0f, 64.0f, 64.0f);
        glColor3f(0.25,0.25,0.75);
        glBegin(GL_QUADS);
        glVertex3f(-0.0f,1.25f,-3.0f); //tengah kiri atas
        glVertex3f(-0.0f,1.25f,0.0f); //tengah kiri atas
        glVertex3f(-1.5f,1.5f,0.0f); //kiri atas
        glVertex3f(-1.5f,1.5f,-3.0f); //kiri atas
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(8.75,1.7,1.5);
        //glColor3d(128.0f, 128.0f, 0.0f);
        glColor3f(0.85,0.85,0.85); //warna container
        glBegin(GL_QUADS);
        glVertex3f(0.25f,0.65f,0.0f); //tengah kanan atas
        glVertex3f(-0.0f,1.25f,0.0f); //tengah kiri atas
        glVertex3f(-0.0f,1.25f,-3.0f); //tengah kiri atas
        glVertex3f(0.25f,0.65f,-3.0f); //tengah kanan atas
        glEnd();
        glPopMatrix();

        glPushMatrix();

            wheelDepan(13.5,0.75,0);
            glEnd();
        glPopMatrix();

    glPopMatrix();
}


