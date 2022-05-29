#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

#include "gameengine.h"

const double pi = std::acos(-1);

int Gameengine::readKeyCycle()
{
    using namespace std;
    char key = 0;
    while (key != 27) // Выход по клавише ESC
    {
        if (0 == _kbhit())
            continue;
        key = _getch();
        switch (key)
        {
        case 'a':
        case 'A':
            //cout << "LEFT\n";
            if (platformPos > (platform.getSize () / 2))
                -- platformPos;
            break;
        case 'd':
        case 'D':
            //cout << "RIGHT\n";
            if (platformPos < width - (platform.getSize() / 2))
                ++ platformPos;
            break;
        case ' ':
        case 'w':
        case 'W':
            //cout << "STARS\n";
            ball.run();
            break;
        case 27:
            //cout << "ESC\n";
            break;
        default:
            break;
        }
    }
    cout << "RETURN 0\n";
    return 0;
}

void Gameengine::draw ()
{
    system("cls");
    currentRow = 0;
    using namespace std;
    calcNewBallRow();
    for (int l = 0; l < 4; ++l)
        drawEmptyLine(true);

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    for (size_t l = 0, lines = brickLines.size(); l < lines; ++l)
        drawBrickLine(hStdOut);

    for ( ; currentRow < (height - 1); ++currentRow)
        drawEmptyLine(false);
    SetConsoleTextAttribute(hStdOut, 0xA);
    fillLine(' ', platformPos - platform.getSize() / 2, false);
    cout << platform;
    fillLine(' ', width - platformPos - platform.getSize() / 2, false);
    SetConsoleTextAttribute(hStdOut, 0xF);
}

void Gameengine::bye()
{
    system("cls");
    std::cout << "Bye!" << std::endl;
}

void Gameengine::calcNewBallRow()
{
    if (!ball.isRunning())
        return;
    using namespace std;
    currentRow = 0;
    if (angle <= 135.0 && angle >= 45.0)
    {
        --ballY;
        //ballX = curLineStartX - abs (ballY - curLineStartY) * cos(angle * pi / 180);
        if (45.0 == angle || 135.0 == angle)
            ballX = curLineStartX - ballY + curLineStartY;
        if (0 == ballY)
        {
            angle = 270.0;
            return;
        }
        auto line = brickLines.find(ballY);
        if (brickLines.end() != line)
        {
            int brickID = ballX / BRICK_SIZE;
            bool isHit = false;
            if (line->second[brickID])
            {
                --line->second[brickID];
                isHit = true;
            }
            if (3 == ballX % BRICK_SIZE && brickID < 19)	// hit 2 bricks
                if (line->second[brickID + 1])
                {
                    --line->second[brickID + 1];
                    isHit = true;
                }
            if (isHit)
            {
                ++ballY;
                angle = 270.0;
            }
        }
    }
    else
    if (angle >= 125.0 && angle <= 305.0)
    {
        ++ballY;
        //ballX = curLineStartX + abs(ballY - curLineStartY) * cos(angle * pi / 180);
        if (ballY == height - 1)
        {
            int da = abs (ballX - platformPos + 1);
            if (da <= 5)
            {
                angle = 90.0 + da * 9;
                --ballY;
                return;
            }
        }
        if (ballY >= height)
            cout << "GAME OVER" << endl;
    }
}

void Gameengine::fillLine(const char sym, const int sz, const bool end)
{
    using namespace std;
    for (int i = 0; i < sz; ++i)
        cout << sym;
    if (end)
        cout << '\n';
}

void Gameengine::drawEmptyLine(bool incr)
{
    using namespace std;
    if (currentRow != ballY)
        for (int i = 0; i < width; ++i)
            cout << ' ';
    else
        for (int i = 0; i < width; ++i)
            if (i != ballX)
                cout << ' ';
            else
            {
                cout << ball;
                ++i;
            }
    cout << '\n';
    if (incr)
        ++currentRow;
}

void Gameengine::drawBrickLine(HANDLE &hStdOut)
{
    using namespace std;
    auto line = brickLines.find(currentRow);
    if (brickLines.end() == line)
    {
        cerr << "!!! Wrong brick line " << currentRow << endl;
    }
    else
    {
        SetConsoleTextAttribute(hStdOut, 0xA);
        if (currentRow != ballY)
            for (auto brick : line->second)
            {
                if (brick)
                    cout << "[##]";
                else
                    cout << "    ";
            }
        else
        {
            bool isBallDrawn = false;
            int brickIndex = 0;
            for (auto brick = line->second.begin (), end = line->second.end(); brick != end; ++ brick)
            {
                if (*brick)
                    cout << "[##]";
                else
                {
                    int curBrickX = BRICK_SIZE * brickIndex;
                    if (ballX <= (curBrickX + BRICK_SIZE) && !isBallDrawn)
                    {
                        isBallDrawn = true;
                        int posInBrick = ballX % BRICK_SIZE;
                        SetConsoleTextAttribute(hStdOut, 0xF);
                        if (0 == posInBrick)
                            cout << ball << "  ";
                        else
                        if (1 == posInBrick)
                            cout << " " << ball << " ";
                        else
                        if (2 == posInBrick)
                            cout << "  " << ball;
                        else
                        {
                            cout << "   " << ball << "   ";
                            ++brick;
                            ++brickIndex;
                        }
                        SetConsoleTextAttribute(hStdOut, 0xA);
                    }
                    else
                        cout << "    ";
                }
                ++brickIndex;
            }
        }
        SetConsoleTextAttribute(hStdOut, 0xF);
    }
    ++currentRow;
    cout << '\n';
}
