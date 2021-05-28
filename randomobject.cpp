#include "randomobject.h"
#include "common.h"

void Objek::setX(float x)
{
    bx = x;
}

void Objek::setY(float y)
{
    by = y;
}

void Objek::setZ(float z)
{
    bz = z;
}

void Objek::setSize(float s)
{
    bsize = s;
}

void Objek::setHitValue(int v){
    bhitval = v;
}

float Objek::getX()
{
    return bx;
}

float Objek::getY()
{
    return by;
}

float Objek::getZ()
{
    return bz;
}

float Objek::getSize()
{
    return bsize;
}

int Objek::getHitValue()
{
    return bhitval;
}

Batu::Batu(float x, float y, float z, float s)
{
    setX(x);
    setY(y);
    setZ(z);
    setSize(s);
    setHitValue(0);

    glPushMatrix();
    glTranslatef(getX(),getY(), getZ());
        glPushMatrix();
            glColor3f(0.48,0.52,0.61);
            glutSolidCube(getSize());
            //jendela
            glPushMatrix();
            glColor3f(0.5,0.5,0.5);
            //kiri double
            glTranslatef((s/2)+0.1, s/3, (s/3));
            glRotatef(90,0,1,0);
            glRectf((s/16), (s/16), (-s/16), (-s/16));
            glTranslatef(s/8+0.5, 0, 0);
			glRectf((s/16), (s/16), (-s/16), (-s/16));
            //kanan double
			glTranslatef((s/2.7), 0, 0);
            glRectf((s/16), (s/16), (-s/16), (-s/16));
            glTranslatef(s/8+0.5, 0, 0);
			glRectf((s/16), (s/16), (-s/16), (-s/16));
			glPopMatrix();
			
			//jendela 2
			glPushMatrix();
            glColor3f(0.5,0.5,0.5);
            glTranslatef(0, (-s/8)-0.2, 0);
            //kiri double
            glTranslatef((s/2)+0.1, s/3, (s/3));
            glRotatef(90,0,1,0);
            glRectf((s/16), (s/16), (-s/16), (-s/16));
            glTranslatef(s/8+0.5, 0, 0);
			glRectf((s/16), (s/16), (-s/16), (-s/16));
            //kanan double
			glTranslatef((s/2.7), 0, 0);
            glRectf((s/16), (s/16), (-s/16), (-s/16));
            glTranslatef(s/8+0.5, 0, 0);
			glRectf((s/16), (s/16), (-s/16), (-s/16));
			glPopMatrix();
			
			//tembok bawah
			glPushMatrix();
			glColor3f(0.71,0.49,0.53);
			glTranslatef((s/2)+0.1, -s/2, 0);
			glRotatef(90,0,1,0);
			glRectf((s/2), (s/2), (-s/2), (-s/2));
			glPopMatrix();
			
			//pintu
			glPushMatrix();
			glColor3f(0.8,0.8,0.8);
			glTranslatef((s/2)+0.2, -s/2, 0);
			glRotatef(90,0,1,0);
			glRectf((s/8), (s/3)+0.5, (-s/8), (-s/3)+0.5);
			glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
void jendela(float s)
{
			//jendela
            glPushMatrix();
            glColor3f(0.5,0.5,0.5);
            //jendela 1 dari kiri
            glTranslatef((s/2)+0.2, s/3, (s/2.8));
            glRotatef(90,0,1,0);
            //jendela 2 dari kiri
            glRectf((s/16), (s/16), (-s/16), (-s/16));
            glTranslatef(s/6+0.5, 0, 0);
			glRectf((s/16), (s/16), (-s/16), (-s/16));
            //jendela 3 dari kiri
			glTranslatef((s/6)+0.5, 0, 0);
            glRectf((s/16), (s/16), (-s/16), (-s/16));
            //jendela 4 dari kiri
            glTranslatef(s/6+0.5, 0, 0);
			glRectf((s/16), (s/16), (-s/16), (-s/16));
			//jendela 5 dari kiri
			glTranslatef(s/6+0.5, 0, 0);
			glRectf((s/16), (s/16), (-s/16), (-s/16));
			glPopMatrix();
}
Gedung::Gedung(float x, float y, float z, float s){
	setX(x);
    setY(y);
    setZ(z);
    setSize(s);
    setHitValue(0);

    glPushMatrix();
    glTranslatef(getX(),getY(), getZ());
        glPushMatrix();
        	//Balok kanan
            glColor3f(0.33,0.23,0.23);
            glutSolidCube(getSize());
            //balok kiri
            glPushMatrix();
            glColor3f(0.33,0.23,0.23);
            glTranslatef(0, 0, s);
            glutSolidCube(getSize());
            glPopMatrix();
            //balok atas kanan
            glPushMatrix();
            glColor3f(0.48,0.52,0.61);
            glTranslatef(-s/8, s/2, s/2);
            glutSolidCube(getSize()/2);
            glPopMatrix();
            //balok atas kiri
            glPushMatrix();
            glTranslatef(-s/8, s/2, s);
            glutSolidCube(getSize()/2);
            glPopMatrix();
			
			
        glPopMatrix();
    glPopMatrix();
}

GedungTinggi::GedungTinggi(float x, float y, float z, float s){
	setX(x);
    setY(y);
    setZ(z);
    setSize(s);
    setHitValue(0);
    glPushMatrix();
    //Balok kanan
    glTranslatef(getX(),getY(), getZ());
        glColor3f(0.33,0.23,0.23);
        glutSolidCube(getSize());
        glPushMatrix();
        glTranslatef(0, s, 0);
        glutSolidCube(getSize());
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, s*2, 0);
        glutSolidCube(getSize());
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, 0, s);
        glutSolidCube(getSize());
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, s, s);
        glutSolidCube(getSize());
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, 0, -s);
        glutSolidCube(getSize());
        glPopMatrix();
    glPopMatrix();
}

//pohon
Pohon::Pohon(float x, float y, float z){
	setX(x);
    setY(y);
    setZ(z);
    setHitValue(0);
    GLUquadricObj *quadratic;
    GLUquadricObj *quadric;
    quadratic = gluNewQuadric();
    quadric = gluNewQuadric();
    
    glPushMatrix();
    glTranslatef(getX(),getY(), getZ());
	//batang
    	GLUquadricObj *pObj;
    	pObj = gluNewQuadric();
    	gluQuadricNormals(pObj, GLU_SMOOTH);
    	glPushMatrix();
    		glColor3ub(104, 70, 14);
    		glRotated(270, 1, 0, 0);
    		glTranslatef(-30,-30,0);
    		gluCylinder(pObj, 1.5, 0.5, 8, 25, 25);   		
		glPopMatrix();
	//daun 1
	glPushMatrix();
		glColor3ub(18,118,13);
		glScaled(2, 2, 2);
		glRotated(90, 0, 1, 0);
		glTranslatef(-15,5,-15);
		glutSolidDodecahedron();
	glPopMatrix();
	//daun 2
	glPushMatrix();
		glColor3ub(18,118,13);
		glScaled(2, 2, 2);
		glRotated(90, 0, 1, 0);
		glTranslatef(-15,4,-14);
		glutSolidDodecahedron();
	glPopMatrix();
	//daun 3
	glPushMatrix();
		glColor3ub(18,118,13);
		glScaled(2, 2, 2);
		glRotated(90, 0, 1, 0);
		glTranslatef(-15,4,-16);
		glutSolidDodecahedron();
	glPopMatrix();
	glPopMatrix();
	glFlush();
    
}
Coin::Coin(float x, float y, float z, float s){
    setX(x);
    setY(y);
    setZ(z);
    setSize(s);
    setHitValue(10);

    glPushMatrix();
    glTranslatef(getX(),getY(), getZ());
        glPushMatrix();
            glColor3f(0.85,0.85,0.15); //warna kuning :)
            glutSolidTorus(getSize()/2,getSize(),5,5);
        glPopMatrix();
    glPopMatrix();
}
