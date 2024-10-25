#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional> // std::hash 사용을 위해 추가

using namespace std;

struct Member {
    string username; // 아이디
    string password; // 비밀번호 (해시화)
    string name;     // 성함
    string contact;  // 연락처
    string address;  // 주소
};

vector<Member> members;

// 비밀번호를 해시화하는 함수
string hashPassword(const string& password) {
    return to_string(std::hash<string>{}(password));
}

// 파일에서 고객 정보를 불러오는 함수
void loadMembersFromFile() {
    ifstream inFile("customers.txt");
    if (!inFile) {
        cout << "고객 정보 파일을 열 수 없습니다.\n";
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
        member.password = line.substr(0, pos); // 해시된 비밀번호
        line.erase(0, pos + 1);

        pos = line.find(',');
        member.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        member.contact = line.substr(0, pos);
        line.erase(0, pos + 1);

        member.address = line; // 마지막 부분은 주소

        members.push_back(member);
    }
    inFile.close();
}

void signUp() {
    Member newMember;
    cout << "아이디를 입력하세요: ";
    cin >> newMember.username;
    cout << "비밀번호를 입력하세요: ";
    string password;
    cin >> password;
    newMember.password = hashPassword(password); // 비밀번호 해시화
    members.push_back(newMember);
    cout << "회원가입이 완료되었습니다.\n";
}

bool login() {
    string username, password;
    cout << "아이디를 입력하세요: ";
    cin >> username;
    cout << "비밀번호를 입력하세요: ";
    cin >> password;

    string hashedPassword = hashPassword(password); // 입력한 비밀번호 해시화

    for (const auto& member : members) {
        if (member.username == username && member.password == hashedPassword) { // 해시된 비밀번호 비교
            cout << "로그인 성공!\n";
            return true;
        }
    }
    cout << "로그인 실패. 사용자 이름 또는 비밀번호가 잘못되었습니다.\n";
    return false;
}

void changePassword() {
    string username, oldPassword, newPassword;
    cout << "사용자 아이디를 입력하세요: ";
    cin >> username;
    cout << "현재 비밀번호를 입력하세요: ";
    cin >> oldPassword;

    string hashedOldPassword = hashPassword(oldPassword); // 현재 비밀번호 해시화

    for (auto& member : members) {
        if (member.username == username && member.password == hashedOldPassword) {
            cout << "새 비밀번호를 입력하세요: ";
            cin >> newPassword;
            member.password = hashPassword(newPassword); // 새 비밀번호 해시화
            cout << "비밀번호가 변경되었습니다.\n";
            return;
        }
    }
    cout << "비밀번호 변경 실패. 사용자 이름 또는 비밀번호가 잘못되었습니다.\n";
}

void registerCustomer() {
    string username;
    Member newCustomer;

    cout << "사용자 아이디를 입력하세요: ";
    cin >> username;

    for (const auto& member : members) {
        if (member.username == username) {
            newCustomer.username = username;
            cout << "성함을 입력하세요: ";
            cin.ignore();
            getline(cin, newCustomer.name);
            cout << "연락처를 입력하세요: ";
            getline(cin, newCustomer.contact);
            cout << "주소를 입력하세요: ";
            getline(cin, newCustomer.address);
            cout << "새 비밀번호를 입력하세요: ";
            getline(cin, member.password);
            members.push_back(newCustomer);
            cout << "고객 정보가 등록되었습니다.\n";
            return;
        }
    }
    cout << "회원이 아닙니다.\n";
}

void viewCustomerInfo() {
    string username;
    cout << "사용자 아이디를 입력하세요: ";
    cin >> username;

    for (const auto& member : members) {
        if (member.username == username) {
            cout << "성함: " << member.name << endl;
            cout << "연락처: " << member.contact << endl;
            cout << "주소: " << member.address << endl;
            cout << "비밀번호: " << member.password << " (해시화된 비밀번호)" << endl; // 해시화된 비밀번호 표시
            return;
        }
    }
    cout << "회원이 아닙니다.\n";
}

void modifyCustomerInfo() {
    string username;
    cout << "사용자 아이디를 입력하세요: ";
    cin >> username;

    for (auto& member : members) {
        if (member.username == username) {
            cout << "새 성함을 입력하세요: ";
            cin.ignore();
            getline(cin, member.name);
            cout << "새 연락처를 입력하세요: ";
            getline(cin, member.contact);
            cout << "새 주소를 입력하세요: ";
            getline(cin, member.address);
            cout << "새 비밀번호를 입력하세요: ";
            getline(cin, member.password);
            cout << "고객 정보가 수정되었습니다.\n";
            return;
        }
    }
    cout << "회원이 아닙니다.\n";
}

void deleteCustomerInfo() {
    string username;
    cout << "삭제할 사용자 아이디를 입력하세요: ";
    cin >> username;

    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it->username == username) {
            members.erase(it);
            cout << "고객 정보가 삭제되었습니다.\n";
            return;
        }
    }
    cout << "회원이 아닙니다.\n";
}

void listCustomers() {
    cout << "고객 목록:\n";
    for (const auto& member : members) {
        cout << "사용자 아이디: " << member.username
            << " | 성함: " << member.name
            << " | 연락처: " << member.contact
            << " | 주소: " << member.address 
            << " | 비밀번호: " << member.password << endl;
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
    cout << "고객 정보가 파일에 저장되었습니다.\n";
}
