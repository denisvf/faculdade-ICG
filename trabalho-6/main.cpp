
#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

// =====================================================
// VARIAVEIS GLOBAIS
// =====================================================

// Camera
float cameraX = 0.0f;
float cameraY = 4.0f;
float cameraZ = 14.0f;

float cameraYaw = 0.0f;
float cameraPitch = -0.12f;

// Transformacoes da casa
float casaX = 0.0f;
float casaY = 0.0f;
float casaZ = 0.0f;

float rotacaoCasa = 0.0f;
float escalaCasa = 1.0f;

// Controle das tres luzes
bool luz1Ligada = true;
bool luz2Ligada = true;
bool luz3Ligada = true;

// Velocidades
float velocidadeCamera = 0.5f;
float velocidadeRotacao = 5.0f;
float velocidadeEscala = 0.1f;

// =====================================================
// DESENHAR UM CUBO
// =====================================================

void cubo(float x, float y, float z,
          float sx, float sy, float sz,
          float r, float g, float b)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glColor3f(r, g, b);
    glutSolidCube(1.0);

    glPopMatrix();
}

// =====================================================
// DESENHAR O TERRENO
// =====================================================

void desenharTerreno()
{
    glColor3f(0.25f, 0.55f, 0.20f);

    glBegin(GL_QUADS);

    glNormal3f(0, 1, 0);

    glVertex3f(-40, 0, -40);
    glVertex3f(-40, 0, 40);
    glVertex3f(40, 0, 40);
    glVertex3f(40, 0, -40);

    glEnd();

    // Caminho de entrada
    cubo(0, 0.025f, 6.0f, 2.0f, 0.05f, 8.0f,
         0.55f, 0.48f, 0.36f);
}

// =====================================================
// DESENHAR O TELHADO
// =====================================================

void desenharTelhado()
{
    glColor3f(0.55f, 0.10f, 0.08f);

    glBegin(GL_QUADS);

    // Lado esquerdo
    glNormal3f(-0.5f, 0.8f, 0);

    glVertex3f(-3.2f, 3.0f, -2.8f);
    glVertex3f(0, 4.8f, -2.8f);
    glVertex3f(0, 4.8f, 2.8f);
    glVertex3f(-3.2f, 3.0f, 2.8f);

    // Lado direito
    glNormal3f(0.5f, 0.8f, 0);

    glVertex3f(0, 4.8f, -2.8f);
    glVertex3f(3.2f, 3.0f, -2.8f);
    glVertex3f(3.2f, 3.0f, 2.8f);
    glVertex3f(0, 4.8f, 2.8f);

    glEnd();

    // Frente triangular
    glBegin(GL_TRIANGLES);

    glNormal3f(0, 0, 1);

    glVertex3f(-3.0f, 3.0f, 2.51f);
    glVertex3f(3.0f, 3.0f, 2.51f);
    glVertex3f(0, 4.8f, 2.51f);

    // Parte traseira
    glNormal3f(0, 0, -1);

    glVertex3f(-3.0f, 3.0f, -2.51f);
    glVertex3f(0, 4.8f, -2.51f);
    glVertex3f(3.0f, 3.0f, -2.51f);

    glEnd();
}

// =====================================================
// DESENHAR UMA JANELA
// =====================================================

void desenharJanela(float x, float z)
{
    // Moldura
    cubo(x, 1.9f, z, 1.3f, 1.2f, 0.15f,
         0.25f, 0.12f, 0.05f);

    // Vidro
    cubo(x, 1.9f, z + 0.09f, 1.05f, 0.95f, 0.04f,
         0.25f, 0.70f, 0.90f);

    // Divisorias
    cubo(x, 1.9f, z + 0.13f, 0.06f, 0.95f, 0.04f,
         0.9f, 0.9f, 0.9f);

    cubo(x, 1.9f, z + 0.13f, 1.05f, 0.06f, 0.04f,
         0.9f, 0.9f, 0.9f);
}

// =====================================================
// DESENHAR A CASA
// =====================================================

void desenharCasa()
{
    glPushMatrix();

    // Transformacoes geometricas da casa
    glTranslatef(casaX, casaY, casaZ);
    glRotatef(rotacaoCasa, 0, 1, 0);
    glScalef(escalaCasa, escalaCasa, escalaCasa);

    // Paredes
    cubo(0, 1.5f, 0, 6.0f, 3.0f, 5.0f,
         0.88f, 0.72f, 0.50f);

    // Telhado
    desenharTelhado();

    // Porta
    cubo(0, 1.1f, 2.56f, 1.2f, 2.2f, 0.15f,
         0.30f, 0.12f, 0.04f);

    // Macaneta
    cubo(0.4f, 1.1f, 2.66f, 0.10f, 0.10f, 0.10f,
         0.95f, 0.75f, 0.10f);

    // Janelas
    desenharJanela(-2.0f, 2.56f);
    desenharJanela(2.0f, 2.56f);

    // Chamine
    cubo(1.8f, 4.0f, -1.0f, 0.7f, 2.0f, 0.7f,
         0.45f, 0.18f, 0.12f);

    glPopMatrix();
}

// =====================================================
// DESENHAR UMA ARVORE
// =====================================================

void desenharArvore(float x, float z)
{
    glPushMatrix();

    glTranslatef(x, 0, z);

    // Tronco
    cubo(0, 1.2f, 0, 0.7f, 2.4f, 0.7f,
         0.35f, 0.16f, 0.05f);

    // Copa
    glColor3f(0.05f, 0.40f, 0.10f);

    glPushMatrix();
    glTranslatef(0, 3.0f, 0);
    glutSolidSphere(1.5, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

// =====================================================
// ILUMINACAO
// =====================================================

void configurarLuzes()
{
    // Luz ambiente global
    GLfloat ambiente[] = {0.18f, 0.18f, 0.18f, 1.0f};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente);

    // -----------------------------
    // LUZ 1: DIRECIONAL
    // -----------------------------

    GLfloat luzDirecional[] = {
        0.9f, 0.85f, 0.7f, 1.0f
    };

    GLfloat direcao[] = {
        -1.0f, -1.0f, -0.5f, 0.0f
    };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDirecional);
    glLightfv(GL_LIGHT0, GL_POSITION, direcao);

    // -----------------------------
    // LUZ 2: PONTUAL
    // -----------------------------

    GLfloat luzPontual[] = {
        0.2f, 0.4f, 1.0f, 1.0f
    };

    GLfloat posicaoPontual[] = {
        -5.0f, 5.0f, 4.0f, 1.0f
    };

    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzPontual);
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoPontual);

    GLfloat atenuacao[] = {1.0f, 0.03f, 0.01f};

    glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, &atenuacao[0]);
    glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, &atenuacao[1]);
    glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, &atenuacao[2]);

    // -----------------------------
    // LUZ 3: SPOT (HOLOFOTE)
    // -----------------------------

    GLfloat luzSpot[] = {
        1.0f, 0.8f, 0.5f, 1.0f
    };

    GLfloat posicaoSpot[] = {
        0.0f, 7.0f, 8.0f, 1.0f
    };

    GLfloat direcaoSpot[] = {
        0.0f, -0.5f, -1.0f
    };

    glLightfv(GL_LIGHT2, GL_DIFFUSE, luzSpot);
    glLightfv(GL_LIGHT2, GL_POSITION, posicaoSpot);

    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direcaoSpot);

    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 35.0f);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 20.0f);

    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.02f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.005f);

    // Ativar ou desativar cada luz
    if (luz1Ligada)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);

    if (luz2Ligada)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);

    if (luz3Ligada)
        glEnable(GL_LIGHT2);
    else
        glDisable(GL_LIGHT2);
}

// =====================================================
// DESENHAR A CENA
// =====================================================

void desenharCena()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Direcao da camera
    float dirX = sin(cameraYaw) * cos(cameraPitch);
    float dirY = sin(cameraPitch);
    float dirZ = -cos(cameraYaw) * cos(cameraPitch);

    gluLookAt(
        cameraX, cameraY, cameraZ,
        cameraX + dirX,
        cameraY + dirY,
        cameraZ + dirZ,
        0, 1, 0
    );

    // Configurar as fontes de luz
    configurarLuzes();

    // Terreno
    desenharTerreno();

    // Casa
    desenharCasa();

    // Arvores
    desenharArvore(-7, 0);
    desenharArvore(7, 0);
    desenharArvore(-7, -7);
    desenharArvore(7, -7);

    glutSwapBuffers();
}

// =====================================================
// REDIMENSIONAR A JANELA
// =====================================================

void redimensionar(int largura, int altura)
{
    if (altura == 0)
        altura = 1;

    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        60.0,
        (double)largura / (double)altura,
        0.1,
        100.0
    );

    glMatrixMode(GL_MODELVIEW);
}

// =====================================================
// TECLADO - TRANSFORMACOES E CAMERA
// =====================================================

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
        // MOVIMENTACAO DA CAMERA

        case 'w':
        case 'W':
            cameraX += sin(cameraYaw) * velocidadeCamera;
            cameraZ -= cos(cameraYaw) * velocidadeCamera;
            break;

        case 's':
        case 'S':
            cameraX -= sin(cameraYaw) * velocidadeCamera;
            cameraZ += cos(cameraYaw) * velocidadeCamera;
            break;

        case 'a':
        case 'A':
            cameraX -= cos(cameraYaw) * velocidadeCamera;
            cameraZ -= sin(cameraYaw) * velocidadeCamera;
            break;

        case 'd':
        case 'D':
            cameraX += cos(cameraYaw) * velocidadeCamera;
            cameraZ += sin(cameraYaw) * velocidadeCamera;
            break;

        case 'q':
        case 'Q':
            cameraY += velocidadeCamera;
            break;

        case 'e':
        case 'E':
            cameraY -= velocidadeCamera;
            break;

        // TRANSFORMACAO: TRANS LACAO

        case 't':
        case 'T':
            casaX -= 0.3f;
            break;

        case 'g':
        case 'G':
            casaX += 0.3f;
            break;

        case 'y':
        case 'Y':
            casaZ -= 0.3f;
            break;

        case 'h':
        case 'H':
            casaZ += 0.3f;
            break;

        // TRANSFORMACAO: ROTACAO

        case 'r':
        case 'R':
            rotacaoCasa += velocidadeRotacao;
            break;

        case 'f':
        case 'F':
            rotacaoCasa -= velocidadeRotacao;
            break;

        // TRANSFORMACAO: ESCALA

        case '+':
        case '=':
            escalaCasa += velocidadeEscala;
            break;

        case '-':
        case '_':
            escalaCasa -= velocidadeEscala;

            if (escalaCasa < 0.2f)
                escalaCasa = 0.2f;

            break;

        // CONTROLE DAS LUZES

        case '1':
            luz1Ligada = !luz1Ligada;
            break;

        case '2':
            luz2Ligada = !luz2Ligada;
            break;

        case '3':
            luz3Ligada = !luz3Ligada;
            break;

        // RESETAR A CENA

        case '0':
            cameraX = 0;
            cameraY = 4;
            cameraZ = 14;

            cameraYaw = 0;
            cameraPitch = -0.12f;

            casaX = 0;
            casaY = 0;
            casaZ = 0;

            rotacaoCasa = 0;
            escalaCasa = 1;
            break;

        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();
}

// =====================================================
// TECLAS ESPECIAIS - ROTACAO DA CAMERA
// =====================================================

void tecladoEspecial(int tecla, int x, int y)
{
    switch (tecla)
    {
        case GLUT_KEY_LEFT:
            cameraYaw -= 0.08f;
            break;

        case GLUT_KEY_RIGHT:
            cameraYaw += 0.08f;
            break;

        case GLUT_KEY_UP:
            cameraPitch += 0.05f;

            if (cameraPitch > 1.4f)
                cameraPitch = 1.4f;

            break;

        case GLUT_KEY_DOWN:
            cameraPitch -= 0.05f;

            if (cameraPitch < -1.4f)
                cameraPitch = -1.4f;

            break;
    }

    glutPostRedisplay();
}

// =====================================================
// INICIALIZACAO DO OPENGL
// =====================================================

void inicializar()
{
    glClearColor(0.45f, 0.70f, 0.95f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    // Permitir que as cores dos objetos sejam usadas
    // como cores dos materiais
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Melhorar a iluminacao
    glEnable(GL_NORMALIZE);

    glShadeModel(GL_SMOOTH);
}

// =====================================================
// FUNCAO PRINCIPAL
// =====================================================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(1000, 700);

    glutInitWindowPosition(100, 50);

    glutCreateWindow("Casa 3D - Trabalho de Computacao Grafica");

    inicializar();

    glutDisplayFunc(desenharCena);

    glutReshapeFunc(redimensionar);

    glutKeyboardFunc(teclado);

    glutSpecialFunc(tecladoEspecial);

    glutMainLoop();

    return 0;
}
