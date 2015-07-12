/***************************************************************************
Copyright May/2011
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

#############################################################################
This example program is showing how to use MUSiiCTaskAbstract class with exteral task function.
***************************************************************************/

#include <stdio.h>
#include <igtlOSUtil.h> //igtl::Sleep
#include <igtlImageMessage.h>

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

#include <MUSiiCigtlMsgFILEIO.h>
#include <MUSiiCTCPServerUni.h>
#include <igtlMUSMessage.h>
#include <MUSiiCUtil.h>
#include <MUSiiCTCPLightServerUni.h>

#include <vector>



//------------------------------------------------------------
// Function to read test image data
int GetTestImage(igtl::USMessage::Pointer& msg, const char* dir, int i)
//int GetTestImage(igtl::ImageMessage::Pointer& msg, const char* dir, int i)
{

  //------------------------------------------------------------
  // Check if image index is in the range
  if (i < 0 || i >= 5) 
    {
    std::cerr << "Image index is invalid." << std::endl;
    return 0;
    }

  //------------------------------------------------------------
  // Generate path to the raw image file
  char filename[128];
  sprintf(filename, "%s/igtlTestImage%d.raw", dir, i+1);
  //std::cerr << "Reading " << filename << "...";

  //------------------------------------------------------------
  // Load raw data from the file
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL)
    {
    std::cerr << "File opeining error: " << filename << std::endl;
    return 0;
    }
  int fsize = msg->GetImageSize();
  size_t b = fread(msg->GetScalarPointer(), 1, fsize, fp);

  fclose(fp);

  //std::cerr << "done." << std::endl;

  return 1;
}


//------------------------------------------------------------
// Function to generate random matrix.
void GetRandomTestMatrix(igtl::Matrix4x4& matrix)
{
  float position[3];
  float orientation[4];

  matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
  matrix[0][1] = 0.0;  matrix[1][1] = 1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
  matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
  matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = 0.0; matrix[3][3] = 1.0;
  
  //igtl::PrintMatrix(matrix);
}

int main (int argc, char* argv[])
{
	//igtl::MUSiiCTCPLightServerUni::Pointer pServer = igtl::MUSiiCTCPLightServerUni::New();
	igtl::MUSiiCTCPServerUni::Pointer pServer = igtl::MUSiiCTCPServerUni::New();
	igtl::MUSiiCigtlMsgFILEIO::Pointer igtlFile = igtl::MUSiiCigtlMsgFILEIO::New();
	pServer->PrepareNetwork();

	pServer->CreateServer(23877);

	std::vector<igtl::USMessage::Pointer> USDatas;
	
	
	igtl::USMessage::Pointer USMsg;
	igtl::USMessage::Pointer USMsg2;
	igtl::MessageBase::Pointer msg;

	const char* dir = "./dataRF";
	//igtl::ImageMessage::Pointer USMsg;
	printf("Prees q for quit this program\n");
	int i = 0;

	for(int kk=0; kk<5; kk++)
	{
		char filename[128];
		sprintf(filename, "%s/igtlTestRF%d.igtl", dir, kk+1);
		msg = igtlFile->ReadSingleFile(filename);
		USMsg = igtl::RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(msg);
		USDatas.push_back(USMsg);
	}
	for(;;)
	{
        
		USMsg2 = USDatas[i];
		USMsg2->Pack();
		pServer->PutigtlMsg((igtl::MessageBase::Pointer)USMsg);
		
		igtl::Sleep(30);
		i++;

		if( i == 5)
			i=0;
	}	
	
	printf("==========================\n");
	printf("==========================\n");
	printf("==========================\n");
	printf("Done\n");
	printf("==========================\n");
	printf("==========================\n");
	printf("==========================\n");
	
	pServer->CloseServer();

	igtl::MUSiiC_TCP_STATUS tcp_status;
	tcp_status =  pServer->GetTCPStatus();
	
	switch(tcp_status)
	{
		case igtl::M_TCP_Server_Disconnected:
			printf("Connected\n");
			break;
	}
	

	return 0;
}
//
//int main (int argc, char* argv[])
//{
//	igtl::MUSiiCTCPServerUni::Pointer pServer = igtl::MUSiiCTCPServerUni::New();
//	pServer->PrepareNetwork();
//
//	pServer->CreateServer(23877);
//	
//	
//	igtl::USMessage::Pointer USMsg;
//	//igtl::ImageMessage::Pointer USMsg;
//	printf("Prees q for quit this program\n");
//	int i = 0; 
//	for(;;)
//	{
//		//------------------ Data Packing ----------------------------
//		//------------------------------------------------------------
//		//------------------------------------------------------------
//        // size parameters
//        int   size[]     = {256, 256, 1};       // image dimension
//        float spacing[]  = {1.0, 1.0, 10.0};     // spacing (mm/pixel)
//        int   svsize[]   = {256, 256, 1};       // sub-volume size
//        int   svoffset[] = {0, 0, 0};           // sub-volume offset
//        int   scalarType = igtl::ImageMessage::TYPE_UINT8;// scalar type
//        
//        //------------------------------------------------------------
//        // Create a new IMAGE type message
//		USMsg = igtl::USMessage::New();//igtl::ImageMessage::New();
//        USMsg->SetDimensions(size);
//        USMsg->SetSpacing(spacing);
//        USMsg->SetScalarType(scalarType);
//        USMsg->SetDeviceName("FAKERF");
//        USMsg->SetSubVolume(svsize, svoffset);
//        USMsg->AllocateScalars();
//		igtl::TimeStamp::Pointer time =igtl::TimeStamp::New();
//		time->GetTime();
//		USMsg->SetTimeStamp(time);
//        
//        //------------------------------------------------------------
//        // Set image data (See GetTestImage() bellow for the details)
//		if(i>4)
//		{
//			igtl::Sleep(500);
//			i=0;
//		}
//        GetTestImage(USMsg, "./data", i % 5);
//        
//        //------------------------------------------------------------
//        // Get randome orientation matrix and set it.
//        igtl::Matrix4x4 matrix;
//        GetRandomTestMatrix(matrix);
//        USMsg->SetMatrix(matrix);
//		USMsg->SetElements(128);
//		USMsg->SetFPS(30);
//		USMsg->SetLineDensity(256);
//        //------------------------------------------------------------
//        // Pack (serialize) and send
//        USMsg->Pack();
//		//------------------------------------------------------------
//		//------------------------------------------------------------
//		//------------------------------------------------------------
//
//		pServer->PutigtlMsg((igtl::MessageBase::Pointer)USMsg);
//		
//		igtl::Sleep(30);
//
//		/*char sel;
//		scanf("%c", &sel);
//
//		if( sel == 'q')
//			break;
//		*/
//		i++;
//	}	
//	
//	printf("==========================\n");
//	printf("==========================\n");
//	printf("==========================\n");
//	printf("Done\n");
//	printf("==========================\n");
//	printf("==========================\n");
//	printf("==========================\n");
//	
//	pServer->CloseServer();
//
//	igtl::MUSiiC_TCP_STATUS tcp_status;
//	tcp_status =  pServer->GetTCPStatus();
//	
//	switch(tcp_status)
//	{
//		case igtl::M_TCP_Server_Disconnected:
//			printf("Connected\n");
//			break;
//	}
//	
//
//	return 0;
//}