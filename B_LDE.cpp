//  bresenham line
 #include <GL/glut.h>
#include <iostream>

using namespace std;

int x1,y1,x2,y2,type;

int sign(int val)
{
    if(val == 0)
        return 0;
    else if(val < 0)
        return -1;
    else
        return 1;
}

void bresenhams(int x1, int y1, int x2, int y2, int type)
{
    int x = x1;
    int y = y1;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);

    int interchange = 0;

    if(dy > dx)
    {
        int temp = dy;
        dy = dx;
        dx = temp;
        interchange = 1;
    }

    int e = 2*dy - dx;

    glPointSize(1.0f);
    if(type == 4)
    {
        glPointSize(5.0f);
    }

    glBegin(GL_POINTS);
    glVertex2i(x,y);

    for(int i = 1; i <= dx; i++)
    {
        if(type == 4 || type == 1)
        {
            glVertex2i((int)x,(int)y);
        }
        else if(i % 4 == 0 && type == 2)
        {
            glVertex2i((int)x,(int)y);
        }
        else if((i/5)%2 == 0 && type == 3)
        {
            glVertex2i((int)x,(int)y);
        }

        while(e >= 0)
        {
            if(interchange)
            {
                x = x + s1;
            }
            else
            {
                y = y + s2;
            }
            e = e - 2 * dx;
        }
        if(interchange)
        {
            y = y + s2;
        }
        else
        {
            x = x+ s1;
        }
        e = e + 2 * dy;
    }
    glEnd();
}

void pattern()
{
    glBegin(GL_LINE_LOOP);
        glVertex2i(-100,70);
        glVertex2i(-100,-70);
        glVertex2i(100,-70);
        glVertex2i(100,70);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2i(0,70);
        glVertex2i(-100,0);
        glVertex2i(0,-70);
        glVertex2i(100,0);
        glVertex2i(0,70);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2i(-40,40);
        glVertex2i(-40,-40);
        glVertex2i(40,-40);
        glVertex2i(40,40);
    glEnd();
}

void Plot(float x, float y)
{
    glVertex2i(x,y);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    for(int i = -700; i <= 700; i++)
    {
        Plot(i,0);
        Plot(0,i);
    }
    glEnd();
    glFlush();

    glColor3f(1.0,0.0,0.0);
    pattern();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-700 / 2, 700 / 2, -700 / 2, 700 / 2);
}
int oldx,oldy;
int newx,newy;
int cnt = 0;

void mouse(int btn, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(btn == GLUT_LEFT_BUTTON)
        {
            int xi = x - 350;
            int yi = 350 - y;

            if(cnt == 0)
            {
                oldx = xi;
                oldy = yi;
                cnt = 1;
            }
            else
            {
                newx = xi;
                newy = yi;
                cnt = 0;

                glBegin(GL_POINTS);
                glVertex2i(oldx,oldy);
                glVertex2i(newx,newy);
                glEnd();

                glColor3f(1.0,0.0,0.0);
                bresenhams(oldx,oldy,newx,newy,type);
                glFlush();
            }


        }
    }
}

void menu(int ch)
{
    type = ch;
}
int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("Bresenham_SIMPLE", 1);
    glutAddMenuEntry("Bresenham_DOTTED", 2);
    glutAddMenuEntry("Bresenham_DASHED", 3);
    glutAddMenuEntry("Bresenham_SOLID", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();

    return 0;
}
