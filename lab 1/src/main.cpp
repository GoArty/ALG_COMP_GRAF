//tsalkovichp@mail.ru
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

float degree_y = 0.0;
float degree_x = 0.0;
float move_y = 0.0;
float move_x = 0.0;

void key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        else if (key == GLFW_KEY_UP)
        {
            degree_y += 0.2;
        }
        else if (key == GLFW_KEY_DOWN)
        {
            degree_y -= 0.2;
        }
        else if (key == GLFW_KEY_LEFT)
        {
            degree_x += 0.2;
        }
        else if (key == GLFW_KEY_RIGHT)
        {
            degree_x -= 0.2;
        }
        else if (key == GLFW_KEY_D)
        {
            move_x += 0.2;
        }
        else if (key == GLFW_KEY_A)
        {
            move_x -= 0.2;
        }
        else if (key == GLFW_KEY_W)
        {
            move_y += 0.2;
        }
        else if (key == GLFW_KEY_S)
        {
            move_y -= 0.2;
        }
    }
}

void display(GLFWwindow *window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(degree_y * 50.f, 1.f, 0.f, 0.f);
    glRotatef(degree_x * 50.f, 0.f, 0.f, 1.f);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex2f(move_x+0.25, move_y+0);
    glColor3f(0, 1, 0);
    glVertex2f(move_x+0.25, move_y+0.5);
    glColor3f(0, 0, 1);
    glVertex2f(move_x+(-0.25), move_y+0.5);
    glColor3f(0, 1, 1);
    glVertex2f(move_x+(-0.25), move_y+0);

    glEnd();

    glPopMatrix();
}

int main(int argc, char const *argv[])
{
    if (!glfwInit())
        exit(1);

    glfwWindowHint (GLFW_RESIZABLE, 1);

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Lab 1", glfwGetPrimaryMonitor(), NULL);

    if (window == NULL)
    {
        glfwTerminate();
        exit(1);
    }    

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key);

    while (!glfwWindowShouldClose(window))
    {
        display(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}