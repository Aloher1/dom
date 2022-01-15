#include "TXLib.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

bool click(int x1, int y1, int x2, int y2){
    return (txMouseButtons() == 1 &&
            txMouseX() > x1 &&
            txMouseY() > y1 &&
            txMouseX() < x2 &&
            txMouseY() < y2);
}

struct subBUTTON{
    const char* text;
};

struct BUTTON{
    const char* text;
    subBUTTON subButton[10];
    int x;
    int y;

    void draw(){
        txSetColor(TX_BLACK,3);
        txRectangle(x, y, x + 200, y + 50);
        txDrawText(x, y, x + 200, y + 50, text);
        /*if(txMouseX() >= x && txMouseX() <= x + 150 &&
           txMouseY() >= y && txMouseY() <= y + 50)
            txSetColor(TX_CYAN);
        txDrawText(x, y, x + 200, y + 50, text);
          */
    }
};

int getWidth(const char* address){
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);
    bmp.read(header, 54);
    int width;
    memcpy(&width, &header[18], sizeof(width));
    return width;
}

int getHeight(const char* address){
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);
    bmp.read(header, 54);
    int height;
    memcpy(&height, &header[22], sizeof(height));
    return height;
}

struct picture{
    string address;
    string folder;
    string section;
    int x;
    int y;
    bool visible;
    HDC pic;
    int width;
    int height;
    void drawIcon(){
        Win32::TransparentBlt (txDC(), x, y, width, height, pic, 0, 0, width, height, TX_WHITE);
    }
};

int main(){
    txCreateWindow (1400, 800);
    txTextCursor (false);

    int x = 0, y = 0;
    int sx = 0; int sy = 0;
    //для кнопок
    int chsnSection = -1;
    string chSection = "";
    string chSubSection = "";
    //активные картинки(в центре)
    picture activeObj[1000];
    int activePic = -1;

    picture obj[100];
    //все картинки
    obj[0].address = "Pictures\\Мебель\\диваны\\Divan1.bmp";
    obj[1].address = "Pictures\\Мебель\\диваны\\Divan2.bmp";
    obj[2].address = "Pictures\\Мебель\\диваны\\Divan3.bmp";
    obj[3].address = "Pictures\\Мебель\\диваны\\Divan4.bmp";
    obj[4].address = "Pictures\\Мебель\\диваны\\Divan5.bmp";
    obj[5].address = "Pictures\\Мебель\\диваны\\Divan6.bmp";
    for(int i = 0;i < 5;i++){
         obj[i].section = "диваны";
    }
    obj[6].address = "Pictures\\Мебель\\кровати\\Bed.bmp";
    obj[7].address = "Pictures\\Мебель\\кровати\\Bed1.bmp";
    obj[8].address = "Pictures\\Мебель\\кровати\\bed2.bmp";
    obj[9].address = "Pictures\\Мебель\\кровати\\bed3.bmp";
    obj[10].address = "Pictures\\Мебель\\кровати\\bed4.bmp";
    obj[11].address = "Pictures\\Мебель\\кровати\\bed5.bmp";
    for(int i = 6;i < 11;i++){
        obj[i].section = "кровати";
    }
    obj[12].address = "Pictures\\Мебель\\столы\\стол и комп.bmp";
    obj[13].address = "Pictures\\Мебель\\столы\\стол и ноутбук.bmp";
    obj[14].address = "Pictures\\Мебель\\столы\\Стол кухонный.bmp";
    obj[15].address = "Pictures\\Мебель\\столы\\стол.bmp";
    for(int i = 12;i < 15;i++){
        obj[i].section = "столы";
    }
    obj[16].address = "Pictures\\Мебель\\стулья\\Stul1.bmp";
    obj[17].address = "Pictures\\Мебель\\стулья\\Stul2.bmp";
    obj[18].address = "Pictures\\Мебель\\стулobj[i].visibleья\\Stul3.bmp";
    obj[19].address = "Pictures\\Мебель\\стулья\\Stul4.bmp";
    obj[20].address = "Pictures\\Мебель\\стулья\\кресло1.bmp";
    obj[21].address = "Pictures\\Мебель\\стулья\\кресло2.bmp";
    for(int i = 16;i < 21;i++){
        obj[i].section = "стулья";
    }
    for(int i = 0;i < 21;i++){
        obj[i].folder  = "Мебель";
    }
    obj[22].address = "Pictures\\Планировка\\планировка\\планировка1.bmp";
    obj[23].address = "Pictures\\Планировка\\планировка\\планировка2.bmp";
    for(int i = 22;i < 23;i++){
        obj[i].folder = "планировка";
        obj[i].section = "планировка";
    }
    obj[24].address = "Pictures\\Пол\\ковры\\Cover1.bmp";
    obj[25].address = "Pictures\\Пол\\ковры\\Cover2.bmp";
    obj[26].address = "Pictures\\Пол\\ковры\\Cover3.bmp";
    obj[27].address = "Pictures\\Пол\\ковры\\Cover4.bmp";
    for(int i = 24;i < 27;i++){
        obj[i].section = "ковры";
    }
    obj[28].address = "Pictures\\Пол\\паркет\\паркет1.bmp";
    obj[29].address = "Pictures\\Пол\\паркет\\паркет2.bmp";
    obj[30].address = "Pictures\\Пол\\паркет\\паркет3.bmp";
    for(int i = 28;i < 30;i++){
        obj[i].section = "паркет";
    }
    for(int i = 24;i < 30;i++){
        obj[i].folder = "Пол";
    }
    obj[31].address = "Pictures\\Разное\\ванные\\ванная1.bmp";
    obj[32].address = "Pictures\\Разное\\туалеты\\туалет1.bmp";
    for(int i = 31;i < 32;i++){
        obj[i].folder = "Разное";
    }
    obj[31].section = "ванные";
    obj[32].section = "туалеты";

    obj[33].address = "Pictures\\Техника\\для кухни\\стиралка1.bmp";
    obj[34].address = "Pictures\\Техника\\компьютеры\\ноутбук.bmp";
    obj[35].address = "Pictures\\Техника\\телевизоры\\телевизор1.bmp";
    obj[33].section = "для кухни";
    obj[34].section = "компьютеры";
    obj[35].section = "телевизоры";
    for(int i = 33;i < 35;i++){
        obj[i].folder = "Техника";
    }

    for(int i = 0;i < 36;i++){
        obj[i].x = 1200;
        obj[i].visible = false;
        obj[i].pic = txLoadImage(obj[i].address.c_str());
        obj[i].width = getWidth(obj[i].address.c_str());
        obj[i].height = getHeight(obj[i].address.c_str());
    }

    //Разделы
    BUTTON button[5];
    button[0] = {"Мебель",     {{"стулья"    }, {"столы"     }, {"кровати"   }, {"диваны"}, {""}}};
    button[1] = {"Техника",    {{"для кухни" }, {"телевизоры"}, {"компьютеры"}, {""      }, {""}}};
    button[2] = {"Пол",        {{"паркет"    }, {"ковры"     }, {""          }, {""      }, {""}}};
    button[3] = {"Разное",     {{"ванные"    }, {"туалеты"   }, {"декор"     }, {""      }, {""}}};
    button[4] = {"Планировка", {{"планировка"}, {""          }, {""          }, {""      }, {""}}};

    //Координаты кнопок
    for (int i = 0;i < 5;i++){
        button[i].x = i * 200;
        button[i].y = 0;
    }

    while(!GetAsyncKeyState(VK_ESCAPE)){
        txBegin();
        txSetFillColor(TX_WHITE);
        txSetColor(TX_BLACK, 3);
        txClear();
        txTransparentBlt(txDC(), 100, 100, obj[23].width, obj[23].height, obj[23].pic, 0, 0, TX_WHITE);
        //Рисование кнопок
        for (int i = 0;i < 5;i++){

            if(txMouseX() >= button[i].x && txMouseX() <= button[i].x + 150 &&
               txMouseY() >= button[i].y && txMouseY() <= button[i].y + 50)
                txSetColor(TX_CYAN);

            button[i].draw();
            txSetColor(TX_BLACK,3);
        }

        //выбор раздела
        for (int i = 0; i < 5; i++){
            if (txMouseY() >= 0            && txMouseY() <= 50 &&
                txMouseX() >= button[i].x && txMouseX() <= button[i].x + 200 &&
                txMouseButtons() == 1)
            {
                chsnSection = i;
                chSection = button[i].text;
            }
        }

        sx = button[chsnSection].x;
        int sy = 50;
        if(chsnSection >= 0){
            int s = 125;
            for(int i = 0; i < 6; i++)
            {
                if(button[chsnSection].subButton[i].text == "")
                    s = s - 25;
            }
            txRectangle (sx, sy, sx + 200, sy + s);
        }

        //раздел подраздел запись
        for(int i = 0;i < 5;i++){
            if(txMouseX() >= sx       && txMouseY() >= sy + 5 + i * 20 &&
               txMouseX() <= sx + 200 && txMouseY() <= sy + 25 + i * 20)
                txSetColor(TX_CYAN);
            if(chsnSection >= 0)
                txDrawText (sx, sy + 5 + i * 20, sx + 200, sy + 25 + i * 20, button[chsnSection].subButton[i].text);

                txSetColor(TX_BLACK, 3);
            if(txMouseX() >= sx       && txMouseY() >= sy + 5 + i * 20 &&
               txMouseX() <= sx + 200 && txMouseY() <= sy + 25 + i * 20 &&
               txMouseButtons() == 1){
                chSection = button[chsnSection].text;
                chSubSection = button[chsnSection].subButton[i].text;
            }
        }

        //отмена выбора
        if (txMouseY() >= 160 && txMouseButtons() == 1){
            chsnSection = -1;
        }
        //картинки справа
        if (chsnSection >= 0){
            int z = 0;
            for (int i = 0;i < 36;i++){
                if (chSubSection == obj[i].section ){
                    if(obj[i].width > obj[i].height)
                        Win32::TransparentBlt  (txDC(), obj[i].x, 50 + z, 150, 150 * obj[i].height/obj[i].width, obj[i].pic, 0, 0, obj[i].width, obj[i].height, TX_WHITE);
                    else if (obj[i].width < obj[i].height)
                        Win32::TransparentBlt  (txDC(), obj[i].x, 50 + z, 150 * obj[i].height/obj[i].width, 150, obj[i].pic, 0, 0, obj[i].width, obj[i].height, TX_WHITE);

                    z = z + obj[i].height + 10;
                }
            }
        }

       /* if (click(x, y, x + 365, y + 116)){
            txTransparentBlt (txDC(), x, y, 365, 116, sofa[0], 0, 0, TX_WHITE);
            x = txMouseX() - 182;   y = txMouseY() - 58;
        }
        else{
            txTransparentBlt (txDC(), x, y, 365, 116, sofa[0], 0, 0, TX_WHITE);
        }  */

        txEnd();
        //txSleep(1);
    }
    //Удаление картинок
    for(int i = 0;i < 36;i++){
        txDeleteDC(obj[i].pic);
    }

    return 0;
}

