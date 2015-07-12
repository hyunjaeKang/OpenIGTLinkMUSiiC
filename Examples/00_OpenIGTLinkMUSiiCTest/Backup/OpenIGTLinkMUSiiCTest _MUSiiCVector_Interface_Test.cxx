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


class TestBase: public Object
{
public:
	/** Standard class typedefs. */
	typedef TestBase			    Self;
	typedef Object						Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	TestBase()
	{
	
	}

	~TestBase()
	{
	}


	int Add_Test(TestBase::Pointer testB)
	{
		return 0;
	}


protected:
	
};

template<class InputData, class OutputData>
class TestInterface: public TestBase
{
public:
	/** Standard class typedefs. */
	typedef TestInterface			    Self;
	typedef TestBase					Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	TestInterface()
	{
		/*m_vInput.clear();
		m_vOutput.clear();*/
		//m_pTestInterface = NULL;

		m_pvInput = igtl::MUSiiCVector<InputData>::New();
		m_pvOutput = igtl::MUSiiCVector<OutputData>::New();
		m_pvInput->concurrent_clear();
		m_pvOutput->concurrent_clear();
		

		m_pTest = NULL;
	}

	~TestInterface()
	{
	}

	int Add_test_Interface(TestInterface<InputData, OutputData>* pTest)
	{
		m_pTest = pTest;
		return 0;
	}

	igtl::SmartPointer<igtl::MUSiiCVector<InputData>> GetInputIF()
	{
		return m_pvInput;
	}

	igtl::SmartPointer<igtl::MUSiiCVector<OutputData>> GetOutputIF()
	{
		return m_pvOutput;
	}

	//template<class In, class Out>
	//int Add_In_TestIF(TestInterface<In, Out>* pTest)
	//{
	//	m_vInput = pTest->GetOutputIF();
	//	return 0;
	//}

	template<class In, class Out>
	int Add_In_TestIF(igtl::SmartPointer<TestInterface<In, Out>> pTest)
	{
		m_pvInput = pTest->GetOutputIF();
		return 0;
	}

	int Add_In_TestIF2(igtl::SmartPointer<TestInterface<InputData, OutputData>> pTest)
	{
		m_pvInput = pTest->GetOutputIF();
		return 0;
	}

	//template<class In, class Out>
	//int Add_In_TestOut(TestInterface<In, Out>* pTest)
	//{
	//	//m_pTest = pTest;
	//	m_vInput = pTest->GetOutputIF();
	//	return 0;
	//}

	template<class In, class Out>
	int Add_Out_TestIF(igtl::SmartPointer<TestInterface<In, Out>> pTest)
	{
		m_pvOutput = pTest->GetInputIF();
		return 0;
	}

	int Add_Out_TestIF2(igtl::SmartPointer<TestInterface<InputData, OutputData>> pTest)
	{
		m_pvOutput = pTest->GetInputIF();
		return 0;
	}

	void printContainer(std::string des = "")
	{
		int sz, i;
		
		std::cout<< des.c_str()<<":  Input Interface" << std::endl;
		InputData invalue;
		sz = m_pvInput->concurrent_size();
		for(i=0; i<sz; i++)
		{
			m_pvInput->concurrent_try_get(invalue, i);
			std::cout << "ID:  " << i << ", Value is : " << invalue <<std::endl;
		}

		std::cout<< des.c_str()<<":  Out Interface" << std::endl;
		OutputData outvalue;
		sz = m_pvOutput->concurrent_size();
		for(i=0; i<sz; i++)
		{
			m_pvOutput->concurrent_try_get(outvalue, i);
			std::cout << "ID:  " << i << ", Value is : " << outvalue <<std::endl;
		}

		std::cout << std::endl;
	}

protected:
	/*std::vector<InputData> m_vInput;
	std::vector<OutputData> m_vOutput;*/
	igtl::SmartPointer<igtl::MUSiiCVector<InputData>> m_pvInput;
	igtl::SmartPointer<igtl::MUSiiCVector<OutputData>> m_pvOutput;
	//TestInterface<InputData, OutputData>* m_pTest;
	igtl::SmartPointer<TestInterface<InputData, OutputData>> m_pTest;

};


class Test: public TestInterface<int, int>
{
public:
	/** Standard class typedefs. */
	typedef Test			            Self;
	typedef TestInterface				Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);


	int AddTest(Test::Pointer test)
	{
		m_pTest = test;
		return 0;
	}
public:
	Test()
	{
	}

	~Test()
	{
	}

protected:
	Test::Pointer m_pTest;
};

//// MFC Memory Leak Checking//////////////////
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

////////////////////////////////////////////

struct TestUS
{
	igtl::USMessage::Pointer us2;
};

int main(int argc, char** argv)
{
	
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	
	int ref_count =0;
	igtl::USMessage::Pointer us1 = GetDummyUSMessage2();
	/*igtl::USMessage::Pointer us2 = us1;*/

	ref_count = us1->GetReferenceCount();

	//TestUS* tempus = new TestUS();
	TestUS* tempus = (TestUS*)malloc(sizeof(TestUS));
	memset(tempus, 0, sizeof(TestUS));
	tempus->us2 = us1;

	ref_count = us1->GetReferenceCount();
	
	TestUS* tempus2 = new TestUS();
	tempus2->us2 = us1;

	ref_count = us1->GetReferenceCount();

	igtl::USMessage* uspointer = (igtl::USMessage*)us1; 
	ref_count = us1->GetReferenceCount();
	
	
	TestInterface<int, int>::Pointer test1 = TestInterface<int, int>::New();
	TestInterface<int, double>::Pointer test2 = TestInterface<int, double>::New();
	TestInterface<double, int>::Pointer test3 = TestInterface<double, int>::New();

	test2->Add_In_TestIF(test1);
	test2->Add_Out_TestIF(test3);
	//test2->Add_In_TestIF<int,int>(test1);
	//test2->Add_In_TestIF2(test1); //Compile Error
	//test2->Add_Out_TestIF2(test3); //Compile Error
	
	//test1->Add_Out_TestIF(test3); //Compile Error
	int i=0;
	for(i=0; i<5; i++)
	{
		test1->GetInputIF()->concurrent_push_back(i/2);
		test1->GetOutputIF()->concurrent_push_back(i);
		test3->GetInputIF()->concurrent_push_back(i*0.5);
		test3->GetOutputIF()->concurrent_push_back(i*3);
	}


	test1->printContainer("Test1");
	test2->printContainer("Test2");
	test3->printContainer("Test3");


	return 0;

}