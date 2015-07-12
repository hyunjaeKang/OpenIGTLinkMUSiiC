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

class CallbackInfo
{
public:
	CallbackInfo()
	{
		m_bigtlMsgVector = false;
	}
	
	~CallbackInfo()
	{
	}

	bool SetDataInterface(igtl::MUSiiCigtlMsgVector::Pointer msgVector)
	{
		if(msgVector.IsNotNull())
		{
			m_pigtlMsgVector = msgVector;
			m_bigtlMsgVector = true;
		}
		else
			m_bigtlMsgVector = false;

		return m_bigtlMsgVector;

	}
	
	int Callbackfunction(int numOfRun, int TaskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
		std::string des;
		bool bData = GetDescription(TaskInfo, des, data1);
		printCallbackInfo(des, bData, numOfRun, TaskInfo, ptr, data1, data2, data3);

		return 0;
	}
	
	void printCallbackInfo(std::string description, bool data, int numOfRun, int Taskinfo, void* ptr, void* data1, void* data2, void* data3)
	{
		double t;
		t = *(double*)data2;
		std::string* name = (std::string*) data3;

		printf("\n");
		printf("/// %s ///\n", description.c_str());
		
		if(data)
			printf("index of data: %d, TaskInfo: %d\n", numOfRun, Taskinfo);
		else
			printf("index of client: %d, TaskInfo: %d\n", numOfRun, Taskinfo);
		
		printf("Message: %s\n", name->c_str() );
		printf("timestamp: %f\n", t);
		printf("\n");
		if(!data)
		{
			int s = m_pigtlMsgVector->concurrent_size();
			printf("The size of Data buffer is %d\n", s);
			printf("=============================\n");
		}
		else
		{
		}

	}

	bool GetDescription(int TaskInfo, std::string& des, void* data1)
	{
		bool bData;
		std::string des_temp;
		switch(TaskInfo)
		{
			case igtl::M_TCP_Server_Created:
				des_temp = "CallbackInfo::TCP Server is created";
				break;
			case igtl::M_TCP_Server_Connected:
				des_temp = "CallbackInfo::TCP Server is connecting";
				break;
			case igtl::M_TCP_Server_Disconnected:
				des_temp = "CallbackInfo::TCP Server is disconnected";
				break;
			case igtl::M_TCP_Server_Pause:
				des_temp = "CallbackInfo::TCP Server Pause";
				break;
		}
			
		std::string temp2;
		if(data1 == NULL)
		{
			temp2 = "_ without Data";
			bData = false;
		}
		else 
		{
			temp2 = "_ with Data";
			bData = true;
		}


		des = des_temp +temp2;
		return bData;
				
	}

public:
	igtl::MUSiiCigtlMsgVector::Pointer m_pigtlMsgVector;
	bool m_bigtlMsgVector;
};


//------------------------------------------------------------
// Function to read test image data
int GetTestImage(igtl::ImageMessage::Pointer& msg, const char* dir, int i)
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
  matrix[0][1] = 0.0;  matrix[1][1] = -1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
  matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
  matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = 0.0; matrix[3][3] = 1.0;
  
  //igtl::PrintMatrix(matrix);
}

int main (int argc, char* argv[])
{
	igtl::MUSiiCTCPServerUni::Pointer pServer = igtl::MUSiiCTCPServerUni::New();
	pServer->PrepareNetwork();

	CallbackInfo call;
	pServer->AddExternalLocalCallbackFunction(&call, &CallbackInfo::Callbackfunction);
	call.SetDataInterface(pServer->GetNetworkBuffer());

	pServer->CreateServer(6125);
	igtl::Sleep(1000);
	
	
	igtl::ImageMessage::Pointer imgMsg;
	for(int i=0; i<100; i ++)
	{
		//------------------ Data Packing ----------------------------
		//------------------------------------------------------------
		//------------------------------------------------------------
        // size parameters
        int   size[]     = {256, 256, 1};       // image dimension
        float spacing[]  = {1.0, 1.0, 5.0};     // spacing (mm/pixel)
        int   svsize[]   = {256, 256, 1};       // sub-volume size
        int   svoffset[] = {0, 0, 0};           // sub-volume offset
        int   scalarType = igtl::ImageMessage::TYPE_UINT8;// scalar type
        
        //------------------------------------------------------------
        // Create a new IMAGE type message
        imgMsg = igtl::ImageMessage::New();
        imgMsg->SetDimensions(size);
        imgMsg->SetSpacing(spacing);
        imgMsg->SetScalarType(scalarType);
        imgMsg->SetDeviceName("ImagerClient");
        imgMsg->SetSubVolume(svsize, svoffset);
        imgMsg->AllocateScalars();
        
        //------------------------------------------------------------
        // Set image data (See GetTestImage() bellow for the details)
        GetTestImage(imgMsg, "./img", i % 5);
        
        //------------------------------------------------------------
        // Get randome orientation matrix and set it.
        igtl::Matrix4x4 matrix;
        GetRandomTestMatrix(matrix);
        imgMsg->SetMatrix(matrix);
        
        //------------------------------------------------------------
        // Pack (serialize) and send
        imgMsg->Pack();
		//------------------------------------------------------------
		//------------------------------------------------------------
		//------------------------------------------------------------

		pServer->PutigtlMsg((igtl::MessageBase::Pointer)imgMsg);
		igtl::Sleep(1000);
	}	
	
	printf("==========================\n");
	printf("==========================\n");
	printf("==========================\n");
	printf("Done\n");
	printf("==========================\n");
	printf("==========================\n");
	printf("==========================\n");
	igtl::Sleep(5000);
	//pServer->WaitTask();
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