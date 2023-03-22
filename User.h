#pragma once
#include <string>
#include <map>
using namespace std;

class User
{
private:
	const string login_; // ����� ������������
	string password_;  // ������
	string name_; // ��� ������������

	map<string,int> _loginId;


public:
	User(const string& login, const string& password, const string& name)
		:login_(login), password_(password), name_(name) {}


	const string& getUserLogin() const noexcept { return this->login_; } /// ��������� ����� ������������

	const string& getUserPassword() const { return this->password_; } /// ��������� ������ ������������
	void setUserPassword(const string& password) { this->password_ = password; } /// ������� ������ ������������

	const string& getUserName() const { return this->name_; } /// ��������� ��� ������������
	void setUserName(const string& name) { this->name_ = name; } /// �������� ��� ������������

	/*-------��_16-------*/
	void addLoginId(const string& login, int idLogin)
	{
		auto value = _loginId.find(login);

		if (value == _loginId.end())
			_loginId.insert(make_pair(login, idLogin));
		else
			cout << "id login ����������" << endl;
	}
	/*--------------*/
};