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
            glColor3f(0.5,0.25,0.5);
            glutSolidCube(getSize());
        glPopMatrix();
    glPopMatrix();
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
