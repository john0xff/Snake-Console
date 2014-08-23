#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "Queue.h"
#include "Types.h"

using namespace std;

class Menu;
class Queue;



class Map
{
friend class Menu;
friend class Queue;

private:
	HANDLE _output;

	static const char _backgroundChar = '.';
	static const char _playerChar = 'x';
	static const char _appleChar = 'o';
	static const int _applesLimit = 10;

	bool _started;

	const int _height;
	const int _width;

	char **_table;

	Point2D _direction;
	Point2D _player;
	Queue _queue;

	int _applesCount;

	void setPosition(int x, int y);

	// Czysci tlo.
	//
	void drawBackground();

	// Losuje punkt na planszy. Jesli nie powiedzie sie losowanie to zwracany jest false.
	//
	bool randomPoint();

	// Dolosowuje punkty do ilosci rownej _applesLimit.
	//
	void randomPoints();

	// Odznacza ostatni element kolejki.
	//
	void unmarkPlayer();

	// Zaznacza pierwszy element kolejki.
	//
	void markPlayer();

	// Aktualizuje jedzenie _applesChar.
	//
	void updateSnake();

	// Sprawdza czy wezyk jest na planszy i czy nie wszedl w siebie.
	//
	bool checkConditions();

	// Ruch wezyka.
	//
	bool movePlayer();

	// Aktualizacja paska _appleChar.
	//
	void updateBar();
	
	// Druk konczacy aktualna rozgrywke.
	//
	void printEnding();

public:
	Map(const Point2D &player, int height, int width);
	~Map();

	void runGame();
};