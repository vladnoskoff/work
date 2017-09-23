
#include "TXlib.h"

void programm (int x, int y, int vx, int vy);

void Physics (int *x, int *y, int *vx, int *vy);



int main ()
    {
    txCreateWindow (1000, 1000);

    programm (300, 300, 7, 5);

    }


void programm (int x, int y, int vx, int vy)
    {
    int x2  = 100, y2  = 200;
    int vx2 = 10,  vy2 = 5;

    int x3  = 700, y3  = 200;
    int vx3 = 10,  vy3 = 5;

    while (!GetAsyncKeyState (VK_ESCAPE))
        {


        txSetFillColor (TX_BLACK);
        txClear        ();

        txSetFillColor (TX_RED);
        txCircle       (x, y, 25);

        txSetFillColor (TX_GREEN);
        txCircle       (x2, y2, 25);

        txSetFillColor (TX_BLUE);
        txCircle       (x3, y3, 25);

        Physics        (&x,  &y,  &vx,  &vy);
        Physics        (&x2, &y2, &vx2, &vy2);
        Physics        (&x3, &y3, &vx3, &vy3);

        txSleep        (10);
        }

//    txMessageBox ("Win");
    }

void Physics (int *x, int *y, int *vx, int *vy)
    {
    *x = *x + *vx;
    *y = *y + *vy;

    if (*x < 0)
        {
        *x  = 0;
        *vx = -*vx;
        }

    if (*y < 0)
        {
        *y  = 0;
        *vy = -*vy;
        }

    if (*x > 950)
        {
        *x  = 950;
        *vx = -*vx;
        }

    if (*y > 950)
        {
        *y  = 950;
        *vy = -*vy;
        }

    }
