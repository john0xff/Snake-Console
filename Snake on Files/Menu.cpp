#include "Map.h"
#include "Menu.h"
#include "Queue.h"

void Menu::menuChoice()
{
	char key;

	cout << "\n\t >> Welcome in SnakeGame <<" << endl
			<< "\n\t Choose menu number: " << endl
			<< "\t 1. New " << endl
			<< "\t 2. Load " << endl
			<< "\t 3. Exit " <<endl;

	cin >> key;

	if(key)
	{
		switch(key)
		{
		case '1':
			{
				Point2D player = {10, 8};
					
				while(true)
				{
					Map *map = new Map(player, 10, 20);
					map->runGame();
					
					cout << "Would you like start game again ? (y/n)" << endl;
					char resp;
					cin >> resp;

					if(resp == 'y')
						continue;	

					break;
				}
			}
			break;

		case '2':
			{
				cout << " I'm working on it" << endl;
			}
			break;

		}
	}
}
