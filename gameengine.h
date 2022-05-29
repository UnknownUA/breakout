#pragma once

#include <map>
#include <vector>
#include <windows.h>

#include "platform.h"
#include "ball.h"

using TheWall = std::map <int, std::vector <char> >;

const int BRICK_SIZE = 4;

class Gameengine
{
public:
    Gameengine(const int w = 80, const int h = 25) : width(w), height(h)
    {
        brickLines[4] = { 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 };
        brickLines[5] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
        brickLines[6] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
        brickLines[7] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
        brickLines[8] = { 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 };
    }

    void setWidth(const int w) noexcept { width = w; }
    int getWidth() const noexcept { return width; }
    void setHeight(const int h) noexcept { height = h; }
    int getHeight() const noexcept { return height; }

    int readKeyCycle();
    void draw();
    void bye();

private:
    int width;
    int height;
    Platform platform { 10 };
    int platformPos = width / 2;
    Ball ball;
    int ballX = platformPos - 1, ballY = height - 2;
    int curLineStartX = ballX, curLineStartY = ballY;
    double angle = 90.0;
    int currentRow = 0;
    TheWall brickLines;

    void calcNewBallRow();
    void fillLine(const char sym, const int sz, const bool end = false);
    void drawEmptyLine(bool incr);
    void drawBrickLine(HANDLE &hStdOut);
};

