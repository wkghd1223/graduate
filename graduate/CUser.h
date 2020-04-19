#pragma once
class CUser
{
public:
	CUser() {}
	~CUser() {}
	CUser(CString name, CString account, CString userId, CString type) {
		this->name = name;
		this->account = account;
		this->userId = userId;
		this->type = type;
	}
	CString getName() { return name; }
	CString getAccount() { return account; }
	CString getUserId() { return userId; }
	CString getType() {return type; }
private:
	CString name;
	CString account;
	CString userId;
	// 접속서버 구분
	CString type;
public:
};

