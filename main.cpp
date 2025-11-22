#include <iostream>
#include "help.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX_LENGTH = 100;
int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH];
int snakeLength = 2;
const int gridSize = 10;
char playerName[30];
int highScore = 0;
int letters;


void cleartrack(int x, int y, int gridSize)
{
    int x1 = x * gridSize;
    int y1 = y * gridSize;
    int x2 = x1 + gridSize;
    int y2 = y1 + gridSize;
    myEllipse(x1, y1, x2, y2, 0, 0, 0);
}

bool checkSelfCollision(int snakeX[], int snakeY[], int snakeLength) {
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            return true;
        }
    }
    return false;
}

void drawSnake(int snakeX[], int snakeY[], int length, int gridsize, int R, int G, int B) {
    for (int i = 0; i < length; i++) {
        int x1 = snakeX[i] * gridSize;
        int y1 = snakeY[i] * gridSize;
        int x2 = x1 + gridSize;
        int y2 = y1 + gridSize;
        myEllipse(x1, y1, x2, y2, R, G, B);
    }
}

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void outputHighScore(char playerName[], int letters, int highScore) {
    ofstream outFile("gameData.txt");
    outFile << playerName << endl;
    outFile << highScore << endl;
    outFile.close();
}

void inputHighScore() {
    ifstream inFile("gameData.txt");
    if (inFile.good()) {
        inFile.getline(playerName, 30);
        inFile >> highScore;
        inFile.close();
    }
    else {
        strcpy_s(playerName, "Player");
        highScore = 0;
    }
    cout << "Welcome !" << endl;
    cout << "Player's name: " << playerName << endl;
    cout << "Highest score: " << highScore << endl;
}

// helper to reset game state so game restarts correctly when returning to menu
void resetGame(int& xa, int& ya, int& score, int& speed, int& wallCount)
{
    snakeLength = 2;
    snakeX[0] = 20; snakeY[0] = 20;
    snakeX[1] = 19; snakeY[1] = 20;
    xa = 40; ya = 20;
    score = 0;
    speed = 100;
    wallCount = 0;
}

int main()
{
    int w = 0;
    bool z = false;
    int length;
    int state = 0;       // 0 = Basic, 1 = Levels, 2 = Custom
    int stateSub = 0;    // levels submenu index (0 easy,1 med,2 hard)
    int stateSub2 = 0;   // color selection index
    bool wasPressed = false;
    int level = 1;
    int speed = 100;
    const int maxwalls = 100;
    int wallx1[maxwalls], wally1[maxwalls], wallx2[maxwalls], wally2[maxwalls];
    int wallCount = 0;

    int x1 = 15, y1 = 10, x2 = 105, y2 = 60; // main rectangle dimensions

    int xa = 40, ya = 20; // food
    int score = 0;
    srand((unsigned int)time(0));

    resetGame(xa, ya, score, speed, wallCount);

    int R = 0, G = 0, B = 0;
    gotoxy(0, 0);
    inputHighScore();
    gotoxy(2, 18);
    setColor(5);
    cout << "Use up and down keys to choose option and left and right keys to change colour";
    gotoxy(2, 20);
    setColor(3);
    cout << "Have fun!";
    gotoxy(0, 4);

    gotoxy(47, 1);
    setColor(13);
    cout << "Colour Selection: " << endl;
    for (int i = 0; i < 2; i++) {
        myRect1(300, 170, 700, 300, 255, 34, 45);
        gotoxy(50, 10);
        setColor(10);
        cout << "Basic";
        gotoxy(50, 11);
        setColor(2);
        cout << "Levels";
        gotoxy(50, 12);
        setColor(2);
        cout << "Custom";
        gotoxy(55, 10);

        int x11 = 350; int x22 = 375;
        for (int i = 0; i < 12; i++) {
            myEllipse(x11, 90, x22, 115, 255, 0, 0);
            x11 += 25;
            x22 += 25;
        }
        Sleep(100);
    }

    while (true)
    {
        // Poll keys; update w if a key is down. If no key is down, reset wasPressed so toggles respond again.
        int tmpKey = w;
        bool anyKey = isCursorKeyPressed(tmpKey);
        if (!anyKey) {
            wasPressed = false;
        }
        else {
            w = tmpKey; // update w only when a key is actually pressed
        }

        if (anyKey)
        {
            if (w == 2) // RIGHT -> change color forward
            {
                if (!wasPressed)
                {
                    if (stateSub2 == 0)
                    {
                        int x11 = 350; int x22 = 375;
                        for (int i = 0; i < 12; i++) {
                            myEllipse(x11, 90, x22, 115, 0, 255, 0);
                            x11 += 25;
                            x22 += 25;
                        }
                        Sleep(100);
                    }
                    else if (stateSub2 == 1)
                    {
                        int x11 = 350; int x22 = 375;
                        for (int i = 0; i < 12; i++) {
                            myEllipse(x11, 90, x22, 115, 0, 0, 255);
                            x11 += 25;
                            x22 += 25;
                        }
                        Sleep(100);
                    }
                    else if (stateSub2 == 2)
                    {
                        int x11 = 350; int x22 = 375;
                        for (int i = 0; i < 12; i++) {
                            myEllipse(x11, 90, x22, 115, 255, 0, 0);
                            x11 += 25;
                            x22 += 25;
                        }
                        Sleep(100);
                    }
                    stateSub2 = (stateSub2 + 1) % 3;
                    wasPressed = true;
                }
            }
            else if (w == 1) // LEFT -> change color backward
            {
                if (!wasPressed)
                {
                    if (stateSub2 == 0)
                    {
                        int x11 = 350; int x22 = 375;
                        for (int i = 0; i < 12; i++) {
                            myEllipse(x11, 90, x22, 115, 0, 0, 255);
                            x11 += 25;
                            x22 += 25;
                        }
                        Sleep(100);
                    }
                    else if (stateSub2 == 1)
                    {
                        int x11 = 350; int x22 = 375;
                        for (int i = 0; i < 12; i++) {
                            myEllipse(x11, 90, x22, 115, 255, 0, 0);
                            x11 += 25;
                            x22 += 25;
                        }
                        Sleep(100);
                    }
                    else if (stateSub2 == 2)
                    {
                        int x11 = 350; int x22 = 375;
                        for (int i = 0; i < 12; i++) {
                            myEllipse(x11, 90, x22, 115, 0, 255, 0);
                            x11 += 25;
                            x22 += 25;
                        }
                        Sleep(100);
                    }
                    stateSub2 = (stateSub2 + 1) % 3;
                    wasPressed = true;
                }
            }
            else if (w == 4) // DOWN
            {
                if (!wasPressed)
                {
                    if (state == 0)
                    {
                        gotoxy(50, 10); setColor(2); cout << "Basic";
                        gotoxy(50, 11); setColor(10); cout << "Levels";
                    }
                    else if (state == 1)
                    {
                        gotoxy(50, 11); setColor(2); cout << "Levels";
                        gotoxy(50, 12); setColor(10); cout << "Custom";
                    }
                    else if (state == 2)
                    {
                        gotoxy(50, 12); setColor(2); cout << "Custom";
                        gotoxy(50, 10); setColor(10); cout << "Basic";
                    }
                    state = (state + 1) % 3;
                    wasPressed = true;
                }
            }
            else if (w == 3) // UP
            {
                if (!wasPressed)
                {
                    if (state == 0)
                    {
                        gotoxy(50, 10); setColor(2); cout << "Basic";
                        gotoxy(50, 12); setColor(10); cout << "Custom";
                    }
                    else if (state == 1)
                    {
                        gotoxy(50, 11); setColor(2); cout << "Levels";
                        gotoxy(50, 10); setColor(10); cout << "Basic";
                    }
                    else if (state == 2)
                    {
                        gotoxy(50, 12); setColor(2); cout << "Custom";
                        gotoxy(50, 11); setColor(10); cout << "Levels";
                    }
                    state = (state + 2) % 3;
                    wasPressed = true;
                }
            }
            else if (w == 5) // ENTER
            {
                if (!wasPressed)
                {
                    if (state == 0) // BASIC
                    {
                        resetGame(xa, ya, score, speed, wallCount);
                        system("cls");
                        bool backToMenu = false;
                        while (!backToMenu)
                        {
                            if (snakeLength > 2) {
                                if (checkSelfCollision(snakeX, snakeY, snakeLength)) {
                                    system("cls");
                                    gotoxy((x2 + x1) / 2, (y2 + y1) / 2);
                                    cout << "Game Over\n";
                                    cout << "Score: " << score << endl;
                                    setColor(15);
                                    cout << "How many letters are there in your name: ";
                                    cin >> letters;
                                    cout << "Enter your name: ";
                                    cin.ignore();
                                    cin.getline(playerName, 30);
                                    if (score > highScore) {
                                        highScore = score;
                                    }
                                    outputHighScore(playerName, letters, highScore);
                                    backToMenu = true;
                                    break;
                                }
                            }

                            myRect1(x1 * gridSize, y1 * gridSize, x2 * gridSize, y2 * gridSize, 255, 0, 0); // main rectangle
                            myEllipse(xa * gridSize, ya * gridSize, (xa + 1) * gridSize, (ya + 1) * gridSize, 0, 0, 255); // food
                            cleartrack(snakeX[snakeLength - 1], snakeY[snakeLength - 1], gridSize); // blacks out previous

                            for (int j = snakeLength - 1; j > 0; j--) // move except head
                            {
                                snakeX[j] = snakeX[j - 1];
                                snakeY[j] = snakeY[j - 1];
                            }

                            int dir = w;
                            isCursorKeyPressed(dir);
                            if (dir == 13) { // ESC
                                backToMenu = true;
                                break;
                            }
                            w = dir;

                            if (w == 1)
                                snakeX[0]--;
                            else if (w == 2)
                                snakeX[0]++;
                            else if (w == 3)
                                snakeY[0]--;
                            else if (w == 4)
                                snakeY[0]++;

                            if (snakeX[0] == xa && snakeY[0] == ya) // food collision
                            {
                                snakeLength++;
                                score++;
                                do
                                {
                                    if (state == 0)
                                        wallCount = 0;
                                    xa = x1 + rand() % (x2 - x1 - 4);
                                    ya = y1 + rand() % (y2 - y1 - 4);

                                    bool valid = true;
                                    for (int i = 0; i < wallCount; i++)
                                    {
                                        if (xa >= wallx1[i] && xa < wallx2[i] &&
                                            ya >= wally1[i] && ya < wally2[i]) // conditions for wall 
                                        {
                                            valid = false;
                                            break;
                                        }
                                    }
                                    if (valid) break;
                                } while (true);
                                myEllipse(xa * gridSize, ya * gridSize, (xa + 1) * gridSize, (ya + 1) * gridSize, 0, 0, 255);
                            }

                            if (snakeX[0] <= x1 || snakeX[0] >= x2 || snakeY[0] <= y1 || snakeY[0] >= y2)
                            {
                                if (state == 0) // spawns from the other side
                                {
                                    if (snakeX[0] < x1) {
                                        snakeX[0] = x2 - 1;
                                    }
                                    else if (snakeX[0] >= x2) {
                                        snakeX[0] = x1 + 1;
                                    }
                                    if (snakeY[0] < y1) {
                                        snakeY[0] = y2 - 1;
                                    }
                                    else if (snakeY[0] >= y2) {
                                        snakeY[0] = y1 + 1;
                                    }
                                }
                            }

                            if (stateSub2 == 0) {
                                drawSnake(snakeX, snakeY, snakeLength, gridSize, 255, 0, 0);
                            }
                            else if (stateSub2 == 1) {
                                drawSnake(snakeX, snakeY, snakeLength, gridSize, 0, 255, 0);
                            }
                            else if (stateSub2 == 2) {
                                drawSnake(snakeX, snakeY, snakeLength, gridSize, 0, 0, 255);
                            }

                            Sleep(speed);
                            z = true;
                        } // end BASIC game loop

                        system("cls");
                        // return to main menu
                        state = 0;
                        wasPressed = true; // avoid immediate menu move
                        continue;
                    }
                    else if (state == 1) // LEVELS
                    {
                        resetGame(xa, ya, score, speed, wallCount);
                        system("cls");
                        if (snakeLength > 2) {
                            if (checkSelfCollision(snakeX, snakeY, snakeLength)) {
                                system("cls");
                                gotoxy((x2 + x1) / 2, (y2 + y1) / 2);
                                cout << "Game Over\n";
                                cout << "Score: " << score << endl;
                                setColor(15);
                                cout << "How many letters are there in your name: ";
                                cin >> letters;
                                cout << "Enter your name: ";
                                cin.ignore();
                                cin.getline(playerName, 30);
                                if (score > highScore) highScore = score;
                                outputHighScore(playerName, letters, highScore);
                            }
                        }

                        for (int i = 0; i < 2; i++) {
                            myRect1(300, 170, 700, 300, 255, 34, 45);
                            gotoxy(50, 10);
                            setColor(14);
                            cout << "Easy";
                            gotoxy(50, 11);
                            setColor(6);
                            cout << "Medium \n";
                            gotoxy(50, 12);
                            setColor(6);
                            cout << "Hard \n";
                            Sleep(100);
                        }

                        bool backToMainFromLevels = false;
                        while (!backToMainFromLevels)
                        {
                            int tmp = w;
                            bool any = isCursorKeyPressed(tmp);
                            if (!any) {
                                wasPressed = false;
                            }
                            else {
                                w = tmp;
                            }

                            if (any && w == 4)
                            {
                                if (!wasPressed)
                                {
                                    if (stateSub == 0) {
                                        gotoxy(50, 10); setColor(6); cout << "Easy";
                                        gotoxy(50, 11); setColor(14); cout << "Medium";
                                    }
                                    else if (stateSub == 1) {
                                        gotoxy(50, 11); setColor(6); cout << "Medium";
                                        gotoxy(50, 12); setColor(14); cout << "Hard";
                                    }
                                    else if (stateSub == 2) {
                                        gotoxy(50, 12); setColor(6); cout << "Hard";
                                        gotoxy(50, 10); setColor(14); cout << "Easy";
                                    }
                                    stateSub = (stateSub + 1) % 3;
                                    wasPressed = true;
                                }
                            }
                            else if (any && w == 3)
                            {
                                if (!wasPressed)
                                {
                                    if (stateSub == 0) {
                                        gotoxy(50, 10); setColor(6); cout << "Easy";
                                        gotoxy(50, 12); setColor(14); cout << "Hard";
                                    }
                                    else if (stateSub == 1) {
                                        gotoxy(50, 11); setColor(6); cout << "Medium";
                                        gotoxy(50, 10); setColor(14); cout << "Easy";
                                    }
                                    else if (stateSub == 2) {
                                        gotoxy(50, 12); setColor(6); cout << "Hard";
                                        gotoxy(50, 11); setColor(14); cout << "Medium";
                                    }
                                    stateSub = (stateSub + 2) % 3;
                                    wasPressed = true;
                                }
                            }
                            else if (any && w == 5)
                            {
                                if (!wasPressed)
                                {
                                    // configure level parameters
                                    if (stateSub == 0) // Easy
                                    {
                                        wallCount = 4;
                                        speed = 150;
                                    }
                                    else if (stateSub == 1) // Medium
                                    {
                                        wallCount = 6;
                                        speed = 100;
                                    }
                                    else // Hard
                                    {
                                        wallCount = 8;
                                        speed = 60;
                                    }

                                    // sample wall coordinates for demo (you can change)
                                    if (wallCount >= 4) {
                                        wallx1[0] = 40; wally1[0] = 30; wallx2[0] = 80; wally2[0] = 31;
                                        wallx1[1] = 40; wally1[1] = 38; wallx2[1] = 80; wally2[1] = 39;
                                        wallx1[2] = 35; wally1[2] = 30; wallx2[2] = 36; wally2[2] = 39;
                                        wallx1[3] = 85; wally1[3] = 30; wallx2[3] = 86; wally2[3] = 39;
                                    }
                                    if (wallCount >= 6) {
                                        wallx1[4] = 55; wally1[4] = 22; wallx2[4] = 60; wally2[4] = 23;
                                        wallx1[5] = 60; wally1[5] = 48; wallx2[5] = 65; wally2[5] = 49;
                                    }
                                    if (wallCount >= 8) {
                                        wallx1[6] = 25; wally1[6] = 35; wallx2[6] = 26; wally2[6] = 45;
                                        wallx1[7] = 95; wally1[7] = 35; wallx2[7] = 96; wally2[7] = 45;
                                    }

                                    // start level gameplay
                                    bool exitToLevelsMenu = false;
                                    while (!exitToLevelsMenu)
                                    {
                                        myRect1(x1 * gridSize, y1 * gridSize, x2 * gridSize, y2 * gridSize, 255, 0, 0);
                                        myEllipse(xa * gridSize, ya * gridSize, (xa + 1) * gridSize, (ya + 1) * gridSize, 0, 0, 255);
                                        for (int i = 0; i < wallCount; i++) // walls drawn
                                        {
                                            myRect(wallx1[i] * gridSize, wally1[i] * gridSize, wallx2[i] * gridSize, wally2[i] * gridSize, 100, 100, 100);
                                        }
                                        cleartrack(snakeX[snakeLength - 1], snakeY[snakeLength - 1], gridSize);

                                        for (int j = snakeLength - 1; j > 0; j--)
                                        {
                                            snakeX[j] = snakeX[j - 1];
                                            snakeY[j] = snakeY[j - 1];
                                        }

                                        int dir2 = w;
                                        isCursorKeyPressed(dir2);
                                        if (dir2 == 13) { // ESC
                                            exitToLevelsMenu = true;
                                            break;
                                        }
                                        w = dir2;

                                        if (w == 1) snakeX[0]--;
                                        else if (w == 2) snakeX[0]++;
                                        else if (w == 3) snakeY[0]--;
                                        else if (w == 4) snakeY[0]++;

                                        if (snakeLength > 2) {
                                            if (checkSelfCollision(snakeX, snakeY, snakeLength)) {
                                                system("cls");
                                                gotoxy((x2 + x1) / 2, (y2 + y1) / 2);
                                                cout << "Game Over\n";
                                                cout << "Score: " << score << endl;
                                                setColor(15);
                                                cout << "How many letters are there in your name: ";
                                                cin >> letters;
                                                cout << "Enter your name: ";
                                                cin.ignore();
                                                cin.getline(playerName, 30);
                                                if (score > highScore) highScore = score;
                                                outputHighScore(playerName, letters, highScore);
                                                exitToLevelsMenu = true;
                                                break;
                                            }
                                        }

                                        if (snakeX[0] == xa && snakeY[0] == ya)
                                        {
                                            snakeLength++;
                                            score++;
                                            do
                                            {
                                                xa = x1 + rand() % (x2 - x1 - 4);
                                                ya = y1 + rand() % (y2 - y1 - 4);

                                                bool valid = true;
                                                for (int i = 0; i < wallCount; i++)
                                                {
                                                    if (xa >= wallx1[i] && xa < wallx2[i] &&
                                                        ya >= wally1[i] && ya < wally2[i])
                                                    {
                                                        valid = false;
                                                        break;
                                                    }
                                                }
                                                if (valid) break;
                                            } while (true);
                                            myEllipse(xa * gridSize, ya * gridSize, (xa + 1) * gridSize, (ya + 1) * gridSize, 0, 0, 255);
                                        }

                                        for (int i = 0; i < wallCount; i++)
                                        {
                                            if (snakeX[0] >= wallx1[i] && snakeX[0] < wallx2[i] &&
                                                snakeY[0] >= wally1[i] && snakeY[0] < wally2[i] && z == true) {
                                                system("cls");
                                                gotoxy((x2 + x1) / 2, (y2 + y1) / 2);
                                                cout << "Game Over\n";
                                                cout << "Score: " << score << endl;
                                                setColor(15);
                                                cout << "How many letters are there in your name: ";
                                                cin >> letters;
                                                cout << "Enter your name: ";
                                                cin.ignore();
                                                cin.getline(playerName, 30);
                                                if (score > highScore) highScore = score;
                                                outputHighScore(playerName, letters, highScore);
                                                exitToLevelsMenu = true;
                                                break;
                                            }
                                        }
                                        if (snakeX[0] <= x1 || snakeX[0] >= x2 || snakeY[0] <= y1 || snakeY[0] >= y2)
                                        {
                                            system("cls");
                                            gotoxy((x2 + x1) / 2, (y2 + y1) / 2);
                                            cout << "Game Over\n";
                                            cout << "Score: " << score << endl;
                                            exitToLevelsMenu = true;
                                            break;
                                        }

                                        if (stateSub2 == 0) drawSnake(snakeX, snakeY, snakeLength, gridSize, 255, 0, 0);
                                        else if (stateSub2 == 1) drawSnake(snakeX, snakeY, snakeLength, gridSize, 0, 255, 0);
                                        else if (stateSub2 == 2) drawSnake(snakeX, snakeY, snakeLength, gridSize, 0, 0, 255);

                                        Sleep(speed);
                                        z = true;
                                    } // end level gameplay

                                    // after finishing a level (or ESC) return to levels menu
                                    system("cls");
                                    wasPressed = true;
                                }
                            }

                            // ESC from levels menu should go back to main menu
                            if (any && w == 13) {
                                backToMainFromLevels = true;
                            }

                            if (backToMainFromLevels) break;
                        } // end levels submenu loop

                        // return to main menu
                        state = 0;
                        wasPressed = true;
                        continue;
                    }
                }
            }
        }

        // small sleep to reduce CPU usage in main menu loop
        Sleep(20);
    }

    return 0;
}
