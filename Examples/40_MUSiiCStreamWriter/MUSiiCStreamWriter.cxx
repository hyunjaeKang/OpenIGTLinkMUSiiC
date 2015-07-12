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

/***************************************************************************
This an example is about FakeRFServer.

***************************************************************************/
#include <stdio.h>
#include <igtlOSUtil.h> //igtl::Sleep
#include <igtlImageMessage.h>

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

#include <MUSiiCIGTLFileIO.h>
#include <MUSiiCTCPClient.h>



int main (int argc, char* argv[])
{	
	//------------------------------------------------------------
	// Parse Arguments

	if (argc != 4) // check number of arguments
	{
		// If not correct, print usage
		std::cerr << "    <hostname> : IP or host name"                    << std::endl;
		std::cerr << "    <port>     : Port # (18944 in Slicer default)"   << std::endl;
		std::cerr << "    prefix of filename : " << std::endl;
		exit(0);
	}

	char*  hostname         = argv[1];
	int    port            = atoi(argv[2]);
	char*  pre_fix_filename  = argv[3];

	igtl::MUSiiCTCPClient::Pointer pClient = igtl::MUSiiCTCPClient::New();
	
	

	igtl::MUSiiCIGTLMsgFileIO::Pointer pIgtlFileIO = igtl::MUSiiCIGTLMsgFileIO::New();


	/// Connect MUSiiCSync to MUSiiCTCPClient as post-MUSiiCTaskInterface
	pClient->AddPostMUSiiCTaskInterface<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>(pIgtlFileIO);


	std::string filename(pre_fix_filename);

	pIgtlFileIO->WriteStreamData(filename);

	pClient->ConnectToHost(hostname, port);

	printf("Prees q for quit this program\n");
	char sel;
	for(;;)
	{
		scanf("%c", &sel);

		if( sel == 'q')
			break;
	}
	
	pIgtlFileIO->WriteStreamDataStop();
	pClient->CloseClientSocket();

	return 0;
}