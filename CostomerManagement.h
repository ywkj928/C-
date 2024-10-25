#ifndef __CUSTOMERMANAGEMENT_H__
#define __CUSTOMERMANAGEMENT_H__

#include <string>
#include <vector>

using namespace std;

struct Member {
    string username; // ���̵�
    string password; // ��й�ȣ
    string name;     // ����
    string contact;  // ����ó
    string address;  // �ּ�
};

extern vector<Member> members;

// ���Ͽ��� �� ������ �ҷ����� �Լ�
void loadMembersFromFile();
void signUp();
bool login();
void changePassword();
void registerCustomer();
void viewCustomerInfo();
void modifyCustomerInfo();
void deleteCustomerInfo();
void listCustomers();
void saveToFile();

#endif
