#include <iostream>
#include "Customer.h"

using namespace std;

// 로그인 메뉴 함수
void displayLoginMenu() {
    cout << "\n=================\n"; // 구분선 추가
    cout << "      로그인     \n"; // 로그인 제목
    cout << "=================\n";
    cout << "1. 회원가입\n"; // 회원가입 옵션
    cout << "2. 로그인\n"; // 로그인 옵션
    cout << "3. 비밀번호 변경\n"; // 비밀번호 변경 옵션
    cout << "0. 종료\n"; // 프로그램 종료 옵션
    cout << "선택: "; // 사용자 선택 안내
}

// 고객 정보 관리 메뉴 함수
void displayCustomerMenu() {
    cout << "\n=================\n"; // 구분선 추가
    cout << " 고객 정보 관리 \n"; // 고객 정보 관리 제목
    cout << "=================\n";
    cout << "1. 고객 정보 등록\n"; // 고객 정보 등록 옵션
    cout << "2. 고객 정보 조회\n"; // 고객 정보 조회 옵션
    cout << "3. 고객 정보 수정\n"; // 고객 정보 수정 옵션
    cout << "4. 고객 정보 삭제\n"; // 고객 정보 삭제 옵션
    cout << "5. 고객 목록\n"; // 고객 목록 보기 옵션
    cout << "6. 고객 정보 파일 출력\n"; // 고객 정보 파일로 저장 옵션
    cout << "0. 종료\n"; // 프로그램 종료 옵션
    cout << "선택: "; // 사용자 선택 안내
}

int main() {
    CustomerManagement cm; // CustomerManagement 클래스 인스턴스 생성
    cm.loadMembersFromFile(); // 프로그램 시작 시 고객 정보 불러오기

    int choice; // 사용자 선택을 저장할 변수
    while (true) {
        displayLoginMenu(); // 로그인 메뉴 표시

        // 사용자 입력 처리
        if (!(cin >> choice)) {
            cin.clear(); // 입력 버퍼 정리
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 남은 입력 무시
            cout << "잘못된 입력입니다. 다시 시도하세요.\n";
            continue; // 잘못된 입력 시 루프 처음으로 돌아감
        }

        switch (choice) {
        case 1:
            cm.signUp(); // 회원가입
            break;
        case 2:
            if (cm.login()) { // 로그인 성공 시
                while (true) {
                    displayCustomerMenu(); // 고객 정보 관리 메뉴 표시
                    if (!(cin >> choice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "잘못된 입력입니다. 다시 시도하세요.\n";
                        continue; // 잘못된 입력 시 루프 처음으로 돌아감
                    }

                    switch (choice) {
                    case 1:
                        cm.registerCustomer(); // 고객 정보 등록
                        break;
                    case 2:
                        cm.viewCustomerInfo(); // 고객 정보 조회
                        break;
                    case 3:
                        cm.modifyCustomerInfo(); // 고객 정보 수정
                        break;
                    case 4:
                        cm.deleteCustomerInfo(); // 고객 정보 삭제
                        break;
                    case 5:
                        cm.listCustomers(); // 고객 목록 보기
                        break;
                    case 6:
                        cm.saveToFile(); // 고객 정보 파일로 저장
                        break;
                    case 0:
                        cout << "프로그램을 종료합니다.\n"; // 종료 메시지
                        return 0; // 종료
                    default:
                        cout << "잘못된 선택입니다.\n"; // 잘못된 입력 처리
                        break;
                    }
                }
            }
            break;
        case 3:
            cm.changePassword(); // 비밀번호 변경
            break;
        case 0:
            cout << "프로그램을 종료합니다.\n"; // 종료 메시지
            return 0; // 종료
        default:
            cout << "잘못된 선택입니다.\n"; // 잘못된 입력 처리
            break;
        }
    }
    return 0; // 프로그램 종료
}
