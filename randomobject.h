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
    Batu(float x, float y, float z, float s, float cr, float cg, float cb); //constructor
};

class Bangunan1: public Objek //Bangunan extends Objek
{
public:
    Bangunan1(float x, float y, float z, float s, float cr, float cg, float cb, int jumlahTumpuk); //constructor
};

class Pohon: public Objek
{
public:
	Pohon(float x, float y, float z, float s);
};

class Pine: public Objek
{
public:
	Pine(float x, float y, float z, float s);
};

class Lampu: public Objek
{
public:
	Lampu(float x, float y, float z, float rotation);
};

class Coin: public Objek //Batu extends Objek
{
public:
    Coin(float x, float y, float z, float s); //constructor
};

class Awan: public Objek //Batu extends Objek
{
public:
    Awan(float x, float y, float z, float s);
};

//tambah blue print objek lain disini
#endif // RANDOMOBJECT_H
