#include <iostream>
#include "Chat.h"

using namespace std;
int main()
{
	setlocale(LC_ALL, ""); // Для кириллицы в консоли. 
	cout << "Добро пожаловать в консольный чат." << endl;
	cout << "Для продолжения работы выберите одну из указанных ниже опций, нажав на соответствующую кнопку." << endl;
	cout << " --------------------------------------------------------------------------------------------- " << endl;
	Chat chat;

	chat.start();

	while (chat.isChatWork()) {

		chat.showLoginMenu();

		while (chat.getCurrentUser()) {
			chat.showUserMenu();
		}
	}

	return 0;
}
