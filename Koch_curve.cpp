
#include<GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;

GLfloat oldx = -0.7;
GLfloat oldy = 0.5;

void drawkoch(GLfloat dir, GLfloat len, GLfloat iter)
{
    GLdouble dirRad = dir * 0.0174533;
    GLfloat newx = oldx + len * cos(dirRad);
    GLfloat newy = oldy + len * sin(dirRad);

        glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    if(iter == 0)
    {
        glVertex2f(newx,newy);//***************//
        glVertex2f(oldx,oldy);

        oldx = newx;
        oldy = newy;
    }
    else
    {
        iter--;
        drawkoch(dir,len,iter);
        dir += 60;
        drawkoch(dir,len,iter);
        dir -= 120;
        drawkoch(dir,len,iter);
        dir += 60;
        drawkoch(dir,len,iter);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int n;
    cout<<"enter no of iter - ";
    cin>>n;

    drawkoch(0.0,0.05,n);
    drawkoch(-120.0,0.05,n);
    drawkoch(120.0,0.05,n);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("KOCH");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
