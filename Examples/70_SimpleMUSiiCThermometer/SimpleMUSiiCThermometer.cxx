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
#include <MUSiiCTCPServer.h>
#include <MUSiiCIGTLUtil.h>
#include <MUSiiCIGTLRS232CSimple.h>


#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
using namespace igtl;
int main(int argc, char** argv)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	
	igtl::MUSiiCIGTLRS232CSimple::Pointer pRS232 = igtl::MUSiiCIGTLRS232CSimple::New();
	int r = pRS232->OpenComPort("COM4", "2400","Even", "7 bit", "1 bit") ;
	std::string msg1, msg2;

	msg1 = "#001N";
	//pRS232->SendBuffer((unsigned char*)msg1.c_str(), 5);
	//pRS232->SendBuffer("#001N", 5);
	char *buff ="#001N";
	

	FILE * pFile;
	pFile = fopen ("MUSiiC_Temp.txt","w");

	fprintf (pFile, "======================\n");
	fprintf (pFile, "Temperature Monitoring\n");
	fprintf (pFile, "======================\n");

	//pRS232->SendBuffer(buff,5);
	for(int i=0; i< 1000; i++)
	{
		pRS232->SendBuffer(buff,5);
		igtl::Sleep(1000);
		msg2 = pRS232->Receive();
	
		std::cout << "============================"<<std::endl;
		std::cout << "Temperature data : " << msg2 <<std::endl;

		fprintf (pFile, "=================================\n");
		fprintf (pFile, "Temperature data : %s", msg2.c_str());

		if(msg2.compare("Err") == 0 || msg2.size() == 0)
		{
			std::cout << "Error " << std::endl;
			fprintf (pFile, "Error");
		}
		else
		{
			float Temp1 = (float)igtl::HexStringToInt(msg2.substr(0,5));
			float Temp2 = (float)igtl::HexStringToInt(msg2.substr(6,5));

			std::string tempunit;
			tempunit = msg2.substr(12,1);
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

			std::string temp1 = igtl::double_To_string(Temp1/10.0);
			std::string temp2 = igtl::double_To_string(Temp2/10.0);
			fprintf (pFile, "TimeStamp1::  : %s",    t1.c_str());
			fprintf (pFile, "TimeStamp1::  : %s",    t2.c_str());
			fprintf (pFile, "T1        ::  : %s  %s", temp1.c_str(), tempunit.c_str());
			fprintf (pFile, "T2        ::  : %s  %s", temp2.c_str(), tempunit.c_str());

//			double ts = igtl::GetTimeStampDouble();//GetTimeStamp();
//			unsigned int sec = (unsigned int) (ts);
//			unsigned int frac = (unsigned int) ((ts-sec)*1e9);
			
		}
	}

	return 0;
}