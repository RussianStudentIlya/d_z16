#pragma once
#include <string>
#include <map>
using namespace std;

class User
{
private:
	const string login_; // логин пользователя
	string password_;  // пароль
	string name_; // имя пользователя

	map<string,int> _loginId;


public:
	User(const string& login, const string& password, const string& name)
		:login_(login), password_(password), name_(name) {}


	const string& getUserLogin() const noexcept { return this->login_; } /// прочитать логин пользователя

	const string& getUserPassword() const { return this->password_; } /// прочитать пароль пользователя
	void setUserPassword(const string& password) { this->password_ = password; } /// изменит пароль пользователя

	const string& getUserName() const { return this->name_; } /// прочитать имя пользователя
	void setUserName(const string& name) { this->name_ = name; } /// изменить имя пользователя

	/*-------ДЗ_16-------*/
	void addLoginId(const string& login, int idLogin)
	{
		auto value = _loginId.find(login);

		if (value == _loginId.end())
			_loginId.insert(make_pair(login, idLogin));
		else
			cout << "id login существует" << endl;
	}
	/*--------------*/
};