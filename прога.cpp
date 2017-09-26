
#include "TXlib.h"

struct Hero
    {
    int x , y;
    int vx, vy;

    int color, size;

    int up, down, right, left,  stop;

    };

void programm ();
void GameHero (Hero *hero);

void Physics (Hero *hero);
void Button  (Hero *hero);
void Draw    (Hero *hero);


int main ()
    {
    txCreateWindow (1000, 1000);

    programm ();

    }


void programm ()
    {
    Hero Viktor    = {300, 300, 2, 2, TX_RED,    25, VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE};
    Hero Romounald = {100, 100, 3, 2, TX_GREEN,  25, 'W',   'S',     'D',      'A',     'Q'};
    Hero Vlad      = {500, 200, 4, 3, TX_BLUE,   50};
    Hero Ilya      = {800, 200, 5, 5, TX_YELLOW, 50};

    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        txSetFillColor (TX_BLACK);
        txClear        ();

        //1
        GameHero (&Viktor);

        //2
        GameHero (&Romounald);

        //3
        GameHero (&Vlad);

        //4
        GameHero (&Ilya);


        txSleep        (10);
        }

//    txMessageBox ("Win");
    }

void Physics (Hero *hero)
    {
    (*hero).x = (*hero).x + (*hero).vx;
    (*hero).y = (*hero).y + (*hero).vy;

    if ((*hero).x < 50)
        {
        (*hero).x  = 50;
        (*hero).vx = -(*hero).vx;
        }

    if ((*hero).y < 50)
        {
        (*hero).y  = 50;
        (*hero).vy = -(*hero).vy;
        }

    if ((*hero).x > 950)
        {
        (*hero).x  = 950;
        (*hero).vx = -(*hero).vx;
        }

    if ((*hero).y > 950)
        {
        (*hero).y  = 950;
        (*hero).vy = -(*hero).vy;
        }

    }

void Button (Hero *hero)
    {

    if (GetAsyncKeyState ((*hero).up))    ((*hero).vy)--;
    if (GetAsyncKeyState ((*hero).down))  ((*hero).vy)++;
    if (GetAsyncKeyState ((*hero).left))  ((*hero).vx)--;
    if (GetAsyncKeyState ((*hero).right)) ((*hero).vx)++;
    if (GetAsyncKeyState ((*hero).stop))  ((*hero).vx) = ((*hero).vy) = 0;
    }

void Draw (Hero *hero)
    {
    txSetFillColor ((*hero).color);
    txCircle       ((*hero).x,  (*hero).y, (*hero).size);
    }


void GameHero (Hero *hero)
    {
    Draw    (*hero);
    Physics (*hero);
    Button  (*hero);
    }
