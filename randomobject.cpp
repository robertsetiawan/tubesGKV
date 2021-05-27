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

Bangunan1::Bangunan1(float x, float y, float z, float s, int jumlahTumpuk)
{
    setX(x);
    setY(y);
    setZ(z);
    setSize(s);
    setHitValue(0);

    for (int i=0;i<jumlahTumpuk;i++){
        glPushMatrix();
        glTranslatef(getX(),getY()+getSize()*i, getZ());
            glPushMatrix();
                glColor3f(0.5,0.25,0.5);
                glutSolidCube(getSize());
            glPopMatrix();
        glPopMatrix();
    }

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
