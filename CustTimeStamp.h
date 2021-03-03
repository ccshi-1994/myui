#pragma once

#include <chrono>

//�߾��ȶ�ʱ����
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

	//��ȡ��
	double getElapseTimeInSecond()
	{
		return getElapseTimeInMicrosec() * 0.000001;
	}
	//��ȡ����
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

