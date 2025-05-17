#include "snake.h"

#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

namespace {
/// @name Состояние игры
/// @{
atomic<bool> gameOver(false);
/// @}

/// @name Параметры доски
/// @{
const int width = 30;   // ширина доски
const int height = 20;  // высота доски
/// @}

int x, y, fruitX, fruitY, score;  // координаты головы, координаты фрукта, итоговый результат
vector<pair<int, int>> body;      // координаты каждого элемента тела, кроме головы

/// @name Направление
enum eDirection {
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN
};  // перечисление направлений
/// @}

eDirection dir;  // направление змейки

mutex mtx;

// Функция ввода
void setupConsole() {
    termios term;
    tcgetattr(0, &term);  // Настройки терминала по умолчанию
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, 0, &term);
    fcntl(0, F_SETFL, O_NONBLOCK);
}
}  // namespace

namespace snake {

// Получение нажатой клавиши
char Snake::getInput() {
    char buf = '_';
    if (read(0, &buf, 1) > 0) {
        return buf;
    }
    return '_';
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

// Генерация еды, чтобы она не попала на змею
void Snake::generateFood() {
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

void Snake::setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    body.clear();
    generateFood();
    score = 0;
    setupConsole();
}

void Snake::draw() {
    lock_guard<mutex> lock(mtx);
    clearScreen();

    // Верхняя граница
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;

    // Основное поле
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width + 2; j++) {
            if (j == 0) {
                cout << "#";
                continue;
            }

            bool isSnake = false;
            if (i == y && j == x) {
                cout << "O";
                continue;
            } else
                for (pair<int, int> t : body) {
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

            if (j == width + 1) {
                cout << "#";
                continue;
            }

            cout << " ";
        }
        cout << endl;
    }

    // Нижняя граница
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

void Snake::input() {
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

void Snake::logic() {
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

    // Проверка столкновений
    if (x < 0 || x >= width || y < 0 || y >= height) {
        gameOver = true;
        return;
    }

    for (auto& t : body) {
        if (x == t.first && y == t.second) {
            gameOver = true;
            return;
        }
    }

    // Поедание еды
    if (x == fruitX && y == fruitY) {
        score += 10;
        if (prevBody.empty()) {
            body.push_back(prevHead);
        } else {
            body.push_back(prevBody.back());
        }
        generateFood();
    }
}

void Snake::Run() {
    srand(time(0));  // Устанавливает начальное значение для генератора случайных чисел
    setup();         // Инициализация и настройка начальных условий

    thread inputThread([&]() {  // Отдельный поток для ввода
        while (!gameOver) {
            input();
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    });

    while (!gameOver) {
        draw();   // Отрисовка поля
        logic();  // Работа игры
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    inputThread.join();  // Объединение потоков

    system("stty sane");  // Возвращение терминала к первоначальным настройкам
    cout << "Game Over! Final Score: " << score << endl;
}

const std::string Snake::GetName() {
    return "Snake";
}
const std::string Snake::GetDescription() {
    return "Snake is a classic arcade game where the player controls a growing snake that moves around the screen, collecting food (usually an apple "
           "or dot) to increase its length. The goal is to avoid hitting the walls or the snake's own body, as this ends the game. With each piece "
           "of food eaten, the snake grows longer, making navigation increasingly challenging. The game tests reflexes and strategy, as players must "
           "plan their moves carefully to survive as long as possible. Simple yet addictive, Snake remains a popular and timeless mobile and "
           "computer game.";
}
const std::string Snake::GetLogoFile() {
    return "";
}
}  // namespace snake
