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


#include <stdio.h>
#include <igtlOSUtil.h> //igtl::Sleep
#include <igtlImageMessage.h>

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

#include <MUSiiCDef.h>
#include <MUSiiCIGTLUtil.h>
#include <vector>
#include <string>

#include <MUSiiCBindIGTLFileIO.h>
igtl::BindMessage::Pointer RetriveBindMessage(igtl::MessageBase::Pointer msg)
{
	
	msg->Pack();

	//// Retrive header file
	igtl::MessageHeader::Pointer headerMsg = igtl::MessageHeader::New();
	headerMsg->InitPack();
	memcpy(headerMsg->GetPackPointer(), msg->GetPackPointer(), headerMsg->GetPackSize());
	headerMsg->Unpack();


	//// Retrive Package
	igtl::BindMessage::Pointer bindMsg = igtl::BindMessage::New();
	bindMsg->SetMessageHeader(headerMsg);
	bindMsg->AllocatePack();
	memcpy(bindMsg->GetPackBodyPointer(), msg->GetPackBodyPointer(), bindMsg->GetPackBodySize());
	int c = bindMsg->Unpack();


	
	return bindMsg;
}

std::vector<igtl::MessageBase::Pointer> CheckBindMessageTest(igtl::MessageBase::Pointer msg, int lit = 0)
{
	std::vector<igtl::MessageBase::Pointer> Messages;
	int it(0);

	if (strcmp(msg->GetDeviceType(), "BIND") == 0)
	{
		igtl::BindMessage::Pointer bind;
		if(lit>0)
			bind = RetriveBindMessage(msg);
		else
			bind = igtl::RetrieveMessage<igtl::BindMessage::Pointer, igtl::BindMessage>(msg);
		
		int NumOfChild(bind->GetNumberOfChildMessages());
		
		for(int i=0; i<NumOfChild; i++)
		{
			if (strcmp(bind->GetChildMessageType(i), "BIND") == 0)
			{
				igtl::BindMessage::Pointer localbind = igtl::BindMessage::New();
				bind->GetChildMessage(i, localbind);
				localbind->Unpack();
				std::vector<igtl::MessageBase::Pointer> SubMessages;
				it++;
				SubMessages = CheckBindMessageTest((igtl::MessageBase::Pointer)localbind, it);
				for(int j=0; j<SubMessages.size(); j++)
				{
					igtl::MessageBase::Pointer tempMsg;
					tempMsg = SubMessages.at(j);
					Messages.push_back(tempMsg);
				}
				SubMessages.clear();
			}
			else
			{
				igtl::MessageBase::Pointer BMsg = igtl::MessageBase::New();
				bind->GetChildMessage(i, BMsg);
				Messages.push_back(BMsg);
			}
			
		}
	}
	else
		Messages.push_back(msg);

	return Messages;
}

igtl::ImageMessage::Pointer GenerateImageMessage(int i)
{
	
	int   size[]     = {256, 256, 1};       // image dimension
    float spacing[]  = {1.0, 1.0, 5.0};     // spacing (mm/pixel)
    int   svsize[]   = {256, 256, 1};       // sub-volume size
    int   svoffset[] = {0, 0, 0};           // sub-volume offset
    int   scalarType = igtl::ImageMessage::TYPE_UINT8;// scalar type

	igtl::ImageMessage::Pointer imgMsg = igtl::ImageMessage::New();
	imgMsg->SetDimensions(size);
    imgMsg->SetSpacing(spacing);
    imgMsg->SetScalarType(scalarType);
    imgMsg->SetDeviceName("ImagerClient");
    imgMsg->SetSubVolume(svsize, svoffset);
    imgMsg->AllocateScalars();

	char filename[128];
	sprintf(filename, "igtlTestImage%d.raw", i+1);
	std::cerr << "Reading " << filename << "...";

	//------------------------------------------------------------
	// Load raw data from the file
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		std::cerr << "File opeining error: " << filename << std::endl;
		return 0;
	}
	
	int fsize = imgMsg->GetImageSize();
	size_t b = fread(imgMsg->GetScalarPointer(), 1, fsize, fp);
	fclose(fp);

	igtl::Matrix4x4 matrix;
	matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
	matrix[0][1] = 0.0;  matrix[1][1] = -1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
	matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
	matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = 0.0; matrix[3][3] = 1.0;

	imgMsg->SetMatrix(matrix);
	
	//imgMsg->Pack();
	
	return imgMsg;
}

igtl::BindMessage::Pointer GetBindImageMessage()
{
	/// Create the 1st Image Message
	igtl::ImageMessage::Pointer Img1 = GenerateImageMessage(1);
	Img1->SetDeviceName("FirstImage");
	Img1->Pack();
	
	/// Create the 2nd Image Message
	igtl::ImageMessage::Pointer Img2 = GenerateImageMessage(2);
	Img2->SetDeviceName("SecondImage");
	Img2->Pack();

	/// Create the 3rd Image Message
	igtl::ImageMessage::Pointer Img3 = GenerateImageMessage(3);
	Img3->SetDeviceName("ThirdImage");
	Img3->Pack();

	
	/// Generate a BindMessage with Image2 and Image3
	igtl::BindMessage::Pointer bindMsg23 = igtl::BindMessage::New();
	bindMsg23->SetDeviceName("BindMessage_23");
	bindMsg23->Init();
	bindMsg23->AppendChildMessage(Img2);
	bindMsg23->AppendChildMessage(Img3);
	bindMsg23->Pack();

	igtl::BindMessage::Pointer bindMsg1B = igtl::BindMessage::New();
	bindMsg1B->SetDeviceName("BindMessage_1B");
	bindMsg1B->Init();
	bindMsg1B->AppendChildMessage(Img1);
	bindMsg1B->AppendChildMessage(bindMsg23);

	//return (igtl::MessageBase::Pointer)bindMsg1B;
	return bindMsg1B;
}


void GetBindImageMessage2(igtl::BindMessage::Pointer bmsg)
{
	/// Create the 1st Image Message
	igtl::ImageMessage::Pointer Img1 = GenerateImageMessage(1);
	Img1->SetDeviceName("FirstImage");
	Img1->Pack();
	
	/// Create the 2nd Image Message
	igtl::ImageMessage::Pointer Img2 = GenerateImageMessage(2);
	Img2->SetDeviceName("SecondImage");
	Img2->Pack();

	/// Create the 3rd Image Message
	igtl::ImageMessage::Pointer Img3 = GenerateImageMessage(3);
	Img3->SetDeviceName("ThirdImage");
	Img3->Pack();

	
	/// Generate a BindMessage with Image2 and Image3
	igtl::BindMessage::Pointer bindMsg23 = igtl::BindMessage::New();
	bindMsg23->SetDeviceName("BindMessage_23");
	bindMsg23->Init();
	bindMsg23->AppendChildMessage(Img2);
	bindMsg23->AppendChildMessage(Img3);
	bindMsg23->Pack();

	igtl::BindMessage::Pointer bindMsg1B = igtl::BindMessage::New();
	bindMsg1B->SetDeviceName("BindMessage_1B");
	bindMsg1B->Init();
	bindMsg1B->AppendChildMessage(Img1);
	bindMsg1B->AppendChildMessage(bindMsg23);

	bmsg =  bindMsg1B;
	//return (igtl::MessageBase::Pointer)bindMsg1B;
	//return bindMsg1B;
}
int main (int argc, char* argv[])
{	
	
	int a =6;
	int b = a%6;
	/// Create a pointer of MUSiiCBindFileIO
	igtl::MUSiiCBindIGTLMsgFileIO::Pointer bindFileIO = igtl::MUSiiCBindIGTLMsgFileIO::New();
	
	/// Create the 1st Image Message
	igtl::ImageMessage::Pointer Img1 = GenerateImageMessage(1);
	Img1->SetDeviceName("FirstImage");
	Img1->Pack();
	
	/// Create the 2nd Image Message
	igtl::ImageMessage::Pointer Img2 = GenerateImageMessage(2);
	Img2->SetDeviceName("SecondImage");
	Img2->Pack();

	/// Create the 3rd Image Message
	igtl::ImageMessage::Pointer Img3 = GenerateImageMessage(3);
	Img3->SetDeviceName("ThirdImage");
	Img3->Pack();

	
	/// Generate a BindMessage with Image2 and Image3
	igtl::BindMessage::Pointer bindMsg23 = igtl::BindMessage::New();
	bindMsg23->SetDeviceName("BindMessage_23");
	bindMsg23->Init();
	bindMsg23->AppendChildMessage(Img2);
	bindMsg23->AppendChildMessage(Img3);
	bindMsg23->Pack();

	igtl::BindMessage::Pointer bindMsg1B = igtl::BindMessage::New();
	bindMsg1B->SetDeviceName("BindMessage_1B");
	bindMsg1B->Init();
	bindMsg1B->AppendChildMessage(Img1);
	bindMsg1B->AppendChildMessage(bindMsg23);

	std::vector<igtl::MessageBase::Pointer> Messages;

	Messages = CheckBindMessageTest((igtl::MessageBase::Pointer)bindMsg1B);

	///////////////////////////////////////////////////////////
	
	igtl::BindMessage::Pointer bmsg = igtl::BindMessage::New();
	//bmsg = GetBindImageMessage();
	
	
	//igtl::MessageBase::Pointer msg = igtl::MessageBase::New();
	GetBindImageMessage2(bmsg);
	
	std::vector<igtl::MessageBase::Pointer> Messages2;
	Messages2 = CheckBindMessageTest((igtl::MessageBase::Pointer)bmsg);
	//Messages2 = CheckBindMessageTest(msg);

	int NumOfMessage(Messages.size());

	Messages.clear();
	
	return 0;
}



