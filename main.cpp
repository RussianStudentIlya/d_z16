#include <iostream>
#include "Chat.h"

using namespace std;
int main()
{
	setlocale(LC_ALL, ""); // ��� ��������� � �������. 
	cout << "����� ���������� � ���������� ���." << endl;
	cout << "��� ����������� ������ �������� ���� �� ��������� ���� �����, ����� �� ��������������� ������." << endl;
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
