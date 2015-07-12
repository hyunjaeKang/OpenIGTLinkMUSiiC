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

#include <MUSiiCTCPServerSocketWin.h>

#include "MUSiiCVectorSet.h"

#include <igtlLightObject.h>
#include <igtlMacro.h>
#include <igtlObjectFactory.h>
#include "igtlM_win32header.h"
#include "MUSiiCUtil.h"

using namespace igtl;

class TxTask1:public MUSiiCTaskInterfaceAbstract<int, int>
{
  public: // Operations
	typedef TxTask1						Self;
	typedef MUSiiCTaskInterfaceAbstract					Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<Self>				ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

	/// Constrcut
	TxTask1()
	{
		Initialize();
	}
	//Deconstrct
	~TxTask1()
	{
	}

	int RunTxTask()
	{
		this->SetEnableThread(true, MUSiiCTaskAbstract::M_ALLTASKOBJECT);
		
		return this->RunTask(MUSiiCTaskObject::M_THREAD_RUN_CONTINUOUS, 0, this, NULL, NULL, NULL, M_ALLTASKOBJECT);
	}

protected:

	virtual void Initialize()
	{
		m_iValue = 0;
	}
	
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		if(this->m_pVOutputDATA_IF_Set->IsMUSiiCVectors())
		{
			MUSiiC_LOG(logINFO) << " <<<<<< TxTask1 m_pVOutputDATA_IF_Set::Try_push_back_ALL, the value is   " << m_iValue;
			this->m_pVOutputDATA_IF_Set->Try_push_back_ALL(m_iValue);
			m_iValue++;

			if(m_iValue == 10)
			   m_iValue =  0;

			igtl::Sleep(10000);
		}

		return 1;
	}

	int m_iValue;
};


class TxTask2:public MUSiiCTaskInterfaceAbstract<int, int>
{
  public: // Operations
	typedef TxTask2						Self;
	typedef MUSiiCTaskInterfaceAbstract					Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<Self>				ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

	/// Constrcut
	TxTask2()
	{
		Initialize();
	}
	//Deconstrct
	~TxTask2()
	{
	}

	int RunTxTask()
	{
		this->SetEnableThread(true, MUSiiCTaskAbstract::M_ALLTASKOBJECT);
		
		return this->RunTask(MUSiiCTaskObject::M_THREAD_RUN_CONTINUOUS, 0, this, NULL, NULL, NULL, M_ALLTASKOBJECT);

	}

protected:

	virtual void Initialize()
	{
		m_iValue = 1000;
	}
	
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		if(this->m_pVOutputDATA_IF_Set->IsMUSiiCVectors())
		{
			MUSiiC_LOG(logINFO) << " <<<<<< TxTask2 m_pVOutputDATA_IF_Set::Try_push_back_ALL, the value is   " << m_iValue;
			this->m_pVOutputDATA_IF_Set->Try_push_back_ALL(m_iValue);
			m_iValue++;

			if(m_iValue == 10000)
			   m_iValue =  1000;

			igtl::Sleep(30000);
		}

		return 1;
	}

	int m_iValue;
};


class RxTask1:public MUSiiCTaskInterfaceAbstract<int, int>
{
  public: // Operations
	typedef RxTask1						Self;
	typedef MUSiiCTaskInterfaceAbstract					Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<Self>				ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

	/// Constrcut
	RxTask1()
	{
		Initialize();
	}
	//Deconstrct
	~RxTask1()
	{
	}

	int RunRxTask()
	{
		this->SetEnableThread(true, MUSiiCTaskAbstract::M_ALLTASKOBJECT);
		
		return this->RunTask(MUSiiCTaskObject::M_THREAD_RUN_CONTINUOUS, 0, this, NULL, NULL, NULL, M_ALLTASKOBJECT);
	}

protected:

	virtual void Initialize()
	{
		//m_iValue = 1000;
	}
	
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		if(this->m_pVInputDATA_IF_Set->IsMUSiiCVectors())
		{
			int a(333333);
			this->m_pVInputDATA_IF_Set->Concurrent_wait_get_pop_front_fromMUSiiCVectorSet(a);
			MUSiiC_LOG(logINFO) << " >>>>>> RxTask1 m_pVInputDATA_IF_Set::Concurrent_wait_get_pop_front_fromMUSiiCVectorSet, the value is   " << a;
			
		}

		return 1;
	}

	int m_iValue;
};


//int main(int argc, char** argv)
//{
//	
//	TxTask1::Pointer Tx1 = TxTask1::New();
//	TxTask2::Pointer Tx2 = TxTask2::New();
//	RxTask1::Pointer Rx1 = RxTask1::New();
//
//	
//	igtl::MUSiiCVector<int>::Pointer IF1 = igtl::MUSiiCVector<int>::New();
//	igtl::MUSiiCVector<int>::Pointer IF2 = igtl::MUSiiCVector<int>::New();
//
//	IF1->concurrent_clear();
//	IF2->concurrent_clear();
//
//	Tx1->AddOutputDataInterface(IF1);
//	Rx1->AddInputDataInterface(IF1);
//
//	Tx2->AddOutputDataInterface(IF2);
//	Rx1->AddInputDataInterface(IF2);
//
//	Rx1->RunRxTask();
//	Tx1->RunTxTask();
//	Tx2->RunTxTask();
//
//
//	Rx1->WaitTask();
//	Tx1->WaitTask();
//	Tx2->WaitTask();
//
//
//
//
//
//	
//	
//	
//	return 0;
//}


//
//template<class Data>
//class Base : public LightObject
//{
//public: // Operations
//	typedef Base						Self;
//	typedef LightObject								Superclass;
//	typedef SmartPointer<Self>						Pointer;
//	typedef SmartPointer<Self>						ConstPointer;
//	
//	/** Method for creation through the object factory. */
//	igtlNewMacro(Self);
//  
//	/** Run-time type information (and related methods). */
//	igtlTypeMacro(Self, Superclass);
//
//	/// Constrcut
//	Base()
//	{
//		printf("The constrcutor of Base\n");
//		Initialize();
//	}
//	/// Deconstruct
//	~Base()
//	{
//		printf("The deconstrcutor of Base\n");
//	}
//
//	igtl::SmartPointer<igtl::MUSiiCVectorSet<Data>> pMV;
//
//protected:
//	virtual void Initialize()
//	{
//		printf("1:The initialize of Base\n");
//		pMV=igtl::MUSiiCVectorSet<Data>::New();
//		printf("2:The initialize of Base\n");
//	}
//};
//
//
//class TEST : public Base<int>
//{
//public: // Operations
//	typedef TEST						Self;
//	typedef Base						Superclass;
//	typedef SmartPointer<Self>			Pointer;
//	typedef SmartPointer<Self>			ConstPointer;
//	
//	/** Method for creation through the object factory. */
//	igtlNewMacro(Self);
//  
//	/** Run-time type information (and related methods). */
//	igtlTypeMacro(Self, Superclass);
//
//	/// Constrcut
//	TEST()
//	{
//		printf("The constrcutor of Test\n");
//		Initialize();
//	}
//	/// Deconstruct
//	~TEST()
//	{
//		printf("The deconstrcutor of Test\n");
//	}
//
//
//protected:
//	virtual void Initialize()
//	{
//		printf("The initialize of Test\n");
//	}
//};
//
//
//
int main(int argc, char** argv)
{
	igtl::MUSiiCTCPServerSocketWin::Pointer pServerSocket;
	pServerSocket = igtl::MUSiiCTCPServerSocketWin::New();

	pServerSocket->CreateServer(12345);
	
	printf("Hello\n");

	float a(0.0);
	while(true)
	{
		
		//continue;
		if(pServerSocket->IsConnectedClients())// && pServerSocket->GetNumOfClients() >3)
		{
			int x(128);
			int y(1000);
			int z(1);
			igtl::ImageMessage::Pointer img = igtl::ImageMessage::New();
			img->SetDimensions(x, y, z);
			img->SetSpacing(1.0,1.0,1.0);
			img->SetScalarTypeToUint8();
			img->SetDeviceName("Dummy ImageMessage");
			img->SetSubVolume(x, y, z, 0,0,0);
			img->AllocateScalars();

			/*int sz = x*y*z;
			*unsigned char* data = new unsigned char [sz];
			ZeroMemory(data, sz);
			memcpy(img->GetScalarPointer(), data, sz);*/

			igtl::Matrix4x4 matrix;
			matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0;
			matrix[0][1] = 0.0;  matrix[1][1] = -1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0;
			matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = -1.0; matrix[3][2] = 0;
			matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = a; matrix[3][3] = 1.0;

			//MUSiiC_LOG(logINFO) << "the value of i is  " << a;
			a +=0.2;
			if(a == 101.0)
				a = 0.0;

			img->SetMatrix(matrix);
			img->Pack();

			pServerSocket->PutIGTLMessage((igtl::MessageBase::Pointer)img);

			/*MUSiiC_LOG(logINFO) << "MUSiiCServerSocket Send out " << a << "-th ImageMessage";

			MUSiiC_LOG(logINFO) << "The size of ImageMessage is  " << img->GetPackSize();*/

			//delete data;

			igtl::StringMessage::Pointer st = igtl::StringMessage::New();
			st->SetDeviceName("Dumy String");
			st->SetString("Hello This is Test");
			//st->Pack();

			pServerSocket->PutIGTLMessage((igtl::MessageBase::Pointer)st);

			//MUSiiC_LOG(logINFO) << "The size of StringMessage is  " << st->GetPackSize();
		}

		igtl::Sleep(20);

	}

	


	pServerSocket->WaitTask();
	pServerSocket->CloseServer();

	/*igtl::MUSiiCVectorSet<int>::Pointer MV1 = igtl::MUSiiCVectorSet<int>::New();
	igtl::MUSiiCVectorSet<int>::Pointer MV2 = igtl::MUSiiCVectorSet<int>::New();
	igtl::SmartPointer<igtl::MUSiiCVectorSet<int>> MV3;
	MV3= igtl::MUSiiCVectorSet<int>::New();

	igtl::MUSiiCVector<int>::Pointer V1 = igtl::MUSiiCVector<int>::New();
	igtl::MUSiiCVector<int>::Pointer V2 = igtl::MUSiiCVector<int>::New();
	igtl::MUSiiCVector<int>::Pointer V3 = igtl::MUSiiCVector<int>::New();

	MV1->AddMUSiiCVector(V1);

	MV2 = MV1;
	MV3 = MV1;


	MV1->AddMUSiiCVector(V2);
	MV1->AddMUSiiCVector(V3);*/
	
	//TEST::Pointer t = TEST::New();

	//igtl::MUSiiCVector<int>::Pointer v1 = igtl::MUSiiCVector<int>::New();
	//int r = t->pMV->AddMUSiiCVector(v1);

	//TEST::Pointer t2 = TEST::New();
	//t2->pMV = t->pMV;
	//igtl::MUSiiCVector<int>::Pointer v2 = igtl::MUSiiCVector<int>::New();
	//t2->pMV->AddMUSiiCVector(v2);
	//igtl::MUSiiCVector<int>::Pointer v3 = igtl::MUSiiCVector<int>::New();
	//t2->pMV->AddMUSiiCVector(v3);
	//igtl::MUSiiCVector<int>::Pointer v4 = igtl::MUSiiCVector<int>::New();
	//t2->pMV->AddMUSiiCVector(v4);

	///*igtl::MUSiiCVector<double>::Pointer v5 = igtl::MUSiiCVector<double>::New();
	//t2->pMV->AddMUSiiCVector(v5);*/

	return 0;

}