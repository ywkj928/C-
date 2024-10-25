#ifndef __CUSTOMERMANAGEMENT_H__
#define __CUSTOMERMANAGEMENT_H__

#include <string>
#include <vector>

using namespace std;

struct Member {
    string username; // 아이디
    string password; // 비밀번호
    string name;     // 성함
    string contact;  // 연락처
    string address;  // 주소
};

extern vector<Member> members;

// 파일에서 고객 정보를 불러오는 함수
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
