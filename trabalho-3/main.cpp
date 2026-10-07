#include <windows.h>
#include <gl/gl.h>
#include <cmath>

// =========================
// VARIÁVEIS DO JOGO
// =========================

// Posição da bola
float bolaX = 0.0f;
float bolaY = 0.0f;

// Velocidade da bola
float velocidadeX = 0.015f;
float velocidadeY = 0.010f;

// Posição da raquete do jogador
float raqueteY = 0.0f;

// Posição da raquete adversária
float raqueteCPUY = 0.0f;

// Pontuação
int pontosJogador = 0;
int pontosCPU = 0;

// Controle das teclas
bool teclaCima = false;
bool teclaBaixo = false;

// Tamanho da janela
int largura = 800;
int altura = 600;


// =========================
// DESENHA UM RETÂNGULO
// =========================

void desenharRetangulo(float x, float y, float largura,
                       float altura)
{
    glBegin(GL_QUADS);

        glVertex2f(x, y);
        glVertex2f(x + largura, y);
        glVertex2f(x + largura, y + altura);
        glVertex2f(x, y + altura);

    glEnd();
}


// =========================
// DESENHA A BOLA
// =========================

void desenharBola(float x, float y, float raio)
{
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);

    for (int i = 0; i <= 360; i++)
    {
        float angulo = i * 3.14159f / 180.0f;

        float px = x + cos(angulo) * raio;
        float py = y + sin(angulo) * raio;

        glVertex2f(px, py);
    }

    glEnd();
}


// =========================
// REINICIA A BOLA
// =========================

void reiniciarBola()
{
    bolaX = 0.0f;
    bolaY = 0.0f;

    velocidadeX = -velocidadeX;

    if (velocidadeX == 0)
        velocidadeX = 0.015f;
}


// =========================
// ATUALIZA O JOGO
// =========================

void atualizarJogo()
{
    // Movimento automático da bola
    bolaX += velocidadeX;
    bolaY += velocidadeY;


    // Colisão com o teto
    if (bolaY >= 0.95f)
    {
        bolaY = 0.95f;
        velocidadeY = -velocidadeY;
    }


    // Colisão com o chão
    if (bolaY <= -0.95f)
    {
        bolaY = -0.95f;
        velocidadeY = -velocidadeY;
    }


    // =========================
    // RAQUETE DO JOGADOR
    // =========================

    if (teclaCima)
        raqueteY += 0.025f;

    if (teclaBaixo)
        raqueteY -= 0.025f;


    // Impede a raquete de sair da tela
    if (raqueteY > 0.75f)
        raqueteY = 0.75f;

    if (raqueteY < -0.75f)
        raqueteY = -0.75f;


    // =========================
    // RAQUETE CPU
    // =========================

    // A CPU acompanha a bola
    if (bolaY > raqueteCPUY)
        raqueteCPUY += 0.012f;

    if (bolaY < raqueteCPUY)
        raqueteCPUY -= 0.012f;


    if (raqueteCPUY > 0.75f)
        raqueteCPUY = 0.75f;

    if (raqueteCPUY < -0.75f)
        raqueteCPUY = -0.75f;


    // =========================
    // COLISÃO COM A RAQUETE
    // =========================

    // Raquete do jogador
    if (bolaX <= -0.85f &&
        bolaX >= -0.90f &&
        bolaY >= raqueteY - 0.20f &&
        bolaY <= raqueteY + 0.20f)
    {
        bolaX = -0.85f;
        velocidadeX = -velocidadeX;
    }


    // Raquete da CPU
    if (bolaX >= 0.85f &&
        bolaX <= 0.90f &&
        bolaY >= raqueteCPUY - 0.20f &&
        bolaY <= raqueteCPUY + 0.20f)
    {
        bolaX = 0.85f;
        velocidadeX = -velocidadeX;
    }


    // =========================
    // PONTO DO JOGADOR
    // =========================

    if (bolaX > 1.05f)
    {
        pontosJogador++;

        reiniciarBola();
    }


    // =========================
    // PONTO DA CPU
    // =========================

    if (bolaX < -1.05f)
    {
        pontosCPU++;

        reiniciarBola();
    }
}


// =========================
// DESENHA O JOGO
// =========================

void desenharJogo()
{
    // Fundo preto
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);


    // =========================
    // RAQUETE DO JOGADOR
    // =========================

    glColor3f(1.0f, 1.0f, 1.0f);

    desenharRetangulo(
        -0.90f,
        raqueteY - 0.20f,
        0.05f,
        0.40f
    );


    // =========================
    // RAQUETE DA CPU
    // =========================

    glColor3f(1.0f, 1.0f, 1.0f);

    desenharRetangulo(
        0.85f,
        raqueteCPUY - 0.20f,
        0.05f,
        0.40f
    );


    // =========================
    // BOLA
    // =========================

    glColor3f(1.0f, 1.0f, 1.0f);

    desenharBola(bolaX, bolaY, 0.035f);


    // =========================
    // LINHA CENTRAL
    // =========================

    glBegin(GL_LINES);

        for (float y = -1.0f; y < 1.0f; y += 0.12f)
        {
            glVertex2f(0.0f, y);
            glVertex2f(0.0f, y + 0.06f);
        }

    glEnd();


    SwapBuffers(wglGetCurrentDC());
}


// =========================
// CONFIGURA OPENGL
// =========================

void configurarOpenGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(
        -1.0, 1.0,
        -1.0, 1.0,
        -1.0, 1.0
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// =========================
// WNDPROC
// =========================

LRESULT CALLBACK WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_KEYDOWN:

            if (wParam == VK_UP)
                teclaCima = true;

            if (wParam == VK_DOWN)
                teclaBaixo = true;

            break;


        case WM_KEYUP:

            if (wParam == VK_UP)
                teclaCima = false;

            if (wParam == VK_DOWN)
                teclaBaixo = false;

            break;


        case WM_TIMER:

            // Atualiza o jogo
            atualizarJogo();

            // Desenha novamente
            desenharJogo();

            break;


        case WM_DESTROY:

            KillTimer(hwnd, 1);

            PostQuitMessage(0);

            break;


        default:

            return DefWindowProc(
                hwnd,
                uMsg,
                wParam,
                lParam
            );
    }

    return 0;
}


// =========================
// WINMAIN
// =========================

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    WNDCLASS wc = {};

    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "PongOpenGL";

    RegisterClass(&wc);


    HWND hwnd = CreateWindow(
        "PongOpenGL",
        "Pong - OpenGL",
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        largura,
        altura,
        NULL,
        NULL,
        hInstance,
        NULL
    );


    HDC hdc = GetDC(hwnd);


    // =========================
    // CONFIGURA PIXEL FORMAT
    // =========================

    PIXELFORMATDESCRIPTOR pfd = {};

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;

    pfd.dwFlags =
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER;

    pfd.iPixelType = PFD_TYPE_RGBA;

    pfd.cColorBits = 32;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;


    int pixelFormat =
        ChoosePixelFormat(hdc, &pfd);

    SetPixelFormat(
        hdc,
        pixelFormat,
        &pfd
    );


    // =========================
    // CRIA CONTEXTO OPENGL
    // =========================

    HGLRC hrc =
        wglCreateContext(hdc);

    wglMakeCurrent(hdc, hrc);


    configurarOpenGL();


    // Mostra a janela
    ShowWindow(hwnd, nCmdShow);


    // =========================
    // TIMER
    // =========================

    // 16 ms ˜ 60 atualizações por segundo
    SetTimer(
        hwnd,
        1,
        16,
        NULL
    );


    // =========================
    // LOOP PRINCIPAL
    // =========================

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);

        DispatchMessage(&msg);
    }


    // =========================
    // FINALIZA OPENGL
    // =========================

    wglMakeCurrent(NULL, NULL);

    wglDeleteContext(hrc);

    ReleaseDC(hwnd, hdc);

    return 0;
}
