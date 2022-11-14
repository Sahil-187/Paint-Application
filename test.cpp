#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;
int max_x;
int max_y;
int colorbox_xi;
int colorbox_yi;
int colorbox_xf;
int colorbox_yf;
POINT Cursor;

bool insideColorBox(int x, int y) {
    return (x >= colorbox_xi && y >= colorbox_yi && x <= colorbox_xf && y <= colorbox_yf);
}

bool insideDrawingArea(int x, int y) {
    return y > 100;
}

void SelectedColorBox(int n) {
    setfillstyle(SOLID_FILL, n);
    setcolor(n);
    rectangle(20, 20, 80, 80);
    floodfill(21, 21, n);
}

struct color {
    pair<int, int> start;
    pair<int, int> end;
    int n;
    void insert(int a, int b) {
        start.first = a;
        start.second = b;
        end.first = a + 30;
        end.second = b + 30;
    }
    void fill(int n) {
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
void drawColorBox() {
    int _x = 90;
    int width = 30;
    int j = 0;
    for (int i = 0; i < 8; i++) {
        v[i].insert(_x, 20);
        v[i].fill(j);
        v[i + 8].insert(_x, 50);
        v[i + 8].fill(j + 8);
        _x += width;
        j++;
    }
    colorbox_xi = v[0].start.first;
    colorbox_yi = v[0].start.second;
    colorbox_xf = v[15].end.first;
    colorbox_yf = v[15].end.second;
}

int selectedColor(int x, int y) {
    for (int i = 0; i < 8; i++) {
        if (x >= v[i].start.first && x <= v[i].end.first) {
            if (y >= v[i].start.second && y <= v[i].end.second) {
                // cout << i << endl;
                SelectedColorBox(i);
                return i;
            } else {
                SelectedColorBox(i + 8);
                return i + 8;
            }
        }
    }

    SelectedColorBox(0);
    return 0;
}

void initial_screen() {
    int width = 100;
    setcolor(LIGHTGRAY);
    rectangle(0, 0, max_x - 1, width);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    floodfill(1, 1, LIGHTGRAY);

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(0, width, max_x - 1, max_y - 27);
    floodfill(2, width + 5, WHITE);

    SelectedColorBox(BLACK);
    drawColorBox();
}

int main() {
    max_x = GetSystemMetrics(SM_CXSCREEN);
    max_y = GetSystemMetrics(SM_CYSCREEN);
    initwindow(max_x, max_y, "My Paint", -3, 0);
    initial_screen();

    int x1 = -1, x2 = -1, y1 = -1, y2 = -1, choice = 1;
    while (true) {
        GetCursorPos(&Cursor);
        ScreenToClient(GetForegroundWindow(), &Cursor);
        // int x = Cursor.x, y = Cursor.y;

        if (ismouseclick(WM_LBUTTONDOWN)) {
            x1 = Cursor.x, y1 = Cursor.y;
            cout << x1 << ", " << y1 << endl;
            clearmouseclick(WM_LBUTTONDOWN);

            if (!insideDrawingArea(x1, y1)) {
                cout << "Above drawing area\n";
                // choice
                if (insideColorBox(x1, y1)) {
                    selectedColor(x1, y1);
                } else if (true) {
                    choice = 1;  // circle
                } else if (true) {
                    choice = 2;  // line
                } else if (true) {
                    choice = 3;
                }
            }
        }

        switch (choice) {
        // circle
        case 0: {
            break;
        }
        case 1: {
            cout << "case 1\n";

            if (ismouseclick(WM_LBUTTONUP)) {
                cout << "inside click?\n";
                x2 = Cursor.x, y2 = Cursor.y;
                cout << x2 << ", " << y2 << endl;
                clearmouseclick(WM_LBUTTONUP);

                int cx = (x1 + x2) / 2, cy = (y1 + y2) / 2;
                int r = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))) / 2;
                cout << "Circle: (" << cx << ", " << cy << "), r = " << r << '\n';
                circle(cx, cy, r);
            }
            break;
        }
        }
    }

    closegraph();
    getch();
    return 0;
}
