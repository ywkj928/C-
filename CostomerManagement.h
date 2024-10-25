#ifndef __CUSTOMERMANAGEMENT_H__
#define __CUSTOMERMANAGEMENT_H__

#include <string>
#include <vector>

// 회원 정보를 저장하는 구조체
struct Member {
    std::string username; // 아이디
    std::string password; // 비밀번호
    std::string name;     // 성함
    std::string contact;  // 연락처
    std::string address;  // 주소
};

// 회원 정보를 저장하는 벡터 선언
extern std::vector<Member> members;

// 고객 정보를 파일에서 불러오는 함수
void loadMembersFromFile();

// 회원가입 함수
void signUp();

// 로그인 함수
bool login();

// 비밀번호 변경 함수
void changePassword();

// 고객 등록 함수
void registerCustomer();

// 고객 정보 조회 함수
void viewCustomerInfo();

// 고객 정보 수정 함수
void modifyCustomerInfo();

// 고객 정보 삭제 함수
void deleteCustomerInfo();

// 고객 목록 출력 함수
void listCustomers();

// 고객 정보를 파일에 저장하는 함수
void saveToFile();

#endif
