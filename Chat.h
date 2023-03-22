#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"
#include "User.h"
#include <map>

#define RAND_MAX 1000

using namespace std;

/*-----����������-----*/
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
	bool isChatWork_ = false; /// ���� ��� ������ �� ����

	//vector<User> users_; /// ������������ ������ (������) ������� �������������
	map<int,User>users_; /// ������������ ������ (��������� map) ������� ������������� ---- ��_16

	vector<Message> messages_; /// ������������ ������ (������) ���������
	shared_ptr<User> currentUser_ = nullptr; /// ���������� �������� ������������

	void login();/// ����������� � ��� �� ��� ���������� ������ � ������
	void signUp(); /// ����������� ������������ � ����
	void showChat() const; // ���������� ������������ ���������, ����������� ������������ ��� ����
	void showAllUsersName() const; /// ����������  ������ ������������� ����
	void addMessage(); //������������ ���������

	//vector<User>& getAllUsers() { return users_; }
	map<int, User>& getAllUsers() { return users_; } /// ---- ��_16

	vector<Message>& getAllMessage() { return messages_; }
	shared_ptr<User> getUserByLogin(const string& login) const;
	shared_ptr<User> getUserByName(const string& name) const;

public:
	void start();/// ������ ����
	bool isChatWork() const { return isChatWork_; } /// ��������, �������� ��� ��� ��� (���� true - ��� ��������, ���� false - ���)
	shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void showLoginMenu(); /// ����������� ���������� ���� ��������� - ���� �������� ������
	void showUserMenu(); // ���������� ���������� ���� ����, ����� ����������� ������������
};
