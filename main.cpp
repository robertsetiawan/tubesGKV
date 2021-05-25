/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

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
float putaranTruk = 90.0;
int gasDitekan = 0;
int setirDitekan = 0; //-1 kiri 1 kanan 0 gak ditekan
float akselerasiDefault = 0.15;
float akselerasi = 0.0;
float dekselerasi = 0.05;
float cx=0.0, cy=0.0, cz=0.0;
float x=22.5f,y=10.0f,z=22.5f; // posisi awal kamera
float angleCam = 360.0;
float lx=0.0f,ly=0.0f,lz=-1.0f;
float tx=0.0, ty=0.0, tz=0.0; //posisi truk (jgn diubah)
extern float cpDepanX, cpDepanZ, cpBelakangX, cpBelakangZ;//shared global variable collision point
int skor = 0;

//renders
int buildings = 1; //seluruh bangunan memakai ini, 0 = seluruh bangunan hilang
int c0x=350.0 , c0z= 400.0, coin0 = 1;
int c1x=2.0, c1z=-190.0, coin1 = 1;
int c2x=-335.0, c2z=-200.0, coin2 = 1;
int c3x=-340.0, c3z=385.0, coin3 = 1;
int c4x=-750.0, c4z=400.0, coin4 = 1;
int c5x=5.0, c5z=580.0, coin5 = 1;
int c6x=345.0, c6z=-320.0, coin6 = 1;
int c7x=870.0, c7z=-400.0, coin7 = 1;
int c8x=875.0, c8z=-200.0, coin8 = 1;
int c9x=850.0, c9z=410.0, coin9 = 1;

void Reshape(int w1, int h1){
    // Fungsi reshape
    if(h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45,ratio,0.1,1000);
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

void cekTabrakan(Objek objek, int *existance) {
    float oMinX, oMaxX, oMinZ, oMaxZ; //objek min x, objek max x, dll.
    //jarak dari kaca depan truk ke koordinat ditengah(0,0,0) itu 10.3

    oMinX = objek.getX() - (objek.getSize()/2) - 1.6; //lebar truk 3.2 (kiri 1,6, kanan 1,6);
    oMaxX = objek.getX() + (objek.getSize()/2) + 1.6;
    oMinZ = objek.getZ() - (objek.getSize()/2) - 1.6;
    oMaxZ = objek.getZ() + (objek.getSize()/2) + 1.6;

    //cek collision areanya
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex3f(oMaxX,  0, oMinZ);
    glVertex3f(oMaxX, 0, oMaxZ);
    glVertex3f(oMinX,  0, oMaxZ);
    glVertex3f(oMinX, 0, oMinZ);
    glEnd();
    glPopMatrix();

    //printf("\n cpx: %f, cpz: %f", cpDepanX, cpDepanZ);
    //cek collision point yang ada di depan truk
    if(cpDepanX >= oMinX && cpDepanX <= oMaxX && cpDepanZ >= oMinZ && cpDepanZ <= oMaxZ){
        printf("\n\n[TABRAKAN] depan stop...");
        printf("%d", objek.getHitValue());
        if (!objek.getHitValue()){
            if (speedX>0){
                speedX = 0.0;
            }
        }else{
            skor += objek.getHitValue();
            *existance = 0;
        }
    }

    //cek collision point yang ada di belakang truk
    if(cpBelakangX >= oMinX && cpBelakangX <= oMaxX && cpBelakangZ >= oMinZ && cpBelakangZ <= oMaxZ){
        printf("\n\n[TABRAKAN] belakang stop...");
         if (!objek.getHitValue()){
            if (speedX<0){
                speedX = 0.0;
            }
        }else{
            skor += objek.getHitValue();
            *existance = 0;
        }
    }
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
        //1 tiap-tiap objek sebaris
        Batu rock1a(40,12.5,-30,25);
        cekTabrakan(rock1a, &buildings);
        Batu rock2a(40,10,10,25);
        cekTabrakan(rock2a, &buildings);
        Batu rock3a(40,10,70,25);
        cekTabrakan(rock3a, &buildings);
        Batu rock4a(40,10,110,25);
        cekTabrakan(rock4a, &buildings);
        Batu rock5a(40,10,150,25);
        cekTabrakan(rock5a, &buildings);
        Batu rock6a(40,10,-200,25);
        cekTabrakan(rock6a, &buildings);
        Batu rock7a(40,10,-240,25);
        cekTabrakan(rock7a, &buildings);
        Batu rock8a(50,10,250,50);
        cekTabrakan(rock8a, &buildings);
        Batu rock9a(40,3,-50,10); //urut seperti pagar
        cekTabrakan(rock9a, &buildings);
        Batu rock10a(40,3,-65,10);
        cekTabrakan(rock10a, &buildings);
        Batu rock11a(40,3,-80,10);
        cekTabrakan(rock11a, &buildings);
        Batu rock12a(40,3,-95,10);
        cekTabrakan(rock12a, &buildings);
        Batu rock13a(40,3,-110,10);
        cekTabrakan(rock13a, &buildings);
        Batu rock14a(40,3,-125,10);
        cekTabrakan(rock14a, &buildings);
        Batu rock15a(40,10,-160,25);
        cekTabrakan(rock15a, &buildings);

        //2
        Batu rock1b(-50,20,300,50);
        cekTabrakan(rock1b, &buildings);
        Batu rock2b(-30,5,360,10);
        cekTabrakan(rock2b, &buildings);
        Batu rock3b(-50,0,360,10);
        cekTabrakan(rock3b, &buildings);
        Batu rock4b(-30,0,340,10);
        cekTabrakan(rock4b, &buildings);
        Batu rock5b(-40,10,240,25);
        cekTabrakan(rock5b, &buildings);
        Batu rock6b(-40,10,200,25);
        cekTabrakan(rock6b, &buildings);
        Batu rock7b(-40,10,160,25);
        cekTabrakan(rock7b, &buildings);
        Batu rock8b(-40,10,120,25);
        cekTabrakan(rock8b, &buildings);
        Batu rock9b(-40,10,20,25);
        cekTabrakan(rock9b, &buildings);
        Batu rock10b(-40,10,-20,25);
        cekTabrakan(rock10b, &buildings);
        Batu rock11b(-50,20,-100,50);
        cekTabrakan(rock11b, &buildings);
        Batu rock12b(-40,10,-140,25);
        cekTabrakan(rock12b, &buildings);

        //3
        Batu rock1c(50,20,350,50);
        cekTabrakan(rock1c, &buildings);
        Batu rock2c(40,12.5,390,25);
        cekTabrakan(rock2c, &buildings);
        Batu rock3c(40,12.5,430,25);
        cekTabrakan(rock3c, &buildings);
        Batu rock4c(40,12.5,470,25);
        cekTabrakan(rock4c, &buildings);
    }

    if (coin1){
        Coin cRender1(c1x, 5, c1z, 2);
        cekTabrakan(cRender1, &coin1);
    }
    if (coin2){
        Coin cRender2(c2x, 5, c2z, 2);
        cekTabrakan(cRender2, &coin2);
    }
    if (coin3){
        Coin cRender3(c3x, 5, c3z, 2);
        cekTabrakan(cRender3, &coin3);
    }
    if (coin4){
        Coin cRender4(c4x, 5, c4z, 2);
        cekTabrakan(cRender4, &coin4);
    }
    if (coin5){
        Coin cRender5(c5x, 5, c5z, 2);
        cekTabrakan(cRender5, &coin5);
    }
    if (coin6){
        Coin cRender6(c6x, 5, c6z, 2);
        cekTabrakan(cRender6, &coin6);
    }
    if (coin7){
        Coin cRender7(c7x, 5, c7z, 2);
        cekTabrakan(cRender7, &coin7);
    }
    if (coin8){
        Coin cRender8(c8x, 5, c8z, 2);
        cekTabrakan(cRender8, &coin8);
    }
    if (coin9){
        Coin cRender9(c9x, 5, c9z, 2);
        cekTabrakan(cRender9, &coin9);
    }
    if (coin0){
        Coin cRender0(c0x, 5, c0z, 2);
        cekTabrakan(cRender0, &coin0);
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
