#include <graphics.h>
#include <bits/stdc++.h>

using namespace std;
int max_x;
int max_y;


void initial_screen() {
    int width = .13*max_y;
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    rectangle(0,0,max_x-1,width);
    floodfill(2,2,LIGHTGRAY);
}

int main(int argc, char const *argv[])
{
    max_x = GetSystemMetrics(SM_CXSCREEN);
    max_y = GetSystemMetrics(SM_CYSCREEN);
    initwindow(max_x,max_y,"My Paint",-3,-3);
    initial_screen();
    getch();
    closegraph();
    return 0;
}
