/*=========================================================================

  Program:   Open IGT Link -- Example for Imager Client Program
  Module:    $RCSfile: $
  Language:  C++
  Date:      $Date: $
  Version:   $Revision: $

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstdio>

#include "igtlOSUtil.h"
#include "igtlImageMessage.h"
#include "igtlClientSocket.h"
#include "MUSiiCProfile.h"
int GetTestImage(igtl::ImageMessage::Pointer& msg, const char* dir, int i);
void GetRandomTestMatrix(igtl::Matrix4x4& matrix);

int main(int argc, char* argv[])
{
  //------------------------------------------------------------
  // Parse Arguments
  igtl::MUSiiCProfile profile;
  profile.SetSampleSizeOfFPS(30);

  if (argc != 5) // check number of arguments
    {
    // If not correct, print usage
    std::cerr << "Usage: " << argv[0] << " <hostname> <port> <fps> <imgdir>"    << std::endl;
    std::cerr << "    <hostname> : IP or host name"                    << std::endl;
    std::cerr << "    <port>     : Port # (18944 in Slicer default)"   << std::endl;
    std::cerr << "    <fps>      : Frequency (fps) to send coordinate" << std::endl;
    std::cerr << "    <imgdir>   : file directory, where \"igtlTestImage[1-5].raw\" are placed." << std::endl;
    std::cerr << "                 (usually, in the Examples/Imager/img directory.)" << std::endl;
    exit(0);
    }

  char*  hostname = argv[1];
  int    port     = atoi(argv[2]);
  double fps      = atof(argv[3]);
  int    interval = (int) (1000.0 / fps);
  char*  filedir  = argv[4];

  //------------------------------------------------------------
  // Establish Connection
  igtl::ClientSocket::Pointer socket;
  socket = igtl::ClientSocket::New();
  int r = socket->ConnectToServer(hostname, port);

  if (r != 0)
    {
    std::cerr << "Cannot connect to the server." << std::endl;
    exit(0);
    }

  //------------------------------------------------------------
  // loop
  for (int i = 0; i < 1000000; i ++)
    {

    //------------------------------------------------------------
    // size parameters
    int   size[]     = {256, 256, 1};       // image dimension
    float spacing[]  = {1.0, 1.0, 5.0};     // spacing (mm/pixel)
    int   svsize[]   = {256, 256, 1};       // sub-volume size
    int   svoffset[] = {0, 0, 0};           // sub-volume offset
    int   scalarType = igtl::ImageMessage::TYPE_UINT8;// scalar type

    //------------------------------------------------------------
    // Create a new IMAGE type message
    igtl::ImageMessage::Pointer imgMsg = igtl::ImageMessage::New();
    imgMsg->SetDimensions(size);
    imgMsg->SetSpacing(spacing);
    imgMsg->SetScalarType(scalarType);
    imgMsg->SetDeviceName("ImagerClient");
    imgMsg->SetSubVolume(svsize, svoffset);
    imgMsg->AllocateScalars();

    //------------------------------------------------------------
    // Set image data (See GetTestImage() bellow for the details)
    GetTestImage(imgMsg, filedir, i % 5);

    //------------------------------------------------------------
    // Get random orientation matrix and set it.
    igtl::Matrix4x4 matrix;
    GetRandomTestMatrix(matrix);
    imgMsg->SetMatrix(matrix);

    //------------------------------------------------------------
    // Pack (serialize) and send
    imgMsg->Pack();
    socket->Send(imgMsg->GetPackPointer(), imgMsg->GetPackSize());
	std::cerr << "fps: " << profile.GetFPS() << std::endl;
    igtl::Sleep(interval); // wait

    }

  //------------------------------------------------------------
  // Close connection
  socket->CloseSocket();

}

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
  std::cerr << "Reading " << filename << "...";

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

  std::cerr << "done." << std::endl;

  return 1;
}

//------------------------------------------------------------
// Function to generate random matrix.
void GetRandomTestMatrix(igtl::Matrix4x4& matrix)
{
  //float position[3];
  //float orientation[4];

  /*
  // random position
  static float phi = 0.0;
  position[0] = 50.0 * cos(phi);
  position[1] = 50.0 * sin(phi);
  position[2] = 0;
  phi = phi + 0.2;

  // random orientation
  static float theta = 0.0;
  orientation[0]=0.0;
  orientation[1]=0.6666666666*cos(theta);
  orientation[2]=0.577350269189626;
  orientation[3]=0.6666666666*sin(theta);
  theta = theta + 0.1;

  igtl::Matrix4x4 matrix;
  igtl::QuaternionToMatrix(orientation, matrix);

  matrix[0][3] = position[0];
  matrix[1][3] = position[1];
  matrix[2][3] = position[2];
  */

  matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
  matrix[0][1] = 0.0;  matrix[1][1] = -1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
  matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
  matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = 0.0; matrix[3][3] = 1.0;
  
  igtl::PrintMatrix(matrix);
}

///***************************************************************************
//Copyright May/2011
//MUSiiC Laboratory
//Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
//Johns Hopkins Medical Institutions
//Department of Radiology, Division of Medical Imaging Physics
//
//For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
//***************************************************************************/
//
//#include <iostream>
//#include <math.h>
//#include <cstdlib>
//#include <cstring>
//
//#include "igtlOSUtil.h"
//#include "igtlMessageHeader.h"
//#include "igtlImageMessage.h"
//#include "igtlClientSocket.h"
//#include "igtlStatusMessage.h"
//#include "MUSiiCUtil.h"
//
//
//#include <iostream>
//#include <fstream>
//
//int main(int argc, char* argv[])
//{
//
//  //------------------------------------------------------------
//  // Establish Connection
//
//  igtl::ClientSocket::Pointer socket;
//  socket = igtl::ClientSocket::New();
//  int r = socket->ConnectToServer("127.0.0.1", 12345);
//  
//  if (r != 0)
//    {
//    std::cerr << "Cannot connect to the server." << std::endl;
//    exit(0);
//    }
//
//  //------------------------------------------------------------
//  // Create a message buffer to receive header
//  /*igtl::MessageHeader::Pointer headerMsg;
//  headerMsg = igtl::MessageHeader::New();
//  */
//  while (1)
//    {
//    //------------------------------------------------------------
//    // loop
//    //for (int i = 0; i < 100; i ++)
//      {
//      
//      // Initialize receive buffer
//	  igtl::MessageBase::Pointer Msg = igtl::MessageBase::New();
//      //headerMsg->InitPack();
//	  Msg->InitPack();
//      
//      // Receive generic header from the socket
//      //int r = socket->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize());
//	  int r = socket->Receive(Msg->GetPackPointer(), Msg->GetPackSize());
//      if (r == 0)
//      {
//        socket->CloseSocket();
//        exit(0);
//      }
//      //if (r != headerMsg->GetPackSize())
//	  if (r != Msg->GetPackSize())
//      {
//        continue;
//      }
//      
//      // Deserialize the header
//      Msg->Unpack();
//      
//	  //igtl::MessageBase::Pointer Msg = igtl::MessageBase::New();
//	  //igtl::ImageMessage::Pointer IM = igtl::ImageMessage::New();
//	  //Msg->SetMessageHeader(headerMsg);
//	  Msg->AllocatePack();
//
//	  /*IM->SetMessageHeader(headerMsg);
//	  IM->AllocatePack();*/
//
//	  int sz1 = Msg->GetBodySizeToRead();
//	  //int sz2 = IM->GetBodySizeToRead();
//
//	  r = socket->Receive(Msg->GetPackBodyPointer(), Msg->GetBodySizeToRead());
//
//	  int c = Msg->Unpack(1);
//	    if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
//		{
//		// Retrive the transform data
//			/*igtl::ImageMessage::Pointer img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(Msg);*/
//			igtl::MessageBase::Pointer Msg2 = Msg;
//			Msg = igtl::MessageBase::New();
//
//			igtl::StringMessage::Pointer stringMsg2 = igtl::RetrieveMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(Msg2);
//			
//			igtl::StringMessage::Pointer stringMsg = stringMsg2;
//
//			stringMsg2 = igtl::StringMessage::New();
//
//			
//			 /*igtl::Matrix4x4 matrix;
//			 img->GetMatrix(matrix);
//			 igtl::PrintMatrix(matrix);
//		     std::cerr << std::endl;*/
//
//			std::cerr << "Encoding: " << stringMsg->GetEncoding() << "; "
//              << "String: " << stringMsg->GetString() << std::endl << std::endl;
//		}
//      }
//    }
//
//  //------------------------------------------------------------
//  // Close connection (The example code never reaches this section ...)
//  
//  socket->CloseSocket();
//
//}



//
//int main(int argc, char* argv[])
//{
//  //------------------------------------------------------------
//  // Parse Arguments
//
//  //if (argc != 3) // check number of arguments
//  //  {
//  //  // If not correct, print usage
//  //  std::cerr << "    <hostname> : IP or host name"                    << std::endl;
//  //  std::cerr << "    <port>     : Port # (18944 in Slicer default)"   << std::endl;
//  //  exit(0);
//  //  }
//
//  //char*  hostname = argv[1];
//  //int    port     = atoi(argv[2]);
//
//  //------------------------------------------------------------
//  // Establish Connection
//
//  igtl::ClientSocket::Pointer socket;
//  socket = igtl::ClientSocket::New();
//  //int r = socket->ConnectToServer(hostname, port);
//  int r = socket->ConnectToServer("127.0.0.1", 12345);
//  
//  if (r != 0)
//    {
//    std::cerr << "Cannot connect to the server." << std::endl;
//    exit(0);
//    }
//
//  //------------------------------------------------------------
//  // Create a message buffer to receive header
//  igtl::MessageHeader::Pointer headerMsg;
//  headerMsg = igtl::MessageHeader::New();
//  
//  while (1)
//    {
//    //------------------------------------------------------------
//    // loop
//    //for (int i = 0; i < 100; i ++)
//      {
//      
//      // Initialize receive buffer
//      headerMsg->InitPack();
//      
//      // Receive generic header from the socket
//      int r = socket->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize());
//      if (r == 0)
//      {
//        socket->CloseSocket();
//        exit(0);
//      }
//      if (r != headerMsg->GetPackSize())
//      {
//        continue;
//      }
//      
//      // Deserialize the header
//      headerMsg->Unpack();
//      
//	  igtl::MessageBase::Pointer Msg = igtl::MessageBase::New();
//	  //igtl::ImageMessage::Pointer IM = igtl::ImageMessage::New();
//	  Msg->SetMessageHeader(headerMsg);
//	  Msg->AllocatePack();
//
//	  /*IM->SetMessageHeader(headerMsg);
//	  IM->AllocatePack();*/
//
//	  int sz1 = Msg->GetBodySizeToRead();
//	  int sz2 = IM->GetBodySizeToRead();
//
//	  r = socket->Receive(Msg->GetPackBodyPointer(), Msg->GetBodySizeToRead());
//
//	  int c = Msg->Unpack(1);
//	    if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
//		{
//		// Retrive the transform data
//			/*igtl::ImageMessage::Pointer img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(Msg);*/
//			igtl::StringMessage::Pointer stringMsg2 = igtl::RetrieveMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(Msg);
//
//			igtl::StringMessage::Pointer stringMsg = stringMsg2;
//
//			stringMsg2 = igtl::StringMessage::New();
//
//			Msg = igtl::MessageBase::New();
//			 /*igtl::Matrix4x4 matrix;
//			 img->GetMatrix(matrix);
//			 igtl::PrintMatrix(matrix);
//		     std::cerr << std::endl;*/
//
//			std::cerr << "Encoding: " << stringMsg->GetEncoding() << "; "
//              << "String: " << stringMsg->GetString() << std::endl << std::endl;
//		}
//      }
//    }
//
//  //------------------------------------------------------------
//  // Close connection (The example code never reaches this section ...)
//  
//  socket->CloseSocket();
//
//}
