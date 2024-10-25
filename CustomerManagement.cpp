#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional> // std::hash 사용을 위해 추가

using namespace std;

// 회원 정보를 저장하는 구조체
struct Member {
    string username; // 아이디
    string password; // 비밀번호 (해시화)
    string name;     // 성함
    string contact;  // 연락처
    string address;  // 주소
};

vector<Member> members; // 회원 정보를 저장하는 벡터

// 비밀번호를 해시화하는 함수
string hashPassword(const string& password) {
    return to_string(std::hash<string>{}(password)); // 비밀번호를 해시화하여 문자열로 반환
}

// 파일에서 고객 정보를 불러오는 함수
void loadMembersFromFile() {
    ifstream inFile("customers.txt"); // 고객 정보 파일 열기
    if (!inFile) { // 파일 열기 실패 시
        cout << "고객 정보 파일을 열 수 없습니다.\n";
        return;
    }

    Member member; // 새로운 회원 정보를 저장할 변수
    string line; // 파일에서 읽은 한 줄
    while (getline(inFile, line)) { // 파일의 각 줄을 읽기
        size_t pos = 0;
        pos = line.find(','); // 첫 번째 쉼표 위치 찾기
        member.username = line.substr(0, pos); // 아이디 저장
        line.erase(0, pos + 1); // 읽은 부분 삭제

        pos = line.find(','); // 다음 쉼표 위치 찾기
        member.password = line.substr(0, pos); // 비밀번호 저장 
        line.erase(0, pos + 1); // 읽은 부분 삭제

        pos = line.find(','); // 다음 쉼표 위치 찾기
        member.name = line.substr(0, pos); // 성함 저장
        line.erase(0, pos + 1); // 읽은 부분 삭제

        pos = line.find(','); // 다음 쉼표 위치 찾기
        member.contact = line.substr(0, pos); // 연락처 저장
        line.erase(0, pos + 1); // 읽은 부분 삭제

        member.address = line; // 마지막 부분은 주소로 저장

        members.push_back(member); // 벡터에 회원 정보 추가
    }
    inFile.close(); // 파일 닫기
}

// 회원가입 함수
void signUp() {
    Member newMember; // 새로운 회원 정보
    cout << "아이디를 입력하세요: ";
    cin >> newMember.username; // 아이디 입력
    cout << "비밀번호를 입력하세요: ";
    string password; // 비밀번호 변수
    cin >> password; // 비밀번호 입력
    newMember.password = hashPassword(password); // 비밀번호 해시화
    members.push_back(newMember); // 벡터에 추가
    cout << "회원가입이 완료되었습니다.\n";
}

// 로그인 함수
bool login() {
    string username, password; // 아이디와 비밀번호 변수
    cout << "아이디를 입력하세요: ";
    cin >> username; // 아이디 입력
    cout << "비밀번호를 입력하세요: ";
    cin >> password; // 비밀번호 입력

    string hashedPassword = hashPassword(password); // 입력한 비밀번호 해시화

    // 회원 정보와 비교
    for (const auto& member : members) {
        if (member.username == username && member.password == hashedPassword) { // 해시된 비밀번호 비교
            cout << "로그인 성공!\n";
            return true; // 로그인 성공
        }
    }
    cout << "로그인 실패. 사용자 이름 또는 비밀번호가 잘못되었습니다.\n";
    return false; // 로그인 실패
}

// 비밀번호 변경 함수
void changePassword() {
    string username, oldPassword, newPassword; // 아이디, 현재 비밀번호, 새 비밀번호 변수
    cout << "사용자 아이디를 입력하세요: ";
    cin >> username; // 아이디 입력
    cout << "현재 비밀번호를 입력하세요: ";
    cin >> oldPassword; // 현재 비밀번호 입력

    string hashedOldPassword = hashPassword(oldPassword); // 현재 비밀번호 해시화

    // 회원 정보와 비교
    for (auto& member : members) {
        if (member.username == username && member.password == hashedOldPassword) {
            cout << "새 비밀번호를 입력하세요: ";
            cin >> newPassword; // 새 비밀번호 입력
            member.password = hashPassword(newPassword); // 새 비밀번호 해시화
            cout << "비밀번호가 변경되었습니다.\n";
            return; // 비밀번호 변경 성공
        }
    }
    cout << "비밀번호 변경 실패. 사용자 이름 또는 비밀번호가 잘못되었습니다.\n";
}

// 고객 등록 함수
void registerCustomer() {
    string username; // 아이디 변수
    Member newCustomer; // 새로운 고객 정보

    cout << "사용자 아이디를 입력하세요: ";
    cin >> username; // 아이디 입력

    // 회원 정보 확인
    for (const auto& member : members) {
        if (member.username == username) {
            newCustomer.username = username; // 아이디 저장
            cout << "성함을 입력하세요: ";
            cin.ignore(); // 이전 입력 버퍼 비우기
            getline(cin, newCustomer.name); // 성함 입력
            cout << "연락처를 입력하세요: ";
            getline(cin, newCustomer.contact); // 연락처 입력
            cout << "주소를 입력하세요: ";
            getline(cin, newCustomer.address); // 주소 입력
            cout << "새 비밀번호를 입력하세요: ";
            string password; // 비밀번호 변수
            getline(cin, password); // 비밀번호 입력
            newCustomer.password = hashPassword(password); // 비밀번호 해시화
            members.push_back(newCustomer); // 고객 정보 추가
            cout << "고객 정보가 등록되었습니다.\n";
            return; // 등록 성공
        }
    }
    cout << "회원이 아닙니다.\n"; // 회원이 아닐 경우
}

// 고객 정보 조회 함수
void viewCustomerInfo() {
    string username; // 아이디 변수
    cout << "사용자 아이디를 입력하세요: ";
    cin >> username; // 아이디 입력

    // 회원 정보 확인
    for (const auto& member : members) {
        if (member.username == username) {
            cout << "성함: " << member.name << endl;
            cout << "연락처: " << member.contact << endl;
            cout << "주소: " << member.address << endl;
            // 비밀번호를 출력하지 않도록 수정
            cout << "비밀번호: (비공개)" << endl; // 비밀번호 보안상 비공개 처리
            return; // 조회 성공
        }
    }
    cout << "회원이 아닙니다.\n"; // 회원이 아닐 경우
}

// 고객 정보 수정 함수
void modifyCustomerInfo() {
    string username; // 아이디 변수
    cout << "사용자 아이디를 입력하세요: ";
    cin >> username; // 아이디 입력

    // 회원 정보 확인
    for (auto& member : members) {
        if (member.username == username) {
            cout << "새 성함을 입력하세요: ";
            cin.ignore(); // 이전 입력 버퍼 비우기
            getline(cin, member.name); // 새 성함 입력
            cout << "새 연락처를 입력하세요: ";
            getline(cin, member.contact); // 새 연락처 입력
            cout << "새 주소를 입력하세요: ";
            getline(cin, member.address); // 새 주소 입력
            cout << "새 비밀번호를 입력하세요: ";
            string password; // 비밀번호 변수
            getline(cin, password); // 새 비밀번호 입력
            member.password = hashPassword(password); // 비밀번호 해시화
            cout << "고객 정보가 수정되었습니다.\n";
            return; // 수정 성공
        }
    }
    cout << "회원이 아닙니다.\n"; // 회원이 아닐 경우
}

// 고객 정보 삭제 함수
void deleteCustomerInfo() {
    string username; // 아이디 변수
    cout << "삭제할 사용자 아이디를 입력하세요: ";
    cin >> username; // 아이디 입력

    // 회원 정보 확인 및 삭제
    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it
