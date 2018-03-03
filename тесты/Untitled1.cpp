#include "Books/TXlib.h"

int main ()
    {
    txCreateWindow (1000, 1000);

    //HDC Fon = txLoadImage ("Image/fon3.bmp");


    const char* level = txInputBox ("Level?!?!", "Game", "");
    txMessageBox (level, "");


    //txBitBlt (txDC(), 0, 0, 1000, 1000, Fon, 500, 0);

    }
