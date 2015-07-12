///***************************************************************************
//Copyright May/2011
//MUSiiC Laboratory
//Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
//Johns Hopkins Medical Institutions
//Department of Radiology, Division of Medical Imaging Physics
//
//For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
//***************************************************************************/

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
#include "MUSiiCUtil.h"

#include <MUSiiCTCPClientSocketWin.h>
#include <map>

using namespace igtl;

#define M_REF_DATA "_M_REF_"
//#define NETWORK 

#if defined NETWORK
int main(int argc, char** argv)
{
	igtl::MUSiiCTCPClientSocketWin::Pointer client = igtl::MUSiiCTCPClientSocketWin::New();

	client->ConnectToHost("127.0.0.1", 12345);

	client->WaitTask();
	return 0;
}
#else
// Function to generate random matrix.
 void GetMatrix1(igtl::Matrix4x4& matrix)
{

	matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
	matrix[0][1] = 0.0;  matrix[1][1] = -1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
	matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
	matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = 0.0; matrix[3][3] = 1.0;
  
	//igtl::PrintMatrix(matrix);
}

void GetMatrix2(igtl::Matrix4x4& matrix)
{
 
	matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
	matrix[0][1] = 0.0;  matrix[1][1] = 1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
	matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
	matrix[0][3] = 10.0;  matrix[1][3] = 10.0;  matrix[2][3] = 1000.0; matrix[3][3] = 1.0;
  
	//igtl::PrintMatrix(matrix);
}

igtl::USMessage::Pointer GenerateDummyUSMessage()
{
	igtl::USMessage::Pointer us = igtl::USMessage::New();
	/// The information of dimension
	int x(10), y(2000), z(1);
	float sx(0.5), sy(0.1), sz(1.0);
	
	us->SetDimensions(x,y,z);
	us->SetSpacing(sx,sy,sz);
	us->SetSubVolume(x,y,z,0,0,0);
	us->SetScalarTypeToInt16();
	us->SetDeviceName("Dummy_RF_DATA");
	us->AllocateScalars();

	igtl::Matrix4x4 matrix1;
	GetMatrix1(matrix1);

	us->SetMatrix(matrix1);
	us->SetElements(128);
	us->SetExtensionAngle(3000);
	us->SetFPS(30);
	us->SetLineDensity(256);


	return us;
}


igtl::ImageMessage::Pointer GenerateDummyImageMessage()
{
	igtl::ImageMessage::Pointer img = igtl::ImageMessage::New();
	/// The information of dimension
	int x(300), y(300), z(1);
	float sx(0.5), sy(0.1), sz(1.0);
	
	img->SetDimensions(x,y,z);
	img->SetSpacing(sx,sy,sz);
	img->SetSubVolume(x,y,z,0,0,0);
	img->SetScalarTypeToUint8();
	img->SetDeviceName("Dummy_IMAGE_DATA");
	img->AllocateScalars();

	igtl::Matrix4x4 matrix1;
	GetMatrix1(matrix1);
	img->SetMatrix(matrix1);
	img->SetEndian(2);

	return img;
}

int main(int argc, char** argv)
{
	
	/*igtl::USMessage::Pointer us = GenerateDummyUSMessage();
	igtl::MessageBase::Pointer msg_us = ConvertMessageBase<igtl::USMessage::Pointer>(us);
	igtl::MessageBase::Pointer msg_us_p = (igtl::MessageBase::Pointer)(us);
	
	igtl::ImageMessage::Pointer img = GenerateDummyImageMessage();
	igtl::MessageBase::Pointer msg_img = ConvertMessageBase<igtl::ImageMessage::Pointer>(img);
	
	std::cerr << msg_us->GetDeviceName() <<std::endl;
	std::cerr << msg_img->GetDeviceName() <<std::endl;

	igtl::USMessage::Pointer us2 = RetrieveMessageIO<igtl::USMessage::Pointer, igtl::USMessage>(msg_us);
	igtl::ImageMessage::Pointer img2 = RetrieveMessageIO<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg_img);
	*/
	
	//// Data Server:: Generate US Data
	igtl::USMessage::Pointer us = GenerateDummyUSMessage();
	//// Receive US Data
	igtl::MessageBase::Pointer msg0 = ConvertMessageBase<igtl::USMessage::Pointer>(us);
	//// Retrieve USMessage from MessgeBase 
	igtl::USMessage::Pointer us2 = RetrieveMessagefromIODevice2<igtl::USMessage::Pointer, igtl::USMessage>(msg0);
	igtl::Matrix4x4 matrix0;
	us->GetMatrix(matrix0);
	
	std::cerr << "Before updating **************" << std::endl;
	igtl::PrintMatrix(matrix0);
	std::cerr << " " << std::endl;
	
	igtl::Matrix4x4 matrix1;
	GetMatrix2(matrix1);
	us2->SetMatrix(matrix1); /// Update Matrix
	std::cerr << "Mew Matrix **************" << std::endl;
	igtl::PrintMatrix(matrix1);
	std::cerr << " " << std::endl;

	//// Convert USMessage to MessageBase
	igtl::MessageBase::Pointer msg1 = ConvertMessageBase<igtl::USMessage::Pointer>(us2);
	/// Retrieve USMessage from MessageBase
	igtl::USMessage::Pointer us3 = RetrieveMessagefromIODevice2<igtl::USMessage::Pointer, igtl::USMessage>(msg1);
	igtl::Matrix4x4 matrix2;
	us3->GetMatrix(matrix2);
	std::cerr << "After updating **************" << std::endl;
	igtl::PrintMatrix(matrix2);
	std::cerr << " " << std::endl;
	

	
	
	
	
	
	
	////// Generate US Message
	
	//igtl::USMessage::Pointer us = GenerateDummyUSMessage();
	////igtl::MessageBase::Pointer msg = (igtl::MessageBase::Pointer)(us);
	//igtl::MessageBase::Pointer msg2 = ConvertMessageBase<igtl::USMessage::Pointer>(us);
	//
	//igtl::ImageMessage::Pointer img = RetrieveMessagefromIODevice2<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg2);
	//igtl::Matrix4x4 matrix;
	//GetMatrix2(matrix);
	//img->SetMatrix(matrix);
	//igtl::MessageBase::Pointer msg3 = ConvertMessageBase<igtl::ImageMessage::Pointer>(img);
	//igtl::USMessage::Pointer us4 = RetrieveMessagefromIODevice2<igtl::USMessage::Pointer, igtl::USMessage>(msg3);
	////igtl::USMessage::Pointer us4 = RetrieveMessageIO<igtl::USMessage::Pointer, igtl::USMessage>(msg2);
	


	
	
	//
	////// Generate US Message
	//igtl::USMessage::Pointer us = GenerateDummyUSMessage();
	////igtl::MessageBase::Pointer msg = (igtl::MessageBase::Pointer)us;
	//igtl::MessageBase::Pointer msg2 = ConvertMessageBase<igtl::USMessage::Pointer>(us);
	//
	//igtl::ImageMessage::Pointer img = RetrieveMessageIO<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg2);
	//igtl::Matrix4x4 matrix;
	//GetMatrix2(matrix);
	//img->SetMatrix(matrix);
	//////igtl::MessageBase::Pointer msg2 = (igtl::MessageBase::Pointer)img;
	//igtl::MessageBase::Pointer msg3 = ConvertMessageBase<igtl::ImageMessage::Pointer>(img);

	////igtl::USMessage::Pointer us2 = RecoverIGTLMSg<igtl::USMessage::Pointer, igtl::USMessage>(msg);
	////igtl::USMessage::Pointer us3 = RetrieveMessageIO<igtl::USMessage::Pointer, igtl::USMessage>(msg2);
	//igtl::USMessage::Pointer us4 = RetrieveMessageIO<igtl::USMessage::Pointer, igtl::USMessage>(msg3);
	////igtl::USMessage::Pointer us2 = RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(msg2);
	//
	//
	
	//igtl::USMessage::Pointer us2 = RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(msg);
	//igtl::USMessage::Pointer us3 = RecoverIGTLMSg<igtl::USMessage::Pointer, igtl::USMessage>(msg);

	//igtl::ImageMessage::Pointer img = GenerateDummyImageMessage();
	//igtl::MessageBase::Pointer Imsg = ConvertMessageBase<igtl::ImageMessage::Pointer>(img);//(igtl::MessageBase::Pointer)img;
	//igtl::MessageBase::Pointer Imsg = (igtl::MessageBase::Pointer)img;
	//igtl::ImageMessage::Pointer img2 = RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(Imsg);
	//igtl::ImageMessage::Pointer img3 = RecoverIGTLMSg<igtl::ImageMessage::Pointer, igtl::ImageMessage>(Imsg);


	
	
	return 0;
}

#endif




////// Generate US Message
//	igtl::USMessage::Pointer us;
//	us = GenerateDummyUSMessage();
//
//	//// Convert USMessage to MessageBase
//	/*igtl::MessageBase::Pointer msg = igtl::MessageBase::New();
//	msg = (igtl::MessageBase::Pointer)us;*/
//
//	igtl::MessageBase::Pointer msg = (igtl::MessageBase::Pointer)us;
//	////// Retrive ImageMessage from MessageBase
//	//igtl::ImageMessage::Pointer img = igtl::ImageMessage::New();
//	//img = RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);
//	///// Update transformation matrix
//	//igtl::Matrix4x4 matrix2;
//	//GetMatrix2(matrix2);
//	//img->SetMatrix(matrix2);
//
//	////// Convert ImageMessage to MessageBase
//	//igtl::MessageBase::Pointer msg2 = igtl::MessageBase::New();
//	//msg2 = (igtl::MessageBase::Pointer)img;
//	//msg2->Pack();
//	igtl::USMessage::Pointer us2;
//	//us2 = RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(msg2);
//	us2 = RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(msg);