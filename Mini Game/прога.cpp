
//áèáëèîòåêà
#include "Books/TXlib.h"
/////////
#include "Books/TXVlad.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void programm ();

void Logic (Hero hero1, Hero *hero2, int area, int *LifeHero, int KillHero);

void DrawPoint (int *LifeHero);

void Level (HDC *fon,              HDC *photohero1,          HDC *photohero2,          HDC *photohero3,          HDC *photohero4,
            const char Fongame[],  const char Imagehero1[],  const char Imagehero2[],  const char Imagehero3[],  const char Imagehero4[]);

void LoadLevel (int NLevel, HDC *fon, HDC *photohero1, HDC *photohero2, HDC *photohero3, HDC *photohero4);

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main ()
    {
    txCreateWindow (1000, 1000);

    programm ();

    }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void programm ()
    {
//                                                                       steps
//    Name             x    y   vx  vy   color    size   ------------------------------------------    photo
    Hero Viktor    = {300, 300,  1, 1,  TX_RED,    25,  VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE};
    Hero Romounald = {100, 100,  3, 2,  TX_GREEN,  25,  'W',   'S',     'D',      'A',     'Q'};
    Hero Vlad      = {500, 200,  4, 3,  TX_BLUE,   50};
    Hero Ilya      = {800, 200,  1, 1,  TX_YELLOW, 50};

//æèçíè èãðîêà
    int LifeHero   = 3;
    int KillHero   = -1;

//ñ÷åò÷èê óðîâíåé
    int NLevel     = 1;

//
    int t          = 0;

    HDC Fon        = NULL;

    LoadLevel (NLevel, &Fon, &Viktor.photo, &Romounald.photo, &Vlad.photo, &Ilya.photo);


//øðèôò äëÿ âñåõ òåêñòîâ
    txSelectFont   ("Arial", 35);

//öèêë
    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (TX_BLACK);
        txClear        ();

        txBitBlt (txDC(), 0, 0, 1000, 1000, Fon, t%2*1000, 0);


        //1
        Viktor.Run     (t);

        //2
        Romounald.Run  (t);

        //3
        Vlad.Run       (t);


        //4
        Ilya.Run       (t);

        DrawPoint (&LifeHero);

        Logic (Vlad, &Viktor, 50, &LifeHero, KillHero);


        if (LifeHero < 1)
            {
            int Answer = txMessageBox ("Play ?????","ÂÎÏÐÎÑ???", MB_YESNO);

            if (Answer != IDYES) break;

            LifeHero = 3;

            NLevel = NLevel + 1;

            if (NLevel > 3) NLevel = 1;

            LoadLevel (NLevel, &Fon, &Viktor.photo, &Romounald.photo, &Vlad.photo, &Ilya.photo);

            }

        printf ("              Level = %i\r", NLevel);

        t++;

        txSleep        (80);
        }

//óäàëåíèå ôîòî ïîñëå çàâåðøåíèÿ
    Vlad.DeleteDC      ();
    Romounald.DeleteDC ();
    Viktor.DeleteDC    ();
    Ilya.DeleteDC      ();

    txDeleteDC (Fon);
    }

//Îòâå÷àåò çà êàñàíèÿ ãåðîÿ ñ ãåðîåì-------------------------------------------------------------------------------------------------------------------------------------------------------

void Logic (Hero hero1, Hero *hero2, int area, int *LifeHero, int KillHero)
    {
    double distance = sqrt (((*hero2).x-hero1.x)*((*hero2).x-hero1.x) + ((*hero2).y-hero1.y)*((*hero2).y-hero1.y));


    if (distance < area)
        {

        *LifeHero = (*LifeHero + KillHero);

        txMessageBox ("Win Viktor");


        (*hero2).x  = rand()/65;
        (*hero2).y  = rand()/65;
        }

    }

//Îòâå÷àåò çà ïåðåõîä íà âòîðîé óðîâåíü----------------------------------------------------------------------------------------------------------------------------------------------------

void Level (HDC *fon,              HDC *photohero1,          HDC *photohero2,          HDC *photohero3,          HDC *photohero4,
            const char Fongame[], const char Imagehero1[],  const char Imagehero2[],  const char Imagehero3[],  const char Imagehero4[])
    {

    txDeleteDC (*fon);

    txDeleteDC (*photohero1);
    txDeleteDC (*photohero2);
    txDeleteDC (*photohero3);
    txDeleteDC (*photohero4);

    *fon        = txLoadImage (Fongame);

    *photohero1 = txLoadImage (Imagehero1);

    *photohero2 = txLoadImage (Imagehero2);

    *photohero3 = txLoadImage (Imagehero3);

    *photohero4 = txLoadImage (Imagehero4);

    }

//Îòâå÷àåò çà çàãðóçêó âñåõ ôîòî íà âñåõ óðîâíÿõ-------------------------------------------------------------------------------------------------------------------------------------------

void LoadLevel (int NLevel, HDC *fon, HDC *photohero1, HDC *photohero2, HDC *photohero3, HDC *photohero4)
    {
    if (NLevel == 1)
            {

            Level (fon,                    photohero1,              photohero2,                      photohero3,               photohero4,
                   "Image/play1/fon3.bmp", "Image/play1/carr2.bmp", "Image/play1/friandkrosha2.bmp", "Image/play1/krosh2.bmp", "Image/play1/mars2.bmp");

            }

    if (NLevel == 2)
            {

            Level (fon,                     photohero1,             photohero2,             photohero3,               photohero4,
                   "Image/play1/Farm2.bmp", "Image/play1/Cow2.bmp", "Image/play1/Fly2.bmp", "Image/play1/Knife2.bmp", "Image/play1/Pig2.bmp");

            }

    if (NLevel == 3)
            {

            Level (fon,                    photohero1,             photohero2,                 photohero3,                photohero4,
                   "Image/play1/Arm2.bmp", "Image/play1/MSI2.bmp", "Image/play1/MacBook2.bmp", "Image/play1/Lenovo2.bmp", "Image/play1/Asus2.bmp");

            }

    }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
                                                Â êàêîé ô. íàì äàí ïàð Y?

                                            êîïèÿ (çíà÷åíèå)         óêàçàòåëü

             â êàêîé ô. íóæíî
             ïåðåäàòü ïàð. Y äàëüøå?

             êîïèÿ (çíà÷åíèå)                Y                         *Y

             óêàçàòåëü                       &Y                        Y


ñäåëàòü òàáëèöó
*/



