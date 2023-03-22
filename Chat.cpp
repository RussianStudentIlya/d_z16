#include <iostream>
#include "Chat.h"

void Chat::start() {
	isChatWork_ = true; /// ���� ��� ������ �� ����
}

shared_ptr<User> Chat::getUserByLogin(const string& login) const /// ---- ��_16
{ 
	for (auto it = users_.begin(); it != users_.end(); ++it) // ���� �������� �� ����� ������� �������������
	{
		if (login == it->second.getUserLogin()) // �������� ���������� ������
			return make_shared<User>(it->second); /// ���������� ��������� �� �������� �������������
	}

	return nullptr;
}

shared_ptr<User> Chat::getUserByName(const string& name) const /// ---- ��_16
{
	for (auto it = users_.begin(); it != users_.end(); ++it)
	{
		if (name == it->second.getUserName())
			return make_shared<User>(it->second); /// ���������� ��������� �� �������� ������������� �� �����
	}

	return nullptr;

}

void Chat::login() /// ����������� � ��� �� ��� ���������� ������ � ������
{
	string login, password;
	char operation;

	do
	{
		cout << "�����: ";
		cin >> login;
		cout << "������: ";
		cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;

			cout << "������ �����..." << endl;
			cout << "������� (0) ����� ����� ��� ������ ������ ����� ��������� ����: ";
			cin >> operation;

			if (operation == '0')
				break;

		}

	} while (!currentUser_);
}

void Chat::signUp() /// ����������� ������������ � ����
{
	string login, password, name;

	cout << "�����: ";
	cin >> login;
	cout << "������: ";
	cin >> password;
	cout << "��� ������������: ";
	cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	if (getUserByName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);

	/*-------��_16-------*/
	int id_user = rand() % RAND_MAX; //�������� id

	user.addLoginId(user.getUserLogin(), id_user); // ���������� id ������������


	users_.insert(make_pair(id_user, user)); // ���������� ������ ������������ � ���������
	/*--------------*/

	currentUser_ = make_shared<User>(user);
}

void Chat::showChat() const // ���������� ������������ ���������, ����������� ������������ ��� ����
{
	string from;
	string to;

	cout << "- - - ��� - - -" << endl;

	for (auto& mess : messages_)
	{
		/// ���������� ���������: �� �������� ������������, ��� ���� � ��� ����
		if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			from = (currentUser_->getUserLogin() == mess.getFrom()) ? "�" : getUserByLogin(mess.getFrom())->getUserName();

			if (mess.getTo() == "all")
			{
				to = "(���� (all))";
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "�" : getUserByLogin(mess.getTo())->getUserName();
			}

			cout << "��������� ��: " << from << " ����: " << to << endl;
			cout << "�����: " << mess.getText() << endl;
		}
	}

	cout << "- - - - - - - - - - - -" << endl;
}

void Chat::showLoginMenu() /// ����������� ���������� ���� ��������� - ���� �������� ������
{
	currentUser_ = nullptr;

	char operation;

	do
	{
		cout << "\033[33m" << "(1)����" << endl;
		cout << "(2)�����������" << endl;
		cout << "(3)������������" << endl;
		cout << "(0)�����" << endl;
		cout << "\033[36m" << ">> " << "\033[0m";
		cin >> operation;

		switch (operation)
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case '3':
			cout << "��� �������� ��������:" << endl;
			cout << "1. ������� �������� - ������, ������ ��� ������� Main.cpp � Chat.h" << endl;
			cout << "2. ���� ������� - ������ ��� ������� User.h � Message.h." << endl;
			cout << "3. Reido Aya - ������ ��� ������ Chat.cpp." << endl;
			break;
		case '0':
			isChatWork_ = false;
			break;
		default:
			cout << "1 ��� 2 ..." << endl;
			break;

		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu() // ���������� ���������� ���� ����, ����� ����������� ������������
{
	char operation;

	cout << "������, " << currentUser_->getUserName() << endl;

	while (currentUser_)
	{
		cout << "(1)�������� ��� | (2)��������� ��������� | (3)�������� ��� � ���� | (0)����� ";

		cout << endl
			<< ">> ";
		cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case '0':
			currentUser_ = nullptr;
			break;
		default:
			cout << "�������� �����.." << endl;
			break;
		}


	}
}

void Chat::showAllUsersName() const /// ����������  ������ ������������� ����
{
	cout << "- - - � ���� - - -" << endl;
	
	/*-------��_16-------*/

	for (auto it = users_.begin(); it != users_.end(); ++it)
	{
		cout << it->second.getUserName();

		if (currentUser_->getUserLogin() == it->second.getUserLogin())
			cout << " (�) ";

		cout << endl;
	}
	/*--------------*/
	cout << "- - - - - - - - -" << endl;
}

void Chat::addMessage() //������������ ���������
{
	string to, text;

	cout << "���� (������������ ��� ����(������� all)): ";
	cin >> to;
	cout << "���������: ";
	cin.ignore(); // ������������ ����� ��������� ����������� �������
	getline(cin, text); /// ���� ���������� ��������� � ���������

	if (!(to == "all" || getUserByName(to))) // ���� �� ������� ����� ���������� �� �����
	{
		cout << "����� ������������ �� ������" << to << endl;
		return;
	}

	if (to == "all")
		messages_.push_back(Message{ currentUser_->getUserLogin(), "all", text });
	else
		messages_.push_back(Message{ currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text });

}