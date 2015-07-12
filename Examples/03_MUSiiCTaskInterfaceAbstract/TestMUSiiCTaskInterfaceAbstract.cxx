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

#include <MUSiiCTaskInterfaceAbstract.h>
#include <MUSiiCSyncDATA.h>
using namespace igtl;

class Test1: public igtl::MUSiiCTaskInterfaceAbstract<int, float>
{
public:
	/** Standard class typedefs. */
	typedef Test1									Self;
	typedef MUSiiCTaskInterfaceAbstract<int,double>	Superclass;
	typedef igtl:: SmartPointer<Self>				Pointer;
	typedef igtl::SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	/// Construction
	Test1()
	{
	}
	/// DeConstruction
	~Test1()
	{
	}

	void SetDescription(std::string des ="")
	{
		m_pNameOfClass = (char*)des.c_str();;
	}

	std::string GetDescription()
	{
		return m_Des;
	}

	int PostTaskProcessing2(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		
		int temp_Value;

		temp_Value = *(int*)data2;
		igtl::MUSiiCSyncData::Pointer tempSync;
		tempSync = (igtl::MUSiiCSyncData*)data3;
		
		int temp = this->RetrieveInputData(data2);

		return 1;
	}

	bool SetEnableTest(bool enable = true)
	{
		return m_bTest = enable; 
	}

public:
	bool m_bTest;
	
protected:
	std::string m_Des;
protected:
	
	
};

class Test2: public igtl::MUSiiCTaskInterfaceAbstract<float, double>
{
public:
	/** Standard class typedefs. */
	typedef Test2									Self;
	typedef MUSiiCTaskInterfaceAbstract<int,double>	Superclass;
	typedef igtl:: SmartPointer<Self>				Pointer;
	typedef igtl::SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	/// Construction
	Test2()
	{
	}
	/// DeConstruction
	~Test2()
	{
	}

	void SetDescription(std::string des ="")
	{
		m_pNameOfClass = (char*)des.c_str();;
	}

	std::string GetDescription()
	{
		return m_Des;
	}
	
	
protected:
	std::string m_Des;
protected:
	
	
};

class Test3: public igtl::MUSiiCTaskInterfaceAbstract<double, int>
{
public:
	/** Standard class typedefs. */
	typedef Test3									Self;
	typedef MUSiiCTaskInterfaceAbstract<int,double>	Superclass;
	typedef igtl:: SmartPointer<Self>				Pointer;
	typedef igtl::SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	/// Construction
	Test3()
	{
	}
	/// DeConstruction
	~Test3()
	{
	}

	void SetDescription(std::string des ="")
	{
		m_pNameOfClass = (char*)des.c_str();;
	}

	std::string GetDescription()
	{
		return m_Des;
	}
	
	
protected:
	std::string m_Des;
protected:
	
	
};

class Test4: public igtl::MUSiiCTaskInterfaceAbstract<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>
{
public:
	/** Standard class typedefs. */
	typedef Test4									Self;
	typedef MUSiiCTaskInterfaceAbstract<int,double>	Superclass;
	typedef igtl:: SmartPointer<Self>				Pointer;
	typedef igtl::SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	/// Construction
	Test4()
	{
	}
	/// DeConstruction
	~Test4()
	{
	}

	void SetDescription(std::string des ="")
	{
		m_pNameOfClass = (char*)des.c_str();;
	}

	std::string GetDescription()
	{
		return m_Des;
	}
	
	
protected:
	std::string m_Des;
protected:
	
	
};

int main(int argc, char** argv)
{
	igtl::MUSiiCVectorSet<int>::Pointer v1 = igtl::MUSiiCVectorSet<int>::New();
	igtl::MUSiiCVectorSet<int>::Pointer v2 = igtl::MUSiiCVectorSet<int>::New();
	v1 = v2;

	
	MUSiiCTaskInterfaceAbstract<int, double>::Pointer task1;
	task1 = MUSiiCTaskInterfaceAbstract<int,double>::New();

	MUSiiCTaskInterfaceAbstract<double, int>::Pointer task2;
	task2 = MUSiiCTaskInterfaceAbstract<double,int>::New();

	////////////////////////////////////////////////////////////////////////
	task1->SetPostInputMUSiiCVectorSet(task2->GetPreInputMUSiiCVectorSet());




	////////////////////////////////////////////////////////////////////////
	igtl::MUSiiCVectorSet<double>::Pointer pVectorSet1 = igtl::MUSiiCVectorSet<double>::New();

	task2->SetPreOutputMUSiiCVectorSet(pVectorSet1);

	//////////////////////////////////////////////////////////////////////
	task1->AddPostMUSiiCTaskInterface<double, int>(task2);
	
	//---------------------------------------------------------------------//
	////////////////////////////////////////////////////////////////////////
	Test1::Pointer ctest1 = Test1::New(); //int, float
	ctest1->SetDescription("ctest1");

		/////**
	int v(3);
	//ctest1->PostTaskProcessing2(0, 0, NULL, NULL, &v, NULL);
	bool result;
	result =  ctest1->SetEnableTest(true);
	result =  ctest1->SetEnableTest(false);



	//Test1::Pointer ctest11 = Test1::New(); //int, float
	//Test1::Pointer ctest12 = Test1::New(); //int, float
	//Test1::Pointer ctest13 = Test1::New(); //int, float
	Test2::Pointer ctest2 = Test2::New(); // float. double
	ctest2->SetDescription("ctest2");
	
	Test3::Pointer ctest3 = Test3::New(); // double int
	ctest3->SetDescription("ctest3");
	//Test3::Pointer ctest31 = Test3::New(); // double int
	//Test3::Pointer ctest32 = Test3::New(); // double int
	//Test3::Pointer ctest33 = Test3::New(); // double int
	
	Test4::Pointer ctest4 = Test4::New(); // igtl::MessageBase::Pointer,igtl::MessageBase::Pointer

	{
		Test1::Pointer ctest11 = Test1::New(); //int, float
		ctest11->SetDescription("ctest11");
		Test1::Pointer ctest12 = Test1::New(); //int, float
		ctest12->SetDescription("ctest12");
		Test1::Pointer ctest13 = Test1::New(); //int, float
		ctest13->SetDescription("ctest13");
		
		
		ctest2->AddPreMUSiiCTaskInterface<int,float>(ctest1);
		ctest2->AddPreMUSiiCTaskInterface<int,float>(ctest11);
		ctest2->AddPreMUSiiCTaskInterface<int,float>(ctest12);
		ctest2->AddPreMUSiiCTaskInterface<int,float>(ctest13);


		Test3::Pointer ctest31 = Test3::New(); // double int
		ctest31->SetDescription("ctest31");
		Test3::Pointer ctest32 = Test3::New(); // double int
		ctest32->SetDescription("ctest32");
		Test3::Pointer ctest33 = Test3::New(); // double int
		ctest33->SetDescription("ctest33");

		ctest2->AddPostMUSiiCTaskInterface<double,int>(ctest3);
		ctest2->AddPostMUSiiCTaskInterface<double,int>(ctest31);
		ctest2->AddPostMUSiiCTaskInterface<double,int>(ctest32);
		ctest2->AddPostMUSiiCTaskInterface<double,int>(ctest33);
	}
	
	int sz, i;
	sz = ctest2->m_vPreMUSiiCTaskList.size();

	std::cout << "Pre MUSiiCTask of ctest2" << std::endl;
	for(i=0; i<sz; i++)
	{
		std::cout<< i << "-th  " <<"Class name is :  "<< ctest2->m_vPreMUSiiCTaskList[i]->GetNameOfMUSiiCClass().c_str() << std::endl;
	}

	sz = ctest2->m_vPreMUSiiCTaskList.size();
	std::cout << "Post MUSiiCTask of ctest2" << std::endl;
	for(i=0; i<sz; i++)
	{
		std::cout<< i << "-th  " <<"Class name is :  "<< ctest2->m_vPostMUSiiCTaskList[i]->GetNameOfMUSiiCClass().c_str() << std::endl;
	}
		
	igtl::MUSiiCVector<int>::Pointer intVector			= igtl::MUSiiCVector<int>::New();
	igtl::MUSiiCVector<float>::Pointer floatVector		= igtl::MUSiiCVector<float>::New();
	igtl::MUSiiCVector<double>::Pointer doubleVector	= igtl::MUSiiCVector<double>::New();
	igtl::MUSiiCVector<igtl::MessageBase::Pointer>::Pointer igtlMBVector =igtl::MUSiiCVector<igtl::MessageBase::Pointer>::New();
	igtl::MUSiiCIGTLMsgVector::Pointer IGTLVector		= igtl::MUSiiCIGTLMsgVector::New();


	// Test of connecting of MUSiiCVectorSet
	ctest1->SetPostInputMUSiiCVectorSet(ctest2->GetPreInputMUSiiCVectorSet());
	ctest1->SetPostOutputMUSiiCVectorSet(ctest2->GetPreOutputMUSiiCVectorSet());


	ctest3->SetPreInputMUSiiCVectorSet(ctest2->GetPostInputMUSiiCVectorSet());
	ctest3->SetPreOutputMUSiiCVectorSet(ctest2->GetPostOutputMUSiiCVectorSet());


	////////////////////////////////////////////////
	//ctest2->AddPreMUSiiCTaskInterface2(ctest1); /// Compile Error
	//ctest2->AddPreMUSiiCTaskInterface2<int,float>(ctest1->GetSmartPointer());///Compile Error
	/*ctest2->AddPreMUSiiCTaskInterface3((igtl::MUSiiCTaskAbstract::Pointer)ctest1);*/


	/// Testing of add Data-Interface
	ctest1->AddPreInputDataInterface(intVector);
	ctest1->AddPreOutputDataInterface(intVector);
	ctest1->AddPostInputDataInterface(ctest2->GetPreInputDataInterface());
	ctest1->AddPostOutputDataInterface(ctest2->GetPreOutputDataInterface());

	floatVector = ctest2->GetPreInputDataInterface();
	floatVector = ctest2->GetPreOutputDataInterface();


	ctest4->AddPreInputDataInterface(igtlMBVector);
	//ctest4->AddPreInputDataInterface(IGTLVector);///Compile Error
	ctest4->AddPreInputDataInterface((igtl::MUSiiCVector<igtl::MessageBase::Pointer>::Pointer)IGTLVector); //Good
	ctest4->AddPreInputDataInterface(IGTLVector->GetSmartPointer()); //Good


	return 0;
}