#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void init(void) {
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
}

void display(void) {
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glLoadIdentity();
   gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glutWireCube(1.0);
   glFlush();
}

void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho(-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include <cublas_v2.h>
#include <curand.h>
#include <stdio.h>

#define DIM 512

GLuint tex;
cudaGraphicsResource *cuda_tex;

__global__ void kernel(unsigned char *ptr) {
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    int y = threadIdx.y + blockIdx.y * blockDim.y;
    int offset = x + y * blockDim.x * gridDim.x;
    float fx = x/(float)DIM - 0.5f;
    float fy = y/(float)DIM - 0.5f;
    unsigned char green = 128 + 127 * sin(abs(fx*100) - abs(fy*100));
    ptr[offset*4 + 0] = 0;
    ptr[offset*4 + 1] = green;
    ptr[offset*4 + 2] = 0;
    ptr[offset*4 + 3] = 255;
}

void init(void) {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DIM, DIM, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    cudaGraphicsGLRegisterImage(&cuda_tex, tex, GL_TEXTURE_2D, cudaGraphicsRegisterFlagsWriteDiscard);
}

void display(void) {
    cudaGraphicsMapResources(1, &cuda_tex, 0);
    unsigned char *dev_ptr;
    size_t size;
    cudaGraphicsResourceGetMappedPointer((void **)&dev_ptr, &size, cuda_tex);
    dim3 grid(DIM/16,DIM/16);
    dim3 block(16,16);
    kernel<<<grid,block>>>(dev_ptr);
    cudaGraphicsUnmapResources(1, &cuda_tex, 0);

    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f,  1.0f);
 
