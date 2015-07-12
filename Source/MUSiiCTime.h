///***************************************************************************
// MUSiiC Laboratory
// Hyun-Jae Kang, Emad M Boctor
//
// Department of Computer Science Department
// Johns Hopkins University
//
// Johns Hopkins Medical Institutions
// Department of Radiology, Division of Medical Imaging Physics
//
// For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
//***************************************************************************/

#ifndef __MUSiiCTIME__
#define __MUSiiCTIME__

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <time.h>
#include <igtlTimeStamp.h>
#include <time.h>

namespace igtl
{

#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
#include <Windows.h>
#include <sys\timeb.h>

inline std::string GetNowTimeString()
{
	const int MAX_LEN = 200;
	char buffer[MAX_LEN];
	if(GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, "HH'_'mm'_'ss", buffer, MAX_LEN) == 0)
		return "Error in NowTime()";

	char result[100] = {0};
	static DWORD first = GetTickCount();
	std::sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first)%1000);
	return result;
}


inline std::string GetCurrentTimeString()
{
	/*time_t now = time(0);
	
	tm* localTime = localtime(&now);
	std::string CurTime(asctime(localTime));

	return CurTime;*/

	const int MAX_LEN = 200;
	char buffer[MAX_LEN];
	if(GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, "HH'_'mm'_'ss", buffer, MAX_LEN) == 0)
		return "Error in NowTime()";

	std::string CurTime(buffer);

	return CurTime;
}
/// Get TimeStamp using windiws's _timeb structure
inline double GetTimeStampDouble()
{
	struct  _timeb timebuffer;
    //unsigned short millitm1;
    _ftime(&timebuffer);
    int ft_s(timebuffer.time);
    int ft_ms(timebuffer.millitm);
    return (double)(ft_s+ft_ms/1000.0);

}

/// Get TimeStamp using QueryPerformanceCounter
inline double GetQueryTimeStampDouble()
{
	LARGE_INTEGER freq, CurrentC;
    QueryPerformanceCounter(&CurrentC);
    QueryPerformanceFrequency(&freq);
    return ( (double)CurrentC.QuadPart / (double)freq.QuadPart );
}

#else //WIN32
//#include <sys\time.h>
#include <sys/time.h>
inline std::string GetNowTimeString()
{
	char buffer[11];
	time_t t;
	time(&t);
	tm r = {0};
	strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
	struct timeval tv;
	gettimeofday(&tv, 0);
	char result [100] ={0};
	std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec/1000);
	return result;
}

inline double GetTimeStampDouble()
{
	double t;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    t = ((double)tv.tv_sec)*1000 + tv.tv_usec/1000;
    return t;
}

#endif//WIN32

/// Get TimeStamp using OpenIGTLink Timer
inline double GetIGTLTimeStampDouble()
{
	igtl::TimeStamp::Pointer ts = igtl::TimeStamp::New();
	ts->GetTime();
	return ts->GetTimeStamp();
}


}

#endif //__MUSiiCTIME__