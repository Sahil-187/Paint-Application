#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;
int max_x;
int max_y;
int colorbox_xi;
int colorbox_yi;
int colorbox_xf;
int colorbox_yf;
int toolbox_xi;
int toolbox_yi;
int toolbox_xf;
int toolbox_yf;
POINT Cursor;
int size = 10;

struct tool {
    pair<int, int> start;
    pair<int, int> end;
    int n;
    void insert(int a, int b) {
        start.first = a;
        start.second = b;
        end.first = a + 30;
        end.second = b + 30;
        rectangle(start.first, start.second, end.first, end.second);
    }
    void generate_image(int n) {
        this->n = n;
        if (n == 0) {
            int mid_x = (start.first + end.first) / 2;
            int mid_y = (start.second + end.second) / 2;
            setcolor(BLACK);
            circle(mid_x, mid_y, 10);
        } else if (n == 1) {
            int start_x = start.first + 5;
            int start_y = start.second + 5;
            int end_x = end.first - 5;
            int end_y = end.second - 5;
            setcolor(BLACK);
            line(start_x, start_y, end_x, end_y);
        } else if (n == 2) {
            int start_x = start.first + 5;
            int start_y = start.second + 7;
            int end_x = end.first - 5;
            int end_y = end.second - 7;
            setcolor(BLACK);
            rectangle(start_x, start_y, end_x, end_y);
        } else if (n == 3) {
            int mid_x = (start.first + end.first) / 2;
            int mid_y = (start.second + end.second) / 2;
            setcolor(BLACK);
            circle(mid_x, mid_y, 6);
            setfillstyle(SOLID_FILL, BLACK);
            floodfill(mid_x, mid_y, BLACK);
        } else if (n == 4) {
            int start_x = start.first + 5;
            int start_y = start.second + 7;
            int end_x = end.first - 5;
            int end_y = end.second - 7;
            setcolor(BLACK);
            rectangle(start_x, start_y, end_x, end_y);
            setfillstyle(SOLID_FILL, BLACK);
            floodfill(end_x - 1, end_y - 1, BLACK);
        } else if (n == 5) {
            int start_x = start.first + 5;
            int start_y = start.second + 7;
            int end_x = end.first - 5;
            int end_y = end.second - 7;
            setcolor(WHITE);
            rectangle(start_x, start_y, end_x, end_y);
            setfillstyle(SOLID_FILL, WHITE);
            floodfill(end_x - 1, end_y - 1, WHITE);
            setcolor(BLACK);
            rectangle(start_x, start_y, end_x, end_y);
        }
    }
};

vector<tool> t(6);

void drawToolBox() {
    int _x = 400;
    int width = 30;
    int j = 0;
    for (int i = 0; i < 3; i++) {
        t[i].insert(_x, 20);
        t[i].generate_image(i);
        t[i + 3].insert(_x, 50);
        t[i + 3].generate_image(i + 3);
        _x += width;
        j++;
    }
    toolbox_xi = t[0].start.first;
    toolbox_yi = t[0].start.second;
    toolbox_xf = t[2].end.first;
    toolbox_yf = t[2].end.second;
}

int selectedTool(int x, int y) {
    for (int i = 0; i < 3; i++) {
        if (x >= t[i].start.first && x <= t[i].end.first) {
            if (y >= t[i].start.second && y <= t[i].end.second) {
                return i;
            } else {
                return i + 3;
            }
        }
    }
    return 1;
}

bool insideToolBox(int x, int y) {
    return (x >= toolbox_xi && y >= toolbox_yi && x <= toolbox_xf && y <= toolbox_yf);
}

bool insideColorBox(int x, int y) {
    return (x >= colorbox_xi && y >= colorbox_yi && x <= colorbox_xf && y <= colorbox_yf);
}

bool insideDrawingArea(int x, int y) {
    return y > 100;
}

void drawRectangle(int x1, int y1, int x2, int y2) {
    int length = abs(x2 - x1), height = abs(y1 - y2);
    if (x1 <= x2) {
        if (y1 <= y2) {
            rectangle(x1, y1, x2, y2);
        } else {
            rectangle(x1, y1 - height, x2, y2 + height);
        }
    } else {
        if (y1 <= y2) {
            rectangle(x1 - length, y1, x2 + length, y2);
        } else {
            rectangle(x2, y2, x1, y1);
        }
    }
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
    drawToolBox();
}

int main() {
    max_x = GetSystemMetrics(SM_CXSCREEN);
    max_y = GetSystemMetrics(SM_CYSCREEN);
    initwindow(max_x, max_y, "My Paint", -3, 0);
    initial_screen();

    int x1 = -1, x2 = -1, y1 = -1, y2 = -1, choice = 4;
    while (true) {
        GetCursorPos(&Cursor);
        ScreenToClient(GetForegroundWindow(), &Cursor);
        // int x = Cursor.x, y = Cursor.y;

        if (ismouseclick(WM_LBUTTONDOWN)) {
            x1 = Cursor.x, y1 = Cursor.y;
            clearmouseclick(WM_LBUTTONDOWN);
            // cout << x1 << ", " << y1 << endl;

            if (!insideDrawingArea(x1, y1)) {
                // choice
                if (insideColorBox(x1, y1)) {
                    selectedColor(x1, y1);
                    clearmouseclick(WM_LBUTTONDOWN);
                }
                //  else if (true) {
                //     choice = 1;  // circle
                // } else if (true) {
                //     choice = 2;  // line
                // } else if (true) {
                //     choice = 3;  // rectangle
                // } else if (true) {
                //     choice = 4;  // brush
                // }
            }
        }

        switch (choice) {
        case 0: {
            break;
        }
        case 1: {
            // circle
            if (ismouseclick(WM_LBUTTONUP)) {
                x2 = Cursor.x, y2 = Cursor.y;
                clearmouseclick(WM_LBUTTONUP);

                int cx = (x1 + x2) / 2, cy = (y1 + y2) / 2;
                int r = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))) / 2;
                cout << "Circle [(" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ")]: (" << cx << ", " << cy << "), r = " << r << '\n';
                circle(cx, cy, r);
            }
            break;
        }
        case 2: {
            // line
            if (ismouseclick(WM_LBUTTONUP)) {
                x2 = Cursor.x, y2 = Cursor.y;
                clearmouseclick(WM_LBUTTONUP);

                cout << "Line [(" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ")]\n";
                line(x1, y1, x2, y2);
            }
            break;
        }
        case 3: {
            // rectangle
            if (ismouseclick(WM_LBUTTONUP)) {
                x2 = Cursor.x, y2 = Cursor.y;
                clearmouseclick(WM_LBUTTONUP);

                cout << "Rectangle [(" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ")]\n";
                drawRectangle(x1, y1, x2, y2);
            }
            break;
        }
        case 4: {
            // brush
            if (GetAsyncKeyState(VK_LBUTTON)) {
                x2 = Cursor.x, y2 = Cursor.y;
                int tsize = size;
                while (tsize--) {
                    circle(x2, y2, tsize);
                }
            }
            break;
        }
        case 5: {
            if (GetAsyncKeyState(VK_LBUTTON)) {
                floodfill(Cursor.x, Cursor.y, BLACK);
            }
            break;
        }
        }
    }

    closegraph();
    getch();
    return 0;
}