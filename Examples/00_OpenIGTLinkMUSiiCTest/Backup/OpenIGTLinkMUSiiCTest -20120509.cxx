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

#include "MUSiiCTCPServerSocketWin.h"



using namespace igtl;



//// MFC Memory Leak Checking//////////////////
//#include <crtdbg.h>
//
//#ifdef _DEBUG
//#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
//#endif

class MUSiiCTaskTest : public MUSiiCTaskAbstract
{
public:
	/** Standard class typedefs. */
	typedef MUSiiCTaskTest			    Self;
	typedef MUSiiCTaskAbstract		    Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Superclass, Object);

	///Constructor
	MUSiiCTaskTest()
	{
		this->m_pNameOfClass = "MUSiiCTaskTest";
	}
	
	///Deconstructor
	~MUSiiCTaskTest()
	{
	}


protected:
	/// Initialize Member variables
	virtual void Initialize()
	{
	}

	/// User-defined Task Function
	virtual int TaskFunction(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		std::cout << "This is the TaskFunction of MUSiiCTaskTest class" << std::endl;

		return 1;
	}


};





int main(int argc, char** argv)
{

	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	
	igtl::MUSiiCTaskInterfaceAbstract<int,double>::Pointer task;
	task = igtl::MUSiiCTaskInterfaceAbstract<int,double>::New();

	igtl::MUSiiCVector<int>::Pointer dataIF = task->GetSelfInputDataInterface();

	igtl::MUSiiCVector<igtl::MessageBase::Pointer>::Pointer pVector1;
	pVector1 = igtl::MUSiiCVector<igtl::MessageBase::Pointer>::New();

	igtl::MUSiiCIGTLMsgVector::Pointer pVector2;
	pVector2 = igtl::MUSiiCIGTLMsgVector::New();

	igtl::SmartPointer<igtl::MUSiiCVector<igtl::MessageBase::Pointer>> pVector3;
	pVector3 = igtl::MUSiiCVector<igtl::MessageBase::Pointer>::New();

	pVector1 = pVector2;

	pVector3 = pVector2;




	
	
	
	
	
	
	
	
	bool bTest;
	
	/*igtl::MUSiiCTCPServerSocketWin::Pointer serversocket = igtl::MUSiiCTCPServerSocketWin::New();
	serversocket->CreateServer(12345);

	serversocket->WaitTask();*/


	/*MUSiiCTaskTest::Pointer task = MUSiiCTaskTest::New();
	task->RunTask(10);
	task->WaitTask();*/

	return 0;

}