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
#include <MUSiiCigtlMsgFILEIO.h>
#include <igtlImageMessage.h>

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

#include <MUSiiCUtil.h>
#include <conio.h>

#include <MUSiiCTCPLightServerUni.h>
#include <MUSiiCTCPSimpleServerUni.h>
using namespace std;

bool g_bIsFile;
igtl::MUSiiCigtlMsgFILEIO::Pointer g_pigtlFile;
igtl::MUSiiCTCPLightServerUni::Pointer g_pServer;
igtl::ImageMessage::Pointer g_img;
MusiicTCPSimpleServerUni<igtl::ImageMessage::Pointer> server;

void wait()
{
    printf("\npress any key to continue");
    while (!_kbhit())
    {
    }
    _getch();
    fflush(stdin);
    system("cls");
}


string GetFileName()
{
	string str;
	cout << "Please enter full name: ";
	cin >> str;
	return str;
}

//igtl::ImageMessage::Pointer ReadImageMessageFile(string filename, igtl::MUSiiCigtlMsgFILEIO::Pointer g_pigtlFile)
//{
//	igtl::ImageMessage::Pointer img;
//	if(g_pigtlFile.IsNotNull())
//	{
//		img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(g_pigtlFile->ReadSingleFile(filename));
//		if(img.IsNotNull())
//		{
//			float matrix[4][4];
//			matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
//			matrix[0][1] = 0.0;  matrix[1][1] = -1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
//			matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
//			matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = 0.0; matrix[3][3] = 1.0;
//			img->SetMatrix(matrix);
//			float s_x, s_y, s_z;
//			img->GetSpacing(s_x, s_y, s_z);
//			s_z = 80.0*0.346*3.14156/180;
//			img->SetSpacing(s_x, s_y, s_z);
//
//			img->Pack();
//			g_bIsFile = true;
//		}
//		else
//			g_bIsFile = false;
//	}
//	else
//		g_bIsFile = false;
//
//	return g_bIsFile ? img : NULL;
//}
igtl::ImageMessage::Pointer DuplateImageMessage(igtl::ImageMessage::Pointer img)
{
	igtl::ImageMessage::Pointer img2;
	////////////////////////////////////////
	img2 = igtl::ImageMessage::New();
	int x,y,z;
	float sx, sy, sz;
	int   scalarType = igtl::ImageMessage::TYPE_UINT8;// scalar type
	int type = img->GetScalarType();
	img->GetDimensions(x,y,z); ///
	img2->SetDimensions(x,y,z);
	img->GetSpacing(sx,sy,sz); ///
	img2->SetSpacing(sz,sy,sz);
	img2->SetScalarTypeToUint8();
	img2->SetSubVolume(x,y,z,0,0,0);
	img2->SetDeviceName("Fake3DBMode");
	igtl::TimeStamp::Pointer ts = igtl::TimeStamp::New();
	ts->GetTime();
	img2->SetTimeStamp(ts);
	float matrix[4][4];
	img->GetMatrix(matrix);
	img2->SetMatrix(matrix);
	img2->AllocateScalars();
	//img2->SetMessageHeader(img);
	//img2->AllocatePack();
	memcpy(img2->GetScalarPointer(), img->GetScalarPointer(), img2->GetImageSize());
	//memcpy(img->GetPackBodyPointer(),img->GetPackBodyPointer(), temp_msg->GetPackBodySize());
	//img2->Pack();

	return img2;

}

igtl::MessageBase::Pointer ReadImageMessageFile(string filename, igtl::MUSiiCigtlMsgFILEIO::Pointer g_pigtlFile)
{
	igtl::ImageMessage::Pointer img;
	igtl::MessageBase::Pointer msg;
	
	if(g_pigtlFile.IsNotNull())
	{
		msg = g_pigtlFile->ReadSingleFile(filename,false);
		//msg = g_pigtlFile->ReadSingleFileRecoverMode(filename);
		img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);
		if(msg.IsNotNull())
		{
			/////////////////////////////////////////
			/*float matrix[4][4];
			matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
			matrix[0][1] = 0.0;  matrix[1][1] = -1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
			matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
			matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = 0.0; matrix[3][3] = 1.0;
			img->SetMatrix(matrix);
			float s_x, s_y, s_z;
			img->GetSpacing(s_x, s_y, s_z);
			s_z = 80.0*0.346*3.14156/180;
			img->SetSpacing(s_x, s_y, s_z);*/

			//img->Pack();
			g_bIsFile = true;
		}
		else
			g_bIsFile = false;
	}
	else
		g_bIsFile = false;

	return g_bIsFile ? msg : NULL;
}

igtl::MessageBase::Pointer ReadIGTLMessageFile(string filename, igtl::MUSiiCigtlMsgFILEIO::Pointer g_pigtlFile)
{
	igtl::MessageBase::Pointer msg;
	
	if(g_pigtlFile.IsNotNull())
	{
		msg = g_pigtlFile->ReadSingleFile(filename);
		if(msg.IsNotNull())
			g_bIsFile = true;
		else
			g_bIsFile = false;
	}
	else
		g_bIsFile = false;

	return g_bIsFile ? msg : NULL;
}



bool SendIGTLMsg(igtl::ImageMessage::Pointer& img)//, igtl::MUSiiCTCPLightServerUni::Pointer pServer)
{
	if(g_pServer.IsNotNull() && img.IsNotNull())
	{
		if(g_pServer->IsConnectedClients())
		{	
			printf("Address %x\n", img);
			igtl::ImageMessage::Pointer temp_img;
			//temp_img = DuplateImageMessage(img);
			temp_img = img;
			temp_img->Pack();
			g_pServer->PutigtlMsg((igtl::MessageBase::Pointer) temp_img);
			return true;
		}
	}
	else
		return false;

}

bool SendIGTLMsg2(igtl::MessageBase::Pointer& msg)//, igtl::MUSiiCTCPLightServerUni::Pointer pServer)
{
	if(g_pServer.IsNotNull() && msg.IsNotNull())
	{
		if(g_pServer->IsConnectedClients())
		{	
			printf("Address %x\n", msg);
			//igtl::ImageMessage::Pointer temp_img;
			//temp_img = DuplateImageMessage(img);
			//temp_img = img;
			//temp_img->Pack();
			msg->Pack();
			g_pServer->PutigtlMsg(msg);
			return true;
		}
	}
	else
		return false;

}



int main (int argc, char* argv[])
{
	g_pigtlFile = igtl::MUSiiCigtlMsgFILEIO::New();
	g_pServer = igtl::MUSiiCTCPLightServerUni::New();

	/*igtl::ImageMessage::Pointer img = igtl::ImageMessage::New();*/
	igtl::ImageMessage::Pointer img;// = igtl::ImageMessage::New();
	igtl::MessageBase::Pointer msg;
	bool b_Server = false;
	int port = 23979;
	g_pServer->PrepareNetwork();
	int r = g_pServer->CreateServer(port);
	
	igtl::Sleep(1000);
	if(r>0)
	{
		cout<< "Server socket was created with port number : " << port << endl;
		b_Server = true;
	}
	else
		cout<< "Server socket was failed with port number : " << port << endl;

	std::string m_FileName;
	char sel;
	
	g_bIsFile = false;

	for (;;)
    {
        printf("Initialized:\n");
		if(b_Server)
			cout<< "Server socket was created with port number : " << port << endl;
        printf("\n");
		printf("(F) Read File\n");
		if(g_bIsFile)
			printf("(S) Send File\n");
        printf("(X) exit\n");
        printf("\n");
        scanf("%c", &sel);

        switch (sel)
		{
			case 'f': case 'F':
				m_FileName = GetFileName();
				cout << "File name is  " << m_FileName <<endl;
				msg = ReadImageMessageFile(m_FileName, g_pigtlFile);
				//msg = ReadIGTLMessageFile(m_FileName, g_pigtlFile);
				break;
			case 's': case 'S':
				//img = ReadImageMessageFile(m_FileName, g_pigtlFile);
				//img = g_img;
				//SendIGTLMsg(img);
				SendIGTLMsg2(msg);
				break;
			case 'x': case 'X': goto goodbye;
        }
		igtl::Sleep(1000);
		wait();   
    }
goodbye:
	g_pServer->CloseServer();
	g_pServer = NULL;
	igtl::Sleep(1000);
	printf("Good Bye!!\n");
	return 0;
}