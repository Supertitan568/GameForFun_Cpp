#include<iostream>
#include<GL/freeglut.h>
#include<vector>
#include<math.h>
#include<cstdlib>
class person 
{
    public:
        int pos [2];
        int vel;
    person (int x,int y,int v)
    {
        pos[0] = x;
        pos[1] = y;
        vel = v;
        std::cout << "Enemy Created" << std::endl;
    }
};
person ch(0,0,4);
std::vector<person> allEnemies {person(10,10,2)};
void createEnemy (int n){
    for (int i=0; i<n; i++){
        person e(-10 , -10 ,2);
        allEnemies.push_back(e);
    }
}

// Initialization function
void startInit (void)
{
    // Reset background color with white (since all three argument is 1.0)
    glClearColor(1.0, 1.0, 1.0, 0.0);
  
    // Set picture color to red (in RGB model)
    // as only argument corresponding to R (Red) is 1.0 and rest are 0.0
    glColor3f(1.0f, 0.0f, 0.0f);
  
    // Set width of point to one unit
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  
    // Set window size in X- and Y- direction
    gluOrtho2D(-620.0, 620.0, -340.0, 340.0);
}
  
// keyboard function : it gets activated when a button is pressed
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 119 :
        ch.pos[1] += ch.vel;
        break;
    case 97 :
        ch.pos[0] -= ch.vel;
        break;
    case 115 :
        ch.pos[1] -= ch.vel;
        break;
    case 100 :
        ch.pos[0] += ch.vel;
        break;
    default:
        break;
    }
}

void drawDisplay(void)
{  
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
        glVertex2i(ch.pos[0],ch.pos[1]);
        glVertex2i(ch.pos[0] , ch.pos[1] + 5);
        glVertex2i(ch.pos[0] + 5, ch.pos[1]+5);
        glVertex2i(ch.pos[0] + 5, ch.pos[1]);
    glEnd();
    for(int i=0; i<allEnemies.size(); i++)
    {
        person c = allEnemies.at(i);
        glBegin(GL_LINE_LOOP);
            glVertex2i(c.pos[0],c.pos[1]);
            glVertex2i(c.pos[0] , c.pos[1] + 10);
            glVertex2i(c.pos[0] + 10, c.pos[1]+10);
            glVertex2i(c.pos[0] + 10, c.pos[1]);
        glEnd();
    }
    glutSwapBuffers();
    glutPostRedisplay();
}

// Driver Program
int main (int argc, char** argv)
{
    glutInit(&argc, argv);
      
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    // Declares window size
    glutInitWindowSize(1100, 600);
      
    // Declares window position which is (0, 0)
    // means lower left corner will indicate position (0, 0)
    glutInitWindowPosition(0, 0);
  
    // Name to window
    glutCreateWindow("Game");
  
    // keyboard function
    glutKeyboardFunc(keyboard);
    // Call to myInit()
    startInit();
    glutDisplayFunc(drawDisplay);
    glutMainLoop();
}