//библиотека
#include "Books/TXlib.h"

struct Hero
    {
    int x,  y;
    int vx, vy;

    HDC photo;
    int FrameSizeX;
    int FrameSizeY;
    void DeleteDC ();
    int status, oldstatus;

    int UP, DOWN, LEFT, RIGHT, STOP;

    void Phisica  ();
    void Logic    ();
    void KeyState ();
    void DrawHero (int t);
    void Mouse    (int leftm, int rightm);
    void Pull     (Hero* hero2);
    };

//------------------------------------------------------

int    pakman      ();
int    Touching    (Hero* pacman, Hero* hero2, Hero* hero3, int *life);
double GetDistance (Hero* hero, Hero* hero2);
void   DrawScore   (int score);
void   DrawLife    (int life);
int    TimeLevel  ();

const int XMap       = 1700;
const int YMap       = 1070;
//const int PacmanTime = 0; вместо const теперь простая переменная к которой присваиваеться функция (SelectLevel)

const int Level      = 0;

const int Life       = 1;
const int Rip        = 0;

const int HeroPlace  = 1000;

//------------------------------------------------------

int main ()
    {
    _txWindowStyle &= ~WS_CAPTION;
    txCreateWindow (XMap, YMap);

    pakman ();
    }

//------------------------------------------------------

int pakman ()
    {
    HDC fon     = txLoadImage ("Image/play2/Fon.bmp");
    HDC fon2     = txLoadImage ("Image/play2/fon2.bmp");
    HDC player  = txLoadImage ("Image/play2/Pacman.bmp");
    HDC boy     = txLoadImage ("Image/play2/boy.bmp");
    HDC boy2    = txLoadImage ("Image/play2/boy2.bmp");
    HDC eat     = txLoadImage ("Image/play2/eat.bmp");

    Hero Pacman  {306, 200, 1, 1, player, 2, 4, Life, Life};
    Hero Red     {812, 550, 1, 1, boy,    2, 4, Life, Life, 'W',   'S',     'A',     'D',     'Q'};
    Hero Yellow  {606, 195, 1, 1, boy2,   2, 4, Life, Life, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT};
    Hero Eat     {606, 200, 0, 0, eat,    1, 1, Life, Life};



    int t = 0;

    int StartTime = GetTickCount();

    Pacman.Logic               ();

    txSelectFont               ("Unispace", 40);

    int PacmanTime = TimeLevel ();

/*
Создаем переменную в функции (SelectLevel)
Присваиваем значения 30 и 10
возвращаем переменную

мы это разбирали
 тоже самое что и return 30 и return 10

я хочу
return 30 :
вызываем функцию (SelectLevel)
мы возвращаем число и присваиваем переменной(PacmanTime)
потом начинаеться работа цикла


на самом деле происходит
вызываем функцию (SelectLevel)
в ней
мы возвращаем число (30 или 10)
 и все

как правильно сделать вызов функции(SelectLevel)

к переменной(PacmanTime) присвоить значения функции (SelectLevel)

int PacmanTime = SelectLevel ();


return 30;


*/


    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor        (TX_BLACK);
        txClear               ();


        txTransparentBlt      (txDC(), 0, 0, 1700, 1000, fon, 0, 0, TX_WHITE);

        Pacman.Phisica        ();

        Red.KeyState          ();
        Yellow.KeyState       ();

        Red.Phisica           ();
        Yellow.Phisica        ();

        Eat.DrawHero          (t);

        Red.DrawHero          (t);


        //Yellow.KeyState       ();

        Yellow.DrawHero       (t);

        Pacman.DrawHero       (t);

        Pacman.Mouse          (MK_LBUTTON, 0);
        Red.Mouse             (0, MK_RBUTTON);

        int life  = 2;

        int score = Touching  (&Pacman, &Red, &Yellow, &life);

        DrawScore             (score);
        DrawLife              (life);

        //if (score == 2)       break;
        //if (life  == 0)       break;

        /*
        // oldstatus    = 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0
        // status       = 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0
        //                                  *                  /
        //                                                                                /
        //if (Red.oldstatus == Life && Red.status == Rip)    StartTime = GetTickCount();
        //                                                                                /
        */


        if (Red.oldstatus     == Life   &&   Red.status     == Rip)    StartTime = GetTickCount();
        if (Yellow.oldstatus  == Life   &&   Yellow.status  == Rip)    StartTime = GetTickCount();

        int time = GetTickCount() - StartTime;

        if (time >= PacmanTime*1000) break;

        printf                ("%d \n", time);


        if (Yellow.status == Rip && Red.status == Rip)
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

        t++;
        txSleep               (100);
        }

    Pacman.DeleteDC           ();
    Red.DeleteDC              ();
    Yellow.DeleteDC           ();
    Eat.DeleteDC              ();




    return 0;
    }

//------------------------------------------------------

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

    if (status == Life)  txTransparentBlt (txDC(), x - xsize/FrameSizeX, y - ysize/FrameSizeX, xsize, ysize, photo, t%FrameSizeX*xsize, v*ysize, TX_WHITE);
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

void Hero::DeleteDC ()
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

double GetDistance (Hero* hero, Hero* hero2)
    {
    double s = sqrt ( (hero->x - hero2->x) * (hero->x - hero2->x) + (hero->y - hero2->y) * (hero->y - hero2->y));

    return s;
    }

int Touching (Hero* pacman, Hero* hero2, Hero* hero3, int *life)
    {
    int score = 0;

    hero2->oldstatus = hero2->status;
    hero3->oldstatus = hero3->status;

    double Distance12 = GetDistance (pacman, hero2);

    if (Distance12 <= 10)
        {
        //printf ("R");
        hero2->status  = Rip;
        }

//----------------------------------------------------------------------------------------------------------------------

    double Distance13 = GetDistance (pacman, hero3);

    if (Distance13 <= 10)
        {
        //printf ("Y");
        hero3->status = Rip;
        }

//----------------------------------------------------------------------------------------------------------------------

    if (hero2->status == Rip) Distance12 = HeroPlace;
    if (hero3->status == Rip) Distance13 = HeroPlace;

    if (Distance12 < Distance13 && hero2->status == Life)
        {
        //printf ("r");
        pacman->Pull (hero2);

        }

    if (Distance13 < Distance12 && hero3->status == Life)
        {
        //printf ("y");
        pacman->Pull (hero3);

        }

//-----------------------------------------------------------------------------------------------------------------------

    if (hero2->status == Rip)  { score++; (*life)--; }
    if (hero3->status == Rip)  { score++; (*life)--; }

    return (score);
    }

void DrawScore (int score)
    {

    txSetColor (TX_YELLOW);

    char text [100] = "";

    sprintf (text, "SCORE : %d", score);

    txTextOut (200, 1010, text);

    }

void DrawLife (int life)
    {

    txSetColor (TX_YELLOW);

    char text [100] = "";

    sprintf (text, "Life : %d", life);

    txTextOut (800, 1010, text);

    }

/*
int TimeLevel ()
    {


    int Answer = txMessageBox ("сложный = ДА , легкий = НЕТ","ВОПРОС???", MB_YESNO);
    if (Answer == IDYES)
        {
        return 10;
        }
    else
        {
        return 30;
        }

    }
*/

int TimeLevel ()
    {

    const char* level = txInputBox ("Level?!?!", "Game", "");

    int select = atoi (level);

    if (select == 0) select = 30;

    return select;
    }


//------------------------------------------------------


