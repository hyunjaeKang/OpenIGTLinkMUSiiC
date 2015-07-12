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

/// IGTL Class Test
#include <MUSiiCIGTLUtil.h>
#include <igtlLightObject.h>
#include <igtlMacro.h>
#include <igtlObjectFactory.h>
#include <igtlMessageBase.h>
#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace igtl;
class  BaseClass : public LightObject
{
public: // Operations
	typedef BaseClass							Self;
	typedef LightObject							Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<Self>					ConstPointer;

	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

public:
	BaseClass()
	{
		name1 = "BaseClass";
	}

	~BaseClass()
	{
	}

	virtual int Test(int v)
	{
		return v;
	}

	void PrintBaseClass()
	{
		std::cout << "The function of PrintBaseClass of BaseClass " << std::endl;
		std::cout << name1 << std::endl;
		std::cout << std::endl;
	}

	virtual void PrintTestMessage()
	{
		std::cout << "The function of PrintBaseClass of BaseClass " << std::endl;
		std::cout << name1 << std::endl;
		std::cout << std::endl;
	}

public:
	std::string name1;


};


template<class T>
class  BaseIO
{
public:
	BaseIO()
	{
		name_IO = "BaseIO";
		m_vData = igtl::MUSiiCVector<T>::New();
	}

	~BaseIO()
	{
	}

	igtl::SmartPointer<igtl::MUSiiCVector<T>> GetAllData()
	{
		return m_vData;
	}

	virtual int AddData(T data)
	{
		m_vData->concurrent_push_back(data);
		return GetSizeOfData();
	}

	int GetSizeOfData()
	{
		return m_vData->concurrent_size();
	}

	virtual void PrintDatas()
	{
		std::cout << "PrintData of BaseIO Class" << std::endl;
		int sz(GetSizeOfData());

		for(int i=0; i<sz; i++)
			std::cout << i << "-th Value is : " << m_vData->concurrent_try_GetData(i) << std::endl;
	}
	
public:
	std::string name_IO;
	//igtl::MUSiiCVector<T>::Pointer m_vData;
	igtl::SmartPointer<igtl::MUSiiCVector<T>> m_vData;
};

/// BaseClass is derived from igtl::LightObject
/// BaseIO1 is not derived from any class. Base01 class is super class.
class ChildIO: public BaseClass, public BaseIO<double>
{

public: // Operations
	typedef ChildIO							Self;
	typedef BaseClass						Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<Self>				ConstPointer;

	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

public:
	ChildIO()
	{
	}

	~ChildIO()
	{
	}

	void TestChild()
	{
		std::cout << "The message of BaseClass :" << this->name1 << std::endl;
		std::cout << "The message of BaseIO3   :" << this->name_IO << std::endl;
	}

	/// The virtual fucntion of BaseIO
	virtual void PrintDatas()
	{
		std::cout << "PrintData of ChildIO Class" << std::endl;
		int sz(GetSizeOfData());

		for(int i=0; i<sz; i++)
			std::cout << i << "-th Value is : " << m_vData->concurrent_try_GetData(i) << std::endl;
	}

	/// The virtual function of BaseClass
	virtual void PrintTestMessage()
	{
		std::cout << "The function of PrintTestMessage of ChildIO " << std::endl;
		std::cout << "The name of Base Class is " << name1 << std::endl;
		std::cout << std::endl;
	}
};

/// BaseClass is derived from igtl::LightObject
/// BaseIO1 is not derived from any class. Base01 class is super class.
class IGTLIO: public BaseClass, public BaseIO<igtl::MessageBase::Pointer>
{

public: // Operations
	typedef IGTLIO							Self;
	typedef BaseClass						Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<Self>				ConstPointer;

	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

public:
	IGTLIO()
	{
	}

	~IGTLIO()
	{
	}

	void TestChild()
	{
		std::cout << "The message of BaseClass :" << this->name1 << std::endl;
		std::cout << "The message of BaseIO3   :" << this->name_IO << std::endl;
	}

	/// The virtual fucntion of BaseIO
	virtual void PrintDatas()
	{
		std::cout << "PrintData of IGTLIO Class" << std::endl;
		int sz(GetSizeOfData());
		std::cout << "The size of Data is : " << sz << std::endl;
	}

	/// The virtual function of BaseClass
	virtual void PrintTestMessage()
	{
		std::cout << "The function of PrintTestMessage of IGTLIO " << std::endl;
		std::cout << "The name of Base Class is " << name1 << std::endl;
		std::cout << std::endl;
	}
};




void PrintFloatData(float v)
{
	std::cout << " Data is  : " << v << std::endl; 
}
int main(int argc, char** argv)
{

	//igtl::SmartPointer<igtl::MUSiiCVector<int>> m_pvInputFileData  = igtl::SmartPointer<igtl::MUSiiCVector<int>>::New();
	igtl::SmartPointer<igtl::MUSiiCVector<int>> m_pvInputFileData  = igtl::MUSiiCVector<int>::New();

	ChildIO::Pointer pChildIO = ChildIO::New();

	pChildIO->PrintBaseClass();
	pChildIO->PrintTestMessage();

	for(int i=0; i<10; i++)
		pChildIO->AddData(((double)(i)*0.5));

	pChildIO->PrintDatas();

	
	/////////////////////////////////////////////////////////////////////////////////////////
	igtl::MUSiiCVector<double>::Pointer pDoubleMVector = igtl::MUSiiCVector<double>::New();

	pDoubleMVector = pChildIO->GetAllData();

	int sz(pDoubleMVector->concurrent_size());
	/////////////////////////////////////////////////////////////////////////////////////////
	
	//// =================================================================================////
	{
		IGTLIO::Pointer pIGTLIO = IGTLIO::New();
		for(int a=0; a<5 ; a++)
		{
			pIGTLIO->AddData(igtl::GetDummyEIMessage());
			pIGTLIO->AddData(igtl::GetDummyImageMessage());
			pIGTLIO->AddData(igtl::GetDummyUSMessage());
		}


		pIGTLIO->PrintBaseClass();
		pIGTLIO->PrintTestMessage();

		
		/*{
			igtl::MUSiiCIGTLMsgVector::Pointer pIGTLMsgVector = igtl::MUSiiCIGTLMsgVector::New();				pIGTLMsgVector = pIGTLIO->GetAllData(); /// Compile Error
		}*/

		{
			igtl::MUSiiCVector<igtl::MessageBase::Pointer>::Pointer pIGTLMsgVector2 = igtl::MUSiiCVector<igtl::MessageBase::Pointer>::New();
			pIGTLMsgVector2 = pIGTLIO->GetAllData();

		}


	}

	
	BaseClass::Pointer pBase = (BaseClass::Pointer)pChildIO;
	pBase->PrintBaseClass();
	pBase->PrintTestMessage();

	return 0;

}