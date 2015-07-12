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



//// MFC Memory Leak Checking//////////////////
//#include <crtdbg.h>
//
//#ifdef _DEBUG
//#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
//#endif

std::vector<igtl::USMessage*> USVector;

std::vector<igtl::MessageBase::Pointer> MsgVector;

std::vector<igtl::USMessage::Pointer> USVector2;

igtl::MessageBase::Pointer RetrieveMessageFromPointer(void* data)
{
	if(data)
	{
		igtl::MessageBase* msg = (igtl::MessageBase*)data;
		msg->Pack();
		igtl::MessageBase::Pointer tempMsg = igtl::MessageBase::New();
		tempMsg->InitPack();
		memcpy(tempMsg->GetPackPointer(), msg->GetPackPointer(), tempMsg->GetPackSize());
		tempMsg->Unpack();
		tempMsg->AllocatePack();
		memcpy(tempMsg->GetPackBodyPointer(), msg->GetPackBodyPointer(), tempMsg->GetPackBodySize());
		int c(tempMsg->Unpack(1));
		if( c & igtl::MessageHeader::UNPACK_BODY)
			return tempMsg;
	}
	
	return NULL;
}

void TestPrintMessage(void* data)
{
	//igtl::MessageBase* msg = (igtl::MessageBase*) data;
	igtl::MessageBase::Pointer msg = RetrieveMessageFromPointer(data);

	//if(msg != NULL)
	if(msg.IsNotNull())
	{
		MsgVector.push_back(msg);
		std::cout<<"The reference count of Message is : " <<msg->GetReferenceCount()<<std::endl;
		std::cout<<std::endl;
		
		PrintUSMessageMB(msg, "TestPrintMessage");
	}
}


void TestPrintUSMessage(void* usdata)
{
	igtl::USMessage* us = (igtl::USMessage*) usdata;
//	igtl::USMessage::Pointer us = (igtl::USMessage::Pointer)usdata;
	
	
	if(us != NULL)
	{
		USVector.push_back(us);
		std::cout<<"The reference count of USMessage is : " <<us->GetReferenceCount()<<std::endl;
		std::cout<<std::endl;

		PrintUSMessage(us, "TestPrintUSMessage");

		//TestPrintMessage(usdata);
	}
}

void TestCallbackinterface(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{
		std::cout << "Here is a message from function call" << std::endl;
		std::cout<<"The reference count of USMessage is : " <<msg->GetReferenceCount()<<std::endl;
		std::cout<<std::endl;
	}
}





int main(int argc, char** argv)
{
	int a(50);

//	TestCallbackinterface((igtl::MessageBase::Pointer)(&a));

	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	for(int i=0; i<10; i++)
	{
		std::cout<<"Before" <<std::endl;
		std::cout<<std::endl;
		{
			igtl::USMessage::Pointer us = GetDummyUSMessage2();
			us->SetTransmitFrequency(i*1000);
			//USVector2.push_back(us);
			//TestPrintUSMessage(us.GetPointer());
			TestPrintMessage(us);
			//TestCallbackinterface((igtl::MessageBase::Pointer)us);
			std::cout<<std::endl;

			std::cout << "The size of Vector is : "<< MsgVector.size() << std::endl; 
		}

		std::cout << "The size of Vector is : "<< MsgVector.size() << std::endl; 
		std::cout<<"After" <<std::endl;
		std::cout<<std::endl;
	}

	std::cout << "The size of Vector is : "<< MsgVector.size() << std::endl; 

	return 0;

}