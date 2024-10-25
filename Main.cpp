#include <iostream>
#include "Customer.h"

using namespace std;

// 로그인 메뉴 함수
void displayLoginMenu() {
    cout << "\n=================\n";
    cout << "      로그인     \n";
    cout << "=================\n";
    cout << "1. 회원가입\n";
    cout << "2. 로그인\n";
    cout << "3. 비밀번호 변경\n";
    cout << "0. 종료\n";
    cout << "선택: ";
}

// 고객 정보 관리 메뉴 함수
void displayCustomerMenu() {
    cout << "\n=================\n";
    cout << " 고객 정보 관리 \n";
    cout << "=================\n";
    cout << "1. 고객 정보 등록\n";
    cout << "2. 고객 정보 조회\n";
    cout << "3. 고객 정보 수정\n";
    cout << "4. 고객 정보 삭제\n";
    cout << "5. 고객 목록\n";
    cout << "6. 고객 정보 파일 출력\n";
    cout << "0. 종료\n";
    cout << "선택: ";
}

int main() {
    CustomerManagement cm;
    cm.loadMembersFromFile(); // 프로그램 시작 시 고객 정보 불러오기

    int choice;
    while (true) {
        displayLoginMenu(); // 로그인 메뉴 표시
        cin >> choice;

        switch (choice) {
        case 1:
            cm.signUp(); // 회원가입
            break;
        case 2:
            if (cm.login()) { // 로그인 성공 시
                while (true) {
                    displayCustomerMenu(); // 고객 정보 관리 메뉴 표시
                    cin >> choice;

                    switch (choice) {
                    case 1: cm.registerCustomer(); break;
                    case 2: cm.viewCustomerInfo(); break;
                    case 3: cm.modifyCustomerInfo(); break;
                    case 4: cm.deleteCustomerInfo(); break;
                    case 5: cm.listCustomers(); break;
                    case 6: cm.saveToFile(); break;
                    case 0: return 0; // 종료
                    default: cout << "잘못된 선택입니다.\n"; break; // 잘못된 입력 처리
                    }
                }
            }
            break;
        case 3:
            cm.changePassword(); // 비밀번호 변경
            break;
        case 0:
            cout << "프로그램을 종료합니다.\n";
            return 0; // 종료
        default:
            cout << "잘못된 선택입니다.\n"; // 잘못된 입력 처리
            break;
        }
    }
    return 0;
}
