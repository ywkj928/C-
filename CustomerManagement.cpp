#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional> // std::hash ����� ���� �߰�

using namespace std;

// ȸ�� ������ �����ϴ� ����ü
struct Member {
    string username; // ���̵�
    string password; // ��й�ȣ (�ؽ�ȭ)
    string name;     // ����
    string contact;  // ����ó
    string address;  // �ּ�
};

vector<Member> members; // ȸ�� ������ �����ϴ� ����

// ��й�ȣ�� �ؽ�ȭ�ϴ� �Լ�
string hashPassword(const string& password) {
    return to_string(std::hash<string>{}(password)); // ��й�ȣ�� �ؽ�ȭ�Ͽ� ���ڿ��� ��ȯ
}

// ���Ͽ��� �� ������ �ҷ����� �Լ�
void loadMembersFromFile() {
    ifstream inFile("customers.txt"); // �� ���� ���� ����
    if (!inFile) { // ���� ���� ���� ��
        cout << "�� ���� ������ �� �� �����ϴ�.\n";
        return;
    }

    Member member; // ���ο� ȸ�� ������ ������ ����
    string line; // ���Ͽ��� ���� �� ��
    while (getline(inFile, line)) { // ������ �� ���� �б�
        size_t pos = 0;
        pos = line.find(','); // ù ��° ��ǥ ��ġ ã��
        member.username = line.substr(0, pos); // ���̵� ����
        line.erase(0, pos + 1); // ���� �κ� ����

        pos = line.find(','); // ���� ��ǥ ��ġ ã��
        member.password = line.substr(0, pos); // ��й�ȣ ���� 
        line.erase(0, pos + 1); // ���� �κ� ����

        pos = line.find(','); // ���� ��ǥ ��ġ ã��
        member.name = line.substr(0, pos); // ���� ����
        line.erase(0, pos + 1); // ���� �κ� ����

        pos = line.find(','); // ���� ��ǥ ��ġ ã��
        member.contact = line.substr(0, pos); // ����ó ����
        line.erase(0, pos + 1); // ���� �κ� ����

        member.address = line; // ������ �κ��� �ּҷ� ����

        members.push_back(member); // ���Ϳ� ȸ�� ���� �߰�
    }
    inFile.close(); // ���� �ݱ�
}

// ȸ������ �Լ�
void signUp() {
    Member newMember; // ���ο� ȸ�� ����
    cout << "���̵� �Է��ϼ���: ";
    cin >> newMember.username; // ���̵� �Է�
    cout << "��й�ȣ�� �Է��ϼ���: ";
    string password; // ��й�ȣ ����
    cin >> password; // ��й�ȣ �Է�
    newMember.password = hashPassword(password); // ��й�ȣ �ؽ�ȭ
    members.push_back(newMember); // ���Ϳ� �߰�
    cout << "ȸ�������� �Ϸ�Ǿ����ϴ�.\n";
}

// �α��� �Լ�
bool login() {
    string username, password; // ���̵�� ��й�ȣ ����
    cout << "���̵� �Է��ϼ���: ";
    cin >> username; // ���̵� �Է�
    cout << "��й�ȣ�� �Է��ϼ���: ";
    cin >> password; // ��й�ȣ �Է�

    string hashedPassword = hashPassword(password); // �Է��� ��й�ȣ �ؽ�ȭ

    // ȸ�� ������ ��
    for (const auto& member : members) {
        if (member.username == username && member.password == hashedPassword) { // �ؽõ� ��й�ȣ ��
            cout << "�α��� ����!\n";
            return true; // �α��� ����
        }
    }
    cout << "�α��� ����. ����� �̸� �Ǵ� ��й�ȣ�� �߸��Ǿ����ϴ�.\n";
    return false; // �α��� ����
}

// ��й�ȣ ���� �Լ�
void changePassword() {
    string username, oldPassword, newPassword; // ���̵�, ���� ��й�ȣ, �� ��й�ȣ ����
    cout << "����� ���̵� �Է��ϼ���: ";
    cin >> username; // ���̵� �Է�
    cout << "���� ��й�ȣ�� �Է��ϼ���: ";
    cin >> oldPassword; // ���� ��й�ȣ �Է�

    string hashedOldPassword = hashPassword(oldPassword); // ���� ��й�ȣ �ؽ�ȭ

    // ȸ�� ������ ��
    for (auto& member : members) {
        if (member.username == username && member.password == hashedOldPassword) {
            cout << "�� ��й�ȣ�� �Է��ϼ���: ";
            cin >> newPassword; // �� ��й�ȣ �Է�
            member.password = hashPassword(newPassword); // �� ��й�ȣ �ؽ�ȭ
            cout << "��й�ȣ�� ����Ǿ����ϴ�.\n";
            return; // ��й�ȣ ���� ����
        }
    }
    cout << "��й�ȣ ���� ����. ����� �̸� �Ǵ� ��й�ȣ�� �߸��Ǿ����ϴ�.\n";
}

// �� ��� �Լ�
void registerCustomer() {
    string username; // ���̵� ����
    Member newCustomer; // ���ο� �� ����

    cout << "����� ���̵� �Է��ϼ���: ";
    cin >> username; // ���̵� �Է�

    // ȸ�� ���� Ȯ��
    for (const auto& member : members) {
        if (member.username == username) {
            newCustomer.username = username; // ���̵� ����
            cout << "������ �Է��ϼ���: ";
            cin.ignore(); // ���� �Է� ���� ����
            getline(cin, newCustomer.name); // ���� �Է�
            cout << "����ó�� �Է��ϼ���: ";
            getline(cin, newCustomer.contact); // ����ó �Է�
            cout << "�ּҸ� �Է��ϼ���: ";
            getline(cin, newCustomer.address); // �ּ� �Է�
            cout << "�� ��й�ȣ�� �Է��ϼ���: ";
            string password; // ��й�ȣ ����
            getline(cin, password); // ��й�ȣ �Է�
            newCustomer.password = hashPassword(password); // ��й�ȣ �ؽ�ȭ
            members.push_back(newCustomer); // �� ���� �߰�
            cout << "�� ������ ��ϵǾ����ϴ�.\n";
            return; // ��� ����
        }
    }
    cout << "ȸ���� �ƴմϴ�.\n"; // ȸ���� �ƴ� ���
}

// �� ���� ��ȸ �Լ�
void viewCustomerInfo() {
    string username; // ���̵� ����
    cout << "����� ���̵� �Է��ϼ���: ";
    cin >> username; // ���̵� �Է�

    // ȸ�� ���� Ȯ��
    for (const auto& member : members) {
        if (member.username == username) {
            cout << "����: " << member.name << endl;
            cout << "����ó: " << member.contact << endl;
            cout << "�ּ�: " << member.address << endl;
            // ��й�ȣ�� ������� �ʵ��� ����
            cout << "��й�ȣ: (�����)" << endl; // ��й�ȣ ���Ȼ� ����� ó��
            return; // ��ȸ ����
        }
    }
    cout << "ȸ���� �ƴմϴ�.\n"; // ȸ���� �ƴ� ���
}

// �� ���� ���� �Լ�
void modifyCustomerInfo() {
    string username; // ���̵� ����
    cout << "����� ���̵� �Է��ϼ���: ";
    cin >> username; // ���̵� �Է�

    // ȸ�� ���� Ȯ��
    for (auto& member : members) {
        if (member.username == username) {
            cout << "�� ������ �Է��ϼ���: ";
            cin.ignore(); // ���� �Է� ���� ����
            getline(cin, member.name); // �� ���� �Է�
            cout << "�� ����ó�� �Է��ϼ���: ";
            getline(cin, member.contact); // �� ����ó �Է�
            cout << "�� �ּҸ� �Է��ϼ���: ";
            getline(cin, member.address); // �� �ּ� �Է�
            cout << "�� ��й�ȣ�� �Է��ϼ���: ";
            string password; // ��й�ȣ ����
            getline(cin, password); // �� ��й�ȣ �Է�
            member.password = hashPassword(password); // ��й�ȣ �ؽ�ȭ
            cout << "�� ������ �����Ǿ����ϴ�.\n";
            return; // ���� ����
        }
    }
    cout << "ȸ���� �ƴմϴ�.\n"; // ȸ���� �ƴ� ���
}

// �� ���� ���� �Լ�
void deleteCustomerInfo() {
    string username; // ���̵� ����
    cout << "������ ����� ���̵� �Է��ϼ���: ";
    cin >> username; // ���̵� �Է�

    // ȸ�� ���� Ȯ�� �� ����
    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it
