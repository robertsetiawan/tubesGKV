//TUBES GKV Game Truk
//Muhammad Afif Azizy / 24060119120011
//Rahadian Fajar Nugroho / 24060119130075
//Robertus Agung Setiawan / 24060119130067
//Merry Tantri Millenia Tobing / 24060119120013

#include <windows.h>
#include "common.h"

#include "truk.h"
#include "lantai.h"
#include "randomobject.h"

float angle = 8.0;
float deltaAngle = 0.0;
float ratio;
float deltaMove = 0,h,w; //for debug cam
int bitmapHeight=12;

//debug and dev
int debugCamera = 0;

//global var buat game mechanics
float speedX = 0.0, speedZ = 0.0; //pergerakan truk
float putaranTruk = 90.0; //jgn di set negatif
int gasDitekan = 0;
int setirDitekan = 0; //-1 kiri 1 kanan 0 gak ditekan
float akselerasiDefault = 0.15;
float akselerasi = 0.0;
float dekselerasi = 0.05;
float cx=0.0, cy=0.0, cz=0.0;
float x=22.5f,y=10.0f,z=22.5f; // posisi awal kamera
float angleCam = 90.0; //jgn di set negatif
float lx=0.0f,ly=0.0f,lz=-1.0f;
float tx=0.0, ty=0.0, tz=0.0; //posisi truk (jgn diubah)
extern float cpDepanX, cpDepanZ, cpBelakangX, cpBelakangZ;//shared global variable collision point
int skor = 0;

//renders
int buildings = 1; //seluruh bangunan memakai ini, 0 = seluruh bangunan hilang
int c0x=350.0 , c0z= 410.0, coin0 = 1;
int c1x=10.0, c1z=-190.0, coin1 = 1;
int c2x=-330.0, c2z=-200.0, coin2 = 1;
int c3x=-340.0, c3z=390.0, coin3 = 1;
int c4x=-30.0, c4z=-210.0, coin4 = 1;
int c5x=-10.0, c5z=580.0, coin5 = 1;
int c6x=350.0, c6z=-320.0, coin6 = 1;
int c7x=-350.0, c7z=-200.0, coin7 = 1;
int c8x=30.0, c8z=300.0, coin8 = 1;
int c9x=330.0, c9z=300.0, coin9 = 1;

void Reshape(int w1, int h1){
    // Fungsi reshape
    if(h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45,ratio,0.1,500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(tx, y, tz, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

void moveCamFlat(float i){
    //kamera ingame
    glLoadIdentity();
    i = i - 90;
    gluLookAt(tx+x*sin(i*M_PI/180), y, tz+z*cos(i*M_PI/180), tx, ty+y/2, tz, 0.0f,1.0f,0.0f);
}


void orientMe(float ang){
    //kamera debug
    // Fungsi ini untuk memutar arah kamera (tengok kiri/kanan)
    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(cx, y, cz, cx + lx,y + ly,cz + lz, 0.0f,1.0f,0.0f);
}

void moveMeFlat(float i){
    //kamera debug
    // Fungsi ini untuk maju mundur kamera
    cx = cx + i*(lx)*0.1;
    cz = cz + i*(lz)*0.1;
    glLoadIdentity();
    gluLookAt(cx, y, cz, cx + lx,y + ly,cz + lz, 0.0f,1.0f,0.0f);
}

void moveTruk(float putaran, float deltaX){
    float deltaMundur = float(abs(180-putaran));
    tx = tx + (deltaX)*0.1*(90.0-deltaMundur)/-90;
    tz = tz + (deltaX)*0.1*-sin(putaran*M_PI/180)*(1-abs((90.0-deltaMundur)/-90));
}

int cekTabrakan(Objek objek, int *existance) {
    float oMinX, oMaxX, oMinZ, oMaxZ; //objek min x, objek max x, dll.
    //jarak dari kaca depan truk ke koordinat ditengah(0,0,0) itu 10.3

    oMinX = objek.getX() - (objek.getSize()/2) - 1.6; //lebar truk 3.2 (kiri 1,6, kanan 1,6);
    oMaxX = objek.getX() + (objek.getSize()/2) + 1.6;
    oMinZ = objek.getZ() - (objek.getSize()/2) - 1.6;
    oMaxZ = objek.getZ() + (objek.getSize()/2) + 1.6;

    //cek collision areanya
    /*glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex3f(oMaxX,  0, oMinZ);
    glVertex3f(oMaxX, 0, oMaxZ);
    glVertex3f(oMinX,  0, oMaxZ);
    glVertex3f(oMinX, 0, oMinZ);
    glEnd();
    glPopMatrix();*/

    //printf("\n cpx: %f, cpz: %f", cpDepanX, cpDepanZ);
    //cek collision point yang ada di depan truk
    if(cpDepanX >= oMinX && cpDepanX <= oMaxX && cpDepanZ >= oMinZ && cpDepanZ <= oMaxZ){
        //printf("\n\n[TABRAKAN] depan stop...");
        //printf("%d", objek.getHitValue());
        if (!objek.getHitValue()){
            if (speedX>0){
                speedX = 0.0;
            }
        }else{
            skor += objek.getHitValue();
            *existance = 0;
            return 1;
        }
    }

    //cek collision point yang ada di belakang truk
    if(cpBelakangX >= oMinX && cpBelakangX <= oMaxX && cpBelakangZ >= oMinZ && cpBelakangZ <= oMaxZ){
        //printf("\n\n[TABRAKAN] belakang stop...");
         if (!objek.getHitValue()){
            if (speedX<0){
                speedX = 0.0;
            }
        }else{
            skor += objek.getHitValue();
            *existance = 0;
            return 1;
        }
    }
    return 0;
}


void renderBitmapString(float x,float y,float z,char *string) {
  char *c;

  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void RenderScore() {
    char s[100];
    glPushMatrix();
    sprintf(s,"Score: %d", skor);
    glColor3f(1,1,1);
    renderBitmapString(5, 30, 0,s); //y axis inverted
    glPopMatrix();
}

void setOrthographicProjection() {
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//gameplay mechanic and renders is done here here
void display() {
    glClearColor(0.64, 0.79, 0.99, 0);
    if (!debugCamera){
        //pergerakan truk
        if (speedX){
            moveTruk(putaranTruk, speedX*2);
        }
        if (!gasDitekan){
            if (speedX>0.1){
                deltaMove -= dekselerasi;
                speedX -= dekselerasi;
            }else if (speedX<-0.1){
                deltaMove += dekselerasi;
                speedX += dekselerasi;
            }else{
                deltaMove = 0;
                speedX = 0;
            }
        }else{
            if (speedX < 4 && speedX > -2){ //speedX dan deltaMove harus sama
                speedX += akselerasi;
            }
            if (setirDitekan){
                putaranTruk -= setirDitekan/abs(setirDitekan);
                if (putaranTruk<0){
                    putaranTruk = 360 + putaranTruk;
                    if (angleCam<360){
                        angleCam += 360;
                    }
                }else if (putaranTruk>360){
                    putaranTruk -= 360;
                    if (angleCam>0){
                        angleCam -= 360;
                    }
                }
            }
        }

        //gerakan camera
        if (abs(angleCam-putaranTruk)<1){
            angleCam = putaranTruk;
        }else if(putaranTruk>0 && putaranTruk<360){
            if (angleCam<putaranTruk){
                angleCam+=0.75;
            }else{
                angleCam-=0.75;
            }
        }
        moveCamFlat(angleCam);
    }else{
        if (deltaMove){
            moveMeFlat(deltaMove*2);
        }
        if (deltaAngle) {
            angle += deltaAngle;
            orientMe(angle*0.2);
        }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    // Gambar grid
    Jalan();
    // Gambar objek di sini...
    if (buildings){
            //x positif start sini
        //1 tiap-tiap objek sebaris
        Batu rock1a(40,12,-30,25,0.8,0.8,0.8);
        cekTabrakan(rock1a, &buildings);
        Batu rock2a(40,10,10,25,0.4,0.6,0.4);
        cekTabrakan(rock2a, &buildings);
        Batu rock3a(40,10,70,25,0.4,0.4,0.7);
        cekTabrakan(rock3a, &buildings);
        Batu rock4a(40,10,110,25,0.4,0.4,0.4);
        cekTabrakan(rock4a, &buildings);
        Batu rock5a(40,10,150,25,0.6,0.4,0.4);
        cekTabrakan(rock5a, &buildings);
        Batu rock6a(40,10,-200,25,0.8,0.8,0.4);
        cekTabrakan(rock6a, &buildings);
        Batu rock7a(40,10,-240,25,0.4,0.4,0.6);
        cekTabrakan(rock7a, &buildings);
        Batu rock8a(50,10,250,50,0.4,0.4,0.6);
        cekTabrakan(rock8a, &buildings);
        Batu rock9a(40,3,-50,10,0.2,0.4,0.4); //urut seperti pagar
        cekTabrakan(rock9a, &buildings);
        Batu rock10a(40,3,-65,10,0.7,0.4,0.4);
        cekTabrakan(rock10a, &buildings);
        Batu rock11a(40,3,-80,10,0.7,0.4,0.4);
        cekTabrakan(rock11a, &buildings);
        Batu rock12a(40,3,-95,10,0.4,0.6,0.4);
        cekTabrakan(rock12a, &buildings);
        Batu rock13a(40,3,-110,10,0.4,0.6,0.6);
        cekTabrakan(rock13a, &buildings);
        Batu rock14a(40,3,-125,10,0.5,0.4,0.5);
        cekTabrakan(rock14a, &buildings);
        Batu rock15a(40,10,-160,25,0.6,0.6,0.6);
        cekTabrakan(rock15a, &buildings);
        Pohon pohon1a(25,0,-60,2);
        cekTabrakan(pohon1a, &buildings);
        Pohon pohon2a(25,0,-90,2);
        cekTabrakan(pohon2a, &buildings);
        Pohon pohon3a(25,0,-120,2);
        cekTabrakan(pohon3a, &buildings);
        Pohon pohon4a(40,0,195,3);
        cekTabrakan(pohon4a, &buildings);
        Lampu lampu1a(21,0,-260, 90);
        cekTabrakan(lampu1a, &buildings);
        Lampu lampu2a(21,0,-220, 90);
        cekTabrakan(lampu2a, &buildings);
        Lampu lampu3a(-21,0,-180, -90);
        cekTabrakan(lampu3a, &buildings);
        Lampu lampu4a(21,0,-140, 90);
        cekTabrakan(lampu4a, &buildings);
        Lampu lampu5a(-21,0,-100, -90);
        cekTabrakan(lampu5a, &buildings);
        Lampu lampu6a(21,0,-60, 90);
        cekTabrakan(lampu6a, &buildings);
        Lampu lampu7a(-21,0,-20, -90);
        cekTabrakan(lampu7a, &buildings);
        Lampu lampu8a(21,0,20, 90);
        cekTabrakan(lampu8a, &buildings);
        Lampu lampu9a(-21,0,60, -90);
        cekTabrakan(lampu9a, &buildings);
        Lampu lampu10a(21,0,100, 90);
        cekTabrakan(lampu10a, &buildings);
        Lampu lampu11a(-21,0,140, -90);
        cekTabrakan(lampu11a, &buildings);
        Lampu lampu12a(21,0,180, 90);
        cekTabrakan(lampu12a, &buildings);
        Lampu lampu13a(-21,0,220, -90);
        cekTabrakan(lampu13a, &buildings);
        Lampu lampu14a(21,0,260, 90);
        cekTabrakan(lampu14a, &buildings);



        //3
        Batu rock1c(50,20,350,50,0.6,0.6,0.4);
        cekTabrakan(rock1c, &buildings);
        Batu rock2c(40,12.5,390,25,0.4,0.7,0.4);
        cekTabrakan(rock2c, &buildings);
        Batu rock3c(40,12.5,430,25,0.4,0.4,0.7);
        cekTabrakan(rock3c, &buildings);
        Batu rock4c(40,12.5,470,25,0.7,0.4,0.7);
        cekTabrakan(rock4c, &buildings);

        //5
        Batu rock1e(40,10,-345,25,0.8,0.8,0.4);
        cekTabrakan(rock1e, &buildings);
        Batu rock2e(70,10,-345,25,0.4,0.4,0.8);
        cekTabrakan(rock2e, &buildings);
        Batu rock3e(100,10,-345,25,0.4,0.8,0.4);
        cekTabrakan(rock3e, &buildings);
        Batu rock4e(130,10,-345,25,0.4,0.8,0.4);
        cekTabrakan(rock4e, &buildings);
        Bangunan1 bang1e(170, 10, -345, 25,0.5,0.8,0.5, 3);
        cekTabrakan (bang1e, &buildings);
        Bangunan1 bang2e(210, 10, -345, 25,0.5,0.8,0.8, 2);
        cekTabrakan (bang2e, &buildings);
        Batu rock5e(230,5,-335,10,0.4,0.4,0.7);
        cekTabrakan(rock5e, &buildings);
        Batu rock6e(250,0,-335,10,0.6,0.4,0.4);
        cekTabrakan(rock6e, &buildings);
        Batu rock7e(250,0,-355,10,0.7,0.4,0.4);
        cekTabrakan(rock7e, &buildings);
        Batu rock8e(270,0,-335,10,0.4,0.8,0.8);
        cekTabrakan(rock8e, &buildings);
        Batu rock9e(270,0,-355,10,0.4,0.6,0.6);
        cekTabrakan(rock9e, &buildings);
        Batu rock10e(290,5,-335,10,0.4,0.7,0.4);
        cekTabrakan(rock10e, &buildings);
        Pine pine1e(300, 0, -360, 2);
        cekTabrakan(pine1e, &buildings);

        //6
        Lampu lampu0f(364,0,-320, 90);
        cekTabrakan(lampu0f, &buildings);
        Lampu lampu1f(317,0,-270, -90);
        cekTabrakan(lampu1f, &buildings);
        Lampu lampu2f(364,0,-220, 90);
        cekTabrakan(lampu2f, &buildings);
        Lampu lampu3f(317,0,-170, -90);
        cekTabrakan(lampu3f, &buildings);
        Lampu lampu4f(364,0,-120, 90);
        cekTabrakan(lampu4f, &buildings);
        Lampu lampu5f(317,0,-70, -90);
        cekTabrakan(lampu5f, &buildings);
        Lampu lampu6f(364,0,-20, 90);
        cekTabrakan(lampu6f, &buildings);
        Lampu lampu7f(317,0, 30, -90);
        cekTabrakan(lampu7f, &buildings);
        Lampu lampu8f(364,0, 80, 90);
        cekTabrakan(lampu8f, &buildings);
        Lampu lampu9f(317,0, 130, -90);
        cekTabrakan(lampu9f, &buildings);
        Lampu lampu10f(364,0, 180, 90);
        cekTabrakan(lampu10f, &buildings);
        Lampu lampu11f(317,0, 230, -90);
        cekTabrakan(lampu11f, &buildings);
        Bangunan1 bang1f(300, 10, 250, 25,0.5,0.8,0.5, 3);
        cekTabrakan (bang1f, &buildings);
        Bangunan1 bang2f(300, 10, 210, 25,0.5,0.7,0.5, 2);
        cekTabrakan (bang2f, &buildings);
        Bangunan1 bang3f(300, 10, 170, 25,0.5,0.7,0.5, 4);
        cekTabrakan (bang3f, &buildings);
        Bangunan1 bang4f(300, 10, 130, 25,0.7,0.7,0.5, 5);
        cekTabrakan (bang4f, &buildings);
        Batu rock1f(300,0,90,25,0.4,0.4,0.9);
        cekTabrakan(rock1f, &buildings);
        Batu rock2f(300,0,50,25,0.6,0.4,0.4);
        cekTabrakan(rock2f, &buildings);
        Bangunan1 bang5f(260, 10, 50, 25,0.8,0.8,0.8, 2);
        cekTabrakan (bang5f, &buildings);
        Batu rock3f(300,10,10,25,0.6,0.4,0.4);
        cekTabrakan(rock3f, &buildings);
        Bangunan1 bang6f(260, 10, 10, 25,0.4,0.4,0.4, 4);
        cekTabrakan (bang6f, &buildings);
        Batu rock4f(300,10,-30,25,0.6,0.6,0.4);
        cekTabrakan(rock4f, &buildings);
        Batu rock5f(300,10,-70,25,0.8,0.8,0.4);
        cekTabrakan(rock5f, &buildings);
        Bangunan1 bang7f(300, 10, -200, 25,0.5,0.6,0.5, 2);
        cekTabrakan (bang7f, &buildings);
        Bangunan1 bang8f(300, 10, -240, 25,0.5,0.8,0.5, 1);
        cekTabrakan (bang8f, &buildings);
        Bangunan1 bang9f(260, 10, -240, 25,0.7,0.7,0.5, 3);
        cekTabrakan (bang9f, &buildings);
        Pine pine1fpos(300, 0, -110, 2);
        cekTabrakan(pine1fpos, &buildings);
        Pine pine2fpos(300, 0, -140, 2);
        cekTabrakan(pine2fpos, &buildings);
        Pine pine3fpos(300, 0, -170, 2);
        cekTabrakan(pine3fpos, &buildings);
        Pine pine4fpos(270, 0, -125, 2);
        cekTabrakan(pine4fpos, &buildings);
        Pine pine5fpos(270, 0, -155, 2);
        cekTabrakan(pine5fpos, &buildings);

        //7
        Bangunan1 bang1gpos(385, 10, 0, 25,0.3,0.3,0.3, 2);
        cekTabrakan (bang1gpos, &buildings);
        Bangunan1 bang2gpos(385, 10, 40, 25,0.4,0.8,0.4, 1);
        cekTabrakan (bang2gpos, &buildings);
        Bangunan1 bang3gpos(425, 10, 40, 25,0.4,0.8,0.8, 2);
        cekTabrakan (bang3gpos, &buildings);
        Pine pine1gpos(385, 0, -50, 2);
        cekTabrakan(pine1gpos, &buildings);
        Pine pine2gpos(385, 0, -80, 2);
        cekTabrakan(pine2gpos, &buildings);
        Pine pine3gpos(385, 0, -110, 2);
        cekTabrakan(pine3gpos, &buildings);
        Pine pine4gpos(385, 0, -140, 2);
        cekTabrakan(pine4gpos, &buildings);
        Pine pine6gpos(385, 0, -170, 2);
        cekTabrakan(pine6gpos, &buildings);
        Pine pine7gpos(385, 0, -200, 2);
        cekTabrakan(pine7gpos, &buildings);
        Pine pine8gpos(385, 0, -230, 2);
        cekTabrakan(pine8gpos, &buildings);
        Pine pine9gpos(385, 0, -260, 2);
        cekTabrakan(pine9gpos, &buildings);
        Pine pine10gpos(385, 0, -290, 2);
        cekTabrakan(pine10gpos, &buildings);
        Pine pine11gpos(385, 0, -320, 2);
        cekTabrakan(pine11gpos, &buildings);
        Pine pine12gpos(385, 0, -350, 2);
        cekTabrakan(pine12gpos, &buildings);
        Pine pine13gpos(415, 0, -30, 2);
        cekTabrakan(pine13gpos, &buildings);
        Pine pine14gpos(415, 0, -60, 2);
        cekTabrakan(pine14gpos, &buildings);
        Pine pine15gpos(415, 0, -90, 2);
        cekTabrakan(pine15gpos, &buildings);
        Pine pine16gpos(415, 0, -120, 2);
        cekTabrakan(pine16gpos, &buildings);
        Pine pine17gpos(415, 0, -150, 2);
        cekTabrakan(pine17gpos, &buildings);
        Pine pine18gpos(415, 0, -180, 2);
        cekTabrakan(pine18gpos, &buildings);
        Pine pine19gpos(415, 0, -210, 2);
        cekTabrakan(pine19gpos, &buildings);
        Pine pine20gpos(415, 0, -240, 2);
        cekTabrakan(pine20gpos, &buildings);
        Pine pine21gpos(415, 0, -270, 2);
        cekTabrakan(pine21gpos, &buildings);
        Pine pine22gpos(415, 0, -300, 2);
        cekTabrakan(pine22gpos, &buildings);
        Pine pine23gpos(415, 0, -330, 2);
        cekTabrakan(pine23gpos, &buildings);

        //9
        Bangunan1 bang1hpos(100, 10, 250, 25,0.3,0.25,0.3, 2);
        cekTabrakan (bang1hpos, &buildings);
        Bangunan1 bang2hpos(130, 10, 250, 25,0.4,0.25,0.4, 2);
        cekTabrakan (bang2hpos, &buildings);
        Bangunan1 bang3hpos(160, 10, 250, 25,0.5,0.5,0.5, 1);
        cekTabrakan (bang3hpos, &buildings);
        Bangunan1 bang4hpos(190, 10, 250, 25,0.7,0.5,0.5, 1);
        cekTabrakan (bang4hpos, &buildings);
        Bangunan1 bang5hpos(220, 10, 250, 25,0.7,0.25,0.5, 2);
        cekTabrakan (bang5hpos, &buildings);
        Bangunan1 bang6hpos(220, 10, 210, 25,0.5,0.7,0.7, 3);
        cekTabrakan (bang6hpos, &buildings);
        Bangunan1 bang7hpos(300, 10, 350, 25,0.5,0.8,0.5, 1);
        cekTabrakan (bang7hpos, &buildings);
        Bangunan1 bang8hpos(270, 10, 350, 25,0.5,0.8,0.5, 1);
        cekTabrakan (bang8hpos, &buildings);
        Bangunan1 bang9hpos(270, 10, 390, 25,0.4,0.7,0.4, 2);
        cekTabrakan (bang9hpos, &buildings);
        Bangunan1 bang10hpos(240, 10, 350, 25,0.5,0.7,0.7, 2);
        cekTabrakan (bang10hpos, &buildings);
        Bangunan1 bang11hpos(240, 10, 390, 25,0.7,0.7,0.7, 3);
        cekTabrakan (bang11hpos, &buildings);
        Bangunan1 bang12hpos(100, 10, 350, 25,0.8,0.8,0.8, 2);
        cekTabrakan (bang12hpos, &buildings);
        Lampu lampu1hpos(315,0, 322, 0);
        cekTabrakan(lampu1hpos, &buildings);
        Lampu lampu2hpos(275,0, 278, 180);
        cekTabrakan(lampu2hpos, &buildings);
        Lampu lampu3hpos(235,0, 322, 0);
        cekTabrakan(lampu3hpos, &buildings);
        Lampu lampu4hpos(195,0, 278, 180);
        cekTabrakan(lampu4hpos, &buildings);
        Lampu lampu5hpos(155,0, 322, 0);
        cekTabrakan(lampu5hpos, &buildings);
        Lampu lampu6hpos(115,0, 278, 180);
        cekTabrakan(lampu6hpos, &buildings);
        Lampu lampu7hpos(75,0, 322, 0);
        cekTabrakan(lampu7hpos, &buildings);
        Pohon pohon1hpos(255,0,250,3);
        cekTabrakan(pohon1hpos, &buildings);
        Pohon pohon2hpos(210,0,330,2);
        cekTabrakan(pohon2hpos, &buildings);
        Pohon pohon3hpos(180,0,330,2);
        cekTabrakan(pohon3hpos, &buildings);
        Pohon pohon4hpos(150,0,330,2);
        cekTabrakan(pohon4hpos, &buildings);
        Pohon pohon5hpos(120,0,330,2);
        cekTabrakan(pohon5hpos, &buildings);
        Pohon pohon6hpos(135,0,350,2);
        cekTabrakan(pohon6hpos, &buildings);
        Pohon pohon7hpos(165,0,350,2);
        cekTabrakan(pohon7hpos, &buildings);
        Pohon pohon8hpos(195,0,350,2);
        cekTabrakan(pohon8hpos, &buildings);

        //11
        Bangunan1 bang1ipos(240, 10, -260, 25,0.5,0.5,0.5, 2);
        cekTabrakan (bang1ipos, &buildings);
        Bangunan1 bang2ipos(210, 10, -260, 25,0.5,0.2,0.2, 1);
        cekTabrakan (bang2ipos, &buildings);
        Bangunan1 bang3ipos(180, 10, -260, 25,0.5,0.8,0.5, 1);
        cekTabrakan (bang3ipos, &buildings);
        Bangunan1 bang4ipos(150, 10, -260, 25,0.5,0.7,0.5, 2);
        cekTabrakan (bang4ipos, &buildings);
        Bangunan1 bang5ipos(120, 10, -260, 25,0.8,0.5,0.8, 1);
        cekTabrakan (bang5ipos, &buildings);
        Bangunan1 bang6ipos(90, 10, -260, 25,0.6,0.25,0.6, 1);
        cekTabrakan (bang6ipos, &buildings);
        Bangunan1 bang7ipos(150, 10, -220, 25,0.4,0.4,0.7, 3);
        cekTabrakan (bang7ipos, &buildings);
        Bangunan1 bang8ipos(120, 10, -220, 25,0.5,0.5,0.7, 2);
        cekTabrakan (bang8ipos, &buildings);
        Bangunan1 bang9ipos(90, 10, -220, 25,0.8,0.5,0.5, 2);
        cekTabrakan (bang9ipos, &buildings);
        Lampu lampu1ipos(280,0,-275, 0);
        cekTabrakan(lampu1ipos, &buildings);
        Lampu lampu2ipos(240,0,-320, 180);
        cekTabrakan(lampu2ipos, &buildings);
        Lampu lampu3ipos(160,0,-275, 0);
        cekTabrakan(lampu3ipos, &buildings);
        Lampu lampu4ipos(120,0,-320, 180);
        cekTabrakan(lampu4ipos, &buildings);
        Lampu lampu5ipos(80,0,-275, 0);
        cekTabrakan(lampu5ipos, &buildings);
        Lampu lampu6ipos(40,0,-320, 180);
        cekTabrakan(lampu6ipos, &buildings);

            //x negatif start sini
        Lampu lampu2x(-23, 0, -255, -90);
        cekTabrakan(lampu2x, &buildings);
        Lampu lampu3x(-23, 0, -305, -90);
        cekTabrakan(lampu3x, &buildings);
        Lampu lampu4x(-23, 0, -355, -90);
        cekTabrakan(lampu4x, &buildings);
        Lampu lampu5x(-23, 0, -405, -90);
        cekTabrakan(lampu5x, &buildings);
        Lampu lampu6x(-23, 0, -455, -90);
        cekTabrakan(lampu6x, &buildings);
        Lampu lampu7x(-23, 0, -555, -90);
        cekTabrakan(lampu7x, &buildings);
        Lampu lampu8x(-23, 0, -605, -90);
        cekTabrakan(lampu8x, &buildings);
        Lampu lampu9x(-23, 0, -655, -90);
        cekTabrakan(lampu9x, &buildings);
        Lampu lampu10x(-23, 0, -705, -90);
        cekTabrakan(lampu10x, &buildings);
        Lampu lampu11x(-23, 0, -755, -90);
        cekTabrakan(lampu11x, &buildings);
        Lampu lampu12x(-23, 0, -805, -90);
        cekTabrakan(lampu12x, &buildings);
        Lampu lampu13x(-23, 0, -855, -90);
        cekTabrakan(lampu13x, &buildings);
        Lampu lampu14x(-23, 0, -905, -90);
        cekTabrakan(lampu14x, &buildings);
        Lampu lampu15x(-23, 0, -955, -90);
        cekTabrakan(lampu15x, &buildings);

        Bangunan1 bang1x(-270, 10, -240, 25,0.1,0.25,0.5, 5);
        cekTabrakan (bang1x, &buildings);
        Pine pine1x(-290, 0, -230, 1);
        cekTabrakan(pine1x, &buildings);
        Pine pine2x(-300, 0, -230, 1);
        cekTabrakan(pine2x, &buildings);
        Pine pine3x(-310, 0, -230, 1);
        cekTabrakan(pine3x, &buildings);
        Pine pine4x(-295, 0, -250, 2);
        cekTabrakan(pine4x, &buildings);
        Pine pine5x(-315, 0, -250, 2);
        cekTabrakan(pine5x, &buildings);

        Bangunan1 bang2x(-270, 10, -160, 25,0.2,0.35,0.5, 2);
        cekTabrakan (bang2x, &buildings);
        Pine pine6x(-290, 0, -150, 1);
        cekTabrakan(pine6x, &buildings);
        Pine pine7x(-300, 0, -150, 1);
        cekTabrakan(pine7x, &buildings);
        Pine pine8x(-310, 0, -150, 1);
        cekTabrakan(pine8x, &buildings);
        Pine pine9x(-295, 0, -170, 2);
        cekTabrakan(pine9x, &buildings);
        Pine pine10x(-315, 0, -170, 2);
        cekTabrakan(pine10x, &buildings);

        Bangunan1 bang3x(-300, 10, -125, 25,0.7,0.1,0.5, 2);
        cekTabrakan (bang3x, &buildings);
        Pine pine11x(-290, 0, -80, 1);
        cekTabrakan(pine11x, &buildings);
        Pine pine12x(-300, 0, -80, 1);
        cekTabrakan(pine12x, &buildings);
        Pine pine13x(-310, 0, -80, 1);
        cekTabrakan(pine13x, &buildings);
        Pine pine14x(-295, 0, -100, 2);
        cekTabrakan(pine14x, &buildings);
        Pine pine15x(-315, 0, -100, 2);
        cekTabrakan(pine15x, &buildings);

        Bangunan1 bang4x(-300, 10, -60, 25,0.2,0.15,0.9, 1);
        cekTabrakan (bang4x, &buildings);
        Pine pine16x(-290, 0, -10, 1);
        cekTabrakan(pine16x, &buildings);
        Pine pine17x(-300, 0, -10, 1);
        cekTabrakan(pine17x, &buildings);
        Pine pine18x(-310, 0, -10, 1);
        cekTabrakan(pine18x, &buildings);
        Pine pine19x(-295, 0, -30, 2);
        cekTabrakan(pine19x, &buildings);
        Pine pine20x(-315, 0, -30, 2);
        cekTabrakan(pine20x, &buildings);

        Bangunan1 bang5x(-300, 10, 10, 25,0.1,0.15,0.5, 1);
        cekTabrakan (bang5x, &buildings);
        Pine pine21x(-290, 0, 60, 1);
        cekTabrakan(pine21x, &buildings);
        Pine pine22x(-300, 0, 60, 1);
        cekTabrakan(pine22x, &buildings);
        Pine pine23x(-310, 0, 60, 1);
        cekTabrakan(pine23x, &buildings);
        Pine pine24x(-295, 0, 40, 2);
        cekTabrakan(pine24x, &buildings);
        Pine pine25x(-315, 0, 40, 2);
        cekTabrakan(pine25x, &buildings);

        Bangunan1 bang6x(-300, 10, 80, 25,0.8,0.15,0.15, 2);
        cekTabrakan (bang6x, &buildings);
        Pine pine26x(-290, 0, 130, 1);
        cekTabrakan(pine26x, &buildings);
        Pine pine27x(-300, 0, 130, 1);
        cekTabrakan(pine27x, &buildings);
        Pine pine28x(-310, 0, 130, 1);
        cekTabrakan(pine28x, &buildings);
        Pine pine29x(-295, 0, 110, 2);
        cekTabrakan(pine29x, &buildings);
        Pine pine30x(-315, 0, 110, 2);
        cekTabrakan(pine30x, &buildings);

        Bangunan1 bang7x(-300, 10, 150, 25,0.1,0.21,0.7, 1);
        cekTabrakan (bang7x, &buildings);
        Pine pine31x(-290, 0, 200, 1);
        cekTabrakan(pine31x, &buildings);
        Pine pine32x(-300, 0, 200, 1);
        cekTabrakan(pine32x, &buildings);
        Pine pine33x(-310, 0, 200, 1);
        cekTabrakan(pine33x, &buildings);
        Pine pine34x(-295, 0, 180, 2);
        cekTabrakan(pine34x, &buildings);
        Pine pine35x(-315, 0, 180, 2);
        cekTabrakan(pine35x, &buildings);

        Bangunan1 bang8x(-300, 10, 220, 25,0.1,0.21,0.3, 1);
        cekTabrakan (bang8x, &buildings);
        Pine pine36x(-290, 0, 270, 1);
        cekTabrakan(pine36x, &buildings);
        Pine pine37x(-300, 0, 270, 1);
        cekTabrakan(pine37x, &buildings);
        Pine pine38x(-310, 0, 270, 1);
        cekTabrakan(pine38x, &buildings);
        Pine pine39x(-295, 0, 250, 2);
        cekTabrakan(pine39x, &buildings);
        Pine pine40x(-315, 0, 250, 2);
        cekTabrakan(pine40x, &buildings);

        Bangunan1 bang9x(-300, 10, 290, 25,0.9,0.25,0.8, 1);
        cekTabrakan (bang9x, &buildings);
        Pine pine41x(-290, 0, 340, 1);
        cekTabrakan(pine41x, &buildings);
        Pine pine42x(-300, 0, 340, 1);
        cekTabrakan(pine42x, &buildings);
        Pine pine43x(-310, 0, 340, 1);
        cekTabrakan(pine43x, &buildings);
        Pine pine44x(-295, 0, 320, 2);
        cekTabrakan(pine44x, &buildings);
        Pine pine45x(-315, 0, 320, 2);
        cekTabrakan(pine45x, &buildings);

        Bangunan1 bang10x(-300, 10, 360, 25,0.3,0.35,0.5, 1);
        cekTabrakan (bang10x, &buildings);
        Bangunan1 bang11x(-300, 10, 440, 25,0.45,0.15,0.5, 2);
        cekTabrakan (bang11x, &buildings);

        Batu rock12x(-70,0,360,10,0.4,0.4,0.4);
        cekTabrakan (rock12x, &buildings);

        Bangunan1 bang12x(-380, 10, -365, 25,0.3,0.75,0.15, 1);
        cekTabrakan (bang12x, &buildings);
        Pohon pohon1x(-380, 0, -345,1);
        cekTabrakan(pohon1x, &buildings);
        Pohon pohon2x(-370,0,-345,1);
        cekTabrakan(pohon2x, &buildings);

        Bangunan1 bang13x(-380, 10, -325, 25,0.1,0.75,0.1, 1);
        cekTabrakan (bang13x, &buildings);
        Pohon pohon3x(-380, 0, -305,1);
        cekTabrakan(pohon3x, &buildings);
        Pohon pohon4x(-370,0,-305,1);
        cekTabrakan(pohon4x, &buildings);

        Bangunan1 bang14x(-380, 10, -285, 25,0.1,0.85,0.15, 1);
        cekTabrakan (bang14x, &buildings);
        Pohon pohon5x(-380, 0, -265,1);
        cekTabrakan(pohon5x, &buildings);
        Pohon pohon6x(-370,0,-265,1);
        cekTabrakan(pohon6x, &buildings);

        Bangunan1 bang15x(-380, 10, -245, 25,0.1,0.15,0.9, 1);
        cekTabrakan (bang15x, &buildings);
        Pohon pohon7x(-380, 0, -225,1);
        cekTabrakan(pohon7x, &buildings);
        Pohon pohon8x(-370,0,-225,1);
        cekTabrakan(pohon8x, &buildings);

        Bangunan1 bang16x(-380, 10, -205, 25,0.8,0.85,0.5, 1);
        cekTabrakan (bang16x, &buildings);
        Pohon pohon9x(-380, 0, -185,1);
        cekTabrakan(pohon9x, &buildings);
        Pohon pohon10x(-370,0,-185,1);
        cekTabrakan(pohon10x, &buildings);

        Bangunan1 bang17x(-380, 10, -165, 25,0.95,0.25,0.5, 1);
        cekTabrakan (bang17x, &buildings);
        Pohon pohon11x(-380, 0, -145,1);
        cekTabrakan(pohon11x, &buildings);
        Pohon pohon12x(-370,0,-145,1);
        cekTabrakan(pohon12x, &buildings);

        Bangunan1 bang18x(-380, 10, -125, 25,0.15,0.95,0.4, 1);
        cekTabrakan (bang18x, &buildings);
        Pohon pohon13x(-380, 0, -105,1);
        cekTabrakan(pohon13x, &buildings);
        Pohon pohon14x(-370,0,-105,1);
        cekTabrakan(pohon14x, &buildings);

        Bangunan1 bang19x(-380, 10, -85, 25,0.2,0.15,0.51, 1);
        cekTabrakan (bang19x, &buildings);
        Pohon pohon15x(-380, 0, -65,1);
        cekTabrakan(pohon15x, &buildings);
        Pohon pohon16x(-370,0,-65,1);
        cekTabrakan(pohon16x, &buildings);

        Bangunan1 bang20x(-380, 10, -45, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang20x, &buildings);
        Pohon pohon17x(-380, 0, -25,1);
        cekTabrakan(pohon17x, &buildings);
        Pohon pohon18x(-370,0,-25,1);
        cekTabrakan(pohon18x, &buildings);

        Bangunan1 bang21x(-380, 10, -5, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang21x, &buildings);
        Pohon pohon19x(-380, 0, 15,1);
        cekTabrakan(pohon19x, &buildings);
        Pohon pohon20x(-370,0, 15,1);
        cekTabrakan(pohon20x, &buildings);

        Bangunan1 bang22x(-380, 10, 35, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang22x, &buildings);
        Pohon pohon21x(-380, 0, 55,1);
        cekTabrakan(pohon21x, &buildings);
        Pohon pohon22x(-370,0,55,1);
        cekTabrakan(pohon22x, &buildings);

        Bangunan1 bang23x(-380, 10, 75, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang23x, &buildings);

        Pohon pohon23x(-380, 0, 95,1);
        cekTabrakan(pohon23x, &buildings);
        Pohon pohon24x(-370,0,95,1);
        cekTabrakan(pohon24x, &buildings);

        Bangunan1 bang24x(-380, 10, 115, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang24x, &buildings);
        Pohon pohon25x(-380, 0, 135,1);
        cekTabrakan(pohon25x, &buildings);
        Pohon pohon26x(-370,0,135,1);
        cekTabrakan(pohon26x, &buildings);

        Bangunan1 bang25x(-380, 10, 155, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang25x, &buildings);
        Pohon pohon27x(-380, 0, 175,1);
        cekTabrakan(pohon27x, &buildings);
        Pohon pohon28x(-370,0,175,1);
        cekTabrakan(pohon28x, &buildings);

        Bangunan1 bang26x(-380, 10, 195, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang26x, &buildings);
        Pohon pohon29x(-380, 0, 215,1);
        cekTabrakan(pohon29x, &buildings);
        Pohon pohon30x(-370,0,215,1);
        cekTabrakan(pohon30x, &buildings);

        Bangunan1 bang27x(-380, 10, 235, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang27x, &buildings);
        Pohon pohon31x(-380, 0, 255,1);
        cekTabrakan(pohon31x, &buildings);
        Pohon pohon32x(-370,0,255,1);
        cekTabrakan(pohon32x, &buildings);

        Bangunan1 bang28x(-380, 10, 275, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang28x, &buildings);
        Pohon pohon33x(-380, 0, 295,1);
        cekTabrakan(pohon33x, &buildings);
        Pohon pohon34x(-370,0,295,1);
        cekTabrakan(pohon34x, &buildings);

        Bangunan1 bang29x(-380, 10, 315, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang29x, &buildings);
        Pohon pohon35x(-380, 0, 335,1);
        cekTabrakan(pohon35x, &buildings);
        Pohon pohon36x(-370,0,335,1);
        cekTabrakan(pohon36x, &buildings);

        Bangunan1 bang30x(-380, 10, 355, 25,0.5,0.25,0.5, 1);
        cekTabrakan (bang30x, &buildings);

        Lampu lampu16x(-23,0,-71,-90);
        cekTabrakan(lampu16x, &buildings);

        Pohon pohon37x(-31,0,375,1);
        cekTabrakan(pohon37x, &buildings);
        Pohon pohon38x(-41,0,375,1);
        cekTabrakan(pohon38x, &buildings);
        Pohon pohon39x(-51,0,375,1);
        cekTabrakan(pohon39x, &buildings);
        Pohon pohon40x(-61,0,375,1);
        cekTabrakan(pohon40x, &buildings);
        Pohon pohon41x(-71,0,375,1);
        cekTabrakan(pohon41x, &buildings);

        Bangunan1 bang31x(-90, 10, 360, 25,0.5,0.25,0.1, 1);
        cekTabrakan (bang31x, &buildings);
        Bangunan1 bang32x(-120, 10, 360, 25,0.5,0.25,0.4, 1);
        cekTabrakan (bang32x, &buildings);
        Bangunan1 bang33x(-150, 10, 360, 25,0.5,0.3,0.1, 2);
        cekTabrakan (bang33x, &buildings);
        Bangunan1 bang34x(-180, 10, 360, 25,0.1,0.3,0.1, 1);
        cekTabrakan (bang34x, &buildings);
        Bangunan1 bang35x(-210, 10, 360, 25,0.5,0.3,0.1, 1);
        cekTabrakan (bang35x, &buildings);
        Bangunan1 bang36x(-240, 10, 360, 25,0.5,0.1,0.1, 2);
        cekTabrakan (bang36x, &buildings);
        Bangunan1 bang37x(-270, 10, 360, 25,0.5,0.1,0.1, 2);
        cekTabrakan (bang37x, &buildings);

        Bangunan1 bang38x(-90, 10, 440, 25,0.5,0.25,0.1, 2);
        cekTabrakan (bang38x, &buildings);
        Bangunan1 bang39x(-120, 10, 440, 25,0.5,0.25,0.4, 1);
        cekTabrakan (bang39x, &buildings);
        Bangunan1 bang40x(-150, 10, 440, 25,0.5,0.3,0.1, 1);
        cekTabrakan (bang40x, &buildings);
        Bangunan1 bang41x(-180, 10, 440, 25,0.1,0.3,0.1, 2);
        cekTabrakan (bang41x, &buildings);
        Bangunan1 bang42x(-210, 10, 440, 25,0.5,0.3,0.1, 1);
        cekTabrakan (bang42x, &buildings);
        Bangunan1 bang43x(-240, 10, 440, 25,0.5,0.1,0.1, 1);
        cekTabrakan (bang43x, &buildings);
        Bangunan1 bang44x(-270, 10, 440, 25,0.2,0.4,0.1, 1);
        cekTabrakan (bang44x, &buildings);
        Bangunan1 bang45x(-60, 10, 440, 25,0.5,0.1,0.1, 1);
        cekTabrakan (bang45x, &buildings);

        Pohon pohon42x(-31,0,425,1);
        cekTabrakan(pohon42x, &buildings);
        Pohon pohon43x(-41,0,425,1);
        cekTabrakan(pohon43x, &buildings);

        //2
        Batu rock1b(-50,20,300,50,0.4,0.4,0.4);
        cekTabrakan(rock1b, &buildings);
        Batu rock2b(-30,5,360,10,0.4,0.4,0.4);
        cekTabrakan(rock2b, &buildings);
        Batu rock3b(-50,0,360,10,0.4,0.4,0.4);
        cekTabrakan(rock3b, &buildings);
        Batu rock4b(-30,0,340,10,0.4,0.4,0.4);
        cekTabrakan(rock4b, &buildings);
        Batu rock5b(-40,10,240,25,0.4,0.4,0.4);
        cekTabrakan(rock5b, &buildings);
        Batu rock6b(-40,10,200,25,0.4,0.4,0.4);
        cekTabrakan(rock6b, &buildings);
        Batu rock7b(-40,10,160,25,0.4,0.4,0.4);
        cekTabrakan(rock7b, &buildings);
        Batu rock8b(-40,10,120,25,0.4,0.4,0.4);
        cekTabrakan(rock8b, &buildings);
        Batu rock9b(-40,10,20,25,0.4,0.4,0.4);
        cekTabrakan(rock9b, &buildings);
        Batu rock10b(-40,10,-20,25,0.4,0.4,0.4);
        cekTabrakan(rock10b, &buildings);
        Batu rock11b(-50,20,-100,50,0.4,0.4,0.4);
        cekTabrakan(rock11b, &buildings);
        Batu rock12b(-40,10,-140,25,0.4,0.4,0.4);
        cekTabrakan(rock12b, &buildings);

        //4
        Bangunan1 bang1d(-120, 10, -240, 25,0.5,0.25,0.5, 3);
        cekTabrakan (bang1d, &buildings);
        Bangunan1 bang2d(-80, 10, -240, 25,0.5,0.25,0.5, 2);
        cekTabrakan (bang2d, &buildings);
        Bangunan1 bang3d(-40, 10, -240, 25,0.5,0.25,0.5, 2);
        cekTabrakan (bang3d, &buildings);
        Batu rock1d(-160,10,-240,25,0.4,0.4,0.4);
        cekTabrakan(rock1d, &buildings);
        Batu rock2d(-200,10,-240,25,0.4,0.4,0.4);
        cekTabrakan(rock2d, &buildings);
        Batu rock3d(-240,10,-240,25,0.4,0.4,0.4);
        cekTabrakan(rock3d, &buildings);
        Batu rock4d(-160,10,-160,25,0.4,0.4,0.4);
        cekTabrakan(rock4d, &buildings);
        Batu rock5d(-200,10,-160,25,0.4,0.4,0.4);
        cekTabrakan(rock5d, &buildings);
        Batu rock6d(-240,10,-160,25,0.4,0.4,0.4);
        cekTabrakan(rock6d, &buildings);
        Batu rock7d(-100,10,-150,50,0.4,0.4,0.4);
        cekTabrakan(rock7d, &buildings);
        Batu rock8d(-50,0,-170,10,0.4,0.4,0.4);
        cekTabrakan(rock8d, &buildings);
        Batu rock9d(-30,5,-170,10,0.4,0.4,0.4);
        cekTabrakan(rock9d, &buildings);


    }

    //glPushMatrix();
    Awan(-4, 65, -10, 3);
    Awan(-4, 65, -150, 1);
    Awan(-100, 65, -10, 2);
    Awan(-10, 100, -15, 4);
    Awan(-15, 55, -100, 3);
    Awan(-150, 55, -15, 1);
    Awan(-250, 55, -120, 2);
    Awan(-100, 55, -70, 3);
    Awan(-135, 55, -100, 4);
    Awan(-235, 55, -140, 1);
    //glPopMatrix();

    int randomNumber;
    if (coin1){
        Coin cRender1(c1x, 5, c1z, 2);
        if (cekTabrakan(cRender1, &coin1)){
            randomNumber = rand()%10 - rand()%10;
            c1z = randomNumber * 100;
            coin1 = 1;
        }
    }
    if (coin2){
        Coin cRender2(c2x, 5, c2z, 2);
        if (cekTabrakan(cRender2, &coin2)){
            randomNumber = rand()%10 - rand()%10;
            c2z = randomNumber * 100;
            coin2 = 1;
        }
    }
    if (coin3){
        Coin cRender3(c3x, 5, c3z, 2);
        if (cekTabrakan(cRender3, &coin3)){
            randomNumber = rand()%9+1;
            c3x = randomNumber * -100;
            coin3 = 1;
        }
    }
    if (coin4){
        Coin cRender4(c4x, 5, c4z, 2);
        if (cekTabrakan(cRender4, &coin4)){
            randomNumber = rand()%27+3;
            c4x = randomNumber * -10;
            coin4 = 1;
        }
    }
    if (coin5){
        Coin cRender5(c5x, 5, c5z, 2);
        if (cekTabrakan(cRender5, &coin5)){
            randomNumber = rand()%10 - rand()%10;
            c5z = randomNumber * 100;
            coin5 = 1;
        }
    }
    if (coin6){
        Coin cRender6(c6x, 5, c6z, 2);
        if (cekTabrakan(cRender6, &coin6)){
            randomNumber = rand()%10 - rand()%10;
            c6z = randomNumber * 100;
            coin6 = 1;
        }
    }
    if (coin7){
        Coin cRender7(c7x, 5, c7z, 2);
        if (cekTabrakan(cRender7, &coin7)){
            randomNumber = rand()%20 - rand()%20;
            c7z = randomNumber * 5;
            coin7 = 1;
        }
    }
    if (coin8){
        Coin cRender8(c8x, 5, c8z, 2);
        if (cekTabrakan(cRender8, &coin8)){
            randomNumber = rand()%27+3;
            c8x = randomNumber * 10;
            coin8 = 1;
        }
    }
    if (coin9){
        Coin cRender9(c9x, 5, c9z, 2);
        if (cekTabrakan(cRender9, &coin9)){
            randomNumber = rand()%20 - rand()%20;
            c9z = randomNumber * 5;
            coin9 = 1;
        }
    }
    if (coin0){
        Coin cRender0(c0x, 5, c0z, 2);
        if (cekTabrakan(cRender0, &coin0)){
            randomNumber = rand()%50 + 35;
            c0x = randomNumber * 10;
            coin0 = 1;
        }
    }

    Truk(putaranTruk, tx, ty, tz);

    //display score
    setOrthographicProjection();
    glPushMatrix();
    glLoadIdentity();
    RenderScore();
    glPopMatrix();
    restorePerspectiveProjection();

    glutSwapBuffers();
    glFlush();
    printf("\ntx: %f, tz: %f, setirDitekan: %d, kecepatan: %f, skor: %d", tx, tz, setirDitekan, speedX, skor);
}

void pressKey(int key, int x, int y) {
    // Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas
    if (debugCamera){
        switch (key) {
            case GLUT_KEY_LEFT : deltaAngle = -0.1f;break;
            case GLUT_KEY_RIGHT : deltaAngle = 0.1f;break;
            case GLUT_KEY_UP : deltaMove = 1;break;
            case GLUT_KEY_DOWN : deltaMove = -1;break;
        }
    }else{
        switch (key) {
            case GLUT_KEY_LEFT :
                if (gasDitekan>0){
                    setirDitekan = -1;
                }else if (gasDitekan<0){
                    setirDitekan = 1;
                }else{
                    setirDitekan = -1;
                }
            break;
            case GLUT_KEY_RIGHT :
                if (gasDitekan>0){
                    setirDitekan = 1;
                }else if (gasDitekan<0){
                    setirDitekan = -1;
                }else{
                    setirDitekan = 1;
                }
            break;
            case GLUT_KEY_UP :
                akselerasi = akselerasiDefault;
                gasDitekan = 1;
            break;
            case GLUT_KEY_DOWN :
                akselerasi = -akselerasiDefault;
                gasDitekan = -1;
                if (setirDitekan==1){
                    setirDitekan = -2;
                }else if (setirDitekan==-1){
                    setirDitekan = 2;
                }
            break;
        }
    }
}

void releaseKey(int key, int x, int y) {
    // Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
    if (debugCamera){
        switch (key) {
            case GLUT_KEY_LEFT :
                if (deltaAngle < 0.0f)
                deltaAngle = 0.0f;
            break;
            case GLUT_KEY_RIGHT :
                if (deltaAngle > 0.0f)
                deltaAngle = 0.0f;
            break;
            case GLUT_KEY_UP :
                if (deltaMove > 0)
                deltaMove = 0;
            break;
            case GLUT_KEY_DOWN :
                if (deltaMove < 0)
                deltaMove = 0;
            break;
        }
    }else{
        switch (key) {
            case GLUT_KEY_LEFT :
                setirDitekan = 0;
            break;
            case GLUT_KEY_RIGHT :
                setirDitekan = 0;
            break;
            case GLUT_KEY_UP :
                gasDitekan = 0;
            break;
            case GLUT_KEY_DOWN :
                gasDitekan = 0;
            break;
        }
    }
}

// Variable untuk pencahayaan
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void lighting(){
    // Fungsi mengaktifkan pencahayaan
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}
void init(void){
    glEnable (GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,480);
    glutCreateWindow("Truk");
    glutIgnoreKeyRepeat(0); // tidak mengabaikan key repeat (saat tombol keyboard dipencet terus)
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display); // Fungsi display-nya dipanggil terusmenerus
    glutReshapeFunc(Reshape);
    lighting();
    init();
    glutMainLoop();
    return(0);
}
