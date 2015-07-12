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


#include <MUSiiCTCPClientSocketWin.h>
#include <map>


#include "MUSiiCSyncDATA.h"
#include "MUSiiCIGTLUtil.h"

//// MFC Memory Leak Checking//////////////////
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

////////////////////////////////////////////



using namespace igtl;

int main(int argc, char** argv)
{
	
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	for(int i=0; i<10; i++)
	{
		/// Generate US Message and Convert USMessage to MessageBase
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		std::cout << "Step 01: Generate US Message and Convert USMessage to MessageBase";
		igtl::MessageBase::Pointer usmsg = GetDummyUSMessage();
		PrintUSMessageMB(usmsg, "Generate US Message and Convert USMessage to MessageBase" );
		std::cout << std::endl;
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;


		/// Retrive US Message from MessageBase with ImageMessage
		std::cout << "Step 02: Retrive US Message from MessageBase with ImageMessage";
		igtl::ImageMessage::Pointer img = RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(usmsg);
		std::cout << std::endl;
		//PrintImageMessage(img, "Before Updateed");
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		
		std::cout << "Step 03: Update the matrix of US Message from MessageBase with ImageMessage";
		igtl::Matrix4x4 matrix;

		std::cout << "Original Matrix of USMessage :";
		PrintImageMessage(img,"Original Matrix of USMessage");
		std::cout << std::endl;

		GetDummyMatrix2(matrix);
		img->SetMatrix(matrix);

		std::cout << "Updated Matrix of USMessage :";
		PrintImageMessage(img,"Updated Matrix of USMessage");
		std::cout << std::endl;
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		//// Convert ImageMessage to MessageBase
		std::cout << "Step 04: Convert ImageMessage to MessageBase";
		igtl::MessageBase::Pointer usmsg2 = (igtl::MessageBase::Pointer)img;
		std::cout << std::endl;
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		//// Retrive USMessage from MessageBase
		std::cout << "Step 05: Retrive USMessage from MessageBase";
		igtl::USMessage::Pointer us = RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(usmsg2);
		PrintUSMessage(us, "Updated US Message");
		std::cout << std::endl;	
	}

	{
		igtl::MessageBase::Pointer imgtemp = GetDummyImageMessage();
		PrintImageMessageMB(imgtemp);
		igtl::EIMessage::Pointer eiimg = RetrieveMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(imgtemp);
		PrintEIMessage(eiimg);
	}

	{
		/// Generate US Message and Convert USMessage to MessageBase
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		std::cout << "Step 01: Generate EIMessage and Convert USMessage to MessageBase";
		igtl::MessageBase::Pointer eimsg = GetDummyEIMessage();
		PrintEIMessageMB(eimsg, "Generate US Message and Convert USMessage to MessageBase" );
		std::cout << std::endl;
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;


		/// Retrive US Message from MessageBase with ImageMessage
		std::cout << "Step 02: Retrive EIMessage from MessageBase with ImageMessage";
		igtl::ImageMessage::Pointer img = RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(eimsg);
		std::cout << std::endl;
		//PrintImageMessage(img, "Before Updateed");
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		
		std::cout << "Step 03: Update the matrix of EIMessage from MessageBase with ImageMessage";
		igtl::Matrix4x4 matrix;

		std::cout << "Original Matrix of EIMessage :";
		PrintImageMessage(img,"Original Matrix of EIMessage");
		std::cout << std::endl;

		GetDummyMatrix2(matrix);
		img->SetMatrix(matrix);

		std::cout << "Updated Matrix of EIMessage :";
		PrintImageMessage(img,"Updated Matrix of EIMessage");
		std::cout << std::endl;
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		//// Convert ImageMessage to MessageBase
		std::cout << "Step 04: Convert ImageMessage to MessageBase";
		igtl::MessageBase::Pointer usmsg2 = (igtl::MessageBase::Pointer)img;
		std::cout << std::endl;
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		//// Retrive USMessage from MessageBase
		std::cout << "Step 05: Retrive USMessage from MessageBase";
		igtl::EIMessage::Pointer us = RetrieveMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(usmsg2);
		PrintEIMessage(us, "Updated EI Message");
		std::cout << std::endl;	
	}
	
	
	
	
	
	return 0;

}



