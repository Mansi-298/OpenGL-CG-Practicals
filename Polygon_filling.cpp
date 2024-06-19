
#include<GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;


void init()
{
   glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
   glPointSize(1.0);
    glLineWidth(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,600,0,600);

}

void display()
{}

struct COLOR
{
    float r;
    float g;
    float b;
};

class polygon_fill
{
    void setPixelColor(int x, int y, COLOR c)
    {
        glColor3f(c.r,c.g,c.b);
        glBegin(GL_POINTS);
        glVertex2f(x,y);
        glEnd();
        glFlush();
    }

    COLOR getPixelColor(int x, int y)
    {
        COLOR c;
        glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&c);
        return c;
    }

public:

    void boundary_fill(int x, int y, COLOR fill, COLOR border)
    {
       COLOR current;
        current = getPixelColor(x,y);

        if(!(current.r != fill.r && current.g != fill.g && current.b != fill.b) &&
           (current.r != border.r && current.g != border.g && current.b != border.b))
        {
            setPixelColor(x,y,fill);
            boundary_fill(x + 1,y,fill,border);
            boundary_fill(x,y + 1,fill,border);
            boundary_fill(x - 1,y,fill,border);
            boundary_fill(x,y - 1,fill,border);
        }
    }

    void flood_fill(int x, int y, COLOR fill, COLOR interior)
    {
        COLOR current;
        current = getPixelColor(x,y);

        if(current.r == interior.r && current.g == interior.g && current.b == interior.b)
        {
            setPixelColor(x,y,fill);
            flood_fill(x + 1 ,y ,fill, interior);
            flood_fill(x ,y + 1 ,fill, interior);
            flood_fill(x - 1 ,y ,fill, interior);
            flood_fill(x ,y - 1 ,fill, interior);
        }

    }
};

int xarr[100];
int yarr[100];
int xc,yc;
int i = 0;

void mouse(int btn, int state, int x, int y)
{
     if(state == GLUT_DOWN)
    {
        if(btn == GLUT_LEFT_BUTTON)
        {
            xarr[i] = x;
            yarr[i] = y;
            i++;

            if(i > 1)
            {
                glColor3f(1.0,0.0,0.0);
                glBegin(GL_LINE_STRIP);
                glVertex2i(xarr[i-2],600-yarr[i-2]);
                glVertex2i(xarr[i-1],600-yarr[i-1]);
                glEnd();
                glFlush();
            }
        }
        if(btn == GLUT_RIGHT_BUTTON)
        {
            xc = x;
            yc = y;
        }
    }
}

void menu(int ch)
{
    polygon_fill p;
    COLOR fill,interior,border;

    fill.r = 0.0;
    fill.g = 1.0;
    fill.b = 0.0;

    border.r = 0.0;
    border.g = 0.0;
    border.b = 0.0;

    interior.r = 1.0;
    interior.g = 1.0;
    interior.b = 1.0;

    switch(ch)
    {
    case 1:
        p.flood_fill(xc,600-yc,fill,interior);
        break;
    case 2:
        p.boundary_fill(xc,600-yc,fill,border);
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("POLYGON");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("flood_fill",1);
    glutAddMenuEntry("boundary_fill",2);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    glutMainLoop();
    return 0;
}
