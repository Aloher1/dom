#include "TXLib.h"

bool click(int x1, int y1, int x2, int y2){
    return (txMouseButtons() == 1 &&
            txMouseX() > x1 &&
            txMouseY() > y1 &&
            txMouseX() < x2 &&
            txMouseY() < y2);
}

int main(){
    txCreateWindow (1400, 800);
    txTextCursor (false);

    int mx1, my1, t=0;
    int mx2, my2;
    int x1, x2, y1, y2;


    while(!GetAsyncKeyState (VK_ESCAPE)){
        txBegin();
        txSetFillColor(TX_WHITE);
        txClear();
        txSetColor(TX_BLACK, 3);
        mx2 = txMouseX();
        my2 = txMouseY();

        while(click(0, 0, 1400, 800)){
            mx1 = txMouseX();
            my1 = txMouseY();
            txRectangle(mx1, my1, mx2, my2);
            x1 = mx1;   y1 = my1;
            x2 = mx2;   y2 = my2;
            t = 1;
            txSleep(10);
        }
        if(t == 1)  txRectangle(x1, y1, x2, y2);

        txSleep(10);
        txEnd();
    }
    return 0;
}

