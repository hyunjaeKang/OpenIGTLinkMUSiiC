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


#ifndef __MUSiiCPROFILE__
#define __MUSiiCPROFILE__

#include <iostream>
#include "MUSiiCLogMessage.h"
#include <deque>

using namespace std;
namespace igtl
{

class MUSiiCProfile
{
public: //Operations
	/// Constructor
	MUSiiCProfile()
	{
		Initialize();
	}
	/// Deconstructor
	~MUSiiCProfile(){;}

	/// MUSiiC Tic
	/// Start clock to measure performance
#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
	void MUSiiCTic()
	{
		//m_dStartTime = GetTimeStampDouble();
		m_dStartTime = GetQueryTimeStampDouble();
		if(m_bEnableLogMessage)
			MUSiiC_LOG(logINFO)<< m_sDescription.c_str() << "  Tic Time is " << m_dStartTime << "sec";
	}
#endif
	/// Get Start clock
	double GetTicTime(){return m_dStartTime;}


	/// MUSiiC Toc
	/// Stop clock to measure performance
	double MUSiiCToc()
	{
		double toc = GetTimeStampDouble() - m_dStartTime;
		if(m_bEnableLogMessage)
			MUSiiC_LOG(logINFO)<< m_sDescription.c_str() << " Toc Time is " << toc << "sec";


		return toc;
	}

	/// MUSiiC Toc
	/// Stop clock to measure performance
#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
	double MUSiiCToc(std::string des = " ")
	{
		//double toc = GetTimeStampDouble() - m_dStartTime;
		double toc = GetQueryTimeStampDouble() - m_dStartTime;
		if(m_bEnableLogMessage)
			MUSiiC_LOG(logINFO)<< m_sDescription.c_str() << " " << des.c_str() << "  Toc Time is " << toc << "sec";

		return toc;
	}
#endif
	//// Intialize MUSiiC-Profile
	void Initialize()
	{
		m_qTocTimes.clear();
		m_qFPSTimes.clear();
		m_dStartTime          = 0.0;
		m_bEnableLogMessage   = false;
		m_dTimeTolerance      = 3.0;
		m_bEnableLogMessage   = false;
		m_iMaxSampleFPS       = 10;
		m_iBackupMaxSampleFPS = 10;
		m_sDescription        = "";
		m_dPreviousTime       = 0.0;
		m_dBackupFPS          = 0.0;
	}

	/// Set an boolean variable for MUSiiCLogMessage
	void EnableLogMessage(bool enable = true)
	{
		m_bEnableLogMessage = enable;
	}

	//// Get Frame rater (FPS) 
	double GetFPS()
	{
		return GetFPS(GetTimeStampDouble());
	}

	//// Get Frame rater (FPS) with input-time-stamp
	double GetFPS(double time)
	{
		double fps(0.0);
		m_qFPSTimes.push_back(time);

		//MUSiiC_LOG(logINFO)<< "Time Stamp is " << time;
		
		/// Check the size of m_qFPSTimes
		if((int)(m_qFPSTimes.size()) > m_iMaxSampleFPS - 1)
		{
			do
			{
				m_qFPSTimes.pop_front();
			}while((int)m_qFPSTimes.size() > m_iMaxSampleFPS - 1);
		}
		
		
		if(m_qFPSTimes.size() <= 1 || (time - m_qFPSTimes.front()) == 0.0)
		{
			fps = 0.0;
		}
		else
		{
			//if(abs(time - m_qFPSTimes.back()) > m_dTimeTolerance)
            
			if(abs(m_qFPSTimes.back() - m_dPreviousTime ) > m_dTimeTolerance)
			{
				MUSiiC_LOG(logINFO)<< " Reset Time_queue: " << "Time Diff  :" << abs(m_qFPSTimes.back() - m_dPreviousTime);
				m_qFPSTimes.clear();
				fps = m_dBackupFPS;
			}
			else
			{
				double fps_temp = (1.0/(m_qFPSTimes.back() - m_qFPSTimes.front()));
				if(m_bEnableLogMessage)
				{
					MUSiiC_LOG(logINFO)<< " current Time: " << time;
					MUSiiC_LOG(logINFO)<< " current Time_queue: " << m_qFPSTimes.back();
					MUSiiC_LOG(logINFO)<< " reference Time_queue: " << m_qFPSTimes.front();
					MUSiiC_LOG(logINFO)<< " Sample Size: " << m_qFPSTimes.size();
					MUSiiC_LOG(logINFO)<< "  Temp FPS is " << fps_temp;// << "Frames";
				}
				fps = fps_temp*((double)m_qFPSTimes.size());
			}
		}

		
		if(m_bEnableLogMessage)
		{
			MUSiiC_LOG(logINFO)<< m_sDescription.c_str() << "  Sample Size of FPS is " << m_qFPSTimes.size() << "Frames";
			MUSiiC_LOG(logINFO)<< m_sDescription.c_str() << "  FPS is " << fps;
		}
		
		/// Backup Data
		m_dPreviousTime = time;
		m_dBackupFPS = fps;
		return fps;
	}

	/// Set Sample size to compute FPS
	void SetSampleSizeOfFPS(int sz)
	{
		m_iMaxSampleFPS			= sz;
		m_iBackupMaxSampleFPS	= sz;
	}

	/// Set time-tolerance for computing FPS
	void SetTimeToleranceFPS(double tolerance)
	{
		m_dTimeTolerance= tolerance;
	}

	void SetDescription(std::string des)
	{
		m_sDescription = des;
	}

protected: //Operations

public: //attributes

protected: //attributes
	double             m_dStartTime;
	std::deque<double> m_qTocTimes;
	std::deque<double> m_qFPSTimes;
	int                m_iMaxSampleFPS;
	int                m_iBackupMaxSampleFPS;
	bool               m_bEnableLogMessage;
	double             m_dTimeTolerance;
	double             m_dPreviousTime;
	double             m_dBackupFPS;
	std::string        m_sDescription;

};

};

#endif