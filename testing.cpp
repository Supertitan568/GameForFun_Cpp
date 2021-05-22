#include<iostream>
#include<GL/freeglut.h>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<thread>
class thing 
{
    public:
        int pos [2];
        int vel;
    thing (int x,int y,int v)
    {
        pos[0] = x;
        pos[1] = y;
        vel = v;
    }
};
bool gameOver = false;
unsigned char k;
thing ch(0,0,4);
std::vector<thing> allEnemies {thing(10,10,1)};
std::vector<thing> allItems {thing(80,80,0)};
void createEnemy (int n)
{
    for (int i=0; i<n; i++)
    {
        thing e(-10 , -10 ,1);
        allEnemies.push_back(e);
    }
}
void logic ()
{
    while (gameOver != true)
    {
        for(int i=0; i<allEnemies.size(); i++)
        {
            if (ch.pos[0] > allEnemies.at(i).pos[0])
            {
                allEnemies.at(i).pos[0] += allEnemies.at(i).vel;
            }
            else if (ch.pos[1] > allEnemies.at(i).pos[1])
            {
                allEnemies.at(i).pos[1] += allEnemies.at(i).vel;
            }
            else if (ch.pos[0] < allEnemies.at(i).pos[0])
            {
                allEnemies.at(i).pos[0] -= allEnemies.at(i).vel;
            }
            else if (ch.pos[1] < allEnemies.at(i).pos[1])
            {
                allEnemies.at(i).pos[1] -= allEnemies.at(i).vel;
            }
        }
        for (int i=0; i<allEnemies.size(); i++)
        {
            if((abs(allEnemies[i].pos[0] - ch.pos[0]) < 5) && (abs(allEnemies[i].pos[1] - ch.pos[1]) < 5))
            {
                std::cout << "You got hit by an Enemy" << std::endl;
            }
        }
        for (int i=0; i<allItems.size(); i++)
        {
            if((abs(allItems[i].pos[0] - ch.pos[0]) < 5) && (abs(allItems[i].pos[1] - ch.pos[1]) < 5))
            {
                std::cout << "You got an item" << std::endl;
            }
        }
        switch (k)
        {
        case 119 :
            ch.pos[1] += ch.vel;
            k = 0;
            break;
        case 97 :
            ch.pos[0] -= ch.vel;
            k = 0;
            break;
        case 115 :
            ch.pos[1] -= ch.vel;
            k = 0;
            break;
        case 100 :
            ch.pos[0] += ch.vel;
            k = 0;
            break;
        default:
            break;
        }
        system("sleep .05");
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
    k = key;
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
    for(int i=0; i<allItems.size(); i++)
    {
        thing c = allItems.at(i);
        glBegin(GL_LINE_LOOP);
            glVertex2i(c.pos[0],c.pos[1]);
            glVertex2i(c.pos[0] , c.pos[1] + 3);
            glVertex2i(c.pos[0] + 3, c.pos[1] + 3);
            glVertex2i(c.pos[0] + 3, c.pos[1]);
        glEnd();
    }
    for(int i=0; i<allEnemies.size(); i++)
    {
        thing c = allEnemies.at(i);
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
    std::thread logicThread(logic);
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
    logicThread.join();
}