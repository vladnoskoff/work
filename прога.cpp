
//библиотека
#include "Books/TXlib.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//структура
struct Hero
    {
    int x , y;
    int vx, vy;

    int color, size;

    HDC  photo;
    void DeleteDC ();

    int up, down, right, left,  stop;

    void Button   ();
    void Physics  ();
    void Draw     ();
    void Run      ();

    };

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void programm ();

void Logic (Hero hero1, Hero *hero2, int area, int *LifeHero, int KillHero);

void DrawPoint (int *LifeHero);

void Level (HDC *fon,              HDC *photohero1,          HDC *photohero2,          HDC *photohero3,          HDC *photohero4,
            const char Fongame[],  const char Imagehero1[],  const char Imagehero2[],  const char Imagehero3[],  const char Imagehero4[]);

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main ()
    {
    txCreateWindow (1000, 1000);

    programm ();

    }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void programm ()
    {
//                                                                                                                 steps                 -
//    Name             x    y   vx  vy   color    size            photo                         ------------------------------------------
    Hero Viktor    = {300, 300,  1, 1,  TX_RED,    25,  txLoadImage ("Image/carr.bmp"),         VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE};
    Hero Romounald = {100, 100,  3, 2,  TX_GREEN,  25,  txLoadImage ("Image/friandkrosha.bmp"), 'W',   'S',     'D',      'A',     'Q'};
    Hero Vlad      = {500, 200,  4, 3,  TX_BLUE,   50,  txLoadImage ("Image/krosh.bmp")};
    Hero Ilya      = {800, 200,  1, 1,  TX_YELLOW, 50,  txLoadImage ("Image/mars.bmp")};

//жизни игрока
    int LifeHero   = 3;
    int KillHero   = -1;

//счетчик уровней
    int NLevel     = 1;

    HDC Fon        = txLoadImage ("Image/fon.bmp");

//шрифт для всех текстов
    txSelectFont   ("Arial", 35);

//цикл
    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor (TX_BLACK);
        txClear        ();


        txBitBlt (0, 0, Fon);

        //1
        Viktor.Run     ();

        //2
        Romounald.Run  ();

        //3
        Vlad.Run       ();

        //4
        Ilya.Run       ();

        DrawPoint (&LifeHero);

        Logic (Vlad, &Viktor, 50, &LifeHero, KillHero);

//переход на второй уровень
        if (LifeHero < 1)
            {
            LifeHero = 3;

            Level (&Fon, &Viktor.photo, &Romounald.photo, &Vlad.photo, &Ilya.photo,
                   "Image/Arm.bmp", "Image/MSI.bmp", "Image/MacBook.bmp", "Image/Lenovo.bmp", "Image/Asus.bmp");

            NLevel = NLevel + 1;

            if (NLevel > 2) break;

            }

        txSleep        (10);
        }

//удаление фото после завершения
    Vlad.DeleteDC      ();
    Romounald.DeleteDC ();
    Viktor.DeleteDC    ();
    Ilya.DeleteDC      ();

    txDeleteDC (Fon);
    }

//Отвичает за движение---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Hero::Physics ()
    {
    x = x + vx;
    y = y + vy;

    if (x < 50)
        {
        x  = 50;
        vx = -vx;
        }

    if (y < 50)
        {
        y  = 50;
        vy = -vy;
        }

    if (x > 950)
        {
        x  = 950;
        vx = -vx;
        }

    if (y > 950)
        {
        y  = 950;
        vy = -vy;
        }

    }

//Клавиши управления-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Hero::Button ()
    {

    if (GetAsyncKeyState (up))    (vy)--;
    if (GetAsyncKeyState (down))  (vy)++;
    if (GetAsyncKeyState (left))  (vx)--;
    if (GetAsyncKeyState (right)) (vx)++;
    if (GetAsyncKeyState (stop))  (vx) = (vy) = 0;
    }

//Рисование шарика-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Hero::Draw ()
    {
    if (photo != 0)
        {
        txTransparentBlt (x - 50, y - 50, photo, TX_WHITE);
        }

    if (photo == 0)
        {
        txSetFillColor (color);
        txCircle       (x,  y, size);
        }

    }

//Отвечает за всего героя------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Hero::Run ()
    {
    Draw    ();
    Physics ();
    Button  ();
    }

//Отвечает за касания героя с героем-------------------------------------------------------------------------------------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void DrawPoint (int *LifeHero)
    {
    char point [50] = "";

    sprintf  (point, "Point = %i \r", *LifeHero);

    txTextOut (0, 0, point);
    }

//Отвечает за переход на второй уровень----------------------------------------------------------------------------------------------------------------------------------------------------

void Level (HDC *fon,              HDC *photohero1,          HDC *photohero2,          HDC *photohero3,          HDC *photohero4,
            const char Fongame[], const char Imagehero1[],  const char Imagehero2[],  const char Imagehero3[],  const char Imagehero4[])
    {

    int Answer = txMessageBox ("Play?????","ВОПРОС???", MB_YESNO);
    if (Answer == IDYES)
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

    }

//Отвечает за удаление фото после завершения-----------------------------------------------------------------------------------------------------------------------------------------------

void Hero::DeleteDC ()
    {
    txDeleteDC (photo);
    }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
                                                В какой ф. нам дан пар Y?

                                            копия (значение)         указатель

             в какой ф. нужно
             передать пар. Y дальше?

             копия (значение)                Y                         *Y

             указатель                       &Y                        Y

*/




