#include "snake.h"

#include <iostream>
#include <vector>
#include <thread>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

namespace {
/// @name Состояние игры
/// @{
bool gameOver = false; // состояние игры
/// @}

/// @name Параметры доски
/// @{
const int width = 30; // ширина доски
const int height = 20; // высота доски
/// @}

int x, y, fruitX, fruitY, score; // координаты головы, координаты фрукта, итоговый результат
vector<pair<int, int>> body; // координаты каждого элемента тела, кроме головы

/// @name Направление
enum eDirection { STOP, LEFT, RIGHT, UP, DOWN }; // перечисление направлений
/// @}

eDirection dir; // направление змейки

// Функция ввода
void setupConsole() {
  termios term;
  tcgetattr(0, &term); // Настройки терминала по умолчанию
  term.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(0, 0, &term);
  fcntl(0, F_SETFL, O_NONBLOCK);
}
}

namespace snake {

// Получение нажатой клавиши
char getInput() {
    char buf = '_';
    if (read(0, &buf, 1) > 0) {
        return buf;
    }
    return '_';
}

// Генерация еды, чтобы она не попала на змею
void generateFood() {
    bool onSnake = false;
    do {
        onSnake = false;
        fruitX = rand() % width;
        fruitY = rand() % height;

        if (fruitX == x && fruitY == y) {
            onSnake = true;
        }

        for (pair<int, int> segment : body) {
            if (fruitX == segment.first && fruitY == segment.second) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);
}

void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    body.clear();
    generateFood();
    score = 0;
    setupConsole();
}

void draw() {
    // Верхняя граница
    for (int i = 0; i < width+2; i++) {
        cout << "#";
    }
    cout << endl;

    // Основное поле
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width+2; j++) {
            if (j == 0) {
                cout << "#";
                continue;
            }

            bool isSnake = false;
            if (i == y && j == x) {
                cout << "O";
                continue;
            }
            else for (pair<int, int> t : body) {
                if (t.first == j && t.second == i) {
                    cout << "o";
                    isSnake = true;
                    break;
                }
            }

            if (isSnake) {
                continue;
            }

            if (i == fruitY && j == fruitX) {
                cout << "F";
                continue;
            }

            if (j == width+1) {
                cout << "#";
                continue;
            }

            cout << " ";
        }
        cout << endl;
    }

    // Нижняя граница
    for (int i = 0; i < width+2; i++) {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

void input() {
    char key = getInput();
    if (key != '_') {
        switch (tolower(key)) {
            case 'a': {
                if (dir != RIGHT) {
                    dir = LEFT;
                }
                break;
            }
            case 'd': {
                if (dir != LEFT) {
                    dir = RIGHT;
                }
                break;
            }
            case 'w': {
                if (dir != DOWN) {
                    dir = UP;
                }
                break;
            }
            case 's': {
                if (dir != UP) {
                    dir = DOWN;
                }
                break;
            }
            case 'x': {
                gameOver = true;
                break;
            }
        }
    }
}

void logic() {
    pair<int, int> prevHead = {x, y};
    vector<pair<int, int>> prevBody = body;

    // Обновление тела
    if (!body.empty()) {
        body.pop_back();
        body.insert(body.begin(), prevHead);
    }

    // Движение головы
    switch (dir) {
        case LEFT: {
            x--;
            break;
        }
        case RIGHT: {
            x++;
            break;
        }
        case UP: {
            y--;
            break;
        }
        case DOWN: {
            y++;
            break;
        }
    }
}

int Run() {
    srand(time(0)); //Устанавливает начальное значение для генератора случайных чисел
    setup(); //Инициализация и настройка начальных условий

    thread inputThread([](){ // Отдельный поток для ввода
        while (!gameOver) {
            input();
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    });

    while (!gameOver) {
        draw(); // Отрисовка поля
        logic(); // Работа игры
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    inputThread.join(); // Объединение потоков

    system("stty sane"); // Возвращение терминала к первоначальным настройкам
    cout << "Game Over! Final Score: " << score << endl;
    return 0;
}

} // namespace chess
