#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
#include "image.h"

/*Konstante*/

/*Konstanta pi */
#define PI 3.1415926535

/* Definisemo granice parametara povrsi */
#define U_FROM -50
#define V_FROM -50
#define U_TO 50
#define V_TO 50

/* Definisemo makro koji vraca maksimalnu vrednost */
#define max(A, B) (((A) > (B)) ? (A) : (B))

/* Definisemo osobine tajmera */
#define TIMER_INTERVAL 10
#define TIMER_ID 0

/* Imena fajlova sa teksturama. */
#define FILENAME0 "slika.bmp"
#define FILENAME1 "ahorn2.bmp"
#define FILENAME2 "rock.bmp"
#define FILENAME3 "stars.bmp"
#define FILENAME4 "purple.bmp"
#define EPSILON 0.01

/*Koristi se pri crtanju kruga */
#define NUMBER_OF_DOTS 100

/* Uglao u sfernom koordinatnom sistemu koji
   odredjuje polozaj vidne tacke. */
static float theta;

/* Inkrement gornjeg uglova. */
static float delta_theta;

/* Inicajalizacija promenljjivih*/

/* Za timer */
static float hours;
float t=0;
int hours3=0;
static int hours2=0;

/* Promenjiva odredjuje na kom smo delu */
static int n=0;

/*Promenljive za rotaciju terena*/
static double rot_pom = 0;
static int rot=0;

/* Identifikatori tekstura. */
static GLuint names[5];

/* Promenljive za kretanje u prvom delu projekta */
static float y=0;
static float tr2 = 0;
static float x=0;

static float tr=0;
static float trx=0;

/*Sluze za kretanje u drugom delu projekta*/
float tra1=0;
float tra2=0;
float tra3=0;

/* Odredjuje da li je animacija u toku */
static int animation_ongoing=0;   
static int timer_active=0;


/*Deklaracije funkcija*/
void output(int x, int y, char *string);
void set_normal_and_vertex_sphere(float u, float v);
static void drawLittleCube();
static void drawCube2();
static void initText(void);
static void drawCube();
static void drawBall();

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);
static void on_display(void);
void on_display2(void);

int main(int argc, char **argv)
{
    /*Inicijalizuje se GLUT*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    /*Ukljucuju se teksture*/
    glEnable(GL_TEXTURE_2D);
    
    /*Kreiranje prozora*/
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    /*Inicializuju se teksture*/
    initText();
    
    /*Registruju se callback funkcije*/
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
    /*Postavljaju se pocetne vrednosti uglova theta i delta_theta*/
    theta = 0;
    delta_theta = PI / 90;
    
    /* Ukljucujemo normalizaciju vektora normala */
    glEnable(GL_NORMALIZE);
    
    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);
    
    /*Program ulazi u glavnu petlju*/
    glutMainLoop();

    return 0;
}

/*Iscrtava se kockica koja se krece u drugom delu projekta*/
static void drawLittleCube(){
/*Iscrtavaju se kvadrati koji cine kocku, koriste se teksture*/
    glBindTexture(GL_TEXTURE_2D, names[4]);
    
    /*Iscrtava se prvi kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.55, -0.55, 0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.55, -0.55, 0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(0.55, 0.55, 0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.55, 0.55, 0.55);
        
    glEnd();
    
    /*Iscrtava se drugi kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.55, 0.55, -0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.55, 0.55, -0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(0.55, 0.55, 0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.55, 0.55, 0.55);
        
    glEnd();
    
    /*Iscrtava se treci kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.55, -0.55, -0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.55, -0.55, -0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(0.55, 0.55, -0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.55, 0.55, -0.55);
        
    glEnd();
    
    /*Iscrtava se cetvrti kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(0.55, -0.55, -0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.55, 0.55, -0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(0.55, 0.55, 0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(0.55, -0.55, 0.55);
        
    glEnd();
    
    /*Iscrtava se peti kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.55, -0.55, -0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(-0.55, 0.55, -0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(-0.55, 0.55, 0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.55, -0.55, 0.55);
        
    glEnd();
    
    /*Iscrtava se sesti kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(0.55, -0.55, -0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(-0.55, -0.55, -0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(-0.55, -0.55, 0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(0.55, -0.55, 0.55);
        
    glEnd();
      
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);
}


/* Pozadina drugog dela projekta*/
void drawBackground(){
    
    glBindTexture(GL_TEXTURE_2D, names[3]);
    /*Iscrtava se kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-3, -3, -2);
        
        
        glTexCoord2f(1,0);
        glVertex3f(3, -3, -2);
        
        glTexCoord2f(1,1);
        glVertex3f(3, 3, -2);
        
        glTexCoord2f(0,1);
        glVertex3f(-3, 3, -2);
        
    glEnd();
    
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);
    
}

/*Iscrtava se krug, koristi se za crtanje duge*/
void drawCircle(){
    glBegin(GL_TRIANGLE_FAN);
    /*Postavlja se normala */
    glNormal3f(0, 0, 1);
    int i;
    for (i = 0; i <= NUMBER_OF_DOTS; i++) {
        /*Postavljaju se koordinate verteksa*/
        glVertex3f(
                cos(2 * i * PI / NUMBER_OF_DOTS),
                sin(2 * i * PI / NUMBER_OF_DOTS),
                0);
    }
    glEnd();
}

/* Iscrtava se zadnji deo duge*/
void drawRainbow1()
{
    
    int i = 0;

        /* Crtamo sest razlicitih nijansi */
        for (i = 2; i < 8; i++) {

            switch (i) {
                /* Podesavamo boju na osnovu rednog broja kruga */
                case 2:
                    glColor3f(.5, .7, 1);
                    break;
                case 3:
                    glColor3f(.9, 0, 0);
                    break;
                case 4:
                    glColor3f(.7, .7, 0);
                    break;
                case 5:
                    glColor3f(.3, .7, 0);
                    break;
                case 6:
                    glColor3f(0, .6, .6);
                    break;
                case 7:
                    glColor3f(0.5, 0, 0.4);
                    break;
            }

            /*Podesavaju se materijali*/
            glDisable(GL_LIGHTING);
            glEnable(GL_COLOR_MATERIAL);
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            
            
            /*Iscrtavaju se krugovi u zavisnosti od parametra i */
            glPushMatrix();
            glScalef(0.2*i, 0.2*i, 0.2*i);
            glTranslatef(0, 0, 0.0001);
            drawCircle();
            glPopMatrix();
            glDisable(GL_COLOR_MATERIAL);
            
        }
    glEnd();
}

/* Iscrtava prednji deo duge*/
void drawRainbow()
{
    int i = 0;

        glDisable(GL_LIGHTING);
        /* Crtamo sest razlicitih nijansi */
        for (i = 2; i < 8; i++) {

            switch (i) {
                /* Podesavamo boju na osnovu rednog broja kruga */
                case 2:
                    glColor3f(.5, .7, 1);
                    break;
                case 3:
                    glColor3f(.9, 0, 0);
                    break;
                case 4:
                    glColor3f(.7, .7, 0);
                    break;
                case 5:
                    glColor3f(.3, .7, 0);
                    break;
                case 6:
                    glColor3f(0, .6, .6);
                    break;
                case 7:
                    glColor3f(0.5, 0, 0.4);
                    break;
            }

            /*Podesavaju se materijali*/
            glDisable(GL_LIGHTING);
            glEnable(GL_COLOR_MATERIAL);
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            
            
            /*Iscrtavaju se krugovi u zavisnosti od parametra i */
            glPushMatrix();
            glScalef(0.2*i, 0.2*i, 0.2*i);
            glTranslatef(0, 0, 0.0001);
            drawCircle();
            glPopMatrix();
            /*Iskljucuju se materijali */
            glDisable(GL_COLOR_MATERIAL);
            /*Ukljucuje se svetlo*/
            glEnable(GL_LIGHTING);
        }
    glEnd();
}


/* Postavlja normalu i kordinate verteksa za tacku sa parametrima
 * u i v, za loptu*/
void set_normal_and_vertex_sphere(float u, float v){
    
    glNormal3f(
        sin(u)*sin(v),
        cos(u),
        sin(u)*cos(v)
    );
    glVertex3f(
        sin(u)*sin(v),
        cos(u),
        sin(u)*cos(v)
    );
}

/* Funkcija koja sluzi za ispisivanje teksta */
void output(int x, int y, char *string)
         {
        
           int len, i;
           /*Iskljucuje se svetlo */
           glDisable(GL_LIGHTING);
           /*Ukljucuju se materijali */
           glEnable(GL_COLOR_MATERIAL);
           glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
           /*Podesava se boja teksta ne belu */
           glColor3f(1, 1, 1);
           /* Postavljaju se x, y i z koordinate objekta */
           glRasterPos3f(0, 0.5, -1);
           /* Racuna se duzina stringa koji se ispisuje */
           len = (int) strlen(string);
           
           /*Ispisuju se slova */
           for (i = 0; i < len; i++) {
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
           }
           
           /*Iskljucuju se materijali */
           glDisable(GL_COLOR_MATERIAL);
           /*Ukljucuje se svetlo */
           glEnable(GL_LIGHTING);
         }

/* Crta se oblak */      
static void drawCloud(){
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 1, 1, 1, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 1, 1, 1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = {1, 1, 1, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.6, 0.6, 0.4, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.6, 0.6, 0.5, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    
    /* Koeficijenti glatkosti materijala. */
    GLfloat shininess = 20;

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    /*Cratju se lopte koje cine oblak*/
    glPushMatrix();
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.15, 0, 0);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.2, 0.05, 0);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.15, 0.05, 0);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
}

/*Iscrtavaja se lopta koja se nalazi na drugom delu projekta*/
static void drawHemisphere(){
    float u, v;
    glBindTexture(GL_TEXTURE_2D, names[2]);
    glPushMatrix();

    /* Crtamo objekat strip po strip */
    for (u = 0; u < PI; u += PI / 50) {
        glBegin(GL_TRIANGLE_STRIP);
        for (v = 0; v <= PI*2 + EPSILON; v += PI / 50) {
            glTexCoord2f(0, 0);
            set_normal_and_vertex_sphere(u, v);
            glTexCoord2f(0, 1);
            set_normal_and_vertex_sphere(u + PI / 20, v);
            glTexCoord2f(1, 1);
        }
        glEnd();
    }
    
    glPopMatrix();
    
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);


}

/* Funkcija iscrtava lopticu koja se krece na prvom delu projekta*/
static void drawBall(){
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 1, 1, 1, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.6, 0, 0, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = {1, 1, 0.9, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.8, 0, 0.1, 1 };
    
    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 1.0, 1, 0.2, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.9, 0.8, 0, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 0.9, 0.9, 0.9, 1 };
    
    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 20;

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    /*Iscrtava se lopta*/
    glutSolidSphere(0.10, 20, 20);
}


/*Funkcija iscrtava puteve kuda se krece lopta/kocka 
 *U pitanju je kocka koja se u funkciji on_display skalira
 *Crta se pet kvadrata, donji se ne crta
 */
static void drawCube2(){
    
    glBindTexture(GL_TEXTURE_2D, names[1]);
    
    /*Crta se prvi kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.55, -0.55, 0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.55, -0.55, 0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(0.55, 0.55, 0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.55, 0.55, 0.55);
        
    glEnd();
    
    /*Crta se drugi kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.55, 0.55, -0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.55, 0.55, -0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(0.55, 0.55, 0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.55, 0.55, 0.55);
        
    glEnd();
    
    /*Crta se treci kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.55, -0.55, -0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.55, -0.55, -0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(0.55, 0.55, -0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.55, 0.55, -0.55);
        
    glEnd();
    
    /*Crta se cetvrti kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(0.55, -0.55, -0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.55, 0.55, -0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(0.55, 0.55, 0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(0.55, -0.55, 0.55);
        
    glEnd();
    
    /*Crta se peti kvadtar*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.55, -0.55, -0.55);
        
        
        glTexCoord2f(1,0);
        glVertex3f(-0.55, 0.55, -0.55);
        
        glTexCoord2f(1,1);
        glVertex3f(-0.55, 0.55, 0.55);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.55, -0.55, 0.55);
        
    glEnd();
    
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);
    
}

/*Funkcija iscrtava jednu kocku iz prvog dela projekta.
 * Sastoji se iz 5 kvadrata (donji se ne crta)
 */
static void drawCube(){
    
    glBindTexture(GL_TEXTURE_2D, names[0]);
    
    /*Crta se prvi kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.25, -0.25, 0.25);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.25, -0.25, 0.25);
        
        glTexCoord2f(1,1);
        glVertex3f(0.25, 0.25, 0.25);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.25, 0.25, 0.25);
        
    glEnd();
    
    /*Crta se drugi kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.25, 0.25, -0.25);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.25, 0.25, -0.25);
        
        glTexCoord2f(1,1);
        glVertex3f(0.25, 0.25, 0.25);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.25, 0.25, 0.25);
        
    glEnd();
    
    /*Crta se treci kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.25, -0.25, -0.25);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.25, -0.25, -0.25);
        
        glTexCoord2f(1,1);
        glVertex3f(0.25, 0.25, -0.25);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.25, 0.25, -0.25);
        
    glEnd();
    
    /*Crta se cetvrti kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(0.25, -0.25, -0.25);
        
        
        glTexCoord2f(1,0);
        glVertex3f(0.25, 0.25, -0.25);
        
        glTexCoord2f(1,1);
        glVertex3f(0.25, 0.25, 0.25);
        
        glTexCoord2f(0,1);
        glVertex3f(0.25, -0.25, 0.25);
        
    glEnd();
    
    /*Crta se peti kvadrat*/
    glBegin(GL_POLYGON);
    
        glTexCoord2f(0,0);
        glVertex3f(-0.25, -0.25, -0.25);
        
        
        glTexCoord2f(1,0);
        glVertex3f(-0.25, 0.25, -0.25);
        
        glTexCoord2f(1,1);
        glVertex3f(-0.25, 0.25, 0.25);
        
        glTexCoord2f(0,1);
        glVertex3f(-0.25, -0.25, 0.25);
        
    glEnd();
    
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);
    
}


/* Tajmer za drugi deo projekta */
static void on_timer2(int value)
{
    /*
     * Proverava se da li callback dolazi od odgovarajuceg tajmera.
     */
    if (value != TIMER_ID) return;
    
    /*Azuriraju se vrednosti promenljivih*/
    hours3+=10;
    
    /* Promenljiva sluzi za kretanje vode */
    t += 10;
    
    /* Azuriraju se promenljive koje sluze za kretanje kockice */
    if (tra1<=0.73)
        tra1+=0.015;
    if (tra1>=0.73 && tra2<=1.3)
        tra2+=0.015;
    if (tra2>1.3  && tra3<=0.6)
        tra3+=0.015;
    
    /*Podesava se da animacija krene ispocetka kada se zavrsi */
    if (tra3>=0.6){
        tra1=0;
        tra2=0;
        tra3=0;
    }

    
    /*Forsira se ponovno iscrtavanje prozora */
    glutPostRedisplay();
    
    /* Po potrebi se ponovo postavlja tajmer. */
    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
    }
}

static void on_keyboard(unsigned char key, int x, int y)
{
    
    switch (key) {
    case 27:
        /* Oslobadjaju se korisceni resursi i zavrsava se program. */
        glDeleteTextures(5, names);
        exit(0);
        break;
    case 'r':
    case 'R': 
    /* U zavisnosti od vrednosti parametra n, bira se koja scena ce se prikazati*/
    if (n==0){  
               /* Da bi se teren rotirao, postavlja se vrednost promenljive r na 1 */
                rot=1;
            /* U zavisnosti od vrednosti promenljive rot_pom, menja se display */
            if (rot_pom>=3.6){
                glutDisplayFunc(on_display2);
                 n=1; 
                 
            }
        
              }
            else {
                /* Postavljaju se vrednosti promenljivih na 0 i menja display */
                rot =0;
                glutDisplayFunc(on_display);
                n = 0;
                rot_pom=0;
            }
        break;
    case 'M':
    case 'm':
        /* Resetuje se uglao theta na pocetne vrednosti. */
        theta = 0;
        break;

    case 't':
        /*
         * Dekrementira se ugao theta i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [-89,89] stepeni.
         */
        theta -= delta_theta;
        if (theta < -(PI / 2 - PI / 180)) {
            theta = -(PI / 2 - PI / 180);
        }
        break;

    case 'T':
        /*
         * Inkrementira se ugao theta i ponovo iscrtava scena. Ovaj
         * ugao se odrzava u intervalu [-89,89] stepeni.
         */
        theta += delta_theta;
        if (theta > PI / 2 - PI / 180) {
            theta = PI / 2 - PI / 180;
        }
        break;
    case 's':
    case 'S':
        /* Zaustavlja se animacija */
        animation_ongoing=0;
        timer_active=0;
        break;
    case 'g':
    case 'G':
        /*Pokrece se animacija */
        if (!timer_active) {
                   glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                   timer_active=1;
                  }
        if (!animation_ongoing) {
            glutTimerFunc(TIMER_INTERVAL, on_timer2, TIMER_ID);
            animation_ongoing = 1;
        }
        
    }
    
}

/* Tajmer za prvi deo projekta */
static void on_timer(int value)
{
    /*
     * Proverava se da li callback dolazi od odgovarajuceg tajmera.
     */
    if (value != 0)
        return;

    /* Azuriraju se vrednosti promenljivih*/
    hours+=18;
    if (tr<0.45)
    tr+=0.005;
    
    if (trx<1.15)
        trx+=0.005;
    
    if (x<3.14)
        x+=0.006;
    
    if (tr2<1.15 && x>=3.14)
        tr2+=0.005;
    
    
    if (y<80 && tr2>=1.15)
        y+=1;
    
    /*Podesava se da animacija krene ispocetka kada se zavrsi*/
    if (y>=80){
        trx=0;
        x=0;
        tr2=0;
        y=0;
        
    }
    /* Forsira se ponovno iscrtavanje prozora */
    glutPostRedisplay();
    
    /* Po potrebi se ponovo postavlja tajmer. */
    if (timer_active) {
                   glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                   timer_active=1;
                  }
    
}
    
static void on_timer3(int value)
{
    /*
     * Proverava se da li callback dolazi od odgovarajuceg tajmera.
     */
    if (value != 0)
        return;

    /* Azurira se vrednost promenljive koja odredjuje rotaciju terena.
     * Vrednost se zaustavlja kada se teren zarotira jednom */
    if (rot_pom<3.6){
        hours2+=10;
        rot_pom+=0.0005;
        
    }
    
    /*Forsira se ponovno iscrtavanje prozora */
    glutPostRedisplay();
    
    /* Po potrebi se ponovo postavlja tajmer. */
    if (rot){
        glutTimerFunc(10, on_timer3, 0);
        rot=1;
        
    }
}

static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 10);
}


/* Izracunava vrednost funkcije za parametre u i v, koristi se u set_vertex_and_normal */
float function(float u, float v){
    
    return 10*sin((u*v)/10);
}

/* Izracunava vrednost funkcije za parametre u i v, koristi se u set_vertex_and_normal2 */
float function2(float u, float v){
    
    return 10*cos((t/10 + u*2)/10);
}

/* Postavlja normalu i kordinate verteksa za tacku sa parametrima
 * u i v *, koristo se u plot_function*/
void set_vertex_and_normal(float u, float v)
{
    float diff_u, diff_v;

    /* Racunamo priblizne vrednosti izvoda funkcije u tacki u, v */
    diff_u = (function(u + 1, v)
             - function(u - 1, v)) / 2.0;
    diff_v = (function(u, v + 1)
             - function(u, v - 1)) / 2.0;

    /* Postavljamo normalu - vektor normalan na tangentnu ravan */
    /* Racuna se priblizan vektor normale: */
    glNormal3f(-diff_u, 1, -diff_v);

    /* Postavljamo verteks */
    glVertex3f(u, function(u, v), v);


}

/* Postavlja normalu i kordinate verteksa za tacku sa parametrima
 * u i v *, koristo se u plot_function2*/
void set_vertex_and_normal2(float u, float v)
{
    float diff_u, diff_v;

    /* Racunamo priblizne vrednosti izvoda funkcije u tacki u, v */
    diff_u = (function2(u + 1, v)
             - function2(u - 1, v)) / 2.0;
    diff_v = (function2(u, v + 1)
             - function2(u, v - 1)) / 2.0;

    /* Postavljamo normalu - vektor normalan na tangentnu ravan */
    /* Racuna se priblizan vektor normale: */
    glNormal3f(-diff_u, 1, -diff_v);

    /* Postavljamo verteks */
    glVertex3f(u, function2(u, v), v);


}

/* Crtamo funkciju 
 * Iscrtava se voda u drugom delu projekta
 */
void plot_function2()
{
    float scale;
    int u, v;

    glPushMatrix();
    /* Racuna se  faktor skaliranja tako da cela funkcija bude prikazana */
    scale = 2.0 / max( U_TO - U_FROM, V_TO - V_FROM );
    glScalef(scale, scale, scale);
    
    /* Crta se  funkcija strip po strip */
    for (u = U_FROM-150; u < U_TO+200; u++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (v = V_FROM+2; v <= V_TO+20; v++) {
            set_vertex_and_normal2(u, v);
            set_vertex_and_normal2(u + 1, v);
        }
        glEnd();
    }

    glPopMatrix();
}

/* Crtamo funkciju 
 * Iscrtava se trava u prvom delu projekta
 */
void plot_function()
{
    float scale;
    int u, v;

    glPushMatrix();
    /* Racuna se faktor skaliranja tako da cela funkcija bude prikazana */
    scale = 3.0 / max( U_TO - U_FROM, V_TO - V_FROM );
    glScalef(scale, scale, scale);
    
    /* Crta se funkcija strip po strip */
    for (u = U_FROM; u < U_TO; u++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (v = V_FROM; v <= V_TO; v++) {
            set_vertex_and_normal(u, v);
            set_vertex_and_normal(u + 1, v);
        }
        glEnd();
    }

    glPopMatrix();
}

static void initText(void){
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image* image;
    
    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, FILENAME0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(5, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Kreira se druga tekstura. */
    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Kreira se treca tekstura. */
    image_read(image, FILENAME2);

    glBindTexture(GL_TEXTURE_2D, names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    
    
    /* Kreira se cetvrta tekstura. */
    image_read(image, FILENAME3);

    glBindTexture(GL_TEXTURE_2D, names[3]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Kreira se peta tekstura. */
    image_read(image, FILENAME4);

    glBindTexture(GL_TEXTURE_2D, names[4]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);
}

static void on_display(void)
{   
    
   
    
    /* Promenjiva odredjuje rotaciju Sunca*/
    float sun_rotation = 360 * hours / (100* 24);
    
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClearColor(0.5, 0.7, 1, 0);
    
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 1, 1, 1, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.9, 0.7, 0, 1 };
    
    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = {1, 1, 0, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 1, 0.1, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.9, 0.7, 0, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.9, 0.8, 0, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 0.9, 0.9, 0.9, 1 };
    
    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 20;
    
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,
              2.5*cos(theta),
              2.5,
              0, 0, 0, 0, 1, 0);

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
      /* Crta se Sunce*/
      glPushMatrix();
        glTranslatef(1, 1.2, 0);
        glRotatef(sun_rotation, 3.75, 0, 0);
        glutSolidSphere(0.16, 20, 20);
      glPopMatrix();  
    
      
    /* Podesava se rotacija celog terena, bez Sunca */
    if (rot)
    glutTimerFunc(TIMER_INTERVAL, on_timer3, TIMER_ID);
    double place_rotation=50*hours2/(100*100);
    if (rot==1)
    glRotatef(place_rotation, 0, 3, 0);
    
    
    /*Crta se duga*/
    glPushMatrix();
    /* Crta se jedan deo duge*/
    glEnable(GL_CLIP_PLANE0);
    double params[]={0, 0.1, 0, 0};
    glTranslatef(0, -0.3, 0);
    glClipPlane(GL_CLIP_PLANE0, params);
    glTranslatef(0, -0.2, -1.45);
    drawRainbow();
    
    
    /*Crta se drugi deo duge */
    glPushMatrix();
    glRotatef(-150, 0, 1, 0);
    glRotatef(-30, 0, 1, 0);
    glTranslatef(0, 0, -0.001);
    drawRainbow1();
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
    
    glPopMatrix();
    
    /*Kretanje loptice u zavisnosti od vrednosti promenljivih*/
    glPushMatrix();
    if (tr2>=1.15){
        glTranslatef(0, 0.2, 0);
        glRotatef(y, 0, 0, 1);
    }
    
    if (tr>=0)
    glTranslatef(0, -tr, 0);
    
    
    if (tr>=0.45)
        glTranslatef(0, 0, trx);
    
    
    if (trx>=1.15){
        if (cos(x)<0)
          glTranslatef(x/4, cos(x)/(-3), 0);
        else glTranslatef(x/4, cos(x)/4, 0);
    }

    if (x>=3.14){
        glTranslatef(0, -0.25, -tr2);
        glTranslatef(0, 0, -0.2);
    }
    
    /* Crta se loptica */
    glTranslatef(-0.5, 0.85, 0);
    glRotatef(sun_rotation, 3.75, 0, 0);
    drawBall();
    
    glPopMatrix();
    
    /* Ambijentalna boja svetla. */
    GLfloat light_ambient2[] = { 0, 0.5, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse2[] = { 0, 0.4, 0.2, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular2[] = { 0.9, 0.9, 0.9, 1 };
    
    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs2[] = { 0.3, 0.3, 0.7, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs2[] = { 0, 0.5, 0, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs2[] = { 0, 0.9, 0.2, 1 };
    
    /* Koeficijent glatkosti materijala. */
    GLfloat shininess2 = 30;
     
    /* Podesavaju se parametri svetla. */
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular2);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs2);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
    glShadeModel(GL_SMOOTH);

    /* Crta se trava */
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    plot_function();
    glPopMatrix();
    
    
    /* Crtaju se kocke, jedna po jedna */
    glPushMatrix();
    glTranslatef(-0.5, 0, -0.2);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.3, 0, -0.3);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.4, 0, 1);
    drawCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.6, 0, 1);
    drawCube();
    glPopMatrix();
    
    /* Crtaju se putici kuda se loptica krece*/
    glPushMatrix();
    glTranslatef(0.3, 0.3, 0.4);
    glScalef(0.15, -0.05, 0.8);
    drawCube2();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.5, 0.3, 0.5);
    glScalef(0.15, -0.05, 0.8);
    drawCube2();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.1, 0.25, 1.2);
    glScalef(0.15, 0.05, 0.2);
    drawCube2();
    glPopMatrix();
    
    /* Ispisuju se slova na terenu u zavisnosti od vrednosti promenljivih*/
    glPushMatrix();
    /* Transliraju se slova */
    glTranslatef(0,0,0.5);
    
    /* Ispisuju se slova u zavisnosti od vrednosti promenljivih rot i rot_pom */
    if (rot!=1 && timer_active)
    output( 0, 0, "Press r to rotate");
    
    if (rot_pom>=3.6)
        output( 0, 0, "Press r to change");
    glPopMatrix();
    
    
    /* Crtaju se oblaci */
    glPushMatrix();
    glTranslatef(-0.5, 1.3, 0);
    drawCloud();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2.2, 0, 0);
    drawCloud();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2, 0.2, 0);
    drawCloud();
    glPopMatrix();
    
    
    
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}


void on_display2(void)
{
   
   /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 1, 1, 1, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.9, 0.9, 0, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = {0.9, 0.7, 0, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.7, 1, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 1.0, 0.1, 0.1, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.9, 0.8, 0, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 0.9, 0.9, 0.9, 1 };
    
    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 20;

    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 2, 2, 0, 0, 0, 0, 1, 0);

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    /* Podesava se rotacija Meseca */
    float moon_rotation = 360 * hours3 / (100* 24);
    
    /*Crta se Mesec */
    glPushMatrix();
        glTranslatef(0.8, 1.2, 0);
        glRotatef(moon_rotation, 3.75, 0,  0);
        glutSolidSphere(0.16, 20, 20);
      glPopMatrix(); 
      
    glPushMatrix();
    
    /* Crta se pozadina */
    glTranslatef(0, 0, 1);
    glScalef(2, 1, 1);
    drawBackground();
    glPopMatrix();

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient2[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse2[] = { 0.8, 0.4, 0, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular2[] = { 0.9, 0.9, 0.9, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs2[] = { 0.3, 0.3, 0.7, 1 };
    
    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs2[] = { 0.2, 0.2, 1, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs2[] = { 1, 0, 0, 1 };
    
    /* Podesavaju se parametri svetla. */
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular2);


    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs2);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    /* Crta se voda */
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    plot_function2();
    glShadeModel(GL_SMOOTH);    
    glPopMatrix();
    
    /* Kretanje i crtanje kockice */
    glPushMatrix();
    glTranslatef(0, 0.5, 0.5);
    glTranslatef(-tra3, 0, -tra3*1.2);
    glTranslatef(tra2, 0, 0);
    glTranslatef(-tra1, tra1/4, tra1*1.2);
    glRotatef(moon_rotation, 1, 0, 0);
    glScalef(0.12, 0.12, 0.12);
    drawLittleCube();
    glPopMatrix();

    /* Ispisuju se slova */
    glPushMatrix();
    glTranslatef(0, 1, 2);
    output( 0, 0, "Press r to change");
    glPopMatrix();
     
     
    /* Crtaju se lopte, jedna po jedna*/
    glPushMatrix();
    glTranslatef(0, -0.8, -0.2);
    glScalef(-0.7, -0.7, -0.7);
    drawHemisphere();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.4, -0.8, 1);
    glScalef(-0.7, -0.7, -0.7);
    drawHemisphere();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.4, -0.8, 1);
    glScalef(-0.7, -0.7, -0.7);
    drawHemisphere();
    glPopMatrix();
     

    /*Crtaju se putevi kuda se krece kocka*/
    glPushMatrix();
    glTranslatef(-0.06, 0.5, 1.3);
    glScalef(0.75, 0.05, 0.1);
    drawCube2();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.5, 0.5, 1);
    glRotatef(45, 0, 1, 0);
    glScalef(0.35, 0.07, 0.1);
    drawCube2();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.48, 0.5, 1.1);
    glRotatef(135, 0, 1, 0);
    glScalef(0.33, 0.05, 0.1);
    drawCube2();
    glPopMatrix();

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
