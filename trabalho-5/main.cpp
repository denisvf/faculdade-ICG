
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

// =====================================================
// CIDADE 3D - DEV-C++ / OPENGL / GLUT
// Uma casa, sol 3D, carro e escultura de teapot
// =====================================================

const float PI = 3.14159265f;

// ---------------- CAMERA ----------------
float camX = 0.0f;
float camY = 4.0f;
float camZ = 12.0f;

float yaw = -90.0f;
float pitch = -10.0f;

// ---------------- CARRO ----------------
float carroX = 0.0f;
float carroZ = 1.5f;
float carroRot = 0.0f;
float carroEscala = 1.0f;

// ---------------- JANELA ----------------
int largura = 1000;
int altura = 700;

float rad(float graus) {
    return graus * PI / 180.0f;
}

void cor(float r, float g, float b) {
    glColor3f(r, g, b);
}

// =====================================================
// 1. CUBO
// =====================================================

void cubo(float x, float y, float z,
          float sx, float sy, float sz,
          float r, float g, float b) {
    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    cor(r, g, b);
    glutSolidCube(1.0);

    glPopMatrix();
}

// =====================================================
// 2. ESFERA
// =====================================================

void esfera(float x, float y, float z,
            float raio, float r, float g, float b) {
    glPushMatrix();

    glTranslatef(x, y, z);
    cor(r, g, b);

    glutSolidSphere(raio, 28, 20);

    glPopMatrix();
}

// =====================================================
// 3. CILINDRO - GLU
// O cilindro e criado ao longo do eixo Z
// =====================================================

void cilindro(float x, float y, float z,
              float raio, float altura,
              float r, float g, float b) {
    GLUquadric* q = gluNewQuadric();

    if (q == NULL) return;

    glPushMatrix();

    glTranslatef(x, y, z);
    cor(r, g, b);

    gluCylinder(q, raio, raio, altura, 24, 8);

    // Tampa inferior
    gluDisk(q, 0.0, raio, 24, 1);

    // Tampa superior
    glTranslatef(0.0f, 0.0f, altura);
    gluDisk(q, 0.0, raio, 24, 1);

    glPopMatrix();

    gluDeleteQuadric(q);
}

// =====================================================
// 4. CONE
// =====================================================

void cone(float x, float y, float z,
          float raio, float altura,
          float r, float g, float b) {
    GLUquadric* q = gluNewQuadric();

    if (q == NULL) return;

    glPushMatrix();

    glTranslatef(x, y, z);
    cor(r, g, b);

    gluCylinder(q, raio, 0.0, altura, 24, 8);
    gluDisk(q, 0.0, raio, 24, 1);

    glPopMatrix();

    gluDeleteQuadric(q);
}

// =====================================================
// TERRENO, RUA E CALCADAS
// =====================================================

void desenharTerreno() {
    // Terreno verde
    glBegin(GL_QUADS);
        cor(0.30f, 0.60f, 0.25f);

        glVertex3f(-15, 0, -10);
        glVertex3f( 15, 0, -10);
        glVertex3f( 15, 0,  10);
        glVertex3f(-15, 0,  10);
    glEnd();

    // Rua
    glBegin(GL_QUADS);
        cor(0.22f, 0.22f, 0.24f);

        glVertex3f(-15, 0.02f, -2);
        glVertex3f( 15, 0.02f, -2);
        glVertex3f( 15, 0.02f,  2);
        glVertex3f(-15, 0.02f,  2);
    glEnd();


    // Calcadas
    cubo(0, 0.10f, -2.65f,
         30, 0.20f, 1.3f,
         0.65f, 0.65f, 0.65f);

    cubo(0, 0.10f, 2.65f,
         30, 0.20f, 1.3f,
         0.65f, 0.65f, 0.65f);
}

// CASA
void desenharCasa() {
    float x = -6.0f;
    float z = -5.0f;

    // Paredes
    cubo(x, 1.2f, z,
         2.5f, 2.4f, 2.2f,
         0.90f, 0.70f, 0.40f);

    // Telhado conico
    glPushMatrix();
    glTranslatef(x, 2.4f, z);
    glRotatef(-90, 1, 0, 0);

    cone(0, 0, 0,
         1.8f, 1.4f,
         0.55f, 0.16f, 0.10f);

    glPopMatrix();

    // Porta
    cubo(x, 0.65f, z + 1.12f,
         0.55f, 1.3f, 0.10f,
         0.30f, 0.14f, 0.06f);

    // Janelas
    cubo(x - 0.75f, 1.55f, z + 1.13f,
         0.45f, 0.45f, 0.08f,
         0.35f, 0.80f, 0.95f);

    cubo(x + 0.75f, 1.55f, z + 1.13f,
         0.45f, 0.45f, 0.08f,
         0.35f, 0.80f, 0.95f);
}

// ARVORES
void desenharArvore(float x, float z) {
    // Tronco cilindrico, vertical
    glPushMatrix();

    glTranslatef(x, 0.15f, z);
    glRotatef(-90, 1, 0, 0);

    cilindro(0, 0, 0,
             0.22f, 1.5f,
             0.40f, 0.20f, 0.08f);

    glPopMatrix();

    // Copa de esferas
    esfera(x, 2.0f, z, 0.85f,
           0.08f, 0.48f, 0.12f);

    esfera(x - 0.40f, 1.85f, z, 0.52f,
           0.10f, 0.60f, 0.12f);

    esfera(x + 0.40f, 1.85f, z, 0.52f,
           0.12f, 0.52f, 0.10f);
}

// POSTES
void desenharPoste(float x, float z) {
    glPushMatrix();

    glTranslatef(x, 0.15f, z);
    glRotatef(-90, 1, 0, 0);

    cilindro(0, 0, 0,
             0.09f, 3.0f,
             0.15f, 0.15f, 0.17f);

    glPopMatrix();

    esfera(x, 3.2f, z, 0.22f,
           1.0f, 0.95f, 0.50f);
}

// SOL 3D - ESFERA
void desenharSol() {
    glPushMatrix();

    glTranslatef(3.5f, 7.0f, -8.0f);

    // Amarelo forte
    glDisable(GL_LIGHTING);

    cor(1.0f, 0.78f, 0.05f);
    glutSolidSphere(1.1, 36, 28);

    glEnable(GL_LIGHTING);

    glPopMatrix();
}

// CARRO
// Objeto usado para translacao, rotacao e escala
void desenharCarro() {
    glPushMatrix();

    glTranslatef(carroX, 0.0f, carroZ);
    glRotatef(carroRot, 0, 1, 0);
    glScalef(carroEscala,
             carroEscala,
             carroEscala);

    // Carroceria
    cubo(0, 0.55f, 0,
         2.0f, 0.55f, 1.0f,
         0.85f, 0.05f, 0.04f);

    // Cabine
    cubo(0, 1.02f, -0.05f,
         1.1f, 0.48f, 0.82f,
         0.90f, 0.12f, 0.06f);

    // Para-brisa
    cubo(0, 1.04f, 0.37f,
         0.75f, 0.30f, 0.04f,
         0.25f, 0.70f, 0.90f);

    // Quatro rodas cilindricas
    for (int lado = -1; lado <= 1; lado += 2) {
        for (int eixo = -1; eixo <= 1; eixo += 2) {
            glPushMatrix();

            glTranslatef(eixo * 0.62f,
                         0.32f,
                         lado * 0.52f);

            cilindro(0, 0, 0,
                     0.25f, 0.12f,
                     0.08f, 0.08f, 0.08f);

            glPopMatrix();
        }
    }

    glPopMatrix();
}

// ESCULTURA DE TEAPOT EM CIMA DA BASE OCTOGONAL
// Formas
// 5. Teapot
// 6. Tetraedro
// 7. Octaedro
// 8. Dodecaedro
// 9. Icosaedro
// 10. Toro
void desenharEscultura() {
    float x = 5.0f;
    float z = -5.0f;

    float raio = 1.7f;
    float yBase = 0.12f;
    float yTopo = 0.75f;

    // BASE OCTOGONAL, face inferior
    glBegin(GL_POLYGON);
        cor(0.28f, 0.30f, 0.34f);

        for (int i = 0; i < 8; i++) {
            float a = 2.0f * PI * i / 8.0f;

            glVertex3f(x + raio * cos(a),
                       yBase,
                       z + raio * sin(a));
        }
    glEnd();

    // face superior
    glBegin(GL_POLYGON);
        cor(0.65f, 0.68f, 0.72f);

        for (int i = 0; i < 8; i++) {
            float a = 2.0f * PI * i / 8.0f;

            glVertex3f(x + raio * cos(a),
                       yTopo,
                       z + raio * sin(a));
        }
    glEnd();

    // faces laterais
    glBegin(GL_QUADS);
        cor(0.42f, 0.44f, 0.48f);

        for (int i = 0; i < 8; i++) {
            float a1 = 2.0f * PI * i / 8.0f;
            float a2 = 2.0f * PI * (i + 1) / 8.0f;

            glVertex3f(x + raio*cos(a1), yBase,
                       z + raio*sin(a1));

            glVertex3f(x + raio*cos(a2), yBase,
                       z + raio*sin(a2));

            glVertex3f(x + raio*cos(a2), yTopo,
                       z + raio*sin(a2));

            glVertex3f(x + raio*cos(a1), yTopo,
                       z + raio*sin(a1));
        }
    glEnd();

    // 5. TEAPOT
    glPushMatrix();

    glTranslatef(x, 1.25f, z);
    glScalef(0.85f, 0.85f, 0.85f);

    cor(0.05f, 0.65f, 0.75f);
    glutSolidTeapot(1.0);

    glPopMatrix();

    // 6. TETRAEDRO
    glPushMatrix();

    glTranslatef(x - 1.15f, 1.0f, z);
    glScalef(0.25f, 0.25f, 0.25f);

    cor(1.0f, 0.45f, 0.10f);
    glutSolidTetrahedron();

    glPopMatrix();

    // 7. OCTAEDRO
    glPushMatrix();

    glTranslatef(x + 1.15f, 1.0f, z);
    glScalef(0.30f, 0.30f, 0.30f);

    cor(0.20f, 0.80f, 0.30f);
    glutSolidOctahedron();

    glPopMatrix();

    // 8. DODECAEDRO
    glPushMatrix();

    glTranslatef(x, 1.0f, z - 1.15f);
    glScalef(0.28f, 0.28f, 0.28f);

    cor(0.90f, 0.20f, 0.50f);
    glutSolidDodecahedron();

    glPopMatrix();

    // 9. ICOSAEDRO
    glPushMatrix();

    glTranslatef(x, 1.0f, z + 1.15f);
    glScalef(0.30f, 0.30f, 0.30f);

    cor(0.20f, 0.40f, 1.0f);
    glutSolidIcosahedron();

    glPopMatrix();

    // 10. TORO decorativo
    glPushMatrix();

    glTranslatef(x, 0.82f, z + 0.65f);
    glRotatef(90, 1, 0, 0);

    cor(0.95f, 0.70f, 0.10f);
    glutSolidTorus(0.06, 0.22, 12, 20);

    glPopMatrix();
}

// CENA COMPLETA
void desenharCena() {
    desenharTerreno();

    desenharCasa();

    desenharArvore(-8.5f, -3.5f);
    desenharArvore(-3.5f, -3.5f);
    desenharArvore(1.0f, 4.0f);
    desenharArvore(8.0f, 3.5f);

    desenharPoste(-4.0f, 2.8f);
    desenharPoste(5.0f, 2.8f);

    desenharEscultura();

    desenharSol();

    desenharCarro();
}

// CAMERA
void configurarCamera() {
    float dx = cos(rad(yaw)) * cos(rad(pitch));
    float dy = sin(rad(pitch));
    float dz = sin(rad(yaw)) * cos(rad(pitch));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        camX, camY, camZ,
        camX + dx, camY + dy, camZ + dz,
        0.0, 1.0, 0.0
    );
}

// EXIBICAO
void display() {
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);

    configurarCamera();
    desenharCena();

    glutSwapBuffers();
}

// REDIMENSIONAMENTO DA JANELA
void reshape(int w, int h) {
    if (h == 0) h = 1;

    largura = w;
    altura = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        60.0,
        (float)w / (float)h,
        0.1, 100.0
    );

    glMatrixMode(GL_MODELVIEW);
}

// TECLADO: TRANSFORMACOES E CAMERA
void teclado(unsigned char key, int x, int y) {
    float velocidade = 0.45f;

    float frenteX = cos(rad(yaw));
    float frenteZ = sin(rad(yaw));

    float ladoX = -sin(rad(yaw));
    float ladoZ = cos(rad(yaw));

    switch (key) {
        // frente e tras
        case 'w':
        case 'W':
            camX += frenteX * velocidade;
            camZ += frenteZ * velocidade;
            break;

        case 's':
        case 'S':
            camX -= frenteX * velocidade;
            camZ -= frenteZ * velocidade;
            break;

        // lados
        case 'a':
        case 'A':
            camX -= ladoX * velocidade;
            camZ -= ladoZ * velocidade;
            break;

        case 'd':
        case 'D':
            camX += ladoX * velocidade;
            camZ += ladoZ * velocidade;
            break;

        // subir e descer
        case 'e':
        case 'E':
            camY += velocidade;
            break;

        case 'q':
        case 'Q':
            camY -= velocidade;

            if (camY < 0.5f)
                camY = 0.5f;
            break;

        // translacao em X
        case 't':
        case 'T':
            carroX += 0.3f;
            break;

        case 'g':
        case 'G':
            carroX -= 0.3f;
            break;

        // translacao em Z
        case 'f':
        case 'F':
            carroZ -= 0.3f;
            break;

        case 'h':
        case 'H':
            carroZ += 0.3f;
            break;

        // rotacao
        case 'r':
        case 'R':
            carroRot += 10.0f;
            break;

        // escala
        case '+':
        case '=':
            carroEscala += 0.1f;

            if (carroEscala > 3.0f)
                carroEscala = 3.0f;
            break;

        case '-':
        case '_':
            carroEscala -= 0.1f;

            if (carroEscala < 0.3f)
                carroEscala = 0.3f;
            break;

        // Reiniciar o carro
        case '0':
            carroX = 0.0f;
            carroZ = 1.5f;
            carroRot = 0.0f;
            carroEscala = 1.0f;
            break;

        // fecha a janela com ESC
        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();
}

// SETAS: GIRAR A CAMERA
void teclasEspeciais(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            yaw -= 5.0f;
            break;

        case GLUT_KEY_RIGHT:
            yaw += 5.0f;
            break;

        case GLUT_KEY_UP:
            pitch += 5.0f;

            if (pitch > 80.0f)
                pitch = 80.0f;
            break;

        case GLUT_KEY_DOWN:
            pitch -= 5.0f;

            if (pitch < -80.0f)
                pitch = -80.0f;
            break;
    }

    glutPostRedisplay();
}

// INICIALIZACAO
void inicializar() {
    glClearColor(0.53f, 0.78f, 0.95f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(
        GL_FRONT_AND_BACK,
        GL_AMBIENT_AND_DIFFUSE
    );

    GLfloat luzAmbiente[] = {
        0.5f, 0.5f, 0.5f, 1.0f
    };

    GLfloat luzDifusa[] = {
        0.9f, 0.9f, 0.9f, 1.0f
    };

    GLfloat posicaoLuz[] = {
        0.0f, 12.0f, 5.0f, 1.0f
    };

    glLightModelfv(
        GL_LIGHT_MODEL_AMBIENT,
        luzAmbiente
    );

    glLightfv(
        GL_LIGHT0,
        GL_DIFFUSE,
        luzDifusa
    );

    glLightfv(
        GL_LIGHT0,
        GL_POSITION,
        posicaoLuz
    );
}

// MAIN
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(largura, altura);
    glutInitWindowPosition(100, 50);

    glutCreateWindow(
        "Cidade 3D - Computacao Grafica"
    );

    inicializar();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclasEspeciais);

    glutMainLoop();

    return 0;
}
