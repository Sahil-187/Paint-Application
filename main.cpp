#include <graphics.h>
#include <bits/stdc++.h>

using namespace std;
int max_x;
int max_y;
int colorbox_xi;
int colorbox_yi;
int colorbox_xf;
int colorbox_yf;

bool insideColorBox(int x,int y) {
    return (x >= colorbox_xi && y >= colorbox_yi && x <= colorbox_xf && y <= colorbox_yf);
}
void SelectedColorBox(int n)
{
    setfillstyle(SOLID_FILL, n);
    setcolor(n);
    rectangle(20, 20, 80, 80);
    floodfill(21, 21, n);
}

struct color
{
    pair<int, int> start;
    pair<int, int> end;
    int n;
    void insert(int a, int b)
    {
        start.first = a;
        start.second = b;
        end.first = a + 30;
        end.second = b + 30;
    }
    void fill(int n)
    {
        this->n = n;
        setcolor(n);
        setfillstyle(SOLID_FILL, n);
        rectangle(start.first, start.second, end.first, end.second);
        floodfill(start.first + 1, start.second + 1, n);
        setcolor(BLACK);
        rectangle(start.first, start.second, end.first, end.second);
    }
};
vector<color> v(16);
void drawColorBox()
{
    floodfill(33, 53, BLACK);
    int s1 = 90;
    int s2 = 90;
    int width = 30;
    vector<color> v(16);
    int j = 0;
    for (int i = 0; i < 8; i++)
    {
        v[i].insert(s1, 20);
        v[i].fill(j++);
        v[i + 8].insert(s2, 50);
        v[i + 8].fill(j++);
        s1 += width;
        s2 += width;
    }
    colorbox_xi = v[0].start.first;
    colorbox_yi = v[0].start.second;
    colorbox_xf = v[7].end.first;
    colorbox_yf = v[7].end.second;
}

int selectedColor(int x, int y)
{
    for (int i = 0; i < 8; i++)
    {
        if (x >= v[i].start.first && x <= v[i].end.first)
        {
            if (y >= v[i].start.second && y <= v[i].end.second)
            {
                SelectedColorBox(i);
                return i;
            }
            else
                {
                    SelectedColorBox(i + 8);
                    return i + 8;
                }
        }
    }
    
    SelectedColorBox(0);
    return 0;
}

void initial_screen()
{
    int width = 100;
    setcolor(LIGHTGRAY);
    rectangle(0, 0, max_x - 1, width);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    floodfill(1, 1, LIGHTGRAY);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(0, width, max_x - 1, max_y - 27);
    floodfill(2, width + 5, WHITE);
    setcolor(BLACK);
    rectangle(20, 20, 80, 80);
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(21, 21, BLACK);
    SelectedColorBox(BLACK);
    drawColorBox();
}

int main(int argc, char const *argv[])
{
    max_x = GetSystemMetrics(SM_CXSCREEN);
    max_y = GetSystemMetrics(SM_CYSCREEN);
    initwindow(max_x, max_y, "My Paint", -3, 0);
    initial_screen();
    getch();
    while(true) {
        int x,y;
        
        x = mousex();
        y = mousey();
        cout<<x<<" "<<y<<endl;
        if(insideColorBox(x,y)) {
            selectedColor(x,y);
        }
    }
    closegraph();
    return 0;
}
