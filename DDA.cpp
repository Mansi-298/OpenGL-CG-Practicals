
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

void dda(int x1,int y1, int x2,int y2,int type)
{
        float dx,dy,length,x,y,xin,yin;

        dx = x2 - x1;
        dy = y2 - y1;

        if(abs(dx) > abs(dy))
        {
            length = abs(dx);
        }
        else
        {
            length = abs(dy);
        }

        xin = dx / length;
        yin = dy / length;

        x = x1 + 0.5*sign(xin);
        y = y1 + 0.5*sign(yin);

        glPointSize(1.0f);
        if(type == 4)
        {
            glPointSize(5.0f);
        }

        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();

        int j = 0;
        for(int i = 0; i < length; i++)
        {
            x = x + xin;
            y = y + yin;

            glBegin(GL_POINTS);
            if(type == 4 || type == 1)
            {
                glVertex2i((int)x,(int)y);
            }
            if(j % 4 == 0 && type == 2)
            {
                glVertex2i((int)x,(int)y);
            }
            if(j < 5 && type == 3)
            {
                glVertex2i((int)x,(int)y);
            }
            j = (j+1)%10;
            glEnd();
        }
        glEnd();
        glFlush();
}

void pattern()
{
    dda(-50,0,50,0,1);
    dda(-50,0,-90,60,1);
    dda(50,0,90,60,1);
    dda(-90,60,90,60,1);

    dda(90,60,90,120,1);
    dda(90,120,60,60,1);

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
int oldx,oldy,newx,newy;
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

                    glColor3f(1.0,0.0,0.0);
                    glBegin(GL_POINTS);
                    glVertex2i(oldx,oldy);
                    glVertex2i(newx,newy);
                    glEnd();

                      glColor3f(1.0,0.0,0.0);
                      dda(oldx,oldy,newx,newy,type);
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
