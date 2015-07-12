/***************************************************************************
Copyright May/2011
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/

#include <stdio.h>
#include <MUSiiCTaskSingleInterface.h>
#include <igtlOSUtil.h> //igtl::Sleep


template<class Data> class SingleTaskTest1: public igtl::MUSiiCTaskSingleInterface<Data>
{
public: ///Operations
	typedef SingleTaskTest1<Data>                       Self;
	typedef igtl::MUSiiCTaskSingleInterface<Data>       Superclass;
	typedef igtl::SmartPointer<Self>                    Pointer;
	typedef igtl::SmartPointer<const Self>              ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	////////////////////////////////////////////////////////////
	SingleTaskTest1()
	{
		m_pNameOfClass="SingleTaskTest1";
		Initialize();
		
	}

	/// Deconstructor
	~SingleTaskTest1()
	{
	}

	int RunTask1(int numofRun = igtl::M_THREAD_RUN_CONTINUOUS)
	{	
		printf("Task1 is starting\n", m_iRunNumber);
		m_iRunNumber = 0;

		this->SetEnableThread(true);
		/// Run network thread for network communication
		return RunTask(numofRun, 100 , this, NULL, NULL, NULL);
	}

	int Task1()
	{
		//printf("Run %d\n", m_iRunNumber);
		if(this->m_bDATA_IF)
		{
			this->m_pDATA_IF->concurrent_push_back(m_iRunNumber);
			printf(">>>>>>Task1 :: Put %d to DataInterface\n", m_iRunNumber);
			igtl::Sleep(1);
		}
		else
			printf("Task1 has no Data-Interface!!!!!\n");
		
		m_iRunNumber++;
		return m_iRunNumber;
	}
protected: /// Operations
	/// Client-Network Task function is implemented in this function.
	/// Initialize Member variables
	virtual void Initialize()
	{
		igtl::MUSiiCTaskSingleInterface <Data>::Initialize();
		m_iRunNumber = 0;
	}
	

	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		return Task1();
	}

public: /// Attributes

protected: /// Attributes
	int m_iRunNumber;

};

template<class Data> class SingleTaskTest2: public igtl::MUSiiCTaskSingleInterface<Data>
{
public: ///Operations
	typedef SingleTaskTest2<Data>						Self;
	typedef igtl::MUSiiCTaskSingleInterface<Data>		Superclass;
	typedef igtl::SmartPointer<Self>							Pointer;
	typedef igtl::SmartPointer<const Self>					ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

	////////////////////////////////////////////////////////////
	SingleTaskTest2()
	{
		m_pNameOfClass="SingleTaskTest2";
		Initialize();
	}

	/// Deconstructor
	~SingleTaskTest2()
	{
	}

	int RunTask2()
	{	
		printf("Task2 is starting\n");

		this->SetEnableThread(true);
		/// Run network thread for network communication
		return RunTask(igtl::M_THREAD_RUN_CONTINUOUS, 100 , this, NULL, NULL, NULL);
	}

	int Task2()
	{
		if(this->m_bDATA_IF)
		{
			//int sz = this->m_pDATA_IF->concurrent_size();
			//if(sz >0)
			{
				int data;
				this->m_pDATA_IF->concurrent_wait_get_pop_front(data);

				printf("<<<<<Task2 :: The data %d is from Task1\n", data);
			}
		}
		else
			printf("Task2 has no data-interface!!!!!\n");
		return 0;
	}

protected: /// Operations
	virtual void Initialize()
	{
		igtl::MUSiiCTaskSingleInterface <Data>::Initialize();
	}
	

	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		return Task2();
	}
public: /// Attributes

protected: /// Attributes

};

int main (int argc, char* argv[])
{
	igtl::MUSiiCVector<int>::Pointer pDataInterface = igtl::MUSiiCVector<int>::New();

	SingleTaskTest1<int>::Pointer pTask1 = SingleTaskTest1<int>::New();
	SingleTaskTest2<int>::Pointer pTask2 = SingleTaskTest2<int>::New();

	pTask1->SetDataInterface(pDataInterface);
	pTask2->SetDataInterface(pDataInterface);
	
	//pTask1->RunTask1(10000);
	pTask1->RunTask1();
	pTask2->RunTask2();

	//pTask1->WaitTask();
	////pTask2->WaitTask();
	//igtl::Sleep(1000);

	printf("Prees q for quit this program\n");
	char sel;
	for(;;)
	{
		scanf("%c", &sel);

		if( sel == 'q')
			break;
	}

	//pTask1->StopTask();
	pTask2->StopTask();
	pTask1->StopTask();
	return 0;
}