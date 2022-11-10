#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

int max_x,max_y;
bool valid(int x,int y) {
    return (x>= 0 && y >= 0 && x < max_x && y < max_y);
}

vector<int> dx = {0,0,-1,1};
vector<int> dy = {-1,1,0,0};
void floodfill(int x,int y,int oldcolor,int newcolor) {
   putpixel(x,y,newcolor);
   for(int i = 0; i < 4; i++) {
    int nx = x+dx[i],ny = y + dy[i];
    cout<<nx<<" "<<ny<<endl;
    if(valid(nx,ny) && getpixel(nx,ny)==oldcolor) {
        floodfill(nx,ny,oldcolor,newcolor);
    }
   }
}
 main(int argc, char const *argv[])
{
    max_x = GetSystemMetrics(SM_CXSCREEN);
    max_y = GetSystemMetrics(SM_CYSCREEN);
    initwindow(max_x,max_y,"My Paint",-3,-3);
    floodfill(10,10,BLACK,YELLOW);
    getch();
    closegraph();
    return 0;
}