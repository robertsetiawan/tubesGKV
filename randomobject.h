#ifndef RANDOMOBJECT_H
#define RANDOMOBJECT_H

class Objek
{
private:
    float bx;
    float by;
    float bz;
    float bsize;

public:
    //setter
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setSize(float s);

    //getter
    float getX();
    float getY();
    float getZ();
    float getSize();
};

class Batu: public Objek //Batu extends Objek
{
public:
    Batu(float x, float y, float z, float s); //constructor
};

//tambah blue print objek lain disini
#endif // RANDOMOBJECT_H
