#include <iostream>
#include "Customer.h"

using namespace std;

// �α��� �޴� �Լ�
void displayLoginMenu() {
    cout << "\n=================\n";
    cout << "      �α���     \n";
    cout << "=================\n";
    cout << "1. ȸ������\n";
    cout << "2. �α���\n";
    cout << "3. ��й�ȣ ����\n";
    cout << "0. ����\n";
    cout << "����: ";
}

// �� ���� ���� �޴� �Լ�
void displayCustomerMenu() {
    cout << "\n=================\n";
    cout << " �� ���� ���� \n";
    cout << "=================\n";
    cout << "1. �� ���� ���\n";
    cout << "2. �� ���� ��ȸ\n";
    cout << "3. �� ���� ����\n";
    cout << "4. �� ���� ����\n";
    cout << "5. �� ���\n";
    cout << "6. �� ���� ���� ���\n";
    cout << "0. ����\n";
    cout << "����: ";
}

int main() {
    CustomerManagement cm;
    cm.loadMembersFromFile(); // ���α׷� ���� �� �� ���� �ҷ�����

    int choice;
    while (true) {
        displayLoginMenu(); // �α��� �޴� ǥ��
        cin >> choice;

        switch (choice) {
        case 1:
            cm.signUp(); // ȸ������
            break;
        case 2:
            if (cm.login()) { // �α��� ���� ��
                while (true) {
                    displayCustomerMenu(); // �� ���� ���� �޴� ǥ��
                    cin >> choice;

                    switch (choice) {
                    case 1: cm.registerCustomer(); break;
                    case 2: cm.viewCustomerInfo(); break;
                    case 3: cm.modifyCustomerInfo(); break;
                    case 4: cm.deleteCustomerInfo(); break;
                    case 5: cm.listCustomers(); break;
                    case 6: cm.saveToFile(); break;
                    case 0: return 0; // ����
                    default: cout << "�߸��� �����Դϴ�.\n"; break; // �߸��� �Է� ó��
                    }
                }
            }
            break;
        case 3:
            cm.changePassword(); // ��й�ȣ ����
            break;
        case 0:
            cout << "���α׷��� �����մϴ�.\n";
            return 0; // ����
        default:
            cout << "�߸��� �����Դϴ�.\n"; // �߸��� �Է� ó��
            break;
        }
    }
    return 0;
}
