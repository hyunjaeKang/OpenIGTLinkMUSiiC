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
	int r = pRS232->OpenComPort("COM5", "115200","None", "8 bit", "1 bit") ;
	std::string msg1, msg2;

	
	////pRS232->SendBuffer(buff,5);
	////for(int i=0; i< 1000; i++)
	////{
	//	msg2 = pRS232->Receive();
	//	std::cout << "Temperature data : " << msg2 <<std::endl;
	////}

	bool bTask= true;
	char c;
	igtl::MUSiiCProfile gProfile;
	gProfile.SetSampleSizeOfFPS(50);

	while(bTask)
	{
		if(igtl::kbhit())
		{
			c = getchar();
			if(c == 'q')
			{
				bTask = false;
				break;
			}
		}

		msg2 = pRS232->Receive();
		if(msg2.find("*ACQ-TGR") != std::string::npos)
		{
			std::cout << "TimeStamp : "<< igtl::GetTimeStampDouble() << ", Message:" << msg2 <<"FPS: "<< gProfile.GetFPS()<<std::endl;
		}
	}

	return 0;
}