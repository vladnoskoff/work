//библиотека
#include "Books/TXlib.h"

struct Hero
    {
    int x,  y;
    int vx, vy;

    HDC photo;
    void DeleteDC ();

    int UP, DOWN, LEFT, RIGHT, STOP;

    void Phisica  ();
    void Logic    ();
    void KeyState ();
    void DrawHero (int t);

    void Run  (int t);
    };

//------------------------------------------------------

int pakman ();

//------------------------------------------------------

int main ()
    {
    txCreateWindow (1000, 1000);

    pakman ();
    }

//------------------------------------------------------

int pakman ()
    {
    HDC fon     = txLoadImage ("Image/play2/Fon.bmp");
    HDC player  = txLoadImage ("Image/play2/Pacman.bmp");
    HDC boy     = txLoadImage ("Image/play2/boy.bmp");

    Hero Pacman {306, 305,  0, 0, player};
    Hero Red    {800, 500, 1, 1, boy,  'W', 'S', 'A', 'D', 'Q'};

    int t = 0;

    Pacman.Logic ();

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txClear          ();

        txTransparentBlt (txDC(), 0, 0, 1000, 1000, fon, 0, 0, TX_WHITE);


        Pacman.Run       (t);

        Red.Run          (t);

        t++;
        txSleep (100);
        }

    Pacman.DeleteDC      ();
    Red.DeleteDC         ();

    txDeleteDC           (fon);


    return 0;
    }

//------------------------------------------------------

void Hero::Phisica ()
    {
    int xOld = x;
    int yOld = y;

    x = x + vx;
    y = y + vy;

    COLORREF pixel = txGetPixel (x, y);

    if (pixel != TX_BLACK)
        {
        x = xOld;
        y = yOld;

        Logic ();
        }

    }

void Hero::KeyState ()
    {
    if (GetAsyncKeyState (UP))    (vy)--;
    if (GetAsyncKeyState (DOWN))  (vy)++;
    if (GetAsyncKeyState (LEFT))  (vx)--;
    if (GetAsyncKeyState (RIGHT)) (vx)++;
    if (GetAsyncKeyState (STOP))  vx = vy = 0;
    }

void Hero::DrawHero (int t)
    {
    int xsize = txGetExtentX (photo);
    int ysize = txGetExtentY (photo);
    int v     = 0;

    if (vx > 0 && vy == 0) v = 0;

    if (vx < 0 && vy == 0) v = 1;

    if (vy > 0 && vx == 0) v = 2;

    if (vy < 0 && vx == 0) v = 3;

/*
1
vx > 0, vy = 0


2
vx< 0 , vy = 0

3
vx = 0, vy < 0

4
vx = 0, vy > 0

0 > -vy , чтобы фото смотрела вверх
0 > vx чтобы смотрел вниз

*/


    txTransparentBlt (txDC(), x - xsize/2, y - ysize/2, xsize/2, ysize/4, photo, t%2*xsize/2, v*ysize/4, TX_WHITE);
    }

void Hero::DeleteDC ()
    {
    txDeleteDC (photo);
    }

void Hero::Run (int t)
    {
    KeyState ();
    Phisica  ();
    DrawHero (t);
    }

void Hero::Logic ()
    {

    if (rand () % 2 == 0)
        {

        if (rand () % 2 == 0) vx = +10;
        else                  vx = -10;

        vy = 0;

        }
    else
        {

        if (rand () % 2 == 0) vy = +10;
        else                  vy = -10;

        vx = 0;

        }

    }

//------------------------------------------------------


