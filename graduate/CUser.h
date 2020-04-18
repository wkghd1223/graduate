#pragma once
class CUser
{
public:
	CUser() {}
	~CUser() {}
	CUser(LPCTSTR name, LPCTSTR account, LPCTSTR userId, LPCTSTR type) {
		this->name = name;
		this->account = account;
		this->userId = userId;
		this->type = type;
	}
	LPCTSTR getName() { return name; }
	LPCTSTR getAccount() { return account; }
	LPCTSTR getUserId() { return userId; }
	LPCTSTR getType() {return type; }
private:
	LPCTSTR name;
	LPCTSTR account;
	LPCTSTR userId;
	// 접속서버 구분
	LPCTSTR type;
public:
};

