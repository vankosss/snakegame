
#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameOver;
const int gamezone_widght = 40;
const int gamezone_height = 20;

int snakehead_x;
int snakehead_y;
int bodysnake_x[100];
int bodysnake_y[100];
int lengthbodysnake = 0;
int apple_x;
int apple_y;
int score = 0;

enum eControl {STOP = 0, LEFT, RIGHT, UP, DOWN};
eControl dir;

void Settings() {

    gameOver = false;
    dir = STOP;
    snakehead_x = rand() % gamezone_widght;
    snakehead_y = rand() % gamezone_height;
    apple_x = rand() % gamezone_widght;
    apple_y = rand() % gamezone_height;
}

void Draw() {
    system("cls");

    for (int i = 0; i < gamezone_widght + 2; i++) // в этом цикле, мы отрисовали верхнюю грань нашего поля, +2 потому что при создании стен слева и справо наше поле сдивинться на 2 
        std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < gamezone_height; i++) { // создаем цикл в котором проходимся по каждому елементу в переменной gamezone_height

        std::cout << "#";

        for (int j = 0; j < gamezone_widght; j++) { // создаем цикл в котором проходимся по каждому елементу в переменной gamezone_widght
            if (i == snakehead_y && j == snakehead_x) std::cout << "O"; // если координаты головы змеи равны нашим внутренним переменным, то рисуем ее голову (в любом случае будет отрисованна, по скольку мы проходимся по всем елементам)
            else if (i == apple_y && j == apple_x) std::cout << "A";
            else {
                bool TailP = false;
                for (int t = 0; t < lengthbodysnake; t++) {
                    if (bodysnake_x[t] == j && bodysnake_y[t] == i) {
                        std::cout << "o";
                        TailP = true;
                    }
                }
                if (!TailP)
                    std::cout << " ";
            }
        }
        std::cout << "#";
        std::cout << std::endl;
    }

   

    for (int i = 0; i < gamezone_widght + 2; i++) // в этом цикле, мы отрисовали нижнюю грань нашего поля, +2 потому что при создании стен слева и справа наше поле сдивинться на 2 
        std::cout << "#";
    std::cout << std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        }
    }
}

void Logic() {

    for (int i = lengthbodysnake - 1; i > 0; i--) {
        bodysnake_x[i] = bodysnake_x[i - 1];
        bodysnake_y[i] = bodysnake_y[i - 1];
    }

    if (lengthbodysnake > 0) {
        bodysnake_x[0] = snakehead_x;
        bodysnake_y[0] = snakehead_y;
    }

    switch (dir) {
    case LEFT:
        snakehead_x--;
        break;
    case RIGHT:
        snakehead_x++;
        break;
    case UP:
        snakehead_y--;
        break;
    case DOWN:
        snakehead_y++;
        break;
    }

    for (int i = 0; i < lengthbodysnake; i++) {
        if (bodysnake_x[i] == snakehead_x && bodysnake_y[i] == snakehead_y) {
            gameOver = true;
        }
    }

    if (snakehead_x >= gamezone_widght) {
        snakehead_x = 0;
    }

    if (snakehead_x < 0) {
        snakehead_x = gamezone_widght - 1;
    }

    if (snakehead_y >= gamezone_height) {
        snakehead_y = 0;
    }

    if (snakehead_y < 0) {
        snakehead_y = gamezone_height - 1;
    }

    if (snakehead_x == apple_x && snakehead_y == apple_y) {
        score += 10;
        lengthbodysnake++;
        apple_x = rand() % gamezone_widght;
        apple_y = rand() % gamezone_height;
    }

}

int main() 
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Settings();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }

    if (gameOver = true) {
        std::cout << "\nВы проиграли! Ваш счет: " << score << std::endl;
        std::cout << "Чтобы выйти нажмите любую кнопку!" << std::endl;
        _getch();
    }
    return 0;
}

