#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional> // std::hash ����� ���� �߰�

using namespace std;

struct Member {
    string username; // ���̵�
    string password; // ��й�ȣ (�ؽ�ȭ)
    string name;     // ����
    string contact;  // ����ó
    string address;  // �ּ�
};

vector<Member> members;

// ��й�ȣ�� �ؽ�ȭ�ϴ� �Լ�
string hashPassword(const string& password) {
    return to_string(std::hash<string>{}(password));
}

// ���Ͽ��� �� ������ �ҷ����� �Լ�
void loadMembersFromFile() {
    ifstream inFile("customers.txt");
    if (!inFile) {
        cout << "�� ���� ������ �� �� �����ϴ�.\n";
        return;
    }

    Member member;
    string line;
    while (getline(inFile, line)) {
        size_t pos = 0;
        pos = line.find(',');
        member.username = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        member.password = line.substr(0, pos); // �ؽõ� ��й�ȣ
        line.erase(0, pos + 1);

        pos = line.find(',');
        member.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        member.contact = line.substr(0, pos);
        line.erase(0, pos + 1);

        member.address = line; // ������ �κ��� �ּ�

        members.push_back(member);
    }
    inFile.close();
}

void signUp() {
    Member newMember;
    cout << "���̵� �Է��ϼ���: ";
    cin >> newMember.username;
    cout << "��й�ȣ�� �Է��ϼ���: ";
    string password;
    cin >> password;
    newMember.password = hashPassword(password); // ��й�ȣ �ؽ�ȭ
    members.push_back(newMember);
    cout << "ȸ�������� �Ϸ�Ǿ����ϴ�.\n";
}

bool login() {
    string username, password;
    cout << "���̵� �Է��ϼ���: ";
    cin >> username;
    cout << "��й�ȣ�� �Է��ϼ���: ";
    cin >> password;

    string hashedPassword = hashPassword(password); // �Է��� ��й�ȣ �ؽ�ȭ

    for (const auto& member : members) {
        if (member.username == username && member.password == hashedPassword) { // �ؽõ� ��й�ȣ ��
            cout << "�α��� ����!\n";
            return true;
        }
    }
    cout << "�α��� ����. ����� �̸� �Ǵ� ��й�ȣ�� �߸��Ǿ����ϴ�.\n";
    return false;
}

void changePassword() {
    string username, oldPassword, newPassword;
    cout << "����� ���̵� �Է��ϼ���: ";
    cin >> username;
    cout << "���� ��й�ȣ�� �Է��ϼ���: ";
    cin >> oldPassword;

    string hashedOldPassword = hashPassword(oldPassword); // ���� ��й�ȣ �ؽ�ȭ

    for (auto& member : members) {
        if (member.username == username && member.password == hashedOldPassword) {
            cout << "�� ��й�ȣ�� �Է��ϼ���: ";
            cin >> newPassword;
            member.password = hashPassword(newPassword); // �� ��й�ȣ �ؽ�ȭ
            cout << "��й�ȣ�� ����Ǿ����ϴ�.\n";
            return;
        }
    }
    cout << "��й�ȣ ���� ����. ����� �̸� �Ǵ� ��й�ȣ�� �߸��Ǿ����ϴ�.\n";
}

void registerCustomer() {
    string username;
    Member newCustomer;

    cout << "����� ���̵� �Է��ϼ���: ";
    cin >> username;

    for (const auto& member : members) {
        if (member.username == username) {
            newCustomer.username = username;
            cout << "������ �Է��ϼ���: ";
            cin.ignore();
            getline(cin, newCustomer.name);
            cout << "����ó�� �Է��ϼ���: ";
            getline(cin, newCustomer.contact);
            cout << "�ּҸ� �Է��ϼ���: ";
            getline(cin, newCustomer.address);
            cout << "�� ��й�ȣ�� �Է��ϼ���: ";
            getline(cin, member.password);
            members.push_back(newCustomer);
            cout << "�� ������ ��ϵǾ����ϴ�.\n";
            return;
        }
    }
    cout << "ȸ���� �ƴմϴ�.\n";
}

void viewCustomerInfo() {
    string username;
    cout << "����� ���̵� �Է��ϼ���: ";
    cin >> username;

    for (const auto& member : members) {
        if (member.username == username) {
            cout << "����: " << member.name << endl;
            cout << "����ó: " << member.contact << endl;
            cout << "�ּ�: " << member.address << endl;
            cout << "��й�ȣ: " << member.password << " (�ؽ�ȭ�� ��й�ȣ)" << endl; // �ؽ�ȭ�� ��й�ȣ ǥ��
            return;
        }
    }
    cout << "ȸ���� �ƴմϴ�.\n";
}

void modifyCustomerInfo() {
    string username;
    cout << "����� ���̵� �Է��ϼ���: ";
    cin >> username;

    for (auto& member : members) {
        if (member.username == username) {
            cout << "�� ������ �Է��ϼ���: ";
            cin.ignore();
            getline(cin, member.name);
            cout << "�� ����ó�� �Է��ϼ���: ";
            getline(cin, member.contact);
            cout << "�� �ּҸ� �Է��ϼ���: ";
            getline(cin, member.address);
            cout << "�� ��й�ȣ�� �Է��ϼ���: ";
            getline(cin, member.password);
            cout << "�� ������ �����Ǿ����ϴ�.\n";
            return;
        }
    }
    cout << "ȸ���� �ƴմϴ�.\n";
}

void deleteCustomerInfo() {
    string username;
    cout << "������ ����� ���̵� �Է��ϼ���: ";
    cin >> username;

    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it->username == username) {
            members.erase(it);
            cout << "�� ������ �����Ǿ����ϴ�.\n";
            return;
        }
    }
    cout << "ȸ���� �ƴմϴ�.\n";
}

void listCustomers() {
    cout << "�� ���:\n";
    for (const auto& member : members) {
        cout << "����� ���̵�: " << member.username
            << " | ����: " << member.name
            << " | ����ó: " << member.contact
            << " | �ּ�: " << member.address 
            << " | ��й�ȣ: " << member.password << endl;
    }
}

void saveToFile() {
    ofstream outFile("customers.txt");
    for (const auto& member : members) {
        outFile << member.username << ","
            << member.password << ","
            << member.name << ","
            << member.contact << ","
            << member.address << endl;
    }
    outFile.close();
    cout << "�� ������ ���Ͽ� ����Ǿ����ϴ�.\n";
}
