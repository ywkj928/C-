#ifndef __CUSTOMERMANAGEMENT_H__
#define __CUSTOMERMANAGEMENT_H__

#include <string>
#include <vector>

// ȸ�� ������ �����ϴ� ����ü
struct Member {
    std::string username; // ���̵�
    std::string password; // ��й�ȣ
    std::string name;     // ����
    std::string contact;  // ����ó
    std::string address;  // �ּ�
};

// ȸ�� ������ �����ϴ� ���� ����
extern std::vector<Member> members;

// �� ������ ���Ͽ��� �ҷ����� �Լ�
void loadMembersFromFile();

// ȸ������ �Լ�
void signUp();

// �α��� �Լ�
bool login();

// ��й�ȣ ���� �Լ�
void changePassword();

// �� ��� �Լ�
void registerCustomer();

// �� ���� ��ȸ �Լ�
void viewCustomerInfo();

// �� ���� ���� �Լ�
void modifyCustomerInfo();

// �� ���� ���� �Լ�
void deleteCustomerInfo();

// �� ��� ��� �Լ�
void listCustomers();

// �� ������ ���Ͽ� �����ϴ� �Լ�
void saveToFile();

#endif
