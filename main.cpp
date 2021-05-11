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
float speedX = 0.0, speedZ = 0.0; //pergerakan truk
bool gasDitekan = false;
float akselerasiDefault = 0.15;
float akselerasi = 0.0;
float dekselerasi = 0.05;
float x=-7.0f,y=7.75f,z=-0.35f; // posisi awal kamera
float lx=1.0f,ly=-0.25f,lz=0.0f; // arah lihat kamera
float tx=0.0, ty=0.0, tz=0.0; //posisi truk (jgn diubah)
float deltaMove = 0,h,w;
int bitmapHeight=12;

int debugCamera = 0; //set ini ke 0, biar kamera ngikutin truk

void Reshape(int w1, int h1)
{
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
    gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

void orientMe(float ang)
{
    // Fungsi ini untuk memutar arah kamera (tengok kiri/kanan)
    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

void moveMeFlat(float i)
{
    // Fungsi ini untuk maju mundur kamera
    x = x + i*(lx)*0.1;
    z = z + i*(lz)*0.1;
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

void moveTruk(float deltaZ, float deltaX)
{
    //pergerakan truk dalam Z, kanan kiri
    tz = tz + (deltaZ)*0.1;
    //pergerakan truk dalam X, maju mundur
    tx = tx + (deltaX)*0.1;
}

void display()
{
    // Kalau move dan angle tidak nol, gerakkan kamera...
    if (deltaMove)
    {
        moveMeFlat(deltaMove*2); //speed2x
    }
    if (deltaAngle)
    {
        angle += deltaAngle;
        orientMe(angle*0.2);
    }
    if (speedZ || speedX)
    {
        moveTruk(speedZ, speedX*2);
    }
    if (!gasDitekan)
    {
        if (speedX>0.1)
        {
            deltaMove -= dekselerasi;
            speedX -= dekselerasi;
        }
        else if (speedX<-0.1)
        {
            deltaMove += dekselerasi;
            speedX += dekselerasi;
        }
        else
        {
            deltaMove = 0;
            speedX = 0;
        }
    }
    else
    {
        if (speedX < 2 && speedX > -1)  //speedX dan deltaMove harus sama
        {
            deltaMove += akselerasi;
            speedX += akselerasi;
        }
    }

    glLoadIdentity();
    moveMeFlat(0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Gambar grid
    Jalan();
    // Gambar objek di sini...
    //glEnable(GL_LIGHTING);

    Truk(tx, ty, tz);
    glutSwapBuffers();
    glFlush();
    //printf("\nx %f, y %f, z %f, angle %f, delta %f", x, y, z, angle, deltaAngle);
    //printf("\nlx %f, ly %f, lz %f", lx, ly, lz);
    printf("\n speedX: %f gas %d", speedX, gasDitekan);
}

void pressKey(int key, int x, int y)
{
    if(debugCamera == 0)
    {
        switch (key)
        {
        case GLUT_KEY_LEFT :
            //gabisa belok kalo ndak di gas
            speedZ = -abs(speedX)*0.25;
            break;
        case GLUT_KEY_RIGHT :
            speedZ = abs(speedX)*0.25;
            break;
        case GLUT_KEY_UP :
            akselerasi = akselerasiDefault;
            gasDitekan = true;
            break;
        case GLUT_KEY_DOWN :
            akselerasi = -akselerasiDefault;
            gasDitekan = true;
            break;
        }
    }
    else
    {
        switch (key)
        {
        case GLUT_KEY_LEFT :
            deltaAngle = -0.1f;
            break;
        case GLUT_KEY_RIGHT :
            deltaAngle = 0.1f;
            break;
        case GLUT_KEY_UP :
            deltaMove = 1;
            gasDitekan = true;
            akselerasi = 0;
            break;
        case GLUT_KEY_DOWN :
            deltaMove = -1;
            gasDitekan = true;
            akselerasi = 0;
            break;
        }
        // Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas

        /*
        //disable atas dan enable ini untuk gerakin kamera only

        */
    }
}

void releaseKey(int key, int x, int y)
{
    // Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
    if(debugCamera == 0)
    {
        switch (key)
        {
        case GLUT_KEY_LEFT :
            if (speedZ < 0.0 || deltaAngle < 0)
            {
                speedZ = 0.0;
                deltaAngle = 0.0;
            }
            break;
        case GLUT_KEY_RIGHT :
            if (speedZ > 0.0 || deltaAngle > 0)
            {
                speedZ = 0.0;
                deltaAngle = 0.0;
            }
            break;
        case GLUT_KEY_UP :
            gasDitekan = false;
            break;
        case GLUT_KEY_DOWN :
            gasDitekan = false;
            break;
        }
    }
    else
    {
        switch (key)
        {
        case GLUT_KEY_LEFT :
            if (speedZ < 0.0 || deltaAngle < 0)
            {
                speedZ = 0.0;
                deltaAngle = 0.0;
            }
            break;
        case GLUT_KEY_RIGHT :
            if (speedZ > 0.0 || deltaAngle > 0)
            {
                speedZ = 0.0;
                deltaAngle = 0.0;
            }
            break;
        case GLUT_KEY_UP :
            if (deltaMove > 0)
            {
                deltaMove = 0.0;
                speedX -= 0.1;
            }
            gasDitekan = false;
            break;
        case GLUT_KEY_DOWN :
            if (deltaMove < 0)
            {
                deltaMove = 0.0;
            }
            gasDitekan = false;
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

void lighting()
{
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
void init(void)
{
    glEnable (GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,480);
    glutCreateWindow("Truk");
    glutIgnoreKeyRepeat(0); // tidak mengabaikan key repeat (saat tombol keyboard dipencet terus)
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display); // Fungsi display-nya dipanggil terus menerus
    glutReshapeFunc(Reshape);
    lighting();
    init();
    glutMainLoop();
    return(0);
}
