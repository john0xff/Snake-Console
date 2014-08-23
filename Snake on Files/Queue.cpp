#include "Map.h"
#include "Menu.h"
#include "Queue.h"

Queue::Queue()
{
	
}

void Queue::push(Point2D point)
{
	this->_queue.push(point);
}

Point2D Queue::pop()
{
	Point2D tmp = this->_queue.front();
	this->_queue.pop();

	return tmp;
}

int Queue::getLength()
{
	return this->_queue.size();
}