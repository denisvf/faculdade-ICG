
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

// ==========================================
// VARIAVEIS DA JANELA
// ==========================================

HDC hDC;
HGLRC hRC;
HWND hWnd;
HINSTANCE hInstance;

// ==========================================
// DESENHAR UM CUBO
// ==========================================

void desenharCubo(float x, float y, float z,
                  float largura, float altura, float profundidade)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(largura, altura, profundidade);

    glBegin(GL_QUADS);

    // Frente
    glColor3f(0.65f, 0.40f, 0.20f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    // Tras
    glColor3f(0.45f, 0.28f, 0.14f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);

    // Esquerda
    glColor3f(0.55f, 0.33f, 0.16f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    // Direita
    glColor3f(0.50f, 0.30f, 0.15f);
    glVertex3f(0.5f, -0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f,  0.5f);

    // Topo
    glColor3f(0.35f, 0.65f, 0.25f);
    glVertex3f(-0.5f, 0.5f,  0.5f);
    glVertex3f( 0.5f, 0.5f,  0.5f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Base
    glColor3f(0.40f, 0.25f, 0.12f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);

    glEnd();

    glPopMatrix();
}

// ==========================================
// DESENHAR UM CILINDRO
// ==========================================

void desenharCilindro(float x, float y, float z,
                      float raio, float altura)
{
    int segmentos = 24;
    float angulo;
    int i;

    glPushMatrix();
    glTranslatef(x, y, z);

    // Laterais do cilindro
    glColor3f(0.48f, 0.27f, 0.12f);
    glBegin(GL_QUAD_STRIP);

    for (i = 0; i <= segmentos; i++)
    {
        angulo = 2.0f * 3.14159265f * i / segmentos;

        float px = raio * cosf(angulo);
        float pz = raio * sinf(angulo);

        glVertex3f(px, 0.0f, pz);
        glVertex3f(px, altura, pz);
    }

    glEnd();

    // Tampa superior
    glColor3f(0.55f, 0.32f, 0.15f);
    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(0.0f, altura, 0.0f);

    for (i = 0; i <= segmentos; i++)
    {
        angulo = 2.0f * 3.14159265f * i / segmentos;

        glVertex3f(
            raio * cosf(angulo),
            altura,
            raio * sinf(angulo)
        );
    }

    glEnd();

    glPopMatrix();
}

// ==========================================
// DESENHAR UM CONE
// ==========================================

void desenharCone(float x, float y, float z,
                  float raio, float altura,
                  float vermelho, float verde, float azul)
{
    int segmentos = 24;
    float angulo;
    int i;

    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3f(vermelho, verde, azul);

    // Laterais do cone
    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(0.0f, altura, 0.0f);

    for (i = 0; i <= segmentos; i++)
    {
        angulo = 2.0f * 3.14159265f * i / segmentos;

        glVertex3f(
            raio * cosf(angulo),
            0.0f,
            raio * sinf(angulo)
        );
    }

    glEnd();

    // Base do cone
    glColor3f(
        vermelho * 0.75f,
        verde * 0.75f,
        azul * 0.75f
    );

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);

    for (i = 0; i <= segmentos; i++)
    {
        angulo = 2.0f * 3.14159265f * i / segmentos;

        glVertex3f(
            raio * cosf(angulo),
            0.0f,
            raio * sinf(angulo)
        );
    }

    glEnd();

    glPopMatrix();
}

// ==========================================
// DESENHAR UMA ESFERA
// ==========================================

void desenharEsfera(float x, float y, float z,
                    float sx, float sy, float sz,
                    float vermelho, float verde, float azul)
{
    GLUquadric* esfera = gluNewQuadric();

    if (esfera == NULL)
        return;

    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glColor3f(vermelho, verde, azul);

    gluSphere(esfera, 1.0, 24, 16);

    glPopMatrix();

    gluDeleteQuadric(esfera);
}

// ==========================================
// DESENHAR UM DISCO CIRCULAR
// ==========================================

void desenharDisco(float y, float raio,
                   float vermelho, float verde, float azul)
{
    int segmentos = 64;
    int i;
    float angulo;

    glColor3f(vermelho, verde, azul);
    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(0.0f, y, 0.0f);

    for (i = 0; i <= segmentos; i++)
    {
        angulo = 2.0f * 3.14159265f * i / segmentos;

        glVertex3f(
            raio * cosf(angulo),
            y,
            raio * sinf(angulo)
        );
    }

    glEnd();
}

// ==========================================
// DESENHAR UMA ARVORE
// ==========================================

void desenharArvore(float x, float z, float tamanho)
{
    float base = -0.48f;

    // Tronco
    desenharCilindro(
        x, base, z,
        0.16f * tamanho,
        1.3f * tamanho
    );

    // Copa inferior
    desenharCone(
        x, base + 0.8f * tamanho, z,
        0.85f * tamanho,
        1.25f * tamanho,
        0.08f, 0.42f, 0.12f
    );

    // Copa superior
    desenharCone(
        x, base + 1.5f * tamanho, z,
        0.62f * tamanho,
        1.15f * tamanho,
        0.12f, 0.58f, 0.16f
    );
}

// ==========================================
// DESENHAR O CENARIO COMPLETO
// ==========================================

void desenharCena()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Posicao da camera
    gluLookAt(
        14.0, 10.0, 18.0,
        0.0,  0.0,  0.0,
        0.0,  1.0,  0.0
    );

    // Sol
    desenharEsfera(
        -6.0f, 6.0f, -7.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.85f, 0.10f
    );

    // Montanhas ao fundo
    desenharCone(
        -5.0f, -0.5f, -4.0f,
        3.0f, 5.0f,
        0.38f, 0.42f, 0.32f
    );

    desenharCone(
        -1.0f, -0.5f, -5.0f,
        3.5f, 6.0f,
        0.48f, 0.50f, 0.42f
    );

    desenharCone(
        4.0f, -0.5f, -5.0f,
        3.0f, 4.5f,
        0.35f, 0.43f, 0.32f
    );

    // Parte inferior da ilha: areia
    desenharCilindro(
        0.0f, -1.0f, 0.0f,
        8.0f, 0.5f
    );

    // Superficie verde da ilha
    desenharDisco(
        -0.49f, 7.98f,
        0.20f, 0.62f, 0.18f
    );

    // Lago azul
    desenharEsfera(
        1.0f, -0.39f, 1.0f,
        2.5f, 0.09f, 1.65f,
        0.05f, 0.55f, 0.90f
    );

    // Arvores na ilha
    desenharArvore(-4.0f, -2.0f, 1.2f);
    desenharArvore(-5.0f,  1.0f, 0.9f);
    desenharArvore( 4.5f, -2.5f, 1.1f);
    desenharArvore( 5.0f,  2.5f, 0.9f);
    desenharArvore(-2.5f,  4.0f, 0.8f);

    // Pedras decorativas
    desenharEsfera(
        -2.0f, -0.35f, 2.0f,
        0.45f, 0.30f, 0.40f,
        0.45f, 0.45f, 0.42f
    );

    desenharEsfera(
        4.0f, -0.35f, 1.0f,
        0.35f, 0.25f, 0.30f,
        0.55f, 0.52f, 0.45f
    );

    // Pequena ponte de madeira sobre uma margem do lago
    desenharCubo(
        1.0f, -0.28f, 2.8f,
        2.0f, 0.12f, 0.55f
    );

    glFlush();
}

// ==========================================
// AJUSTAR A PROJECAO AO REDIMENSIONAR
// ==========================================

void redimensionar(int largura, int altura)
{
    if (altura == 0)
        altura = 1;

    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float proporcao = (float)largura / (float)altura;

    gluPerspective(
        45.0,
        proporcao,
        0.1,
        100.0
    );

    glMatrixMode(GL_MODELVIEW);
}

// ==========================================
// INICIALIZAR OPENGL
// ==========================================

void inicializarOpenGL()
{
    glEnable(GL_DEPTH_TEST);

    // Cor do ceu
    glClearColor(
        0.45f, 0.75f, 0.95f, 1.0f
    );

    glShadeModel(GL_SMOOTH);
}

// ==========================================
// CRIAR CONTEXTO OPENGL
// ==========================================

void EnableOpenGL(HWND hwnd, HDC* hdc, HGLRC* hrc)
{
    PIXELFORMATDESCRIPTOR pfd;
    int formato;

    *hdc = GetDC(hwnd);

    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags =
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER;

    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;

    formato = ChoosePixelFormat(*hdc, &pfd);
    SetPixelFormat(*hdc, formato, &pfd);

    *hrc = wglCreateContext(*hdc);
    wglMakeCurrent(*hdc, *hrc);
}

// ==========================================
// ENCERRAR OPENGL
// ==========================================

void DisableOpenGL(HWND hwnd, HDC hdc, HGLRC hrc)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);
    ReleaseDC(hwnd, hdc);
}

// ==========================================
// PROCEDIMENTO DA JANELA
// ==========================================

LRESULT CALLBACK WndProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg)
    {
        case WM_SIZE:
            redimensionar(
                LOWORD(lParam),
                HIWORD(lParam)
            );
            return 0;

        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;

        case WM_DESTROY:
            return 0;

        default:
            return DefWindowProc(
                hwnd, msg, wParam, lParam
            );
    }
}

// ==========================================
// FUNCAO PRINCIPAL DO WINDOWS
// ==========================================

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE hPrevInst,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    WNDCLASS wc;
    MSG msg;
    BOOL sair = FALSE;

    hInstance = hInst;

    ZeroMemory(&wc, sizeof(wc));

    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Ilha3DOpenGL";

    RegisterClass(&wc);

    hWnd = CreateWindow(
        "Ilha3DOpenGL",
        "Ilha Tropical - OpenGL 3D",
        WS_OVERLAPPEDWINDOW,
        100, 100, 1000, 700,
        NULL, NULL,
        hInstance, NULL
    );

    EnableOpenGL(hWnd, &hDC, &hRC);

    inicializarOpenGL();

    redimensionar(1000, 700);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Loop principal
    while (!sair)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                sair = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            desenharCena();

            // Apresentar a imagem na janela
            SwapBuffers(hDC);
        }
    }

    DisableOpenGL(hWnd, hDC, hRC);

    UnregisterClass(
        "Ilha3DOpenGL", hInstance
    );

    return 0;
}
