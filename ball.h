#ifndef BALL_H
#define BALL_H

#include <iostream>

// another branch commit 2

class Ball
{
public:

	void run() noexcept { running = true; };
	bool isRunning() const noexcept { return running; }
	friend std::ostream& operator<<(std::ostream& os, const Ball& b);

private:
	int curRow, curCol;
	double angle;
	bool running = false;
};

#endif // BALL_H
