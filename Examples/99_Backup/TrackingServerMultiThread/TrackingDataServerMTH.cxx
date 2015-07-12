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
#include <igtlTrackingDataMessage.h>

#include <MUSiiCTCPSimpleServerUni.h>
//#include <MUSiiCTCPSimpleClientUni.h>


//------------------------------------------------------------
// Function to read test image data
int GetTestImage(igtl::USMessage::Pointer& msg, const char* dir, int i)
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
void GetRandomTestMatrix(igtl::Matrix4x4& matrix, float v)
{
  /*matrix[0][0] = v;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
  matrix[0][1] = 0.0;  matrix[1][1] = v;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
  matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = v; matrix[3][2] = 0.0;
  matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = 0.0; matrix[3][3] = v;*/
 
	float phi0   = 0.0;
	float theta0 = 0.0;
	float phi1   = 0.0;
	float theta1 = 0.0;
	float phi2   = 0.0;
	float theta2 = 0.0;
	
	float position[3];
	float orientation[4];

	// random position
	position[0] = 50.0 * cos(phi0);
	position[1] = 50.0 * sin(phi0);
	position[2] = 50.0 * cos(phi0);
	phi0 = phi0 + 0.2;

	// random orientation
	orientation[0]=0.0;
	orientation[1]=0.6666666666*cos(theta0);
	orientation[2]=0.577350269189626;
	orientation[3]=0.6666666666*sin(theta0);
	theta0 = theta0 + 0.1;

	//igtl::Matrix4x4 matrix;
	igtl::QuaternionToMatrix(orientation, matrix);

	matrix[0][3] = position[0];
	matrix[1][3] = position[1];
	matrix[2][3] = position[2];
}

int main (int argc, char* argv[])
{
	igtl::MUSiiCTCPServerUni::Pointer pServer = igtl::MUSiiCTCPServerUni::New();
	pServer->PrepareNetwork();

	pServer->CreateServer(23579);
	igtl::Sleep(1000);

	
	// MusiicTCPSimpleServerUni<igtl::TrackingDataMessage::Pointer> SimpleServer;
	// SimpleServer.CreateServer(23578);
	// igtl::Sleep(1000);

	igtl::TrackingDataMessage::Pointer trackingMsg;
	printf("Prees q for quit this program\n");
	int i = 0;
	igtl::Matrix4x4 matrix;
	for(;;)
	{   
        //------------------------------------------------------------
        // Create a new IMAGE type message
        trackingMsg = igtl::TrackingDataMessage::New();
      	trackingMsg->SetDeviceName("Tracker");
        
        igtl::TrackingDataElement::Pointer trackElement0;
		trackElement0 = igtl::TrackingDataElement::New();
		trackElement0->SetName("Channel 0");
		trackElement0->SetType(igtl::TrackingDataElement::TYPE_6D);;
		GetRandomTestMatrix(matrix, 1);
		trackElement0->SetMatrix(matrix);

		igtl::TrackingDataElement::Pointer trackElement1;
		trackElement1 = igtl::TrackingDataElement::New();
		trackElement1->SetName("Channel 1");
		trackElement1->SetType(igtl::TrackingDataElement::TYPE_6D);
		GetRandomTestMatrix(matrix, 2);
		trackElement1->SetMatrix(matrix);

		igtl::TrackingDataElement::Pointer trackElement2;
		trackElement2 = igtl::TrackingDataElement::New();
		trackElement2->SetName("Channel 2");
		trackElement2->SetType(igtl::TrackingDataElement::TYPE_6D);
		GetRandomTestMatrix(matrix, 3);
		trackElement2->SetMatrix(matrix);
		
		igtl::TimeStamp::Pointer time =igtl::TimeStamp::New();
		time->GetTime();
		trackingMsg->SetTimeStamp(time);
		trackingMsg->AddTrackingDataElement(trackElement0);
		trackingMsg->AddTrackingDataElement(trackElement1);
		trackingMsg->AddTrackingDataElement(trackElement2);
        // Pack (serialize) and send
        trackingMsg->Pack();
		//------------------------------------------------------------
		//------------------------------------------------------------
		//------------------------------------------------------------

		if(pServer->IsConnectedClients())
			pServer->PutigtlMsg((igtl::MessageBase::Pointer)trackingMsg);
			//pServer->TryPutigtlMsg((igtl::MessageBase::Pointer)trackingMsg);

		// if(SimpleServer.IsConnected())
			// SimpleServer.PutMessageData(trackingMsg);
		
		igtl::Sleep(0);

		/*char sel;
		scanf("%c", &sel);

		if( sel == 'q')
			break;*/

		i++;
	}	
	
	printf("==========================\n");
	printf("==========================\n");
	printf("==========================\n");
	printf("Done\n");
	printf("==========================\n");
	printf("==========================\n");
	printf("==========================\n");
	
	pServer->CloseServer();
	//SimpleServer.CloseServer();

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