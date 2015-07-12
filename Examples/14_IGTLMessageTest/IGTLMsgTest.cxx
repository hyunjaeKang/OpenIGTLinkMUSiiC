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

#include <MUSiiCDef.h>
#include <MUSiiCIGTLUtil.h>
#include <vector>
#include <string>
class FunctionNameTest
{
public:
	FunctionNameTest()
	{
		std::cout << "Function name is : " << __FUNCTION__ << endl;

		std::string funname = __FUNCTION__;
		std::cout << "Function name with string : " <<funname << std::endl;
	}

	~FunctionNameTest()
	{
		std::cout << "Function name is : " << __FUNCTION__ << endl;
	}

	void Test1()
	{
		std::cout << "Function name is : " << __FUNCTION__ << endl;

		std::string funname = __FUNCTION__;
		std::cout << "Function name with string : " <<funname << std::endl;
	}

	void Test2()
	{
		std::cout << "Function name is : " << __FUNCTION__ << endl;

		std::string funname = __FUNCTION__;
		std::cout << "Function name with string : " <<funname << std::endl;
	}

	void Test3()
	{
		std::cout << "Function name is : " << __FUNCTION__ << endl;

		std::string funname = __FUNCTION__;
		std::cout << "Function name with string : " <<funname << std::endl;
	}

};

int main (int argc, char* argv[])
{	
	
	/// Test ArgMessage
	/// Create ArgMessage
	std::cout << " Test ArgMessage " <<std::endl;

	igtl::ArgMessage::Pointer argMsg = igtl::ArgMessage::New();
	argMsg->AddArgument("MTKTaskID");
	argMsg->AddArgument("1000");
	argMsg->AddArgument("int");
	argMsg->AddArgument("100");

	argMsg->AllocateArguments();
	argMsg->Pack();

	/// Convert MessageBase
	igtl::MessageBase::Pointer MsgB = (igtl::MessageBase::Pointer)argMsg;

	/// Retrive ArgMessage
	igtl::ArgMessage::Pointer ArgMsg2 = igtl::RetrieveMessage<igtl::ArgMessage::Pointer, igtl::ArgMessage>(MsgB);

	int num = ArgMsg2->GetNumOfArguments();

	for(int i=0; i< num; i++)
	{
		std::cout << i <<"-th Argument:: " << ArgMsg2->GetArgument(i) << std::endl;
	}

	std::cout << std::endl;


	/// Test String Message
	std::cout << "Test StringMessage" << std::endl;

	igtl::StringMessage::Pointer strMsg = igtl::StringMessage::New();
	strMsg->SetString("Hello World");
	strMsg->SetString("MTKTaskID");
	strMsg->SetString("10000");
	strMsg->SetString("XXXXXXX");

	strMsg->AllocatePack();

	strMsg->Pack();

	igtl::MessageBase::Pointer MsgB2 = (igtl::MessageBase::Pointer)strMsg;

	igtl::StringMessage::Pointer strMsg2 = igtl::RetrieveMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(MsgB2);

	std::cout<< "String Message is :: " << strMsg2->GetString() << std::endl;

	
	///// Test of Function Name
	{
		FunctionNameTest funt;
		funt.Test1();
		funt.Test2();
		funt.Test3();
	}
	
	return 0;
}