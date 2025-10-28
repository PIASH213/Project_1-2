#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;

const int width = 70;
const int height = 20;
const int paddleSize = 7;

int score = 0;
int ballX = width / 2;
int ballY = height - 2;
int ballSpeedX = 1;
int ballSpeedY = -1;
int paddleX = (width - paddleSize) / 2;

bool bricks[width][height];
bool gameOver = false;

void drawGame() {
    system("cls");
    cout << setw(46) << "| BRICK BREAKER |\n" << endl;
    for (int i = 0; i < width + 2; i++)
        cout << "=";
    cout << endl;

    for (int y = 0; y < height; y++) {
        cout << "|";
        for (int x = 0; x < width; x++) {
            if (x >= paddleX && x < paddleX + paddleSize && y == height - 1) {
                cout << "=";
            }
            else if (bricks[x][y]) {
                cout << "#";
            }
            else if (x == ballX && y == ballY) {
                cout << "o";
            }
            else {
                cout << " ";
            }
        }
        cout << "|" << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "=";
    cout << endl;

    cout << "Score: " << score << endl;
}

void movePaddle(int direction) {
    paddleX += direction;

    if (paddleX < 0) {
        paddleX = 0;
    }
    else if (paddleX + paddleSize > width) {
        paddleX = width - paddleSize;
    }
}

void initializeBricks() {
    for (int y = 0; y < height / 2; ++y) {
        for (int x = 0; x < width; ++x) {
            bricks[x][y] = true;
        }
    }
}

void updateBall() {
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    if (ballX == 0 || ballX == width - 1) {
        ballSpeedX = -ballSpeedX;
    }

    if (ballY == 0) {
        ballSpeedY = -ballSpeedY;
    }

    if (ballY == height - 1 && ballX >= paddleX && ballX < paddleX + paddleSize) {
        ballSpeedY = -ballSpeedY;
    }

    if (bricks[ballX][ballY]) {
        bricks[ballX][ballY] = false;
        bricks[ballX-1][ballY] = false;
        bricks[ballX+1][ballY] = false;
        ballSpeedY = -ballSpeedY;
        score += 10;
    }

    if (ballY == height) {
        gameOver = true;
        cout << "Game Over! Score: " << score - 10;
        cout << ".\nPress Space to restart or 'q' to quit." << endl;
    }
}

int main() {
    initializeBricks();

    while (!gameOver) {
        drawGame();
        updateBall();

        if (_kbhit()) {
            char key = _getch();

            switch (key) {
                case 'a':
                    movePaddle(-3);
                    break;
                case 'd':
                    movePaddle(3);
                    break;
            }
        }
        while (gameOver) {
            if (_kbhit()) {
                char key = _getch();
                if (key == ' ') {
                    ballX = width / 2;
                    ballY = height - 2;
                    ballSpeedY = -1;
                    initializeBricks();
                    score = 0;
                    gameOver = false;
                }
                else if (key == 'q') {
                    cout << "Quitting the game..." << endl;
                    exit(0);
                }
            }
        }
        Sleep(100);
    }
    return 0;
}

