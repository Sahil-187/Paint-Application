#include <graphics.h>
#include <bits/stdc++.h>

using namespace std;
int max_x;
int max_y;

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
void initial_screen() {
    int width = .13*max_y;
  //line top
  line(0,0,max_x,0);
  //line left
  line(0,0,0,width);
  //line buttom
  line(0,width,max_x-1,width);
  //line right 
  line(max_x-1,0,max_x-1,width);
  //colour of top_box
  floodfill(1,1,YELLOW);
}

int main(int argc, char const *argv[])
{
    max_x = GetSystemMetrics(SM_CXSCREEN);
    max_y = GetSystemMetrics(SM_CYSCREEN);
    max_x -=100;
    max_y-=100;
    initwindow(max_x,max_y,"My Paint",-3,-3);
    initial_screen();
    getch();
    closegraph();
    return 0;
}
