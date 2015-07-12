///***************************************************************************
//Copyright May/2011
//MUSiiC Laboratory
//Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
//Johns Hopkins Medical Institutions
//Department of Radiology, Division of Medical Imaging Physics
//
//For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
//***************************************************************************/



//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif
//
//#define malloc DEBUG_MALLOC
//#define DEBUG_MALLOC(size) _malloc_dbg(size, _NORMAL_BLOCK, __FILE__ , __LINE__)





//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <time.h>
#include <MUSiiCProfile.h>


#include <igtlImageMessage.h>
#include <MUSiiCVector.h>
#include <igtlUnit.h>
#include "igtlOSUtil.h"
#include <MUSiiCTaskInterfaceAbstract.h>

#include <MUSiiCTCPServerSocketWin.h>

#include "MUSiiCVectorSet.h"

#include <igtlLightObject.h>
#include <igtlMacro.h>
#include <igtlObjectFactory.h>
#include "igtlM_win32header.h"
#include "MUSiiCIGTLUtil.h"

#include <MUSiiCTCPClientSocketWin.h>
#include <map>


#include "MUSiiCSyncDATA.h"
#include <MUSiiCVector.h>





using namespace igtl;


class Test1: public igtl::MUSiiCTaskInterfaceAbstract<int, double>
{
public:
	/** Standard class typedefs. */
	typedef Test1									Self;
	typedef MUSiiCTaskInterfaceAbstract<int,double>	Superclass;
	typedef igtl:: SmartPointer<Self>				Pointer;
	typedef igtl::SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	/// Construction
	Test1()
	{
	}
	/// DeConstruction
	~Test1()
	{
	}
	/// RunTask1
	virtual int RunTask1()
	{
		m_iIndex = 0;
		this->SetEnableThread(true, M_ALLTASKOBJECT);
		
		return this->RunTask(M_THREAD_RUN_CONTINUOUS, 1, this, NULL, NULL, NULL, M_ALLTASKOBJECT);
	}

protected:
	/// Initialization
	virtual void Initialize()
	{
		m_iIndex = 0;
	}

	/// The user-defined task function.
	/// You can make your own taskfunction by making subclass of MUSiiCAbstract
	virtual int TaskFunction(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		if(m_iIndex == 10000)
		{
			this->StopTask();
			MUSiiC_LOG(logINFO) << "Task 1 is Stoped";
			igtl::Sleep(1000000);
		}

		double result = (double)m_iIndex*0.5;

		this->m_pVOutputDATA_IF_Set->Concurrent_push_back_ALL(result);
		MUSiiC_LOG(logINFO) << "Task 1:: Sending " << result ;

		igtl::Sleep(1000);
		m_iIndex++;

		return 0;
	}


protected:
	int m_iIndex;
	
};


class Test2: public igtl::MUSiiCTaskInterfaceAbstract<double, int>
{
public:
	/** Standard class typedefs. */
	typedef Test2									Self;
	typedef MUSiiCTaskInterfaceAbstract<double,int>	Superclass;
	typedef igtl::SmartPointer<Self>				Pointer;
	typedef igtl::SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	/// Construction
	Test2()
	{
	}
	/// DeConstruction
	~Test2()
	{
	}
	/// RunTask1
	virtual int RunTask2()
	{
		/*m_iIndex = 0;*/
		this->SetEnableThread(true, M_ALLTASKOBJECT);
		
		return this->RunTask(M_THREAD_RUN_CONTINUOUS, 1, this, NULL, NULL, NULL, M_ALLTASKOBJECT);
	}

protected:
	/// Initialization
	virtual void Initialize()
	{
		/*m_iIndex = 0;*/
	}

	/// The user-defined task function.
	/// You can make your own taskfunction by making subclass of MUSiiCAbstract
	virtual int TaskFunction(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
	
		double result;

		//this->m_pVInputDATA_IF_Set->Concurrent_wait_get_pop_front_fromMUSiiCVectorSet(result);
		this->m_pSelfInputDataInterface->concurrent_wait_get_pop_front(result);
		MUSiiC_LOG(logINFO) << "Task 2 received following value:  " << result;

		return 0;
	}


protected:
	//int m_iIndex;
	
};


class Test3: public igtl::MUSiiCTaskInterfaceAbstract<double, float>
{
public:
	/** Standard class typedefs. */
	typedef Test3									Self;
	typedef MUSiiCTaskInterfaceAbstract<double,float>	Superclass;
	typedef igtl::SmartPointer<Self>				Pointer;
	typedef igtl::SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	/// Construction
	Test3()
	{
	}
	/// DeConstruction
	~Test3()
	{
	}
	/// RunTask1
	virtual int RunTask3()
	{
		/*m_iIndex = 0;*/
		this->SetEnableThread(true, M_ALLTASKOBJECT);
		
		return this->RunTask(M_THREAD_RUN_CONTINUOUS, 1, this, NULL, NULL, NULL, M_ALLTASKOBJECT);
	}

protected:
	/// Initialization
	virtual void Initialize()
	{
		/*m_iIndex = 0;*/
	}

	/// The user-defined task function.
	/// You can make your own taskfunction by making subclass of MUSiiCAbstract
	virtual int TaskFunction(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
	
		double result;

		//this->m_pVInputDATA_IF_Set->Concurrent_wait_get_pop_front_fromMUSiiCVectorSet(result);
		this->m_pSelfInputDataInterface->concurrent_wait_get_pop_front(result);
		MUSiiC_LOG(logINFO) << "Task 3 received following value:  " << result;

		return 0;
	}


protected:
	//int m_iIndex;
	
};



int main(int argc, char** argv)
{
	
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	/// Create an object of Test1 class
	Test1::Pointer test1 = Test1::New();
	/// Create an object of Test2 class
	Test2::Pointer test2 = Test2::New();
	/// Create an object of Test3 class
	Test3::Pointer test3 = Test3::New();

	igtl::SmartPointer<igtl::MUSiiCTaskInterfaceAbstract<int,double>> temp_test1;
	igtl::SmartPointer<igtl::MUSiiCTaskInterfaceAbstract<double,int>> temp_test2;

	igtl::MUSiiCTaskInterfaceAbstract<double,int>::Pointer temp; 
	temp_test1 = test1;
	temp_test2 = test2;
	//test1->AddPostMUSiiCTaskInterface(test2); /// Compile Error
	//test1->AddPostMUSiiCTaskInterface<double, int>(test2); /// Compile Error
	//test1->AddPostMUSiiCTaskInterface((igtl::SmartPointer<igtl::MUSiiCTaskInterfaceAbstract<double,int>>)test2);
	//test1->AddPostMUSiiCTaskInterface3<double,int>(test2); //working
	//test1->AddPostMUSiiCTask(test2->GetMUSiiCTaskAbstract()); 

	test1->AddPostMUSiiCTaskInterface<double,float>(test3);
	test2->AddPreMUSiiCTaskInterface<int, double>(test1);
	
	test3->RunTask3();
	test2->RunTask2();
	test1->RunTask1();


	test1->WaitTask();
	test2->WaitTask();
	test3->WaitTask();



	return 0;

}