#pragma once

#include <string>

using std::string;

class HKError
{
private:
	explicit HKError();
	~HKError();
	HKError(const HKError&);
	HKError& operator=(const HKError&);

public:
	static HKError& GetInstance()
	{
		static HKError instance;
		return instance;
	}

	enum Err
	{
		OK_ = 0,
		ACCESSIBLE_ = 1,
		CREATE_HANDLE_ = 2,
		OPEN_ = 3,
		SetPacketSize_ = 4,
		GetPacketSize_ = 5,
		LOADPROPERTIES_ = 6,
		STARTGRABBING_ = 7,
		GETIMAGE_ = 8,
		STOPGRABBING_ = 9,
		CLOSE_ = 10,
		DESTROYHANLDE_ = 11
	};

	string ParaseError(const int& err);
};

