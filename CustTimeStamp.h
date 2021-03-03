#pragma once

#include <chrono>

//高精度定时器类
class CustTimeStamp
{
public:
	CustTimeStamp() { update(); };
	~CustTimeStamp() {};

	void update()
	{
		m_begin = std::chrono::high_resolution_clock::now();
	}

	long long elapse_millisec()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}

	//获取秒
	double getElapseTimeInSecond()
	{
		return getElapseTimeInMicrosec() * 0.000001;
	}
	//获取毫秒
	double getElapseTimeInMillicSec()
	{
		return getElapseTimeInMicrosec() * 0.001;
	}
 
private:
	long long getElapseTimeInMicrosec()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();;
	}

	std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};

