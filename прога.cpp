
//����������
#include "Books/TXlib.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//���������
struct Hero
    {
    int x , y;
    int vx, vy;

    int color, size;

    int up, down, right, left,  stop;

    HDC  photo;
    void DeleteDC ();

    void Button   ();
    void Physics  ();
    void Draw     (int t);
    void Run      (int t);

    };

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

//����� ������
    int LifeHero   = 3;
    int KillHero   = -1;

//������� �������
    int NLevel     = 1;

//
    int t          = 0;

    HDC Fon        = NULL;

    LoadLevel (NLevel, &Fon, &Viktor.photo, &Romounald.photo, &Vlad.photo, &Ilya.photo);


//����� ��� ���� �������
    txSelectFont   ("Arial", 35);

//����
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
            int Answer = txMessageBox ("Play ?????","������???", MB_YESNO);

            if (Answer != IDYES) break;

            LifeHero = 3;

            NLevel = NLevel + 1;

            if (NLevel > 3) NLevel = 1;

            LoadLevel (NLevel, &Fon, &Viktor.photo, &Romounald.photo, &Vlad.photo, &Ilya.photo);

            }

        printf ("              Level = %i\r", NLevel);

        t++;

        txSleep        (100);
        }

//�������� ���� ����� ����������
    Vlad.DeleteDC      ();
    Romounald.DeleteDC ();
    Viktor.DeleteDC    ();
    Ilya.DeleteDC      ();

    txDeleteDC (Fon);
    }

//�������� �� ��������---------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

//������� ����������-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Hero::Button ()
    {

    if (GetAsyncKeyState (up))    (vy)--;
    if (GetAsyncKeyState (down))  (vy)++;
    if (GetAsyncKeyState (left))  (vx)--;
    if (GetAsyncKeyState (right)) (vx)++;
    if (GetAsyncKeyState (stop))  (vx) = (vy) = 0;

    }

//��������� ������-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Hero::Draw (int t)
    {// ���� ��������� ���������
    if (photo != 0)
        {
        //txTransparentBlt (txDC(), x, y, 200, 150, photo, t%2*100, 0);
        txBitBlt (txDC(), x, y, 200, 150, photo, t%2*100, 0);
        }

    if (photo == 0)
        {
        txSetFillColor (color);
        txCircle       (x,  y, size);
        }

    }

//�������� �� ����� �����------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Hero::Run (int t)
    {
    Draw    (t);
    Physics ();
    Button  ();
    }

//�������� �� ������� ����� � ������-------------------------------------------------------------------------------------------------------------------------------------------------------

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

//�������� �� ������� �� ������ �������----------------------------------------------------------------------------------------------------------------------------------------------------

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

//�������� �� �������� ���� ����� ����������-----------------------------------------------------------------------------------------------------------------------------------------------

void Hero::DeleteDC ()
    {
    txDeleteDC (photo);
    }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void LoadLevel (int NLevel, HDC *fon, HDC *photohero1, HDC *photohero2, HDC *photohero3, HDC *photohero4)
    {
    if (NLevel == 1)
            {

            Level (fon,              photohero1,        photohero2,                photohero3,         photohero4,
                   "Image/fon3.bmp", "Image/carr2.bmp", "Image/friandkrosha2.bmp", "Image/krosh2.bmp", "Image/mars2.bmp");

            }

    if (NLevel == 2)
            {

            Level (fon,               photohero1,       photohero2,       photohero3,         photohero4,
                   "Image/Farm2.bmp", "Image/Cow2.bmp", "Image/Fly2.bmp", "Image/Knife2.bmp", "Image/Pig2.bmp");

            }

    if (NLevel == 3)
            {

            Level (fon,              photohero1,       photohero2,           photohero3,          photohero4,
                   "Image/Arm2.bmp", "Image/MSI2.bmp", "Image/MacBook2.bmp", "Image/Lenovo2.bmp", "Image/Asus2.bmp");

            }

    }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
                                                � ����� �. ��� ��� ��� Y?

                                            ����� (��������)         ���������

             � ����� �. �����
             �������� ���. Y ������?

             ����� (��������)                Y                         *Y

             ���������                       &Y                        Y

*/




