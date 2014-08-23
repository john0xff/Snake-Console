#pragma once

#include <queue>
#include "Types.h"

using namespace std;


struct Point2D;

class Queue
{
private:
	::queue<Point2D> _queue;

public:
	Queue();
	//~Queue();

	void push(Point2D point);

	Point2D pop();

	int getLength();
};



