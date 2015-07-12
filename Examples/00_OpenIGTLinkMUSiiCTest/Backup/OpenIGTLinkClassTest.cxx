///***************************************************************************
//Copyright May/2011
//MUSiiC Laboratory
//Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
//Johns Hopkins Medical Institutions
//Department of Radiology, Division of Medical Imaging Physics
//
//For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
//***************************************************************************/

/// IGTL Class Test
#include <MUSiiCIGTLUtil.h>
#include <igtlLightObject.h>
#include <igtlMacro.h>
#include <igtlObjectFactory.h>
#include <igtlMessageBase.h>
#include <iostream>
#include <algorithm>

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

public:
	std::string name1;


};

class  BaseIO : public LightObject
{
public: // Operations
	typedef BaseIO							Self;
	typedef LightObject						Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<Self>				ConstPointer;

	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

public:
	BaseIO()
	{
		name2 = "BaseIO";
	}

	~BaseIO()
	{
	}

public:
	std::string name2;


};

class  BaseIO2
{
public:
	BaseIO2()
	{
		name2 = "BaseIO";
	}

	~BaseIO2()
	{
	}

public:
	std::string name2;

};

template<class T>
class  BaseIO3
{
public:
	BaseIO3()
	{
		name3 = "BaseIO3";
	}

	~BaseIO3()
	{
	}

	void GenerateData()
	{
		for(int i=0; i<10; i++)
			m_vData.push_back((T)i);
	}

	std::vector<T>& GetAllData()
	{
		return m_vData;
	}

	void PrintData(T& t)
	{
		std::cout << " " << t << std::endl;
	}


public:
	std::string name3;
	std::vector<T> m_vData;
};


/// BaseClass is derived from igtl::LightObject
/// BaseIO1 is not derived from any class. Base01 class is super class.
class Child1: public BaseClass, public BaseIO2
{

public: // Operations
	typedef Child1							Self;
	typedef BaseClass						Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<Self>				ConstPointer;

	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

public:
	Child1()
	{
		//BaseClass::BaseClass();
		//BaseIO::BaseIO();
	}

	~Child1()
	{
		//BaseClass::~BaseClass();
		//BaseIO::~BaseIO();
	}

	void TestChild()
	{
		std::cout << "The message of BaseClass :" << this->name1 << std::endl;
		std::cout << "The message of BaseIO2   :" << this->name2 << std::endl;
	}
};


/// BaseClass is derived from igtl::LightObject
/// BaseIO1 is not derived from any class. Base01 class is super class.
class Child2: public BaseClass, public BaseIO3<float>
{

public: // Operations
	typedef Child2							Self;
	typedef BaseClass						Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<Self>				ConstPointer;

	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

public:
	Child2()
	{
		//BaseClass::BaseClass();
		//BaseIO::BaseIO();
	}

	~Child2()
	{
		//BaseClass::~BaseClass();
		//BaseIO::~BaseIO();
	}

	void TestChild()
	{
		std::cout << "The message of BaseClass :" << this->name1 << std::endl;
		std::cout << "The message of BaseIO3   :" << this->name3 << std::endl;
	}
};

void PrintFloatData(float v)
{
	std::cout << " Data is  : " << v << std::endl; 
}
int main(int argc, char** argv)
{
	
	//Child1 c;
	//c.TestChild(); // Error of LightObject

	/*igtl::SmartPointer<Child1> pChild = new Child1;
	pChild->TestChild();*/

	Child1::Pointer pChild = Child1::New();
	pChild->TestChild();


	Child2::Pointer pChild2 = Child2::New();
	pChild2->TestChild();

	pChild2->GenerateData();
	std::vector<float> tempData = pChild2->GetAllData();

	std::for_each(tempData.begin(), tempData.end(), PrintFloatData);

	tempData.size();
	return 0;

}