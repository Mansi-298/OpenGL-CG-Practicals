
#include<iostream>
#include<math.h>
#include<GL/glut.h>
using namespace std;

int mati[100][100];
int mato[100][100];
int k = 0;
float tx,ty;
float sx,sy;
float Xm,Ym;

void init()
{
    glPointSize(1.5f);
    glLineWidth(1.5f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-700/2,700/2,-700/2,700/2);
     glClear(GL_COLOR_BUFFER_BIT);
}

void mul(float arrT[3][3])
{
    for(int i = 0; i < k; i++)
    {
         float x = mati[i][0];
        float y = mati[i][1];
        mato[i][0] = arrT[0][0] * x + arrT[0][1] * y + arrT[0][2];
        mato[i][1] = arrT[1][0] * x + arrT[1][1] * y + arrT[1][2];
    }

    cout << "mato Points:\n";
    for (int i = 0; i < k; i++) {
        cout << "(" << mato[i][0] << ", " << mato[i][1] << ")\n";
    }
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

void translation(float tx, float ty)
{
    float arrT[3][3] = {1, 0, tx, 0, 1, ty, 0, 0, 1};
    mul(arrT);
    // Draw the polygon with translated points
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < k; i++) {
        glVertex2f(mato[i][0], mato[i][1]);
    }
    glEnd();
    glFlush(); // Flush the drawing commands
    glutPostRedisplay(); // Request display update
}

void scaling(float sx, float sy)
{
    float arrT[3][3] = {sx, 0, 0, 0, sy, 0, 0, 0, 1};

    // Apply scaling
    mul(arrT);

    // Draw the polygon with scaled points
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < k; i++) {
        glVertex2f(mato[i][0], mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
}



void Reflection_X_axis()
{
    // y = 0
    // x' = x
    // y' = -y

    float arrT[3][3] = {1, 0, 0, 0, -1, 0, 0, 0, 1};
    mul(arrT);

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++)
    {
        glVertex2f(mato[i][0],mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void Reflection_Y_axis()
{
    // x = 0;
    // x' = -x;
    // y' = y;
    float arrT[3][3] = {-1,0,0,0,1,0,0,0,1};
    mul(arrT);

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++)
    {
        glVertex2f(mato[i][0],mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void Reflection_X_equal_Y_axis()
{
    // x' = y
    // y' = x

    float arrT[3][3] = {0,1,0,1,0,0,0,0,1};
    mul(arrT);

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++)
    {
        glVertex2f(mato[i][0],mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();

}

void Reflection_About_Origin()
{
    // x' = -x;
    // y' = -y;

    float arrT[3][3] = {-1,0,0,0,-1,0,0,0,1};
    mul(arrT);

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++)
    {
        glVertex2f(mato[i][0],mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void Reflection_X_equal_minus_Y_axis()
{
    // x = -y
    // x' = -y
    // y' = -x

     float arrT[3][3] = {0,-1,0,-1,0,0,0,0,1};
    mul(arrT);

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++)
    {
        glVertex2f(mato[i][0],mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void Rotation(float angle)
{
    float arrT[3][3] = {cos(angle),-(sin(angle)), 0, sin(angle), cos(angle),0,0,0,1};
    mul(arrT);

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++)
    {
        glVertex2f(mato[i][0],mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void shearing_X_axis()
{
     float shx;
     cout << "Enter the value of shx :";
     cin >> shx;

    float arrT[3][3] = {1,shx,0,0,1,0,0,0,1};
    mul(arrT);

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++)
    {
        glVertex2f(mato[i][0],mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void shearing_Y_axis()
{
    float shy;
     cout << "Enter the value of shy :";
     cin >> shy;

    float arrT[3][3] = {1,0,0,shy,1,0,0,0,1};
    mul(arrT);

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++)
    {
        glVertex2f(mato[i][0],mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void Rotation_about_arbitory() {
     float angle;
     cout << "Enter the Rotaion angle : ";
     cin >> angle;
     angle = (angle * (3.142 / 180));
     cout << "Enter the value of Xm :";
     cin >> Xm;
     cout << "Enter the value of Ym :";
     cin >> Ym;
     float arrT[3][3] = {cos(angle),-sin(angle),(-Xm * cos(angle) + Ym * sin(angle) + Xm),
                        sin(angle),cos(angle),(-Xm * sin(angle) - Ym * cos(angle) + Ym),
                        0,0,1};
     mul(arrT);

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++)
    {
        glVertex2f(mato[i][0],mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void Scalling_about_arbitary_point() {
     cout << "Enter the value of Xm :";
     cin >> Xm;
     cout << "Enter the value of Ym :";
     cin >> Ym;
     cout << "Enter the value of Sx :";
     cin >> sx;
     cout << "Enter the value of Sy :";
     cin >> sy;
     float arrT[3][3] = {sx,0,(-Xm*sx)+Xm,
                         0,sy,(-Ym*sy)+Ym,
                         0,0,1};
     mul(arrT);

    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < k; i++)
    {
        glVertex2f(mato[i][0],mato[i][1]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(btn == GLUT_LEFT_BUTTON)
        {
            mati[k][0] = (float)(x - 350);
            mati[k][1] = (float)(350 - y);

              // Debugging: Print input coordinates
            cout << "Input Coordinates:\n";
            for (int i = 0; i <= k; i++) {
                cout << "(" << mati[i][0] << ", " << mati[i][1] << ")\n";
            }

            glColor3f(0.0,1.0,0.0);
            glBegin(GL_POINTS);
            glVertex2f(mati[k][0],mati[k][1]);
            glEnd();
            k++;
            glFlush();
        }
        if(btn == GLUT_RIGHT_BUTTON)
        {
            glColor3f(0.0,1.0,0.0);
            glBegin(GL_LINE_LOOP);
            for(int i = 0; i < k; i++)
            {
                glVertex2f(mati[i][0],mati[i][1]);
            }
            glEnd();
            glFlush();
        }

    }
}

void menu(int ch)
{
    switch(ch)
    {
    case 1:
        cout << "Enter the value of tx :";
        cin >> tx;
        cout << "Enter the value of ty :";
        cin >> ty;
        translation(tx,ty);
        break;
    case 2:
        cout << "Enter the value of Sx :";
        cin >> sx;
        cout << "Enter the value of Sy :";
        cin >> sy;
        scaling(sx, sy);
        break;
    case 3:
        Reflection_X_axis();
        break;
    case 4:
        Reflection_Y_axis();
        break;
    case 5:
        Reflection_X_equal_Y_axis();
        break;
    case 6:
        Reflection_About_Origin();
        break;
    case 7:
        Reflection_X_equal_minus_Y_axis();
        break;
    case 8:
        float angle1;
        cout << "Enter the Rotaion angle : ";
        cin >> angle1;
        angle1 = (angle1 * (3.142 / 180));
        Rotation(-(angle1));
        break;
    case 9:
        float angle2;
        cout << "Enter the Rotaion angle : ";
        cin >> angle2;
        angle2 = (angle2 * (3.142 / 180));
         Rotation(angle2);
        break;
        break;
    case 10:
        shearing_X_axis();
        break;
    case 11:
        shearing_Y_axis();
        break;
    case 12:
        Rotation_about_arbitory();
        break;
    case 13:
        Scalling_about_arbitary_point();
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(700,700);
    glutCreateWindow("Transformation_2");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("Translation : xy-axis",1);
    glutAddMenuEntry("Scaling : xy-axis",2);
    glutAddMenuEntry("Reflection : x-axis",3);
    glutAddMenuEntry("Reflection : y-axis",4);
    glutAddMenuEntry("Reflection : xy-axis",5);
    glutAddMenuEntry("Reflection : Origin",6);
    glutAddMenuEntry("Reflection : x=-y axis",7);
    glutAddMenuEntry("Rotation : clockwise",8);
    glutAddMenuEntry("Rotation : anti-clockwise",9);
    glutAddMenuEntry("Shearing : x-axis",10);
    glutAddMenuEntry("Shearing : y-axis",11);
    glutAddMenuEntry("Rotation about arbitary point",12);
    glutAddMenuEntry("Scaling about arbitary point",13);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    glutMainLoop();
    return 0;
}
