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
#include "igtlOSUtil.h" //igtl::Sleep
//#include <MUSiiCCallbackInterfaceControl.h>
//#include <MUSiiCFileIOAbstract.h>
//#include <MUSiiCVector.h>
#include <igtlTimeStamp.h>
#include <MUSiiCigtlMsgFILEIO.h>

int GlobalTask(int numOfRun, int v, void* ptr,void* data1,void* data2,void* data3)
{
	std::string* str = (std::string*)(data1);

	for(int i=0; i<v;i++)
		printf("Global Task:: %d: %s\n",i, str->c_str());

	return v;
}
 
int GlobalCallback(int numOfRun, int v, void* ptr,void* data1,void* data2,void* data3)
{
	std::string* str = (std::string*)(data1);

	for(int i=0; i<v;i++)
		printf("Global Callback:: %d: %s\n",i, str->c_str());

	return v;
}

class TestTask
{
public:	
	TestTask()
	{
	}

	~TestTask()
	{
	}

	int Task(int numOfRun, int v, void* ptr, void* data1, void* data2, void* data3)
	{
		std::string* str = (std::string*)(data1);

		for(int i=0; i<v;i++)
			printf("Local Task:: %d: %s\n",i, str->c_str());

		return v;
	}

	int Callback(int numOfRun, int v, void* ptr, void* data1, void* data2, void* data3)
	{
		std::string* str = (std::string*)(data1);

		for(int i=0; i<v;i++)
			printf("Local Callback:: %d: %s\n",i, str->c_str());

		return v;
	}

	int Callback2(int numOfRun, int v, void* ptr, void* data1, void* data2, void* data3)
	{
		std::string* str = (std::string*)(data1);

		for(int i=0; i<v;i++)
			printf("Local Callback2:: %d: %s\n",i, str->c_str());

		return v;
	}

	int Callback3(int numOfRun, int v, void* ptr, void* data1, void* data2, void* data3)
	{
		std::string* str = (std::string*)(data1);

		for(int i=0; i<v;i++)
			printf("Local Callback3:: %d: %s\n",i, str->c_str());

		return v;
	}
};

template<class Data> class TestVector
{
public:
	TestVector()
	{
	}
	~TestVector()
	{
	}

	bool SetDataIF(igtl::MUSiiCVector<Data>* dataIF)
	{
		if(dataIF!= NULL)
		{
			m_pMUSiiCVector = dataIF;
			return true;
		}
		return false;
	}

public:
	igtl::MUSiiCVector<Data>* m_pMUSiiCVector;
	//igtl::MUSiiCVector<Data>::Pointer  m_pVector;

};

int main (int argc, char* argv[])
{
	igtl::MUSiiCVector<double>::Pointer doubleVector;
	TestVector<double>			testclass;

	doubleVector = igtl::MUSiiCVector<double>::New();
	bool r = testclass.SetDataIF(doubleVector);

	int a(3);
	int* b = new int[1];
	b = &a;

	int c;
	c = *b;

	printf("A:%d\n", a);
	printf("B:%d\n", *b);
	printf("C:%d\n", c);

	


	igtl::TimeStamp::Pointer time;
	time = igtl::TimeStamp::New();
	time->GetTime();
	double t = time->GetTimeStamp();

	igtl::MUSiiCigtlMsgFILEIO::Pointer p_igtlF = igtl::MUSiiCigtlMsgFILEIO::New();
	


	
	
	//TestTask t;

	//igtl::MUSiiCCallbackInterfaceControl::Pointer call;
	//call = igtl::MUSiiCCallbackInterfaceControl::New();

	//call->AddExternalGlobalFunction(GlobalCallback, "GlobalCallback");
	//call->AddExternalLocalFunction(&t, &TestTask::Callback, "LocalCallback1");
	//call->AddExternalLocalFunction(&t, &TestTask::Callback2, "LocalCallback2");
	//call->AddExternalLocalFunction(&t, &TestTask::Callback3, "LocalCallback3");

	//std::string str1("Hello World");
	//std::string str2("My name is John");
	//std::string str3("Hello!!!!!!");
	//std::string str4("Good Bye");
	//int id;
	//int v;
	//std::string name;
	//int r; 

	//printf("**********************************\n");
	//printf("CALL All external callback function\n");
	//call->CallAllExternalInterfaces(NULL, &str1, NULL, NULL, 3);
	//printf("\n");

	//printf("**********************************\n");
	//printf("CALL One external callback function\n");
	//call->CallOneExternalInterfaceName("GlobalCallback",NULL, &str2, NULL, NULL, 1);
	//id = call->GetIDOfExternalInterface("GlobalCallback");
	//printf("The ID is %d\n", id);
	//printf("The function name is '%s'\n", call->GetNameOfExternalInterface(id).c_str());
	//name = call->GetNameOfExternalInterface(id).c_str();
	//printf("The return value of the function is %d(ID)\n", call->GetRetunValueOfExternalInterfaceID(id));
	//printf("The return value of the function is %d(Name)\n", call->GetRetunValueOfExternalInterfaceName(name));
	//printf("\n");

	//printf("**********************************\n");
	//printf("CALL One external callback function with Wrong name\n");
	//call->CallOneExternalInterfaceName("LocalCallback",NULL, &str3, NULL, NULL, 2);
	//id = call->GetIDOfExternalInterface("LocalCallback");
	//printf("The ID is %d\n", id);
	//printf("The function name is '%s'\n", call->GetNameOfExternalInterface(id).c_str());
	//name = call->GetNameOfExternalInterface(id).c_str();
	//printf("The return value of the function is %d(ID)\n", call->GetRetunValueOfExternalInterfaceID(id));
	//printf("The return value of the function is %d(Name)\n", call->GetRetunValueOfExternalInterfaceName(name));
	//printf("\n");

	//printf("**********************************\n");
	//printf("CALL One external callback function\n");
	//call->CallOneExternalInterfaceName("LocalCallback1",NULL, &str3, NULL, NULL, 2);
	//id = call->GetIDOfExternalInterface("LocalCallback1");
	//printf("The ID is %d\n", id);
	//printf("The function name is '%s'\n", call->GetNameOfExternalInterface(id).c_str());
	//name = call->GetNameOfExternalInterface(id).c_str();
	//printf("The return value of the function is %d(ID)\n", call->GetRetunValueOfExternalInterfaceID(id));
	//printf("The return value of the function is %d(Name)\n", call->GetRetunValueOfExternalInterfaceName(name));
	//printf("\n");

	//printf("**********************************\n");
	//printf("CALL some external callback functions with ID_List\n");
	//std::vector<int> list;
	//list.push_back(0);
	//list.push_back(1);
	//list.push_back(3);
	//list.push_back(4);
	//r = call->CallSomeExternalInterfacesIDs(list, NULL, &str3, NULL, NULL, 2);
	////call->CallOneExternalInterfaceName("LocalCallback1",NULL, &str3, NULL, NULL, 2);
	//printf("The number of called callback function is %d\n", r);
	//printf("\n");

	//printf("**********************************\n");
	//printf("CALL some external callback functions with Name_List\n");
	//std::vector<std::string> name_list;
	//name_list.push_back("GlobalCallback");
	//name_list.push_back("LocalCallback1");
	//name_list.push_back("LocalCallback3");
	//name_list.push_back("LocalCallback4");
	//r = call->CallSomeExternalInterfacesNames(name_list, NULL, &str3, NULL, NULL, 1);
	////call->CallOneExternalInterfaceName("LocalCallback1",NULL, &str3, NULL, NULL, 2);
	//printf("The number of called callback function is %d\n", r);
	//printf("\n");


	//printf("**********************************\n");
	//printf("CALL some external callback functions with wrong ID_list\n");
	//std::vector<int> wlist;
	//wlist.push_back(0);
	//wlist.push_back(1);
	//wlist.push_back(3);
	//wlist.push_back(4);
	//wlist.push_back(5);
	//wlist.push_back(7);
	//r = call->CallSomeExternalInterfacesIDs(wlist, NULL, &str3, NULL, NULL, 2);
	////call->CallOneExternalInterfaceName("LocalCallback1",NULL, &str3, NULL, NULL, 2);
	//printf("The number of called callback function is %d\n", r);
	//printf("\n");


	//printf("**********************************\n");
	//printf("CALL All external callback function excluding one function with ID \n");
	//call->CallAllExternalInterfacesExcludeID(0,NULL, &str1, NULL, NULL, 3);
	//printf("\n");

	//printf("**********************************\n");
	//printf("CALL All external callback function excluding one function with Name \n");
	//call->CallAllExternalInterfacesExcludeName("LocalCallback2",NULL, &str1, NULL, NULL, 3);
	//printf("\n");

	
	printf("All Tasks are stoppped\n");
	return 0;
}