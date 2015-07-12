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



//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif
//
//#define malloc DEBUG_MALLOC
//#define DEBUG_MALLOC(size) _malloc_dbg(size, _NORMAL_BLOCK, __FILE__ , __LINE__)


#include <stdexcept>
#include <MUSiiCDef.h>
#include <MUSiiCIGTLUtil.h>



int main(int argc, char** argv)
{
	
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	//for(int i=0; i<10; i++)
	{
		/// Generate US Message and Convert USMessage to MessageBase
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		std::cout << "Step 01: Generate US Message and Convert USMessage to MessageBase";
		igtl::MessageBase::Pointer usmsg = igtl::GetDummyUSMessage();
		PrintUSMessageMB(usmsg, "Generate US Message and Convert USMessage to MessageBase" );
		std::cout << std::endl;
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;

		/// Retrive US Message from MessageBase with ImageMessage
		std::cout << "Step 02: Retrive US Message from MessageBase with ImageMessage"<< std::endl;
		igtl::ImageMessage::Pointer img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(usmsg);
		std::cout << std::endl;
		//PrintImageMessage(img, "Before Updateed");
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		
		std::cout << "Step 03: Update the matrix of US Message from MessageBase with ImageMessage";
		igtl::Matrix4x4 matrix;

		std::cout << "Original Matrix of USMessage :";
		PrintImageMessage(img,"Original Matrix of USMessage");
		std::cout << std::endl;

		igtl::GetDummyMatrix2(matrix);
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
		igtl::USMessage::Pointer us = igtl::RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(usmsg2);
		PrintUSMessage(us, "Updated US Message");
		std::cout << std::endl;	
	}

	{
		/// Generate US Message and Convert USMessage to MessageBase
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		std::cout << "Step 01: Generate EIMessage and Convert USMessage to MessageBase";
		igtl::MessageBase::Pointer eimsg = igtl::GetDummyEIMessage();
		PrintEIMessageMB(eimsg, "Generate US Message and Convert USMessage to MessageBase" );
		std::cout << std::endl;
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;


		/// Retrive US Message from MessageBase with ImageMessage
		std::cout << "Step 02: Retrive EIMessage from MessageBase with ImageMessage";
		igtl::ImageMessage::Pointer img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(eimsg);
		std::cout << std::endl;
		//PrintImageMessage(img, "Before Updateed");
		std::cout <<"-----------------------------------------------------------------------"<< std::endl;
		
		std::cout << "Step 03: Update the matrix of EIMessage from MessageBase with ImageMessage";
		igtl::Matrix4x4 matrix;

		std::cout << "Original Matrix of EIMessage :";
		PrintImageMessage(img,"Original Matrix of EIMessage");
		std::cout << std::endl;

		igtl::GetDummyMatrix2(matrix);
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
		igtl::EIMessage::Pointer us = igtl::RetrieveMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(usmsg2);
		PrintEIMessage(us, "Updated EI Message");
		std::cout << std::endl;	
	}

	return 0;

}