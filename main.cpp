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
int size = 20;
// int curColor = BLACK;

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
    toolbox_xf = t[5].end.first;
    toolbox_yf = t[5].end.second;
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

    setcolor(BLACK);
    if (n == BLACK) setcolor(WHITE);
    rectangle(20, 20, 80, 80);

    setcolor(n);
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
    int _x = 100;
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

    int old = getcolor();
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(8, VERT_DIR, 1);
    outtextxy(390, 22, (char *)"TOOLS");
    line(0, 98, max_x, 98);
    setcolor(old);

    SelectedColorBox(BLACK);
    drawColorBox();
    drawToolBox();
}

void initial_drawing_area() {
    int old = getcolor();
    int width = 100;
    // int col = COLOR(163, 167, 176);
    int col = WHITE;
    setcolor(col);
    setfillstyle(SOLID_FILL, col);
    rectangle(0, width, max_x - 1, max_y - 1);
    floodfill(2, width + 5, col);
    setcolor(old);
}

void display_buttons() {
    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    settextstyle(8, HORIZ_DIR, 1);
    outtextxy(1300, 35, (char *)("SIZE: " + to_string(size)).c_str());
    rectangle(1220, 45, 1245, 75);
    floodfill(1221, 46, BLACK);
    line(1225, 60, 1240, 60);
    line(1232, 53, 1232, 67);
    rectangle(1265, 45, 1290, 75);
    floodfill(1266, 46, BLACK);
    line(1270, 60, 1285, 60);

    setbkcolor(WHITE);
    rectangle(560, 20, 620, 80);
    floodfill(561, 21, BLACK);
    outtextxy(617, 60, (char *)("CLEAR"));
    rectangle(640, 20, 700, 80);
    floodfill(641, 21, BLACK);
    outtextxy(692, 60, (char *)("SAVE"));
    rectangle(720, 20, 780, 80);
    floodfill(721, 21, BLACK);
    outtextxy(767, 60, (char *)("CAR"));
}

void increase_size() {
    size += 10;
    initial_screen();
    display_buttons();
}

void decrease_size() {
    if (size > 10) size -= 10;
    initial_screen();
    display_buttons();
}

int insideButtons(int x, int y) {
    if (x >= 1220 && x <= 1245 && y >= 45 && y <= 75) return 1;
    if (x >= 1265 && x <= 1290 && y >= 45 && y <= 75) return 2;
    if (x >= 560 && x <= 620 && y >= 20 && y <= 80) return 3;
    if (x >= 640 && x <= 700 && y >= 20 && y <= 80) return 4;
    if (x >= 720 && x <= 780 && y >= 20 && y <= 80) return 5;
    return 0;
}

void drawCar(int x, int y) {
    if (x < 0 || x > max_x - 176 || y <= 100 || y > max_y - 145) return;
    int old = getcolor();
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    circle(x + 47, y + 95, 25);
    circle(x + 129, y + 95, 25);
    floodfill(x + 47, y + 95, BLACK);
    floodfill(x + 129, y + 95, BLACK);
    rectangle(x, y + 40, x + 176, y + 95);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(x + 1, y + 41, BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    setcolor(BLACK);
    line(x + 20, y + 40, x + 40, y);
    line(x + 24, y + 40, x + 44, y + 4);
    line(x + 156, y + 40, x + 136, y);
    line(x + 152, y + 40, x + 132, y + 4);
    line(x + 40, y, x + 136, y);
    line(x + 44, y + 4, x + 86, y + 4);
    line(x + 90, y + 4, x + 132, y + 4);
    line(x + 86, y + 4, x + 86, y + 40);
    line(x + 90, y + 4, x + 90, y + 40);
    floodfill(x + 21, y + 39, BLACK);
    setcolor(old);
}

int main() {
    max_x = GetSystemMetrics(SM_CXSCREEN);
    max_y = GetSystemMetrics(SM_CYSCREEN);
    initwindow(max_x, max_y, "Paint - By Akshat, Sahil & Tanveer", -3, 0);
    initial_screen();
    initial_drawing_area();
    display_buttons();

    int x1 = -1, x2 = -1, y1 = -1, y2 = -1, choice = 4;
    while (true) {
        GetCursorPos(&Cursor);
        ScreenToClient(GetForegroundWindow(), &Cursor);

        if (ismouseclick(WM_LBUTTONDOWN)) {
            x1 = Cursor.x, y1 = Cursor.y;
            clearmouseclick(WM_LBUTTONDOWN);

            if (!insideDrawingArea(x1, y1)) {
                // choice
                if (insideColorBox(x1, y1)) {
                    selectedColor(x1, y1);
                    clearmouseclick(WM_LBUTTONDOWN);
                } else if (insideToolBox(x1, y1)) {
                    choice = selectedTool(x1, y1) + 1;
                    initial_screen();
                } else if (insideButtons(x1, y1) == 1) {
                    increase_size();
                } else if (insideButtons(x1, y1) == 2) {
                    decrease_size();
                } else if (insideButtons(x1, y1) == 3) {
                    cleardevice();
                    initial_screen();
                    initial_drawing_area();
                    display_buttons();
                } else if (insideButtons(x1, y1) == 4) {
                    writeimagefile((char *)("save.jpg"), 0, 100, max_x - 1, max_y - 1);
                    delay(500);
                    cleardevice();
                    initial_screen();
                    initial_drawing_area();
                    display_buttons();
                } else if (insideButtons(x1, y1) == 5) {
                    choice = 7;
                }
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
                if (cy <= 100) continue;
                if (cy - r <= 100) r = cy - 100;
                cout << "Circle [(" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ")]: (" << cx << ", " << cy << "), r = " << r << '\n';
                circle(cx, cy, r);
                // circle(cx, cy + 1, r);
            }
            break;
        }
        case 2: {
            // line
            if (ismouseclick(WM_LBUTTONUP)) {
                x2 = Cursor.x, y2 = Cursor.y;
                clearmouseclick(WM_LBUTTONUP);

                cout << "Line [(" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ")]\n";
                line(x1, max(y1, 101), x2, max(y2, 101));
                // line(x1, max(y1 + 1, 101), x2, max(y2 + 1, 101));
            }
            break;
        }
        case 3: {
            // rectangle
            if (ismouseclick(WM_LBUTTONUP)) {
                x2 = Cursor.x, y2 = Cursor.y;
                clearmouseclick(WM_LBUTTONUP);

                cout << "Rectangle [(" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ")]\n";
                drawRectangle(x1, max(y1, 101), x2, max(y2, 101));
                // drawRectangle(x1, max(y1 + 1, 101), x2, max(y2 + 1, 101));
            }
            break;
        }
        case 4: {
            // brush
            if (GetAsyncKeyState(VK_LBUTTON)) {
                x2 = Cursor.x, y2 = Cursor.y;
                int tsize = size / 2;
                if (y2 - tsize <= 100) continue;
                while (tsize--) {
                    circle(x2, y2, tsize);
                }
            }
            break;
        }
        case 5: {
            // flood fill
            if (GetAsyncKeyState(VK_LBUTTON)) {
                if (Cursor.y <= 100) continue;
                floodfill(Cursor.x, Cursor.y, BLACK);  // no floodfill on black
            }
            break;
        }
        case 6: {
            // eraser
            int old = getcolor();
            setcolor(WHITE);
            if (GetAsyncKeyState(VK_LBUTTON)) {
                x2 = Cursor.x, y2 = Cursor.y;
                int tsize = size;
                if (y2 - tsize / 2 < 100) continue;
                while (tsize--) {
                    rectangle(x2 - tsize / 2, y2 - tsize / 2, x2 + tsize / 2, y2 + tsize / 2);
                }
            }
            setcolor(old);
            break;
        }
        case 7: {
            // car

            if (ismouseclick(WM_LBUTTONUP)) {
                x2 = Cursor.x, y2 = Cursor.y;
                clearmouseclick(WM_LBUTTONUP);
                if (x2 == x1 && y2 == y1) {
                    drawCar(x1 - 88, y1 - 40);
                    break;
                }

                initial_drawing_area();
                setcolor(COLOR(163, 167, 176));
                line(0, 98, max_x, 98);

                int delta_x = x2 - x1, delta_y = y2 - y1;
                int steps = max(abs(delta_x), abs(delta_y));
                float dx = delta_x / (float)steps;
                float dy = delta_y / (float)steps;
                float x = x1, y = y1;

                for (int i = 0; i <= steps; ++i) {
                    drawCar(round(x) - 88, round(y) - 40);
                    delay(1);  // to see line being drawn
                    x += dx;
                    y += dy;

                    setfillstyle(SOLID_FILL, WHITE);
                    rectangle(0, 100, max_x - 1, max_y - 1);
                    floodfill(2, 105, COLOR(163, 167, 176));
                }
                drawCar(round(x) - 88, round(y) - 40);
            }
            break;
        }
        }
    }

    closegraph();
    getch();
    return 0;
}