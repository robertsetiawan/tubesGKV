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


Batu::Batu(float x, float y, float z, float s)
{
    setX(x);
    setY(y);
    setZ(z);
    setSize(s);

    glPushMatrix();
    glTranslatef(getX(),getY(), getZ());
        glPushMatrix();
            glColor3f(1.0,0.0,0.0);
            glutSolidCube(getSize());
        glPopMatrix();
    glPopMatrix();
}

