#include <iostream>
#include "Customer.h"

using namespace std;

// �α��� �޴� �Լ�
void displayLoginMenu() {
    cout << "\n=================\n"; // ���м� �߰�
    cout << "      �α���     \n"; // �α��� ����
    cout << "=================\n";
    cout << "1. ȸ������\n"; // ȸ������ �ɼ�
    cout << "2. �α���\n"; // �α��� �ɼ�
    cout << "3. ��й�ȣ ����\n"; // ��й�ȣ ���� �ɼ�
    cout << "0. ����\n"; // ���α׷� ���� �ɼ�
    cout << "����: "; // ����� ���� �ȳ�
}

// �� ���� ���� �޴� �Լ�
void displayCustomerMenu() {
    cout << "\n=================\n"; // ���м� �߰�
    cout << " �� ���� ���� \n"; // �� ���� ���� ����
    cout << "=================\n";
    cout << "1. �� ���� ���\n"; // �� ���� ��� �ɼ�
    cout << "2. �� ���� ��ȸ\n"; // �� ���� ��ȸ �ɼ�
    cout << "3. �� ���� ����\n"; // �� ���� ���� �ɼ�
    cout << "4. �� ���� ����\n"; // �� ���� ���� �ɼ�
    cout << "5. �� ���\n"; // �� ��� ���� �ɼ�
    cout << "6. �� ���� ���� ���\n"; // �� ���� ���Ϸ� ���� �ɼ�
    cout << "0. ����\n"; // ���α׷� ���� �ɼ�
    cout << "����: "; // ����� ���� �ȳ�
}

int main() {
    CustomerManagement cm; // CustomerManagement Ŭ���� �ν��Ͻ� ����
    cm.loadMembersFromFile(); // ���α׷� ���� �� �� ���� �ҷ�����

    int choice; // ����� ������ ������ ����
    while (true) {
        displayLoginMenu(); // �α��� �޴� ǥ��

        // ����� �Է� ó��
        if (!(cin >> choice)) {
            cin.clear(); // �Է� ���� ����
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���� �Է� ����
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n";
            continue; // �߸��� �Է� �� ���� ó������ ���ư�
        }

        switch (choice) {
        case 1:
            cm.signUp(); // ȸ������
            break;
        case 2:
            if (cm.login()) { // �α��� ���� ��
                while (true) {
                    displayCustomerMenu(); // �� ���� ���� �޴� ǥ��
                    if (!(cin >> choice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n";
                        continue; // �߸��� �Է� �� ���� ó������ ���ư�
                    }

                    switch (choice) {
                    case 1:
                        cm.registerCustomer(); // �� ���� ���
                        break;
                    case 2:
                        cm.viewCustomerInfo(); // �� ���� ��ȸ
                        break;
                    case 3:
                        cm.modifyCustomerInfo(); // �� ���� ����
                        break;
                    case 4:
                        cm.deleteCustomerInfo(); // �� ���� ����
                        break;
                    case 5:
                        cm.listCustomers(); // �� ��� ����
                        break;
                    case 6:
                        cm.saveToFile(); // �� ���� ���Ϸ� ����
                        break;
                    case 0:
                        cout << "���α׷��� �����մϴ�.\n"; // ���� �޽���
                        return 0; // ����
                    default:
                        cout << "�߸��� �����Դϴ�.\n"; // �߸��� �Է� ó��
                        break;
                    }
                }
            }
            break;
        case 3:
            cm.changePassword(); // ��й�ȣ ����
            break;
        case 0:
            cout << "���α׷��� �����մϴ�.\n"; // ���� �޽���
            return 0; // ����
        default:
            cout << "�߸��� �����Դϴ�.\n"; // �߸��� �Է� ó��
            break;
        }
    }
    return 0; // ���α׷� ����
}
