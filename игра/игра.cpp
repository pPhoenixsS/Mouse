#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "colors.h"

using namespace std;

// размеры игрового поля
int WIDTH = 10;
int HEIGHT = 5;

// размеры игрового поля (уровень 1)
int WIDTH1 = 10;
int HEIGHT1 = 5;

// размеры игрового поля (уровень 2)
int WIDTH2 = 20;
int HEIGHT2 = 12;

// размеры игрового поля (уровень 3)
int WIDTH3 = 50;
int HEIGHT3 = 24;

// координаты мышеловки
int xMouseDead = 2;
int yMouseDead = 2;

// координаты сырчика
int xCheese = 4;
int yCheese = 4;

// перемещение курсора в заданную позицию
void setCursorPosition(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// отрисовка мышки
void drawMouse(int &xMouse, int &yMouse)
{
    setCursorPosition(xMouse, yMouse);
    cout << "M";
}

// убираем персонажа :(
void clearCharacter(int& x, int& y)
{
    setCursorPosition(x, y);
    cout << " ";
}

// отрисовка кошки
void drawCat(int& xCat, int& yCat)
{
    setCursorPosition(xCat, yCat);
    cout << "C";
}

// функция для отрисовки игрового поля
void drawField()
{
    setCursorPosition(0, 0);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 or i == HEIGHT - 1 or j == 0 or j == WIDTH - 1) {
                cout << "#"; // отрисовка границы
            }
            else {
                cout << " "; // отрисовка пустой клетки
            }
        }
        cout << endl;
    }
}

// мышь бегит :)
void runMouse(int&xMouse, int&yMouse)
{
    char key = _getch(); // считывание клавиши

    clearCharacter(xMouse, yMouse); // очищаем старую позицию мыши

    // обработка нажатия клавиш
    switch (key)
    {
    case 'a':
        if (xMouse > 1) {
            xMouse--;
        }
        break;
    case 'd':
        if (xMouse < WIDTH - 2) {
            xMouse++;
        }
        break;
    case 'w':
        if (yMouse > 1) {
            yMouse--;
        }
        break;
    case 's':
        if (yMouse < HEIGHT - 2) {
            yMouse++;
        }
        break;
    }

    drawMouse(xMouse, yMouse); // отрисовываем новую позицию мыши
}

// кисик бегит :)
void runCat(int& xCat, int& yCat, int& xMouse, int& yMouse)
{
    clearCharacter(xCat, yCat); // стираем предыдущую позицию кошки

    if ((xCat > 1) and (xCat > xMouse))
    {
        xCat--;
    }
    else if ((xCat < WIDTH - 2) and (xCat < xMouse))
    {
        xCat++;
    }
    else if ((yCat > 1) and (yCat > yMouse))
    {
        yCat--;
    }
    else if ((yCat < HEIGHT - 2) and (yCat < yMouse))
    {
        yCat++;
    }
    else if ((yCat < WIDTH - 2) and (xCat == xMouse))
    {
        if (yCat > yMouse)
            yCat--;
        else if (yCat < yMouse)
            yCat++;
    }
    else if ((xCat > 1) and (yCat == yMouse))
    {
        if (xCat > xMouse)
            xCat--;
        else if (xCat < xMouse)
            xCat++;
    }

    drawCat(xCat, yCat); // выводим позицию кошки
}

// все кошечки бегут за мышкой без остановок
void runCatToMouse(int& xCat1, int& yCat1, int& xCat2, int& yCat2, int& xCat3, int& yCat3, int& xMouse, int& yMouse)
{
    runCat(xCat1, yCat1, xMouse, yMouse);
    runCat(xCat2, yCat2, xMouse, yMouse);
    runCat(xCat3, yCat3, xMouse, yMouse);
}

// одна мышеловка
void MouseDead(vector<pair<int, int>>& MouseDeadCoord)
{
    xMouseDead = 2 + rand() % (WIDTH - 4); // координата x мышеловки
    yMouseDead = 2 + rand() % (HEIGHT - 4); // координата y мышеловки

    while (xMouseDead == xCheese and yMouseDead == yCheese) // чтобы мышеловка не оказалась на месте сыра (сюрпрайз)
    {
        xMouseDead = 2 + rand() % (WIDTH - 4); // координата x мышеловки
        yMouseDead = 2 + rand() % (HEIGHT - 4); // координата y мышеловки
    }

    setCursorPosition(xMouseDead, yMouseDead);
    cout << "!";
    MouseDeadCoord.push_back({ xMouseDead, yMouseDead }); // добавление координат
}

// все мышеловки
void AllMouseDeads(vector<pair<int, int>>& MouseDeadCoord, int& CountMouseDeads)
{
    for (int i = 0; i < CountMouseDeads; i++)
    {
        MouseDead(MouseDeadCoord);
    }
}

// расставляем сырчик
void Cheese(int&CountMouseDeads, vector<pair<int, int>>& MouseDeadCoord)
{
    xCheese = 2 + rand() % (WIDTH - 4); // координата x сырчика
    yCheese = 2 + rand() % (HEIGHT - 4); // координата y сырчика

    for (int i = 0; i < CountMouseDeads; i++)
    {
        while (MouseDeadCoord[i].first == xCheese and MouseDeadCoord[i].second == yCheese) // чтобы мышеловка не оказалась на месте сыра (сюрпрайз)
        {
            xCheese = 2 + rand() % (WIDTH - 4); // координата x мышеловки
            yCheese = 2 + rand() % (HEIGHT - 4); // координата y мышеловки
        }
    }

    setCursorPosition(xCheese, yCheese);
    cout << "*";
}


int main()
{
    // убираем мигающий курсор
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // установите bVisible как "FALSE", чтобы скрыть курсор
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // добавление музыкального сопровождения
    HINSTANCE result;
    result = ShellExecute(NULL, NULL, L"C:\Music.MP3", NULL, NULL, SW_SHOWDEFAULT);

    srand(time(NULL));
    setlocale(LC_ALL, "RU");
    Colors color; // подключаем класс цветов

    color.set_color(CL_WHITE);
    cout << "Игра 'Голодающая мышь'" << endl;
    cout << "\nПравила игры:\nУправление клавишами a, w, s, d." << endl;
    cout << "\nОбозначения:" << endl;
    color.set_color(CL_GRAY);
    cout << "M";
    color.set_color(CL_WHITE);
    cout << " - мышка (Вы)" << endl;
    color.set_color(CL_PURPLE);
    cout << "C";
    color.set_color(CL_WHITE);
    cout << " - кошки (пытаются Вас поймать)" << endl;
    color.set_color(CL_YELLOW);
    cout << "*";
    color.set_color(CL_WHITE);
    cout << " - сыр, который нужно собрать" << endl;
    color.set_color(CL_RED);
    cout << "!";
    color.set_color(CL_WHITE);
    cout << " - мышеловки" << endl;
    cout << "\nУдачной игры!" << endl;

    Sleep(12000); // чтобы не сразу очищался экран
    system("cls"); // очистка экрана

    int xMouse, yMouse, xCat1, yCat1, xCat2, yCat2, xCat3, yCat3, CountMouseDeads;
    int LVL = 1;

    while (LVL <= 3)
    {
        if (LVL == 1)
        {
            WIDTH = WIDTH3;
            HEIGHT = HEIGHT3;
        }
        else if (LVL == 2)
        {
            WIDTH = WIDTH2;
            HEIGHT = HEIGHT2;
        }
        else if (LVL == 3)
        {
            WIDTH = WIDTH1;
            HEIGHT = HEIGHT1;
        }

        // координаты мыши
        xMouse = WIDTH / 2;
        yMouse = HEIGHT / 2;

        // координаты кошки 1
        xCat1 = 1;
        yCat1 = 1;

        // координаты кошки 2
        xCat2 = WIDTH - 2;
        yCat2 = HEIGHT - 2;

        // координаты кошки 3
        xCat3 = 1;
        yCat3 = HEIGHT - 2;

        // количество мышеловок
        CountMouseDeads = HEIGHT - 4;

        int StrokaLVL = 15; // строка для вывода уровня
        setCursorPosition(60, StrokaLVL);
        cout << "Уровень " << LVL << endl;

        int CountLife = 3; // количество жизней (уменьшается при столкновении с кошкой или попадании в мышеловку)
        int StrokaLife = 1; // строка для вывода количества жизней
        setCursorPosition(60, StrokaLife);
        cout << "У Вас " << CountLife << " жизни. Не попадитесь кошкам." << endl;

        int CountCheese = 0; // сытость (увеличивается при поедании сыра)
        int StrokaCheese = 6; // строка для вывода сытости
        setCursorPosition(60, StrokaCheese);
        cout << "У Вас " << CountCheese << " сытости. Мышка голодная!" << endl;

        vector<pair<int, int>> MouseDeadCoord;

        drawField(); // рисуем поле

        color.set_color(CL_GRAY);
        drawMouse(xMouse, yMouse); // отрисовываем изначальную позицию мыши

        color.set_color(CL_RED);
        AllMouseDeads(MouseDeadCoord, CountMouseDeads); // рисуем все мышеловки

        // чтобы изначальное расположение мышки не совпало с расположением мышеловки
        for (int i = 0; i < CountMouseDeads; i++)
        {
            while (xMouse == MouseDeadCoord[i].first and yMouse == MouseDeadCoord[i].second)
            {
                MouseDeadCoord.erase(MouseDeadCoord.begin() + i); // убираем координаты старой мышеловки

                color.set_color(CL_RED);
                MouseDead(MouseDeadCoord); // рисуем новую мышеловку
                drawMouse(xMouse, yMouse); // отрисовываем изначальную позицию мыши
            }
        }

        color.set_color(CL_YELLOW);
        Cheese(CountMouseDeads, MouseDeadCoord); // расставляем сырчик


        // отрисовываем изначальные позиции кошек
        color.set_color(CL_PURPLE);
        drawCat(xCat1, yCat1);
        drawCat(xCat2, yCat2);
        drawCat(xCat3, yCat3);

        int cnt = 0; // будем менять расположение мышеловок через каждые 5 шагов
        int NotCheese = 1; // есть сыр на поле или нет

        while (true)
        {
            Sleep(200);

            if (cnt == 5)
            {
                for (int i = 0; i < CountMouseDeads; i++)
                {
                    clearCharacter(MouseDeadCoord[i].first, MouseDeadCoord[i].second);
                }
                MouseDeadCoord.clear();

                color.set_color(CL_RED);
                AllMouseDeads(MouseDeadCoord, CountMouseDeads); // рисуем все мышеловки
                cnt = 0;
            }
            else cnt++;

            color.set_color(CL_GRAY);
            runMouse(xMouse, yMouse);
            color.set_color(CL_PURPLE);
            runCatToMouse(xCat1, yCat1, xCat2, yCat2, xCat3, yCat3, xMouse, yMouse);

            // столкновение с кошкой
            if ((xMouse == xCat1 and yMouse == yCat1) or (xMouse == xCat2 and yMouse == yCat2) or (xMouse == xCat3 and yMouse == yCat3))
            {
                CountLife--;
                StrokaLife++;
                setCursorPosition(60, StrokaLife);
                color.set_color(CL_WHITE);
                cout << "Количество оставшихся жизней: " << CountLife << ". Кошки Вас пощадили.";

                // отправляем кошек далеко, чтобы мышь сразу не повесилась
                clearCharacter(xCat1, yCat1);
                clearCharacter(xCat2, yCat2);
                clearCharacter(xCat3, yCat3);

                xCat1 = 1; yCat1 = 1; xCat2 = WIDTH - 2; yCat2 = HEIGHT - 2; xCat3 = 1; yCat3 = HEIGHT - 2;
                // отрисовываем изначальные позиции героев
                color.set_color(CL_PURPLE);
                drawCat(xCat1, yCat1);
                drawCat(xCat2, yCat2);
                drawCat(xCat3, yCat3);

                color.set_color(CL_GRAY);
                drawMouse(xMouse, yMouse);
            }

            // кошка попала на сыр
            if ((xCheese == xCat1 and yCheese == yCat1) or (xCheese == xCat2 and yCheese == yCat2) or (xCheese == xCat3 and yCheese == yCat3))
            {
                color.set_color(CL_YELLOW);
                Cheese(CountMouseDeads, MouseDeadCoord); // расставляем новый сырчик
            }

            // кошка прошлась по мышеловке
            for (int i = 0; i < CountMouseDeads; i++)
            {
                if (xCat1 == MouseDeadCoord[i].first and yCat1 == MouseDeadCoord[i].second)
                {
                    MouseDeadCoord.erase(MouseDeadCoord.begin() + i); // убираем координаты старой мышеловки

                    color.set_color(CL_RED);
                    MouseDead(MouseDeadCoord); // рисуем новую мышеловку

                    clearCharacter(xCat1, yCat1);
                    xCat1 = 1; yCat1 = 1;

                    color.set_color(CL_PURPLE);
                    drawCat(xCat1, yCat1);
                }
                if (xCat2 == MouseDeadCoord[i].first and yCat2 == MouseDeadCoord[i].second)
                {
                    MouseDeadCoord.erase(MouseDeadCoord.begin() + i); // убираем координаты старой мышеловки

                    color.set_color(CL_RED);
                    MouseDead(MouseDeadCoord); // рисуем новую мышеловку

                    clearCharacter(xCat2, yCat2);
                    xCat2 = WIDTH - 2; yCat2 = HEIGHT - 2;

                    color.set_color(CL_PURPLE);
                    drawCat(xCat2, yCat2);
                }
                if (xCat3 == MouseDeadCoord[i].first and yCat3 == MouseDeadCoord[i].second)
                {
                    MouseDeadCoord.erase(MouseDeadCoord.begin() + i); // убираем координаты старой мышеловки

                    color.set_color(CL_RED);
                    MouseDead(MouseDeadCoord); // рисуем новую мышеловку

                    clearCharacter(xCat3, yCat3);
                    xCat3 = 1; yCat3 = HEIGHT - 2;

                    color.set_color(CL_PURPLE);
                    drawCat(xCat3, yCat3);
                }
            }

            // сырчик
            if (xMouse == xCheese and yMouse == yCheese)
            {
                CountCheese += 1;
                StrokaCheese++;
                setCursorPosition(60, StrokaCheese);
                color.set_color(CL_WHITE);
                cout << "Ваша сытость: " << CountCheese << ". Мышка должна больше есть!";

                NotCheese = 0;
            }


            // попадание в мышеловку
            bool ok = true;
            for (int i = 0; i < CountMouseDeads; i++)
            {
                if (xMouse == MouseDeadCoord[i].first and yMouse == MouseDeadCoord[i].second)
                {
                    system("cls"); // очистка экрана
                    ok = false;
                    color.set_color(CL_WHITE);
                    cout << "Вы попали в мышеловку. Попробуйте еще раз!" << endl;
                    Sleep(1000);
                    system("cls"); // очистка экрана
                    break;
                }
            }

            if (ok == false)
            {
                break;
                Sleep(4000);
            }


            if (CountLife == 0) // мышь повесилась
            {
                system("cls"); // очистка экрана
                color.set_color(CL_WHITE);
                cout << "Вас съели кошки. Попробуйте еще раз!" << endl;
                Sleep(1000);
                system("cls"); // очистка экрана
                break;
            }
            else if (CountCheese == 3) // мышь съела 3 штуки сыра
            {
                system("cls"); // очистка экрана
                color.set_color(CL_WHITE);
                cout << "Вы накормили мышку. Мышка счастлива." << endl;

                if (LVL != 3)
                {
                    cout << "\nПереходим к следующему уровню..." << endl;
                    Sleep(1000);
                    system("cls"); // очистка экрана
                }
                else 
                    cout << "\nВы прошли игру!" << endl;
                LVL += 1;
                Sleep(4000);
                break;
            }
            else if (NotCheese == 0) // сыра нет на поле
            {
                color.set_color(CL_YELLOW);
                Cheese(CountMouseDeads, MouseDeadCoord); // расставляем новый сырчик
                NotCheese = 1;
            }
        }
    }

    return 0;
}