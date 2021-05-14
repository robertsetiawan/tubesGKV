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

float angle=8.0, deltaAngle = 0.0, ratio;
float deltaMove = 0,h,w;
int bitmapHeight=12;

//debug and dev
int debugCamera = 0;

//global var buat game mechanics
float speedX = 0.0, speedZ = 0.0; //pergerakan truk
float putaranTruk = 360.0;
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
    tz = tz + (deltaX)*0.1*-sin(putaranTruk*M_PI/180)*(1-abs((90.0-deltaMundur)/-90));
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
            if (speedX < 2 && speedX > -1){ //speedX dan deltaMove harus sama
                speedX += akselerasi;
            }
            if (setirDitekan){
                putaranTruk -= setirDitekan*1;
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
    // Gambar grid
    Jalan();
    // Gambar objek di sini...
    glEnable(GL_LIGHTING);
    Truk(putaranTruk, tx, ty, tz);
    glutSwapBuffers();
    glFlush();
    printf("\ntx: %f, tz: %f, angle: %f, angleCam: %f", tx, tz, putaranTruk, deltaMove);
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
                if (setirDitekan){
                    setirDitekan = setirDitekan*-1;
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
