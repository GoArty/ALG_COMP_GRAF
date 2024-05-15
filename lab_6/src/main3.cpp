//#include <windows.h>		// Заголовочный файл для Windows
#include <gl\gl.h>		// Заголовочный файл для OpenGL32 библиотеки
#include <gl\glu.h>		// Заголовочный файл для GLu32 библиотеки
#include <gl\glaux.h>		// Заголовочный файл для GLaux библиотеки

static HGLRC hRC;		// Постоянный контекст рендеринга
static HDC hDC;			// Приватный контекст устройства GDI

BOOL	keys[256];		// Массив для процедуры обработки клавиатуры

GLfloat	xrot;			// Вращение X
GLfloat	yrot;			// Y
GLfloat	zrot;			// Z

GLuint	texture[1];		// Место для одной текстуры
/ Загрузка картинки и конвертирование в текстуру
GLvoid LoadGLTextures()
{
	// Загрузка картинки
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad("texture.bmp");
	// Создание текстуры
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
	GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}
GLvoid InitGL(GLsizei Width, GLsizei Height)
{
LoadGLTextures();			// Загрузка текстур
glEnable(GL_TEXTURE_2D);		// Разрешение наложение текстуры
glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
glClearDepth(1.0);
glDepthFunc(GL_LESS);
glEnable(GL_DEPTH_TEST);
glShadeModel(GL_SMOOTH);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

glMatrixMode(GL_MODELVIEW);
}
GLvoid DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-5.0f);
	glRotatef(xrot,1.0f,0.0f,0.0f);		// Вращение по оси X
	glRotatef(yrot,0.0f,1.0f,0.0f);		// Вращение по оси Y
	glRotatef(zrot,0.0f,0.0f,1.0f);		// Вращение по оси Z
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);

				// Передняя грань
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ лево
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ право
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Верх право
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Верх лево

				// Задняя грань
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Низ право
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх право
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх лево
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Низ лево

				// Верхняя грань
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх лево
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Низ лево
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Низ право
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх право
	
				// Нижняя грань
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Верх право
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Верх лево
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ лево
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ право

				// Правая грань
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Низ право
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх право
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Верх лево
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ лево

				// Левая грань
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Низ лево
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ право
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Верх право
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх лево

glEnd();
xrot+=0.3f;			// Ось вращения X
	yrot+=0.2f;			// Ось вращения Y
	zrot+=0.4f;			// Ось вращения Z
}
	
	
