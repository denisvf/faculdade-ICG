#include <windows.h>
#include <gl/gl.h>
#include <math.h>

// TAMANHO
const int LARGURA = 900;
const int ALTURA = 600;

// VARIÁVEIS DO CARRO
float carroX = 650.0f;
float carroY = 110.0f;

bool arrastandoCarro = false;

float distanciaMouseX = 0.0f;
float distanciaMouseY = 0.0f;

// DECLARAÇÕES
LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
);

void EnableOpenGL(
    HWND hWnd,
    HDC *hDC,
    HGLRC *hRC
);

void DisableOpenGL(
    HWND hWnd,
    HDC hDC,
    HGLRC hRC
);

// RETÂNGULO
void retangulo(
    float x1,
    float y1,
    float x2,
    float y2
)
{
    glBegin(GL_QUADS);

    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);

    glEnd();
}

// TRIÂNGULO
void triangulo(
    float x1, float y1,
    float x2, float y2,
    float x3, float y3
)
{
    glBegin(GL_TRIANGLES);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);

    glEnd();
}

// CÍRCULO
void circulo(
    float centroX,
    float centroY,
    float raio
)
{
    const int pontos = 100;
    const float PI = 3.14159265f;

    glBegin(GL_POLYGON);

    for (int i = 0; i < pontos; i++)
    {
        float angulo =
            2.0f * PI * i / pontos;

        float x =
            centroX + raio * cos(angulo);

        float y =
            centroY + raio * sin(angulo);

        glVertex2f(x, y);
    }

    glEnd();
}

// SOL
void desenharSol()
{
    glColor3f(1.0f, 0.75f, 0.0f);

    circulo(760, 490, 55);
}

// ÁRVORE
void desenharArvore(float x, float y)
{
    // Tronco
    glColor3f(
        0.45f,
        0.25f,
        0.10f
    );

    retangulo(
        x - 12,
        y,
        x + 12,
        y + 100
    );

    // Copa
    glColor3f(
        0.05f,
        0.45f,
        0.10f
    );

    circulo(
        x,
        y + 125,
        45
    );

    glColor3f(
        0.08f,
        0.55f,
        0.15f
    );

    circulo(
        x - 30,
        y + 115,
        35
    );

    glColor3f(
        0.06f,
        0.50f,
        0.12f
    );

    circulo(
        x + 30,
        y + 115,
        35
    );
}

// CASA
void desenharCasa()
{
    // base
    glColor3f(
        0.80f,
        0.55f,
        0.30f
    );

    retangulo(
        180,
        160,
        420,
        320
    );

    // telhado
    glColor3f(
        0.55f,
        0.10f,
        0.08f
    );

    triangulo(
        150, 320,
        450, 320,
        300, 450
    );

    // porta
    glColor3f(
        0.30f,
        0.15f,
        0.07f
    );

    retangulo(
        270,
        160,
        330,
        250
    );

    // maçaneta
    glColor3f(
        1.0f,
        0.85f,
        0.0f
    );

    circulo(
        318,
        205,
        5
    );
}

// CARRO
void desenharCarro()
{
    // base
    glColor3f(
        0.10f,
        0.25f,
        0.80f
    );

    retangulo(
        carroX,
        carroY,
        carroX + 170,
        carroY + 60
    );

    // parte superior
    glColor3f(
        0.10f,
        0.25f,
        0.80f
    );

    triangulo(
        carroX + 30,
        carroY + 60,

        carroX + 60,
        carroY + 105,

        carroX + 110,
        carroY + 105
    );

    triangulo(
        carroX + 110,
        carroY + 105,

        carroX + 145,
        carroY + 60,

        carroX + 30,
        carroY + 60
    );

    // janelas
    glColor3f(
        0.50f,
        0.80f,
        0.95f
    );

    retangulo(
        carroX + 55,
        carroY + 65,
        carroX + 82,
        carroY + 95
    );

    retangulo(
        carroX + 87,
        carroY + 65,
        carroX + 115,
        carroY + 95
    );

    // rodas
    glColor3f(
        0.03f,
        0.03f,
        0.03f
    );

    circulo(
        carroX + 40,
        carroY,
        22
    );

    circulo(
        carroX + 130,
        carroY,
        22
    );

    // aro das rodas
    glColor3f(
        0.65f,
        0.65f,
        0.65f
    );

    circulo(
        carroX + 40,
        carroY,
        9
    );

    circulo(
        carroX + 130,
        carroY,
        9
    );

    // farol
    glColor3f(
        1.0f,
        1.0f,
        0.30f
    );

    circulo(
        carroX + 165,
        carroY + 35,
        7
    );
}

// CENA
void desenharCena()
{
    // CÉU
    glColor3f(
        0.40f,
        0.75f,
        1.0f
    );

    retangulo(
        0,
        300,
        900,
        600
    );

    // GRAMA
    glColor3f(
        0.20f,
        0.65f,
        0.20f
    );

    retangulo(
        0,
        0,
        900,
        300
    );

    // ESTRADA
    glColor3f(
        0.25f,
        0.25f,
        0.25f
    );

    retangulo(
        0,
        70,
        900,
        160
    );

    // SOL
    desenharSol();

    // CASA
    desenharCasa();

    // ÁRVORES
    desenharArvore(80, 160);
    desenharArvore(500, 170);
    desenharArvore(850, 160);

    // CARRO
    desenharCarro();
}

// VERIFICA SE O MOUSE ESTÁ NO CARRO
bool mouseDentroDoCarro(
    float x,
    float y
)
{
    return
        x >= carroX &&
        x <= carroX + 170 &&
        y >= carroY &&
        y <= carroY + 105;
}

// WINMAIN
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int iCmdShow
)
{
    WNDCLASS wc;

    HWND hWnd;

    HDC hDC;

    HGLRC hRC;

    MSG msg;

    BOOL bQuit = FALSE;

    // REGISTRA JANELA
    wc.style = CS_OWNDC;

    wc.lpfnWndProc = WndProc;

    wc.cbClsExtra = 0;

    wc.cbWndExtra = 0;

    wc.hInstance = hInstance;

    wc.hIcon =
        LoadIcon(
            NULL,
            IDI_APPLICATION
        );

    wc.hCursor =
        LoadCursor(
            NULL,
            IDC_ARROW
        );

    wc.hbrBackground =
        (HBRUSH)GetStockObject(
            BLACK_BRUSH
        );

    wc.lpszMenuName = NULL;

    wc.lpszClassName =
        "GLPaisagem";

    RegisterClass(&wc);

    // CRIA JANELA
    RECT rect;

    rect.left = 0;
    rect.top = 0;
    rect.right = LARGURA;
    rect.bottom = ALTURA;

    AdjustWindowRect(
        &rect,
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        FALSE
    );

    hWnd = CreateWindow(
        "GLPaisagem",
        "Trabalho OpenGL - Paisagem 2D",
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        100,
        50,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    // ATIVA OPENGL
    EnableOpenGL(
        hWnd,
        &hDC,
        &hRC
    );

    // CONFIGURAÇÃO 2D
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(
        0,
        LARGURA,
        0,
        ALTURA,
        -1,
        1
    );

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    // MOSTRA JANELA
    ShowWindow(
        hWnd,
        iCmdShow
    );

    // LOOP PRINCIPAL
    while (!bQuit)
    {
        if (PeekMessage(
                &msg,
                NULL,
                0,
                0,
                PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);

                DispatchMessage(&msg);
            }
        }
        else
        {
            // Limpa tela
            glClearColor(
                0.40f,
                0.75f,
                1.0f,
                1.0f
            );

            glClear(
                GL_COLOR_BUFFER_BIT
            );

            glLoadIdentity();

            // Desenha paisagem
            desenharCena();

            // Mostra na tela
            SwapBuffers(hDC);
        }
    }

    // FINALIZA OPENGL
    DisableOpenGL(
        hWnd,
        hDC,
        hRC
    );

    DestroyWindow(hWnd);

    return msg.wParam;
}

// CONTROLE DA JANELA
LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (message)
    {
        // MOUSE PRESSIONADO
        case WM_LBUTTONDOWN:
        {
            float mouseX = (float)LOWORD(lParam);

            float mouseY =(float)(ALTURA - HIWORD(lParam));

            if (mouseDentroDoCarro(mouseX, mouseY))
            {
                arrastandoCarro = true;

                distanciaMouseX =
                    mouseX - carroX;

                distanciaMouseY =
                    mouseY - carroY;

                SetCapture(hWnd);
            }

            return 0;
        }

        // MOUSE MOVENDO
        case WM_MOUSEMOVE:
        {
            if (arrastandoCarro)
            {
                float mouseX =
                    (float)LOWORD(lParam);

                float mouseY =
                    (float)(
                        ALTURA -
                        HIWORD(lParam)
                    );

                carroX =
                    mouseX -
                    distanciaMouseX;

                carroY =
                    mouseY -
                    distanciaMouseY;

                // Limites horizontais
                if (carroX < 0)
                    carroX = 0;

                if (carroX >
                    LARGURA - 170)
                {
                    carroX =
                        LARGURA - 170;
                }

                // Limites verticais
                if (carroY < 0)
                    carroY = 0;

                if (carroY >
                    ALTURA - 105)
                {
                    carroY =
                        ALTURA - 105;
                }
            }

            return 0;
        }

        // MOUSE SOLTO
        case WM_LBUTTONUP:
        {
            arrastandoCarro = false;

            ReleaseCapture();

            return 0;
        }

        // TECLA
        case WM_KEYDOWN:
        {
            if (wParam == VK_ESCAPE)
            {
                PostQuitMessage(0);
            }

            return 0;
        }

        // FECHAR
        case WM_CLOSE:
        {
            PostQuitMessage(0);

            return 0;
        }

        case WM_DESTROY:
        {
            return 0;
        }
    }

    return DefWindowProc(
        hWnd,
        message,
        wParam,
        lParam
    );
}

// ATIVA OPENGL
void EnableOpenGL(
    HWND hWnd,
    HDC *hDC,
    HGLRC *hRC
)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    *hDC = GetDC(hWnd);

    ZeroMemory(
        &pfd,
        sizeof(pfd)
    );

    pfd.nSize =
        sizeof(pfd);

    pfd.nVersion = 1;

    pfd.dwFlags =
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER;

    pfd.iPixelType =
        PFD_TYPE_RGBA;

    pfd.cColorBits = 24;

    pfd.cDepthBits = 16;

    pfd.iLayerType =
        PFD_MAIN_PLANE;

    iFormat =
        ChoosePixelFormat(
            *hDC,
            &pfd
        );

    SetPixelFormat(
        *hDC,
        iFormat,
        &pfd
    );

    *hRC =
        wglCreateContext(
            *hDC
        );

    wglMakeCurrent(
        *hDC,
        *hRC
    );
}

// DESATIVA OPENGL
void DisableOpenGL(
    HWND hWnd,
    HDC hDC,
    HGLRC hRC
)
{
    wglMakeCurrent(
        NULL,
        NULL
    );

    wglDeleteContext(hRC);

    ReleaseDC(
        hWnd,
        hDC
    );
}
