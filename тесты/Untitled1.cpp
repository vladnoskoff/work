#include "Books/TXlib.h"

struct Hero
    {
    int x,  y;
    int vx, vy;

    HDC photo;
    int FrameSizeX;
    int FrameSizeY;
    int status, oldstatus;

    int UP, DOWN, LEFT, RIGHT, STOP;

    void Phisica  ();
    void Logic    ();
    void KeyState ();
    void DrawHero (int t);
    void Mouse    (int leftm, int rightm);
    void Pull     (Hero* hero2);
    void DeleteHDCDC ();
    };

int main ()
    {
    txCreateWindow (1000, 1000);

    HDC player  = txLoadImage ("Image/play2/Pacman.bmp");

    //HDC Fon = txLoadImage ("Image/fon3.bmp");


    //const char* level = txInputBox ("Level?!?!", "Game", "");
    //txMessageBox (level, "");


    //txBitBlt (txDC(), 0, 0, 1000, 1000, Fon, 500, 0);

    Hero Pacman = {306, 200, 1, 1, player, 2, 4, 1, 1};

    int t = 0;

    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        Pacman.Phisica        ();
        Pacman.DrawHero       (t);

        }

    Pacman.DeleteHDCDC    ();

    t++;
    }



void Hero::Phisica ()
    {
    int xOld = x;
    int yOld = y;

    x = x + vx;
    y = y + vy;

    int xsize = txGetExtentX (photo) / 2 - 6;
    int ysize = txGetExtentY (photo) / 4 - 6;

/*
    printf ("xsize= %d\n", xsize);
    printf ("ysize= %d\n", ysize);
    txSetColor     (TX_YELLOW);
    txSetFillColor (TX_NULL);
    txCircle (x - xsize/2,   y,         5);
    txCircle (x,           y + ysize/2, 5);
    txCircle (x + xsize/2,   y,         5);
    txCircle (x,           y - ysize/2, 5);
    txSetColor (TX_GREEN);
    txSetFillColor (TX_NULL);
    txCircle (x,           y,         5);
*/

    COLORREF leftpixel  = txGetPixel (x - xsize/2,  y);
    COLORREF uppixel    = txGetPixel (x,            y + ysize/2);
    COLORREF rightpixel = txGetPixel (x + xsize/2,  y);
    COLORREF downpixel  = txGetPixel (x,            y - ysize/2);

    if (leftpixel != TX_BLACK || rightpixel != TX_BLACK)
        {
        x = xOld;

        Logic ();
        }

    if (uppixel   != TX_BLACK || downpixel  != TX_BLACK)
        {
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
    //if (GetAsyncKeyState ('E'))   status  = Life;
    //if (GetAsyncKeyState ('E'))   status  = Rip;

    }

void Hero::DrawHero (int t)
    {
    int xsize = txGetExtentX (photo) / FrameSizeX;
    int ysize = txGetExtentY (photo) / FrameSizeY;
    int v     = 0;

    if (vx > 0 && vy == 0) v = 0;

    if (vx < 0 && vy == 0) v = 1;

    if (vy > 0 && vx == 0) v = 2;

    if (vy < 0 && vx == 0) v = 3;

    //if (status == Life)  txTransparentBlt (txDC(), x - xsize/FrameSizeX, y - ysize/FrameSizeX, xsize, ysize, photo, t%FrameSizeX*xsize, v*ysize, TX_WHITE);
    //if (status == Rip)  { txSetFillColor (TX_WHITE); txCircle (x, y , 15); }

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



если статус = 1 , то TransparentBlt не вызывает  для еды
 если статус = 0 , то функция DrawHero будет вызывать TransparentBlt для еды

*/

    }

void Hero::DeleteHDCDC ()
    {
    txDeleteDC (photo);
    }

void Hero::Logic ()
    {

    if (rand () % 2 == 0)
        {

        if (rand () % 2 == 0) vx = +1;
        else                  vx = -1;

        vy = 0;

        }
    else
        {

        if (rand () % 2 == 0) vy = +1;
        else                  vy = -1;

        vx = 0;

        }

    }

void Hero::Mouse (int leftm, int rightm)
    {

    if (GetAsyncKeyState (leftm))
        {
        x = txMouseX();
        y = txMouseY();
        }

    if (GetAsyncKeyState (rightm))
        {
        x = txMouseX();
        y = txMouseY();
        }

    }

void Hero::Pull (Hero* hero2)
    {

    vx = -(x - hero2->x) / 50;
    vy = -(y - hero2->y) / 50;

    }




    /*
        if (Yellow.status == Rip || Red.status == Rip)
            {
            int Answer = txMessageBox ("Level 2 ?!?!?","ВОПРОС???", MB_YESNO);
            if (Answer == IDYES)
                {
                //txDeleteDC            (fon);
                txTransparentBlt      (txDC(), 0, 0, 1700, 1070, fon2, 0, 0, TX_WHITE);

                Red.status            = Life;
                Yellow.status         = Life;

                score = Touching  (&Pacman, &Red, &Yellow, &life);

                }
            else
                {
                break;

                }

            }
    */
