#ifndef RANDOMOBJECT_H
#define RANDOMOBJECT_H

class Objek
{
private:
    float bx;
    float by;
    float bz;
    float bsize;
    int bhitval;

public:
    //setter
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setSize(float s);
    void setHitValue(int v);

    //getter
    float getX();
    float getY();
    float getZ();
    float getSize();
    int getHitValue(); //0 berarti tidak tembus, selain itu buat skor
};

class Batu: public Objek //Batu extends Objek
{
public:
    Batu(float x, float y, float z, float s); //constructor
};

class Coin: public Objek //Batu extends Objek
{
public:
    Coin(float x, float y, float z, float s); //constructor
};

//tambah blue print objek lain disini
#endif // RANDOMOBJECT_H
