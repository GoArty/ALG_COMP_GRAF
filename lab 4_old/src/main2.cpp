#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Отрисовываем исходное изображение

    // Применяем фильтр с равномерным усреднением области 3х3
    int kernel[3][3] = {
        {0, 1, 0},
        {1, 2, 1},
        {0, 1, 0}
    };

    int divisor = 9;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_POINTS);
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 640; x++) {
            int r = 0, g = 0, b = 0;
            for (int ky = 0; ky < 3; ky++) {
                for (int kx = 0; kx < 3; kx++) {
                    unsigned char pixel[3];
                    glReadPixels(x + kx - 1, y + ky - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
                    r += pixel[0] * kernel[ky][kx];
                    g += pixel[1] * kernel[ky][kx];
                    b += pixel[2] * kernel[ky][kx];
                }
            }
            r /= divisor;
            g /= divisor;
            b /= divisor;
            glColor3ub(r, g, b);
            glVertex2f(x / 640.0, y / 480.0);
        }
    }
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Post-Filtering with 3x3 Uniform Averaging");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}