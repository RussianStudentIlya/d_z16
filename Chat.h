#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"
#include "User.h"
#include <map>

#define RAND_MAX 1000

using namespace std;

/*-----Исключение-----*/
struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override { return "error: user login is busy"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "error: user name is busy"; }
};
/*-----*/

class Chat 
{
	bool isChatWork_ = false; /// Флаг для выхода из меню

	//vector<User> users_; /// Динамический массив (вектор) текущих пользователей
	map<int,User>users_; /// Динамический массив (контейнер map) текущих пользователей ---- ДЗ_16

	vector<Message> messages_; /// Динамический массив (вектор) сообщений
	shared_ptr<User> currentUser_ = nullptr; /// показывает текущего пользователя

	void login();/// Авторизация в чат по уже созданному логину и паролю
	void signUp(); /// Регистрация пользователя в чате
	void showChat() const; // показывает отправленные сообщения, конкретному пользователю или всем
	void showAllUsersName() const; /// Показывает  список пользователей чата
	void addMessage(); //Формирования сообщения

	//vector<User>& getAllUsers() { return users_; }
	map<int, User>& getAllUsers() { return users_; } /// ---- ДЗ_16

	vector<Message>& getAllMessage() { return messages_; }
	shared_ptr<User> getUserByLogin(const string& login) const;
	shared_ptr<User> getUserByName(const string& name) const;

public:
	void start();/// запуск чата
	bool isChatWork() const { return isChatWork_; } /// проверка, работает чат или нет (если true - чат работает, если false - нет)
	shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void showLoginMenu(); /// Отображение стартового меню программы - Меню верхнего уровня
	void showUserMenu(); // отображает внутреннее меню чата, после авторизации пользователя
};
