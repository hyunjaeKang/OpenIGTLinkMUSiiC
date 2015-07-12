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

#include <MUSiiCIGTLUtil.h>
#include <MUSiiCIGTLRS232C_IOCP.h>
using namespace igtl;

igtl::MUSiiCIGTLRS232C_IOCP::Pointer g_pRS232;
bool                                 g_bTask;
double                               gTxTime;
double                               gRxTime;
int                                  g_Count;

int SendData()
{
	char *buff ="#001N";
	return g_pRS232->SendString(buff);
}

void PrintTemperature(std::string msg)
{
	if(msg.find("Err") != std::string::npos || msg.size() < 16)
	{
		/*std::cout << "Error " << std::endl;
		fprintf (pFile, "Error");*/
	}
	else
	{
		float Temp1 = (float)igtl::HexStringToInt(msg.substr(0,5));
		float Temp2 = (float)igtl::HexStringToInt(msg.substr(6,5));

		std::string tempunit;
		tempunit = msg.substr(12,1);
		if(tempunit.compare("0") == 0)
			tempunit = "Celsius";
		else
			tempunit = "Fahrenheit";

		//double ts = igtl::GetTimeStampDouble();
		//igtl::double_To_string(igtl::GetTimeStampDouble())
		std::string t1 = igtl::GetNowTimeString();
		std::string t2 = igtl::double_To_string(igtl::GetTimeStampDouble());
		std::cout << "TimeStamp1:: " << t1 << std::endl;
		std::cout << "TimeStamp2:: " << t2 << std::endl;
		std::cout << "T1 : " << Temp1/10.0 << " " << tempunit << std::endl;
		std::cout << "T2 : " << Temp2/10.0 << " " << tempunit << std::endl;

		igtl::Sleep(50);
		SendData();
		/*std::string temp1 = igtl::double_To_string(Temp1/10.0);
		std::string temp2 = igtl::double_To_string(Temp2/10.0);
		*/
	//			double ts = igtl::GetTimeStampDouble();//GetTimeStamp();
	//			unsigned int sec = (unsigned int) (ts);
	//			unsigned int frac = (unsigned int) ((ts-sec)*1e9);
	}
}


/// Declare a function that is called MUSiiCCallbackInterface
/// rCallback = this->PostTaskProcessing(M_POST_CONTROL_PRAR_DATA, M_RS232C_RX, this, NULL, rs232_io, rs232_port); // Check point
/// rCallback = this->PostTaskProcessing(M_POST_CONTROL_PRAR_DATA, M_RS232C_TX, this, NULL, rs232_io, rs232_port); // Check point
int PostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	/*std::cout << "PostCallback Function called!" << std::endl;*/
	
	igtl::LP_MTKRS232C_PORT_INFO rs232_port;
	igtl::LP_MTKRS232C_IO_DATA   rs232_io;

	if (data2 != NULL && data3 != NULL)
	{
		rs232_io = (igtl::LP_MTKRS232C_IO_DATA)data2;
		rs232_port = (igtl::LP_MTKRS232C_PORT_INFO)data3;
	}
	else
		return 0;

	if(taskInfo ==  M_RS232C_RX)
	{
		gRxTime = igtl::GetTimeStampDouble();
		std::string msg = rs232_io->buf; 
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
		std::cout << igtl::GetNowTimeString() << " :: " << rs232_io->strPort << ": Rx Data <<  " << msg << std::endl;
		std::cout << "****** Elasped Time : " << gRxTime - gTxTime << std::endl; 
		std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
		PrintTemperature(rs232_io->buf );
		g_Count = 0;
		
	}
	else if((taskInfo ==  M_RS232C_TX))
	{
		gTxTime = igtl::GetTimeStampDouble();
		std::cout << std::endl;
		std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
		std::cout << igtl::GetNowTimeString() << " :: " << rs232_io->strPort << ": Tx Data <<  " << rs232_io->buf << std::endl;
		std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	}
	else if(taskInfo ==  M_RS232C_TX_INCOMPLETE) 
	{
		g_Count++;
		//std::cout << g_Count << "-th Tx Incomplete Message Transfer !" <<std::endl;
		if(g_Count >7)
			SendData();
	}
	else if(taskInfo ==  M_RS232C_RX_INCOMPLETE)
	{
		g_Count++;
		//std::cout << g_Count << "-th Rx Incomplete Message Transfer !" <<std::endl;
		if(g_Count >7)
			SendData();
	}
	else
		std::cout << "Wrong FeedBack !" <<std::endl;
	
	
	return 0;
}
void PrintMenu()
{
	////////////////////////////////
	std::cout << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << "****** How to use ***************" << std::endl;
	std::cout << "01. Show Menu         : Press 'm'" << std::endl;
	std::cout << "02. Quit this program : Press 'q'" << std::endl;
	std::cout << "03. Send Data         : Press 's'" << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << std::endl;
	/////////////////////////////
}




int main(int argc, char** argv)
{


	char c;
	char* testbuff = new char[100];
	g_pRS232 = igtl::MUSiiCIGTLRS232C_IOCP::New();
	g_pRS232->AddExternalGlobalOutputCallbackFunction(PostCallback, "PostCallbackFunction");

	int r = g_pRS232->OpenComPort("COM4", "2400","Even", "7 bit", "1 bit") ;
	PrintMenu();
	SendData();
	g_pRS232->StartMonitoring();
	
	g_bTask = true;

	while(g_bTask)
	{
		if(igtl::kbhit())
		{
			c = getchar();
			if(c == 'q')
			{
				g_bTask = false;
				break;
			}
			else if(c == 'm')
				PrintMenu();
			else if(c == 's')
				SendData();
		}
		
		
	}

	

	return 0;
}

//for(int i=0; i< 10; i++)
//	{
//		char *buff ="#001N";
//		g_pRS232->SendString(buff);
//		
//		//pRS232->Receive_SYNC();
//	
//		//std::cout << "============================"<<std::endl;
//		//std::cout << "Temperature data : " << msg2 <<std::endl;
//
//		/*fprintf (pFile, "=================================\n");
//		fprintf (pFile, "Temperature data : %s", msg2.c_str());*/
//
////		if(msg2.compare("Err") == 0 || msg2.size() == 0)
////		{
////			/*std::cout << "Error " << std::endl;
////			fprintf (pFile, "Error");*/
////		}
////		else
////		{
//////			float Temp1 = (float)igtl::HexStringToInt(msg2.substr(0,5));
//////			float Temp2 = (float)igtl::HexStringToInt(msg2.substr(6,5));
//////
//////			std::string tempunit;
//////			tempunit = msg2.substr(12,1);
//////			if(tempunit.compare("0") == 0)
//////				tempunit = "Celsius";
//////			else
//////				tempunit = "Fahrenheit";
//////
//////			//double ts = igtl::GetTimeStampDouble();
//////			//igtl::double_To_string(igtl::GetTimeStampDouble())
//////			std::string t1 = igtl::GetNowTimeString();
//////			std::string t2 = igtl::double_To_string(igtl::GetTimeStampDouble());
//////			std::cout << "TimeStamp1:: " << t1 << std::endl;
//////			std::cout << "TimeStamp2:: " << t2 << std::endl;
//////			std::cout << "T1 : " << Temp1/10.0 << " " << tempunit << std::endl;
//////			std::cout << "T2 : " << Temp2/10.0 << " " << tempunit << std::endl;
//////
//////			std::string temp1 = igtl::double_To_string(Temp1/10.0);
//////			std::string temp2 = igtl::double_To_string(Temp2/10.0);
//////			fprintf (pFile, "TimeStamp1::  : %s",    t1.c_str());
//////			fprintf (pFile, "TimeStamp1::  : %s",    t2.c_str());
//////			fprintf (pFile, "T1        ::  : %s  %s", temp1.c_str(), tempunit.c_str());
//////			fprintf (pFile, "T2        ::  : %s  %s", temp2.c_str(), tempunit.c_str());
//////
////////			double ts = igtl::GetTimeStampDouble();//GetTimeStamp();
////////			unsigned int sec = (unsigned int) (ts);
////////			unsigned int frac = (unsigned int) ((ts-sec)*1e9);
////			
////		}
//	}