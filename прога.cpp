
#include "TXlib.h"

void programm ();

int main ()
    {
    txCreateWindow (1000, 1000);

    programm ();
    }


void programm ()
    {
    txSetColor (TX_RED);
    txLine (100, 100, 500, 500);
    }
