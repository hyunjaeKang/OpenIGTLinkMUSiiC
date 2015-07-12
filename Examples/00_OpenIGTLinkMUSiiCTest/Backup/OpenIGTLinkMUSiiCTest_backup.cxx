///***************************************************************************
//Copyright May/2011
//MUSiiC Laboratory
//Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
//Johns Hopkins Medical Institutions
//Department of Radiology, Division of Medical Imaging Physics
//
//For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
//***************************************************************************/

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <time.h>
#include <MUSiiCProfile.h>


#include <igtlImageMessage.h>
#include <MUSiiCVector.h>
#include <igtlUnit.h>
#include "igtlOSUtil.h"
#include <MUSiiCTaskInterfaceAbstract.h>

#include <MUSiiCVector.h>

class Base 
{
public:
	Base()
	{
		std::cerr << "+++ The constrcutor of Base Class" <<std::endl;
		Initialize();
	}

	~Base()
	{
		std::cerr << "--- The deconstrcutor of Base Class" <<std::endl;
	}

	virtual void Initialize()
	{
		std::cerr << "*** The Initalize function of Base Class" <<std::endl;

	}
 
};

class Drived1 : public Base 
{
public:
	Drived1()
	{
		std::cerr << "+++ The constrcutor of Drived1 Class" <<std::endl;
		Initialize();
	}

	~Drived1()
	{
		std::cerr << "--- The deconstrcutor of Drived1 Class" <<std::endl;
	}

	virtual void Initialize()
	{
		std::cerr << "*** The Initalize function of Drived1 Class" <<std::endl;
	}
};

class Drived2 : public Drived1 
{
public:
	Drived2()
	{
		std::cerr << "+++ The constrcutor of Drived2 Class" <<std::endl;
		Initialize();
	}

	~Drived2()
	{
		std::cerr << "--- The deconstrcutor of Drived2 Class" <<std::endl;
	}

	virtual void Initialize()
	{
		std::cerr << "*** The Initalize function of Drived2 Class" <<std::endl;
	}
};


#include "MUSiiCTaskInterfaceAbstract.h"

int main(int argc, char** argv)
{
	igtl::MUSiiCTaskInterfaceAbstract<int, double>::Pointer  task = igtl::MUSiiCTaskInterfaceAbstract<int, double>::New();
	//igtl::MUSiiCTaskAbstract::Pointer task = igtl::MUSiiCTaskAbstract::New();
	task->SetEnableDebug(true);
	task->SetDebug(true);

<<<<<<< .mine
	std::vector<igtl::ImageMessage::Pointer> m_vImageList;

	for(int i=0; i<10;i++)
=======
	igtl::MUSiiCVector<int>::Pointer pIntP = igtl::MUSiiCVector<int>::New();
	task->AddInputDataInterface(pIntP);

	igtl::MUSiiCVector<int> IntP;
	task->AddInputDataInterface(&IntP);

	igtl::MUSiiCVector<int>::Pointer pIntP2;
	if(pIntP)
>>>>>>> .r781
	{
		printf("Hello\n");
	}

	if(pIntP2)
	{
		printf("Hello\n");
	}

	

	/*igtl::MUSiiCTaskObject::Pointer taskObject = task->GetTaskObject();
	taskObject->SetEnableDebug(true);*/
	

	return 0;
}
//int main(int argc, char** argv)
//{
//
//	/*std::vector<igtl::ImageMessage::Pointer> m_vImageList;
//	for(int i=0; i<10;i++)
//	{
//		igtl::ImageMessage::Pointer img = igtl::ImageMessage::New();
//		m_vImageList.push_back(img);
//	}
//	
//	igtl::ImageMessage::Pointer tempImage = m_vImageList[5];
//
//	for(int j=0; j<m_vImageList.size(); j++)
//	{
//		if(m_vImageList[j] == tempImage)
//		{
//			m_vImageList.erase(m_vImageList.begin()+j);
//		}
//	}*/
//
//	//igtl::MUSiiCVector<igtl::MUSiiCVector<igtl::ImageMessage::Pointer>*> m_vImageSet;
//	//igtl::MUSiiCVector<igtl::MUSiiCVector<igtl::ImageMessage*>*> m_vImageSet;
//	//
//	//igtl::MUSiiCVector<igtl::ImageMessage*>::Pointer ImageSet;
//	//for(int i=0; i<10; i++)
//	//{
//	//	ImageSet = igtl::MUSiiCVector<igtl::ImageMessage*>::New();
//	//	m_vImageSet.concurrent_push_back(ImageSet);
//	//}
//
//	//igtl::MUSiiCVector<igtl::ImageMessage*>* tempImageSet;
//	//m_vImageSet.concurrent_try_get(tempImageSet,5);
//
//	//for(int j=0;j<m_vImageSet.concurrent_size();j++)
//	//{
//	//	igtl::MUSiiCVector<igtl::ImageMessage*>* tempImageSet2;
//	//	m_vImageSet.concurrent_try_get(tempImageSet2,j);
//
//	//	if(tempImageSet == tempImageSet2)
//	//	{
//	//		m_vImageSet.concurrent_erase_element(j);//(tempImageSet2,j);
//	//	}
//	//}
//
//	//igtl::MUSiiCVector<igtl::MUSiiCVector<int>::Pointer> m_vIntSet = igtl::MUSiiCVector<igtl::MUSiiCVector<int>::Pointer>::New();
//
//	//igtl::MUSiiCVector<int>* INT;
//
//	/*std::vector<igtl::MUSiiCVector<int>*>  Test;
//
//	igtl::MUSiiCVector<int>::Pointer INT1 = igtl::MUSiiCVector<int>::New();
//	Test.push_back(INT1);
//	igtl::MUSiiCVector<int>::Pointer INT2 = igtl::MUSiiCVector<int>::New();
//	Test.push_back(INT2);
//	igtl::MUSiiCVector<int>::Pointer INT3 = igtl::MUSiiCVector<int>::New();
//	Test.push_back(INT3);
//	igtl::MUSiiCVector<int>::Pointer INT4 = igtl::MUSiiCVector<int>::New();
//	Test.push_back(INT4);
//	igtl::MUSiiCVector<int>::Pointer INT5 = igtl::MUSiiCVector<int>::New();
//	Test.push_back(INT5);
//	igtl::MUSiiCVector<int>::Pointer INT6 = igtl::MUSiiCVector<int>::New();
//	Test.push_back(INT6);
//	igtl::MUSiiCVector<int>::Pointer INT7 = igtl::MUSiiCVector<int>::New();
//	Test.push_back(INT7);
//	igtl::MUSiiCVector<int>::Pointer INT8 = igtl::MUSiiCVector<int>::New();
//	Test.push_back(INT8);
//	igtl::MUSiiCVector<int>::Pointer INT9 = igtl::MUSiiCVector<int>::New();
//	Test.push_back(INT9);
//	igtl::MUSiiCVector<int>::Pointer INT10 = igtl::MUSiiCVector<int>::New();
//	Test.push_back(INT10);
//
//
//	for(int ii=0; ii < Test.size(); ii++)
//	{
//		if(INT5 == Test[ii])
//			Test.erase(Test.begin()+ii);
//	}*/
//	
//	int i;
//
//	std::vector<igtl::ImageMessage::Pointer>  Test2;
//	std::vector<igtl::MUSiiCVector<int>::Pointer>  Test3;
//	std::vector<igtl::MUSiiCVector<int>::Pointer>  Test4;
//
//	igtl::MUSiiCVector<igtl::MUSiiCVector<int>*>::Pointer m_vIntSet = igtl::MUSiiCVector<igtl::MUSiiCVector<int>*>::New();
//	for(int i=0; i<10; i++)
//	{
//		//INT = NULL;
//		igtl::ImageMessage::Pointer img = igtl::ImageMessage::New();
//		Test2.push_back(img);
//		
//		igtl::MUSiiCVector<int>::Pointer INT = igtl::MUSiiCVector<int>::New();
//		Test3.push_back(INT);
//		INT = NULL;
//
//		igtl::MUSiiCVector<int>::Pointer INT2 = igtl::MUSiiCVector<int>::New();
//		Test4.push_back(INT2);
//
//		m_vIntSet->concurrent_push_back(INT2);
//
//		
//	}
//
//
//	//igtl::MUSiiCVector<igtl::MessageBase::Pointer>::
//	
//	
//	Drived2* object = new Drived2;
//	delete object;
//
//	std::ostringstream os;
//	double d(3.14159);
//	std::string msg = "Hello World!";
//	std::cout << "Using cout function: Value: " << d << std::endl;
//	os << "Using ostringstream: Value::  " << d << std::endl; //
//	os << "String Value" << msg.c_str() << std::endl;
//	MUSiiC_LOG(logINFO) << "Hello World!!" << d ;
//	return 0;
//}










//
//#include "igtlMultiThreader.h"
//#include "igtlOSUtil.h"
//#include <stdio.h>
//#include <iostream>
//#include <MUSiiCProfile.h>
//
//typedef struct {
//  int   nloop;
//  int   *sum;
//  igtl::MutexLock::Pointer glock;
//} ThreadData;
//
//igtl::MUSiiCProfile gProfile;
//igtl::MUSiiCProfile gProfile0;
//char msg[100];
//
//void* ThreadFunction1(void* ptr)
//{
//  
//
//  // Get thread information
//  igtl::MultiThreader::ThreadInfo* info = 
//    static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);
//
//  ThreadData* data = static_cast<ThreadData*>(info->UserData);
//  int nloop = data->nloop;
//  igtl::MutexLock::Pointer glock = data->glock;
//
//  glock->Lock();
//  memset(msg, 0, 100);
//  sprintf(msg, "%.7f", gProfile.MUSiiCToc("Thread1 is Starting"));
//  std::cerr<< "Thread1 Start: "<< msg <<std::endl;
//  long interval = 1; // (ms)
//  glock->Unlock();
//  
//  for (int i = 0; i < nloop; i ++)
//    {
//    glock->Lock();
//    int s1 = *(data->sum);
//    igtl::Sleep(interval);
//    int s2 = *(data->sum);
//    *(data->sum) = s1 + s2;
//	printf("Thread1:: sum is %d\n", *(data->sum));
//    glock->Unlock();
//    }
//
//  return NULL;
//}
//
//void* ThreadFunction2(void* ptr)
//{
//	
//
//  // Get thread information
//  igtl::MultiThreader::ThreadInfo* info = 
//    static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);
//
//  ThreadData* data = static_cast<ThreadData*>(info->UserData);
//  int nloop = data->nloop;
//  igtl::MutexLock::Pointer glock = data->glock;
//
//  glock->Lock();
//  memset(msg, 0, 100);
//  sprintf(msg, "%.7f", gProfile.MUSiiCToc("Thread2 is Starting"));
//  std::cerr<< "Thread2 Start: "<< msg <<std::endl;
//  long interval = 1; // (ms)
//  glock->Unlock();
//
//  for (int i = 0; i < nloop; i ++)
//    {
//    glock->Lock();
//    int s1 = *(data->sum);
//    igtl::Sleep(interval);
//    int s2 = *(data->sum);
//    *(data->sum) = s1 + s2;
//	printf("Thread2:: sum is %d\n", *(data->sum));
//    glock->Unlock();
//    }
//
//  return NULL;
//}
//
//void* ThreadFunction3(void* ptr)
//{
//
//  // Get thread information
//  igtl::MultiThreader::ThreadInfo* info = 
//    static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);
//
//  ThreadData* data = static_cast<ThreadData*>(info->UserData);
//  int nloop = data->nloop;
//  igtl::MutexLock::Pointer glock = data->glock;
//
//  glock->Lock();
//  memset(msg, 0, 100);
//  sprintf(msg, "%.7f", gProfile.MUSiiCToc("Thread3 is Starting"));
//  std::cerr<< "Thread3 Start: "<< msg <<std::endl;
//  long interval = 1; // (ms)
//  glock->Unlock();
//
//  for (int i = 0; i < nloop; i ++)
//    {
//    glock->Lock();
//    int s1 = *(data->sum);
//    igtl::Sleep(interval);
//    int s2 = *(data->sum);
//    *(data->sum) = s1 + s2;
//	printf("Thread3:: sum is %d\n", *(data->sum));
//    glock->Unlock();
//    }
//
//  return NULL;
//}
//
//void* ThreadFunction4(void* ptr)
//{
//
//  // Get thread information
//  igtl::MultiThreader::ThreadInfo* info = 
//    static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);
//
//  ThreadData* data = static_cast<ThreadData*>(info->UserData);
//  int nloop = data->nloop;
//  igtl::MutexLock::Pointer glock = data->glock;
//
//  glock->Lock();
//  memset(msg, 0, 100);
//  sprintf(msg, "%.7f", gProfile.MUSiiCToc("Thread4 is Starting"));
//  std::cerr<< "Thread4 Start: "<< msg <<std::endl;
//  long interval = 1; // (ms)
//  glock->Unlock();
//
//  for (int i = 0; i < nloop; i ++)
//    {
//    glock->Lock();
//    int s1 = *(data->sum);
//    igtl::Sleep(interval);
//    int s2 = *(data->sum);
//    *(data->sum) = s1 + s2;
//	printf("Thread3:: sum is %d\n", *(data->sum));
//    glock->Unlock();
//    }
//
//  return NULL;
//}
//
//void* ThreadFunction5(void* ptr)
//{
//
//  // Get thread information
//  igtl::MultiThreader::ThreadInfo* info = 
//    static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);
//
//  ThreadData* data = static_cast<ThreadData*>(info->UserData);
//  int nloop = data->nloop;
//  igtl::MutexLock::Pointer glock = data->glock;
//
//  glock->Lock();
//  memset(msg, 0, 100);
//  sprintf(msg, "%.7f", gProfile.MUSiiCToc("Thread5 is Starting"));
//  std::cerr<< "Thread5 Start: "<< msg <<std::endl;
//  long interval = 1; // (ms)
//  glock->Unlock();
//
//  for (int i = 0; i < nloop; i ++)
//    {
//    glock->Lock();
//    int s1 = *(data->sum);
//    igtl::Sleep(interval);
//    int s2 = *(data->sum);
//    *(data->sum) = s1 + s2;
//	printf("Thread3:: sum is %d\n", *(data->sum));
//    glock->Unlock();
//    }
//
//  return NULL;
//}
//
//void* MainThreadFunction(void* ptr)
//{
//	std::cerr<< "Thread0 Start:  "<< gProfile0.MUSiiCToc("Thread0 is Starting")<<std::endl;
//	// Get thread information
//	igtl::MultiThreader::ThreadInfo* info = 
//	static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);
//
//	ThreadData* data = static_cast<ThreadData*>(info->UserData);
//	int nloop = data->nloop;
//	
//	igtl::MultiThreader::Pointer thread = igtl::MultiThreader::New();
//
//	for(int i=0; i< nloop; i++)
//	{
//		
//		igtl::MutexLock::Pointer lglock = igtl::MutexLock::New();
//
//		int ssum = 1;
//		
//		ThreadData td;
//		td.nloop = 4;
//		td.sum   = &ssum;
//		td.glock = lglock;
//  
//		//igtl::MultiThreader::Pointer threader = igtl::MultiThreader::New();
//		gProfile.MUSiiCTic();
//		std::cerr<<"MUSiiCTic Sub Thread"<<std::endl;
//		int id1 = thread->SpawnThread((igtl::ThreadFunctionType) &ThreadFunction1, &td);
//		int id2 = thread->SpawnThread((igtl::ThreadFunctionType) &ThreadFunction2, &td);
//		int id3 = thread->SpawnThread((igtl::ThreadFunctionType) &ThreadFunction3, &td);
//		int id4 = thread->SpawnThread((igtl::ThreadFunctionType) &ThreadFunction4, &td);
//		int id5 = thread->SpawnThread((igtl::ThreadFunctionType) &ThreadFunction5, &td);
//
//		// wait for the threads
//		thread->TerminateThread(id1);
//		thread->TerminateThread(id2);
//		thread->TerminateThread(id3);
//		thread->TerminateThread(id4);
//		thread->TerminateThread(id5);
//	}
//	
//	
//	
//	return NULL;
//}
//
//int main(int argc, char** argv)
//{
//	igtl::MutexLock::Pointer glock = igtl::MutexLock::New();
//
//	int sum = 1;
//
//	ThreadData td;
//	td.nloop = 3;
//	td.sum   = &sum;
//	td.glock = glock;
//  
//	igtl::MultiThreader::Pointer threader = igtl::MultiThreader::New();
//	gProfile0.MUSiiCTic();
//	std::cerr<<"MUSiiCTic Main Thread"<<std::endl;
//	int id1 = threader->SpawnThread((igtl::ThreadFunctionType) &MainThreadFunction, &td);
//	//int id2 = threader->SpawnThread((igtl::ThreadFunctionType) &ThreadFunction2, &td);
//	//int id3 = threader->SpawnThread((igtl::ThreadFunctionType) &ThreadFunction3, &td);
//
//	// wait for the threads
//	threader->TerminateThread(id1);
//	//threader->TerminateThread(id2);
//	//threader->TerminateThread(id3);
//    
//	return 0;
//}