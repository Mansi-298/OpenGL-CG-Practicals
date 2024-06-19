#include<iostream>
#include<math.h>
#include<GL/glut.h>
using namespace std;
int h = 0;
int k = 0;

void init()
{
    //glPointSize(1.5f);
    //glLineWidth(1.5f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-700/2,700/2,-700/2,700/2);
     glClear(GL_COLOR_BUFFER_BIT);
}

void Plot(float x, float y)
{
    glVertex2i(x,y);
}
void display()
{

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POINTS);
    for(int i = -700; i <= 700; i++)
    {
        Plot(i,0);
        Plot(0,i);
    }
    glEnd();
    glFlush();
}
void drawMainCircle(int r)
{
    int d = 3 - 2*r;
    int x = 0;
    int y = r;

    glBegin(GL_POINTS);
    do
    {
        glVertex2i(h - x, k + y);
        glVertex2i(h - y, k + x);
        glVertex2i(h + y, k + x);
        glVertex2i(h + x, k + y);

        glVertex2i(h + x, k - y);
        glVertex2i(h + y, k - x);
        glVertex2i(h - y, k - x);
        glVertex2i(h - x, k - y);

        if(d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4*(x - y)+10;
            y = y - 1;
        }
        x = x + 1;
    }while(x<=y);
    glEnd();

}

void drawCirclePTN(int r)
{

    int d = 3 - 2*r;
    int x = 0;
    int y = r;

    glBegin(GL_POINTS);
    do
    {
        glVertex2i(h + x, k - y);
        glVertex2i(h + y, k - x);
        glVertex2i(h - y, k - x);
        glVertex2i(h - x, k - y);

        if(d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4*(x - y)+10;
            y = y - 1;
        }
        x = x + 1;
    }while(x<=y);
    glEnd();
}

void drawCircleNTP(int r)
{

    int d = 3 - 2*r;
    int x = 0;
    int y = r;

    glBegin(GL_POINTS);
    do
    {
        glVertex2i(h - x, k + y);
        glVertex2i(h - y, k + x);
        glVertex2i(h + y, k + x);
        glVertex2i(h + x, k + y);

        if(d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4*(x - y)+10;
            y = y - 1;
        }
        x = x + 1;
    }while(x<=y);
    glEnd();

}

void simple(int r)
{
    drawMainCircle(r);
}

void cocentric(int r)
{
    while(r < 100)
    {
        drawMainCircle(r);
        r += 10;
    }
}

void spiral(int r)
{
    for(int i = 0; i < 6; ++i)
    {
        drawCircleNTP(r);
        h -= 10;
        r += 10;
        drawCirclePTN(r);
        h += 10;
        r += 10;
    }
}

void olympic(int r)
{
    for(int i = 0; i < 3; ++i)
    {
        drawMainCircle(r);
        h += 2.5 * r;
    }
    k += 1.3 * r;
    h -= 3.7 *r;
    for(int i = 0; i < 2; ++i)
    {
        drawMainCircle(r);
        h -= 2.5 * r;
    }
}
void menu(int ch)
{
    switch(ch)
    {
    case 1:
        simple(55);
        break;
    case 2:
        cocentric(55);
        break;
    case 3:
        spiral(55);
        break;
    case 4:
        olympic(55);
        break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(700,700);
    glutCreateWindow("Circle");
    init();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("simple",1);
    glutAddMenuEntry("cocentric",2);
    glutAddMenuEntry("spiral",3);
    glutAddMenuEntry("olympic",4);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    glutMainLoop();
    return 0;
}
