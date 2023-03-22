#include <iostream>
#include "Chat.h"

void Chat::start() {
	isChatWork_ = true; /// Флаг для выхода из меню
}

shared_ptr<User> Chat::getUserByLogin(const string& login) const /// ---- ДЗ_16
{ 
	for (auto it = users_.begin(); it != users_.end(); ++it) // цикл проходит по всему массиву пользователей
	{
		if (login == it->second.getUserLogin()) // проверка совподения логина
			return make_shared<User>(it->second); /// возвращает указатель на текущего полльзователя
	}

	return nullptr;
}

shared_ptr<User> Chat::getUserByName(const string& name) const /// ---- ДЗ_16
{
	for (auto it = users_.begin(); it != users_.end(); ++it)
	{
		if (name == it->second.getUserName())
			return make_shared<User>(it->second); /// возвращает указатель на текущего полльзователя по имени
	}

	return nullptr;

}

void Chat::login() /// Авторизация в чат по уже созданному логину и паролю
{
	string login, password;
	char operation;

	do
	{
		cout << "Логин: ";
		cin >> login;
		cout << "Пароль: ";
		cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;

			cout << "Ошибка входа..." << endl;
			cout << "Нажмите (0) чтобы выйти или другую кнопку чтобы повторить вход: ";
			cin >> operation;

			if (operation == '0')
				break;

		}

	} while (!currentUser_);
}

void Chat::signUp() /// Регистрация пользователя в чате
{
	string login, password, name;

	cout << "Логин: ";
	cin >> login;
	cout << "Пароль: ";
	cin >> password;
	cout << "Имя пользователя: ";
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

	/*-------ДЗ_16-------*/
	int id_user = rand() % RAND_MAX; //создание id

	user.addLoginId(user.getUserLogin(), id_user); // добавление id пользователя


	users_.insert(make_pair(id_user, user)); // Добавление нового пользователя в контейнер
	/*--------------*/

	currentUser_ = make_shared<User>(user);
}

void Chat::showChat() const // показывает отправленные сообщения, конкретному пользователю или всем
{
	string from;
	string to;

	cout << "- - - Чат - - -" << endl;

	for (auto& mess : messages_)
	{
		/// Показывает сообщение: от текущего пользователя, для него и для всех
		if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			from = (currentUser_->getUserLogin() == mess.getFrom()) ? "Я" : getUserByLogin(mess.getFrom())->getUserName();

			if (mess.getTo() == "all")
			{
				to = "(Всем (all))";
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "Я" : getUserByLogin(mess.getTo())->getUserName();
			}

			cout << "Сообщение от: " << from << " кому: " << to << endl;
			cout << "Текст: " << mess.getText() << endl;
		}
	}

	cout << "- - - - - - - - - - - -" << endl;
}

void Chat::showLoginMenu() /// Отображение стартового меню программы - Меню верхнего уровня
{
	currentUser_ = nullptr;

	char operation;

	do
	{
		cout << "\033[33m" << "(1)Вход" << endl;
		cout << "(2)Регистрация" << endl;
		cout << "(3)Разработчики" << endl;
		cout << "(0)Выход" << endl;
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
			cout << "Над проектом работали:" << endl;
			cout << "1. Дмитрий Воробьев - тимлид, работа над блоками Main.cpp и Chat.h" << endl;
			cout << "2. Илья Кривцов - Работа над блоками User.h и Message.h." << endl;
			cout << "3. Reido Aya - Работа над блоком Chat.cpp." << endl;
			break;
		case '0':
			isChatWork_ = false;
			break;
		default:
			cout << "1 или 2 ..." << endl;
			break;

		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu() // отображает внутреннее меню чата, после авторизации пользователя
{
	char operation;

	cout << "Привет, " << currentUser_->getUserName() << endl;

	while (currentUser_)
	{
		cout << "(1)Показать чат | (2)Отправить сообщение | (3)Показать кто в чате | (0)Выйти ";

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
			cout << "сделайте выбор.." << endl;
			break;
		}


	}
}

void Chat::showAllUsersName() const /// Показывает  список пользователей чата
{
	cout << "- - - В чате - - -" << endl;
	
	/*-------ДЗ_16-------*/

	for (auto it = users_.begin(); it != users_.end(); ++it)
	{
		cout << it->second.getUserName();

		if (currentUser_->getUserLogin() == it->second.getUserLogin())
			cout << " (Я) ";

		cout << endl;
	}
	/*--------------*/
	cout << "- - - - - - - - -" << endl;
}

void Chat::addMessage() //Формирования сообщения
{
	string to, text;

	cout << "Кому (пользователю или всем(команда all)): ";
	cin >> to;
	cout << "Сообщение: ";
	cin.ignore(); // игнорировать любые введенные посторонние символы
	getline(cin, text); /// ввод текстового сообщения с пробелами

	if (!(to == "all" || getUserByName(to))) // если не удалось найти получателя по имени
	{
		cout << "Такой пользователь не найден" << to << endl;
		return;
	}

	if (to == "all")
		messages_.push_back(Message{ currentUser_->getUserLogin(), "all", text });
	else
		messages_.push_back(Message{ currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text });

}