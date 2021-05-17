#include<iostream>
#include<GL/glut.h>
#include<vector>
#include<math.h>
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
    }
};
std::vector<person> allPeople;
void createEnemy (int n){
    for (int i=0; i<n; i++){
        person e(5,5,1);
        allPeople.push_back(e);
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
        allPeople[0].pos[1] ++;
        break;
    case 97 :
        allPeople[0].pos[0] --;
        break;
    case 115 :
        allPeople[0].pos[1] --;
        break;
    case 100 :
        allPeople[0].pos[0] ++;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
  
void myDisplay(void)
{
    int k;
    for (k = 0; k <= 400; k += 5)
    {    
        glClear(GL_COLOR_BUFFER_BIT);
        for(int i=0; i<allPeople.size(); i++)
        {
            person c = allPeople.at(i);
            glBegin(GL_LINE_LOOP);
                glVertex2i(c.pos[0],c.pos[1]);
                glVertex2i(c.pos[0] , c.pos[1] + 10);
                glVertex2i(c.pos[0] + 10, c.pos[1]+10);
                glVertex2i(c.pos[0] + 10, c.pos[1]);
            glEnd();
  
        }
        glutSwapBuffers();
    }
}
  
  
// Driver Program
int main (int argc, char** argv)
{
    createEnemy(1);
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
    glutDisplayFunc(myDisplay);
    glutMainLoop();
}