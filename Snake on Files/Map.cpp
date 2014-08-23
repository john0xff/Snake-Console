#include "Map.h"
#include "Menu.h"
#include "Queue.h"

void Map::setPosition(int x, int y) 
{ 
	COORD pos = {x, y};
	SetConsoleCursorPosition(this->_output, pos);
}

void Map::drawBackground()
{
	for(int y = 0; y < this->_height; ++y)
	{
		char *&row = this->_table[y];

		for(int x = 0; x < this->_width; ++x)
		{
			row[x] = this->_backgroundChar;
			cout << row[x];
		}
		cout << endl;
	}

	cout.flush();
}

bool Map::randomPoint()
{
	if(this->_applesCount >= _applesLimit)
		return false;

	Point2D point;

	point.x = ((double)rand() / (double)RAND_MAX) * (this->_width - 1) + 0.5; // obliczamy wartosc x losowanego punktu
	point.y = ((double)rand() / (double)RAND_MAX) * (this->_height - 1) + 0.5;

	char &value = this->_table[point.y][point.x]; // referencja do wartosci w tablicy

	if(value == _appleChar || value == _playerChar)  // wylosowana pozycja nie moze zawierac punktu ani fragmentu wezyka
		return false;

	value = _appleChar; // majac referencje ustawiamy 'o' (punkt)
	++this->_applesCount;
		
	this->setPosition(point.x, point.y);
	cout << _appleChar;

	return true;
}

void Map::randomPoints()
{
	while(this->randomPoint());
}

void Map::unmarkPlayer()
{
	Point2D tmp = this->_queue.pop();

	this->_table[tmp.y][tmp.x] = _backgroundChar;
	this->setPosition(tmp.x, tmp.y);
	cout << _backgroundChar;
}

void Map::markPlayer()
{
	this->_queue.push(this->_player);

	this->_table[this->_player.y][this->_player.x] = _playerChar;
	this->setPosition(this->_player.x, this->_player.y);
	cout << _playerChar;
}

void Map::updateSnake()
{
	if(this->_table[this->_player.y][this->_player.x] == _appleChar)
		--this->_applesCount;

	else
		this->unmarkPlayer();

	this->markPlayer();
}

bool Map::checkConditions()
{
	if(this->_player.x < 0
		|| this->_player.x > this->_width - 1
		|| this->_player.y < 0
		|| this->_player.y > this->_height - 1
		|| this->_table[this->_player.y][this->_player.x] == _playerChar)
	{
		this->printEnding();

		return false;
	}

	return true;
}

bool Map::movePlayer()
{
	if(_kbhit())
	{
		char key = _getch();

		switch(key)
		{
		case 'a':
			{
				int tmp = this->_direction.x;
				this->_direction.x = this->_direction.y;
				this->_direction.y = -tmp;
			}
			break;

		case 'd':
			{
				int tmp = this->_direction.x;
				this->_direction.x = -this->_direction.y;
				this->_direction.y = tmp;
			}
			break;
		}
	}

	this->_player.x += this->_direction.x;
	this->_player.y += this->_direction.y;

	if(this->checkConditions())
	{
		this->updateSnake();

		return true;
	}
	else
	{
		return false;
	}
}

void Map::updateBar()
{
	this->setPosition(0, this->_height);
	cout << "Apples count: " << this->_applesCount << " " << endl;
}

void Map::printEnding()
{
	system("cls");

	cout << "You walked in wall, sorry end of game.\n" << endl;
}

Map::Map(const Point2D &player, int height = 10, int width = 20)
	: _height(height), _width(width)
{
	this->_output = GetStdHandle(STD_OUTPUT_HANDLE);
	this->_started = false;

	this->_table = new char*[_height];

	for(int y = 0; y < this->_height; ++y)
		this->_table[y] = new char[_width];

	this->_applesCount = 0;
	this->_player = player;
	this->_direction.x = 0;
	this->_direction.y = -1;
}

Map::~Map()
{
	CloseHandle(this->_output);

	for(int y = 0; y < this->_height; ++y)
		delete [] this->_table[y];

	delete [] this->_table;
}

void Map::runGame()
{
	if(this->_started)
		return;

	this->_started = true;

	system("cls");
						
	this->drawBackground();
	this->markPlayer();
	this->randomPoints();
	
	while(this->movePlayer())
	{
		this->randomPoints();
		this->updateBar();

		Sleep(400);
	}

	this->_started = false;
}
