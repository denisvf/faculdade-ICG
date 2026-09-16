#include <windows.h>
#include <gl/gl.h>
#include <math.h>

float carroX = 0.0f;
float carroY = 0.0f;

float carroEscala = 1.0f;

float carroAngulo = 0.0f;


void desenharCirculo(float x, float y, float raio)
{
    int i;
    int quantidadePontos = 100;

    glBegin(GL_POLYGON);

    for (i = 0; i < quantidadePontos; i++)
    {
        float angulo = 2.0f * 3.14159f * i / quantidadePontos;

        float px = x + raio * cos(angulo);
        float py = y + raio * sin(angulo);

        glVertex2f(px, py);
    }

    glEnd();
}

void desenharSol()
{
    glColor3f(1.0f, 0.8f, 0.0f);

    desenharCirculo(0.70f, 0.72f, 0.12f);
}

void desenharCasa()
{
    glColor3f(0.85f, 0.55f, 0.30f);

    glBegin(GL_QUADS);

        glVertex2f(-0.80f, -0.05f);
        glVertex2f(-0.25f, -0.05f);
        glVertex2f(-0.25f, 0.35f);
        glVertex2f(-0.80f, 0.35f);

    glEnd();

    glColor3f(0.55f, 0.10f, 0.08f);

    glBegin(GL_TRIANGLES);

        glVertex2f(-0.85f, 0.35f);
        glVertex2f(-0.20f, 0.35f);
        glVertex2f(-0.525f, 0.65f);

    glEnd();

    glColor3f(0.30f, 0.15f, 0.05f);

    glBegin(GL_QUADS);

        glVertex2f(-0.58f, -0.05f);
        glVertex2f(-0.45f, -0.05f);
        glVertex2f(-0.45f, 0.20f);
        glVertex2f(-0.58f, 0.20f);

    glEnd();
}

void desenharNuvem(float x, float y)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    desenharCirculo(x, y, 0.07f);
    desenharCirculo(x + 0.08f, y + 0.02f, 0.09f);
    desenharCirculo(x + 0.17f, y, 0.07f);
}

void desenharRua()
{
    glColor3f(0.25f, 0.65f, 0.20f);

    glBegin(GL_QUADS);

        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(-1.0f, 0.0f);

    glEnd();

    glColor3f(0.25f, 0.25f, 0.25f);

    glBegin(GL_QUADS);

        glVertex2f(-1.0f, -0.55f);
        glVertex2f(1.0f, -0.55f);
        glVertex2f(1.0f, -0.05f);
        glVertex2f(-1.0f, -0.05f);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glLineWidth(4.0f);

    glBegin(GL_LINES);

        glVertex2f(-0.90f, -0.30f);
        glVertex2f(-0.65f, -0.30f);

        glVertex2f(-0.50f, -0.30f);
        glVertex2f(-0.25f, -0.30f);

        glVertex2f(-0.10f, -0.30f);
        glVertex2f(0.15f, -0.30f);

        glVertex2f(0.30f, -0.30f);
        glVertex2f(0.55f, -0.30f);

        glVertex2f(0.70f, -0.30f);
        glVertex2f(0.95f, -0.30f);

    glEnd();
}

void desenharCarro()
{

    glPushMatrix();

    glTranslatef(carroX, carroY, 0.0f);

    glRotatef(carroAngulo, 0.0f, 0.0f, 1.0f);

    glScalef(carroEscala, carroEscala, 1.0f);

    glColor3f(0.8f, 0.05f, 0.05f);

    glBegin(GL_QUADS);

        glVertex2f(0.05f, -0.40f);
        glVertex2f(0.55f, -0.40f);
        glVertex2f(0.55f, -0.25f);
        glVertex2f(0.05f, -0.25f);

    glEnd();

    glColor3f(0.8f, 0.05f, 0.05f);

    glBegin(GL_QUADS);

        glVertex2f(0.15f, -0.25f);
        glVertex2f(0.43f, -0.25f);
        glVertex2f(0.35f, -0.10f);
        glVertex2f(0.22f, -0.10f);

    glEnd();

    glColor3f(0.20f, 0.60f, 0.80f);

    glBegin(GL_QUADS);

        glVertex2f(0.23f, -0.23f);
        glVertex2f(0.32f, -0.23f);
        glVertex2f(0.30f, -0.13f);
        glVertex2f(0.24f, -0.13f);

    glEnd();

    glBegin(GL_QUADS);

        glVertex2f(0.34f, -0.23f);
        glVertex2f(0.41f, -0.23f);
        glVertex2f(0.35f, -0.13f);
        glVertex2f(0.32f, -0.13f);

    glEnd();

    glColor3f(0.05f, 0.05f, 0.05f);

    desenharCirculo(0.15f, -0.43f, 0.08f);

    desenharCirculo(0.45f, -0.43f, 0.08f);

    glColor3f(0.60f, 0.60f, 0.60f);

    desenharCirculo(0.15f, -0.43f, 0.035f);
    desenharCirculo(0.45f, -0.43f, 0.035f);

    glPopMatrix();
}

void desenharCenario()
{
    glColor3f(0.45f, 0.75f, 1.0f);

    glBegin(GL_QUADS);

        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);

    glEnd();

    desenharSol();

    desenharNuvem(-0.60f, 0.75f);
    desenharNuvem(0.10f, 0.82f);

    desenharRua();
    
    desenharCasa();

    desenharCarro();
}


void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    *hDC = GetDC(hWnd);

    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;

    pfd.dwFlags =
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER;

    pfd.iPixelType = PFD_TYPE_RGBA;

    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);

    wglDeleteContext(hRC);

    ReleaseDC(hWnd, hDC);
}

LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (message)
    {
        case WM_KEYDOWN:

            if (wParam == VK_LEFT)
                carroX -= 0.05f;

            if (wParam == VK_RIGHT)
                carroX += 0.05f;

            if (wParam == VK_UP)
                carroY += 0.05f;

            if (wParam == VK_DOWN)
                carroY -= 0.05f;

            if (wParam == 'Z')
            {
                carroEscala += 0.1f;
            }
            
            if (wParam == 'X')
            {
                carroEscala -= 0.1f;
            
                if (carroEscala < 0.2f)
                    carroEscala = 0.2f;
            }
            
            if (wParam == VK_SUBTRACT || wParam == '-')
            {
                carroEscala -= 0.1f;
                if (carroEscala < 0.2f)
                    carroEscala = 0.2f;
            }

            if (wParam == 'A')
                carroAngulo += 5.0f;

            if (wParam == 'D')
                carroAngulo -= 5.0f;

            if (wParam == 'R')
            {
                carroX = 0.0f;
                carroY = 0.0f;

                carroEscala = 1.0f;

                carroAngulo = 0.0f;
            }

            if (wParam == VK_ESCAPE)
                PostQuitMessage(0);

            InvalidateRect(hWnd, NULL, FALSE);

            return 0;

        case WM_CLOSE:

            PostQuitMessage(0);

            return 0;

        case WM_DESTROY:

            return 0;
    }


    return DefWindowProc(
        hWnd,
        message,
        wParam,
        lParam);
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;

    HDC hDC;
    HGLRC hRC;

    MSG msg;

    wc.style = CS_OWNDC;

    wc.lpfnWndProc = WndProc;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;

    wc.hInstance = hInstance;

    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    wc.hbrBackground =
        (HBRUSH)GetStockObject(BLACK_BRUSH);

    wc.lpszMenuName = NULL;

    wc.lpszClassName = "OpenGL";


    RegisterClass(&wc);

    hWnd = CreateWindow(
        "OpenGL",
        "Cenario 2D - Transformacoes",
        WS_CAPTION |
        WS_POPUPWINDOW |
        WS_VISIBLE,

        100,
        100,

        900,
        700,

        NULL,
        NULL,
        hInstance,
        NULL);

    EnableOpenGL(hWnd, &hDC, &hRC);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);

        DispatchMessage(&msg);

        glClearColor(
            0.45f,
            0.75f,
            1.0f,
            1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        glOrtho(
            -1.0,
            1.0,
            -1.0,
            1.0,
            -1.0,
            1.0);


        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        desenharCenario();

        SwapBuffers(hDC);
    }

    DisableOpenGL(hWnd, hDC, hRC);

    DestroyWindow(hWnd);


    return 0;
}
