/*
 * Tetris Console
 * First Issue: 2021/02/04
 * Copyright: Ellias Kiri Stuart
 * Licence: MIT
 * GitHub: https://github.com/novaELLIAS/TetrisConsole
 */

#pragma GCC optimize ("Ofast", 3)
#pragma GCC target ("sse3","sse2","sse")
#pragma GCC target ("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target ("f16c")

#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

#define a1 0
#define a2 1

#define b1 2

#define c1 3
#define c2 4
#define c3 5
#define c4 6

#define d1 7
#define d2 8
#define d3 9
#define d4 10

#define e1 11
#define e2 12

#define f1 13
#define f2 14

#define g1 15

#define h1 16
#define h2 17
#define h3 18
#define h4 19

#define k1 20
#define k2 21

#define m1 22
#define m2 23

#define PRE 224
#define UP  72
#define LT  75
#define RT  77
#define DW  80
#define SP  32

#define MP(x,y) make_pair(x,y)

/*
const int dMapOrigin[24][9] = {
    {0, 0, 1, 0, 2, 0, 3, 0, 4}, {0, 0, 0, 1, 0, 2, 0, 3, 1},
    {0, 0, 1, 0, 0, 1, 1, 1, 2},
    {0, 0, 1, 0, 1, 1, 1, 2, 2}, {0, 1, 1, 1, 2, 0, 2, 1, 3}, {0, 0, 0, 1, 0, 2, 1, 2, 2}, {0, 0, 0, 1, 1, 0, 2, 0, 3},
    {1, 0, 1, 1, 1, 2, 0, 2, 2}, {0, 0, 0, 1, 1, 1, 2, 1, 3}, {0, 0, 0, 1, 0, 2, 1, 0, 2}, {0, 0, 1, 0, 2, 0, 2, 1, 3},
    {0, 0, 0, 1, 1, 1, 1, 2, 2}, {0, 1, 1, 0, 1, 1, 2, 0, 3},
    {0, 1, 0, 2, 1, 0, 1, 1, 2}, {0, 0, 1, 0, 1, 1, 2, 1, 3},
    {0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 0, 0, 0, 2}, {0, 0, 0, 0, 1, 0, 1, 1, 2}, {0, 0, 0, 0, 1, 0, 1,-1, 2}, {0, 0, 0, 0, 0,-1, 1, 0, 2},
    {0, 0, 0, 0, 0, 1, 0, 2, 1}, {0, 0, 0, 0, 1, 0, 2, 0, 3},
    {0, 0, 0, 0, 1, 0, 1, 0, 2}, {0, 0, 0, 0, 0, 1, 0, 1, 1}
};
*/

int height[24] = {4, 1, 2, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 1, 2, 2, 2, 2, 1, 3, 2, 1};

const vector <pair<int, int> > dMap[24] = {

    {MP(0, 0), MP(1, 0), MP(2, 0), MP(3, 0)},
    {MP(0, 0), MP(0, 1), MP(0, 2), MP(0, 3)},

    {MP(0, 0), MP(1, 0), MP(0, 1), MP(1, 1)},

    {MP(0, 0), MP(1, 0), MP(1, 1), MP(1, 2)},
    {MP(0, 1), MP(1, 1), MP(2, 0), MP(2, 1)},
    {MP(0, 0), MP(0, 1), MP(0, 2), MP(1, 2)},
    {MP(0, 0), MP(0, 1), MP(1, 0), MP(2, 0)},

    {MP(1, 0), MP(1, 1), MP(1, 2), MP(0, 2)},
    {MP(0, 0), MP(0, 1), MP(1, 1), MP(2, 1)},
    {MP(0, 0), MP(0, 1), MP(0, 2), MP(1, 0)},
    {MP(0, 0), MP(1, 0), MP(2, 0), MP(2, 1)},

    {MP(0, 0), MP(0, 1), MP(1, 1), MP(1, 2)},
    {MP(0, 1), MP(1, 0), MP(1, 1), MP(2, 0)},

    {MP(0, 1), MP(0, 2), MP(1, 0), MP(1, 1)},
    {MP(0, 0), MP(1, 0), MP(1, 1), MP(2, 1)},

    {MP(0, 0)},

    {MP(0, 0), MP(0, 1), MP(1, 0)},
    {MP(0, 0), MP(1, 0), MP(1, 1)},
    {MP(0, 0), MP(1, 0), MP(1,-1)},
    {MP(0, 0), MP(0,-1), MP(1, 0)},

    {MP(0, 0), MP(0, 1), MP(0, 2)},
    {MP(0, 0), MP(1, 0), MP(2, 0)},

    {MP(0, 0), MP(1, 0)},
    {MP(0, 0), MP(0, 1)}
};

#define maxl 24
#define maxh 26

unsigned int seed = 19260817;

inline int rotate (int);
#define setCursor(x,y); {COORD tmpSC; tmpSC.X=x, tmpSC.Y=y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmpSC);}
inline void isCursorDisplay(bool);
inline void setColor (int);

inline int realRand ();
inline int qpow (int, int);

inline void drawDataInt (int, int);
inline void drawScore ();
inline void drawLogo();

//#define drawCntDn(); {setColor(3); setCursor(30, 15); cout<<setw(16)<<setiosflags(ios::internal)<<cntDown;}
//#define drawScore(); {setColor(3); setCursor(30, 19); printf("%m16d", score);}
//#define drawInter(); {setColor(3); setCursor(30, 23); printf("%m16d", 301-interval);}
#define drawCntDn(); {drawDataInt(cntDown, 15);}
#define drawInter(); {drawDataInt(301-interval, 23);}
#define drawData();  {drawScore(); drawInter(); drawCntDn();}
#define drawBlock() printf("■")
#define drawSpace() printf("  ")
inline void drawWelcome ();
inline void drawUI ();
inline void drawGameOver();
inline void drawYouWin();
inline void drawTetris (int, int, int, bool);
inline void drawPrediction (int, bool);

#define placeLegal() ((~tmpx)&&(tmpx<25)&&(~tmpy)&&(tmpy<13)&&!vis[tmpx][tmpy])
inline bool placeJudge (int, int, int);

bool vis[28][16];

int top = 25, nowx, nowy = 5, steins, kurisu, interval=300, cntDown=1;
long long score, chBase = 1ll;

signed main () {
    drawWelcome();
    drawUI();
    drawLogo();

    srand(time(NULL));
    do steins = (rand() + 24) % 24;
    while (steins>=11 && steins<=14);
    kurisu = (rand() + 24) % 24;

    drawTetris(kurisu, 5, 16, false);
    drawTetris(steins, nowx, nowy, false);
    drawPrediction(steins, false);

    register int timer = 0;

    isCursorDisplay(false);
    drawData();

    while (true) {
        if (timer>=interval) {
            timer = 0; score += log(cntDown); cntDown = 1; drawData();
            DROPTEST:
            if (placeJudge(steins, nowx + 1, nowy)) {
                drawTetris(steins, nowx ++, nowy, true);
                drawTetris(steins, nowx, nowy, false);
                if (!placeJudge(steins, nowx + 1, nowy)) goto BLOCKFREEZE;
            } else {
                BLOCKFREEZE:
                register int tmpx, tmpy;
                auto iter = dMap[steins].cbegin();
                for (; iter != dMap[steins].cend(); ++ iter) {
                    tmpx = nowx + iter->first;
                    tmpy = nowy + iter->second;
                    setCursor((tmpy + 1) << 1, tmpx + 1);
                    setColor(0); drawBlock();
                    vis[tmpx][tmpy] = true;
                } top = top > nowx ? nowx : top;

                register bool tflag = false, flag; register int clrCnt = 0;
                for (register int i=nowx; i < nowx+height[steins]; ++ i, flag=true) {
                    for (register int j=0; j^13; ++ j) {
                        if (!vis[i][j]) {
                            if (clrCnt) {
                                score += (300-(int)(interval*0.85)) << clrCnt;
                                drawScore();
                            } flag = clrCnt = 0; break;
                        }
                    } if (flag) {
                        clrCnt += (tflag = true);
                        for (register int j = i; j >= top; -- j) {
                            for (register int k = 0; k ^ 13; ++ k) {
                                vis[j][k] = vis[j - 1][k];
                                setCursor((k + 1) << 1, j + 1);
                                if (vis[j][k]) drawBlock();
                                else drawSpace();
                            }
                        }
                    }
                } if (tflag) {
                    interval = (int)(interval * 0.85);
                    if (clrCnt) score += (300 - interval) << clrCnt;
                    drawData(); drawLogo();
                }

                steins = kurisu; kurisu = (rand() + 24) % 24;
                drawTetris(steins, 5, 16, true);
                drawTetris(kurisu, 5, 16, false);
                nowx = 0, nowy = 5;
                drawPrediction(steins, false);
                drawTetris(steins, nowx, nowy, false);

                if (!placeJudge(steins, nowx, nowy)) drawGameOver();
            }
        }

        register int key;
        if(_kbhit()) if((key=_getch()) ^ PRE) {
            if (!(key^SP)&&placeJudge(kurisu,nowx,nowy)&&(steins^kurisu)) {
                drawTetris(steins, nowx, nowy, true);
                drawTetris(kurisu, 5, 16, true);
                steins^=kurisu^=steins^=kurisu;
                drawPrediction(steins, true);
                drawTetris(steins, nowx, nowy, false);
                drawTetris(kurisu, 5, 16, false);
                score += log(cntDown) - (chBase<<=1); cntDown = 1;
                interval = (int)(interval * 0.99); drawData();
            }
        } else {
            key = _getch();
            switch(key) {
                case UP:
                    score += log(cntDown); cntDown = 1; drawData();
                    if (placeJudge(rotate(steins), nowx, nowy)) {
                        drawTetris(steins, nowx, nowy, true);
                        steins = rotate(steins);
                        drawPrediction(steins, true);
                        drawTetris(steins, nowx, nowy, false);
                    } break;
                case LT:
                    score += log(cntDown); cntDown = 1; drawData();
                    if (placeJudge(steins, nowx, nowy-1)) {
                        drawTetris(steins, nowx, nowy --, true);
                        drawPrediction(steins, true);
                        drawTetris(steins, nowx, nowy, false);
                    } break;
                case RT:
                    score += log(cntDown); cntDown = 1; drawData();
                    if (placeJudge(steins, nowx, nowy+1)) {
                        drawTetris(steins, nowx, nowy ++, true);
                        drawPrediction(steins, true);
                        drawTetris(steins, nowx, nowy, false);
                    } break;
                case DW:
                    if (placeJudge(steins, nowx+1, nowy)) {
                        drawTetris(steins, nowx ++, nowy, true);
                        drawTetris(steins, nowx, nowy, false);
                        ++ cntDown; drawData();
                        goto DROPTEST;
                    } goto BLOCKFREEZE; break;
            }
        } Sleep(1); ++ timer;
    } system("pause"); return 0;
}

inline bool placeJudge (int name, int x, int y) {
    register int tmpx, tmpy;
    auto iter = dMap[name].begin();
    for (; iter != dMap[name].end(); ++ iter) {
        tmpx = x + iter->first;
        tmpy = y + iter->second;
        if(!placeLegal()) return false;
    } return true;
}

inline void drawDataInt (int num, int y) {
    setCursor(30, y);
    for (register int i=0; i^16; ++ i) putchar(' ');
    register int cnt = 0, a = num;
    setColor(3); setCursor(30, y);
    while (a /= 10) ++ cnt;
    cnt = (16-cnt) >> 1;
    while (cnt --) putchar(' ');
    printf("%d", num);
}

long long preScore;

inline void drawScore () {
    setCursor(30, 19);
    printf("                ");
    static char cMap[4] = {' ', 'K', 'M', 'G'};
    register int cnt = 0, cPos = 0;
    register long long a = score;
    register bool minusFlag = false;
    if (a<0ll) a = -a, minusFlag = true, ++ cnt;
    setColor(3); setCursor(30, 19);
    while (a /= 10ll) ++ cnt; a = score;
    while (cnt>8) {
        cnt -= 2, a /= 1000, ++ cPos;
        if (cPos > 3) minusFlag? drawGameOver():drawYouWin();
    } cnt = (16-cnt) >> 1;
    while (cnt --) putchar(' ');
    printf("%lld", a);
    putchar(cMap[cPos]);
}

int preName = -1, prex, prey;

inline void drawPrediction (int name, bool isClr) {
    register int tmpx, tmpy;
    auto iter = dMap[preName].begin();
    if (isClr) for (; iter != dMap[preName].end(); ++ iter) {
        tmpx = prex + iter->first;
        tmpy = prey + iter->second;
        setCursor((tmpy+1)<<1, tmpx+1);
        drawSpace();
    }

    register int x = nowx - 1, y = nowy, cnt = 0;
    while (placeJudge(name, ++ x, y)); x --;

    iter = dMap[name].begin();
    for (; iter != dMap[name].end(); ++ iter, ++ cnt) {
        tmpx = x + iter->first;
        tmpy = y + iter->second;
        setCursor((tmpy+1)<<1, tmpx+1);
        setColor(cnt + 1); printf("□");
    } prex = x, prey = y, preName = name;
}

inline void drawTetris (int name, int x, int y, bool re) {
    register int tmpx, tmpy, cnt = 0;
    auto iter = dMap[name].begin();
    for (; iter != dMap[name].end(); ++ iter, ++ cnt) {
        tmpx = x + iter->first;
        tmpy = y + iter->second;
        setCursor((tmpy+1)<<1, tmpx+1);
        if (re) drawSpace();
        else {setColor(cnt + 1); drawBlock();}
    }
}

inline void drawYouWin () {
    system("cls");
    isCursorDisplay(true);
    puts("YouWin!");
    printf("Your score is: %d.\n", score);
    exit(0);
}

inline void drawGameOver () {
    system("cls");
    isCursorDisplay(true);
    puts("Game Over");
    printf("Your score is: %d.\n", score);
    exit(0);
}

inline void drawWelcome () {
    system("cls");
    puts("Welcome to tetris!");
    puts("Code By Ellias Kiri Stuart @ 2021/03/24");
    //puts("Press any key to start...");
    system("pause");
    system("cls");
}

inline void drawUI () {
    setColor(3);
    for (register int i=0; i^15; ++ i) {
        setCursor(i<<1, 0); printf("##"); //drawBlock();
        setCursor(i<<1, maxh); printf("##"); //drawBlock();
    } for (register int i=15; i^23; ++ i) {
        setCursor(i<<1, 0); printf("=");
        setCursor(i<<1, maxh); printf("=");
    } for (register int i=0; i^maxh; ++ i) {
        setCursor(0, i);       printf("##"); //drawBlock();
        setCursor(maxl+4, i);  printf("##"); //drawBlock();
        //setCursor(maxl+22, i); printf("##"); //drawBlock();
        setCursor(maxl+22, i); printf("￤");
    }

    setCursor(0, 0); printf("□");
    setCursor(0, maxh); printf("□");
    setCursor(14<<1, 0); printf("□≡≡");
    setCursor(14<<1, maxh); printf("□≡≡");
    setCursor((23<<1)-2, 0); putchar('-');
    setCursor((23<<1)-2, maxh); putchar('-');
    setCursor(23<<1, 0); printf("◇");
    setCursor(23<<1, maxh); printf("◇");

    drawScore(); drawInter();
    setColor(3); setCursor(36, 2);  printf("NEXT");
    setColor(3); setCursor(32, 13); printf("Down Counter");
    setColor(3); setCursor(35, 17); printf("nScore");
    setColor(3); setCursor(35, 21); printf("nSpeed");
}

inline int rotate (int name) {
    switch (name) {
        case a1: return a2;
        case a2: return a1;

        case b1: return b1;

        case c1: return c2;
        case c2: return c3;
        case c3: return c4;
        case c4: return c1;

        case d1: return d2;
        case d2: return d3;
        case d3: return d4;
        case d4: return d1;

        case e1: return e2;
        case e2: return e1;

        case f1: return f2;
        case f2: return f1;

        case g1: return g1;

        case h1: return h2;
        case h2: return h3;
        case h3: return h4;
        case h4: return h1;

        case k1: return k2;
        case k2: return k1;

        case m1: return m2;
        case m2: return m1;
    } return -1;
}

inline void setColor (int color) {
    switch (color % 5) {
        case 0: color = 0x08; break;
        case 1: color = 0x0C; break;
        case 2: color = 0x0D; break;
        case 3: color = 0x0E; break;
        case 4: color = 0x0A; break;
    } SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline int realRand () {
    seed^=seed<<17, seed^=seed>>5, seed^=seed<<23;
    return seed;
}

inline void isCursorDisplay(bool flag) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = flag;
    SetConsoleCursorInfo(handle, &CursorInfo);
}

inline int qpow (int a, int t) {
    register int base = a, ret = 1;
    while (t) {
        if (t&1) ret = ret * base;
        base = base * base, t >>= 1;
    } return ret;
}

const vector<int> logoMap[5] = {
        {0, 17, 18, 20},
        {1, 2, 5, 11, 14, 17, 19, 21},
        {1, 2, 5, 6, 7, 11, 14, 15, 16, 19, 21, 22, 23, 24},
        {1, 2, 5, 11, 14, 16, 19, 24},
        {0, 0, 1, 3, 4, 9, 10, 12, 13, 15, 16, 18}
};

#define logoStartX (28<<1)
#define logoStartY 3

inline void drawLogo () {
    register int colorOffset = rand();
    for (register int i=0; i^5; ++ i) {
        auto iter = logoMap[i].begin();
        register bool flag = *iter;
        if (!flag) {
            setCursor(logoStartX, logoStartY+i);
            for (register int j=0; j^25; ++ j) {
                setColor(i+j+colorOffset); printf(rand()%3? "□":"■");
            }
        } for (++ iter; iter != logoMap[i].end(); ++ iter) {
            setCursor(logoStartX+(*iter<<1), logoStartY+i);
            setColor(i+((*iter)<<1)+colorOffset);
            printf(flag? (rand()%3? "□":"■"):"  ");
        }
    }
}