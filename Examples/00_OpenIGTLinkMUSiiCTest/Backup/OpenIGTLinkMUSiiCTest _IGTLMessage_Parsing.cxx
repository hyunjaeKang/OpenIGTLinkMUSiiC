/***************************************************************************
Copyright May/2011
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

#include "igtlOSUtil.h"
#include "igtlMessageHeader.h"
#include "igtlImageMessage.h"
#include "igtlClientSocket.h"
#include "igtlStatusMessage.h"
#include "MUSiiCUtil.h"


#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{

  //------------------------------------------------------------
  // Establish Connection

  igtl::ClientSocket::Pointer socket;
  socket = igtl::ClientSocket::New();
  int r = socket->ConnectToServer("127.0.0.1", 12345);
  
  if (r != 0)
    {
    std::cerr << "Cannot connect to the server." << std::endl;
    exit(0);
    }

  //------------------------------------------------------------
  // Create a message buffer to receive header
  /*igtl::MessageHeader::Pointer headerMsg;
  headerMsg = igtl::MessageHeader::New();
  */
  while (1)
    {
    //------------------------------------------------------------
    // loop
    //for (int i = 0; i < 100; i ++)
      {
      
      // Initialize receive buffer
	  igtl::MessageBase::Pointer Msg = igtl::MessageBase::New();
      //headerMsg->InitPack();
	  Msg->InitPack();
      
      // Receive generic header from the socket
      //int r = socket->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize());
	  int r = socket->Receive(Msg->GetPackPointer(), Msg->GetPackSize());
      if (r == 0)
      {
        socket->CloseSocket();
        exit(0);
      }
      //if (r != headerMsg->GetPackSize())
	  if (r != Msg->GetPackSize())
      {
        continue;
      }
      
      // Deserialize the header
      Msg->Unpack();
      
	  //igtl::MessageBase::Pointer Msg = igtl::MessageBase::New();
	  //igtl::ImageMessage::Pointer IM = igtl::ImageMessage::New();
	  //Msg->SetMessageHeader(headerMsg);
	  Msg->AllocatePack();

	  /*IM->SetMessageHeader(headerMsg);
	  IM->AllocatePack();*/

	  int sz1 = Msg->GetBodySizeToRead();
	  //int sz2 = IM->GetBodySizeToRead();

	  r = socket->Receive(Msg->GetPackBodyPointer(), Msg->GetBodySizeToRead());

	  int c = Msg->Unpack(1);
	    if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
		{
		// Retrive the transform data
			/*igtl::ImageMessage::Pointer img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(Msg);*/
			igtl::MessageBase::Pointer Msg2 = Msg;
			Msg = igtl::MessageBase::New();

			igtl::StringMessage::Pointer stringMsg2 = igtl::RetrieveMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(Msg2);
			
			igtl::StringMessage::Pointer stringMsg = stringMsg2;

			stringMsg2 = igtl::StringMessage::New();

			
			 /*igtl::Matrix4x4 matrix;
			 img->GetMatrix(matrix);
			 igtl::PrintMatrix(matrix);
		     std::cerr << std::endl;*/

			std::cerr << "Encoding: " << stringMsg->GetEncoding() << "; "
              << "String: " << stringMsg->GetString() << std::endl << std::endl;
		}
      }
    }

  //------------------------------------------------------------
  // Close connection (The example code never reaches this section ...)
  
  socket->CloseSocket();

}



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
