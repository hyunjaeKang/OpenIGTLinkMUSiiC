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
This a basic example is about how to use MUSiiCIOFilter.

01. Create a pointer of MUSiiCIOFilter
02. Initialize MUSiiCIOFilter
03. Add data-types on MUSiiCIOFilter
04. Check
	1.Check USMessage
	2.Check Reference_USMessage 
	3.Check ImageMessage
***************************************************************************/

#include <MUSiiCDef.h>
#include <MUSiiCIGTLUtil.h>

bool CheckMessage1(igtl::MUSiiCIOFilter::Pointer filter, igtl::MessageBase::Pointer msg, bool checkDevicetype = false)
{
	std::cout<< "CheckMessage1:: Using the function of 'find of std::string'"<<std::endl;
	if(filter->CheckMessageBase(msg, checkDevicetype).IsNotNull())
	{
		std::cout<< "Message of " << msg->GetDeviceName() << " is defined MUSiiCIOFilter." << std::endl;
		std::cout<<std::endl;
		return true;
	}	
	else
	{
		std::cout<< "Message of " << msg->GetDeviceName() << " is not defined MUSiiCIOFilter." << std::endl;
		std::cout<<std::endl;
		return false;
	}
}


bool CheckMessage2(igtl::MUSiiCIOFilter::Pointer filter, igtl::MessageBase::Pointer msg, bool checkDevicetype = false)
{
	std::cout<< "CheckMessage2:: Using the function of 'find of std::map'"<<std::endl;
	if(filter->CheckMessageBase2(msg, checkDevicetype).IsNotNull())
	{
		std::cout<< "Message of " << msg->GetDeviceName() << " is defined MUSiiCIOFilter." << std::endl;
		std::cout<<std::endl;
		return true;
	}	
	else
	{
		std::cout<< "Message of " << msg->GetDeviceName() << " is not defined MUSiiCIOFilter." << std::endl;
		std::cout<<std::endl;
		return false;
	}
}


int main(int argc, char** argv)
{
	/// Create a pointer of MUSiiCIOFilter
	igtl::MUSiiCIOFilter::Pointer pMUSiiCFilter = igtl::MUSiiCIOFilter::New();
	/// Initialize MUSiiCIOFilter
	pMUSiiCFilter->ResetMUSiiCIOFilter();

	/// Add data-types on MUSiiCIOFilter
	std::cout<<std::endl;
	std::cout<< "***** Add data-types in MUSiiCIOFilter" << std::endl;
	pMUSiiCFilter->SetMUSiiCIOFilter(M_DUMMY_RF); /// Device Name (at MUSiiCDef.h) 
	pMUSiiCFilter->SetMUSiiCIOFilter(M_DUMMY_EI); /// Device Name (at MUSiiCDef.h)
	pMUSiiCFilter->SetMUSiiCIOFilter(IGTL_IMAGE); /// Device Type (at MUSiiCDef.h)

	/// Check the number of data-types of MUSiiCIOFilter
	int s(pMUSiiCFilter->GetNumberOfDataType());
	
	std::cout<< "The number of Data-type in MUSiiCIOFilter is " << s << std::endl;
	std::cout<<std::endl;
	std::cout<< "The information of MUSiiCIOFilter " << s << std::endl;
	pMUSiiCFilter->PrintIOFilter();
	std::cout<< "***** Add data-types in MUSiiCIOFilter" << std::endl;
	std::cout<<std::endl;
	std::cout<<std::endl;

	/// Check Dummy USMessage using pre-defined MUSiiCIOFilter
	igtl::MessageBase::Pointer us = igtl::GetDummyUSMessage();
	/// Check Method 1 : Just use the Device-Name of Message 
	std::cout <<std::endl;
	std::cout<<"*** Check US Message" <<std::endl;
	CheckMessage1(pMUSiiCFilter, us);
	CheckMessage2(pMUSiiCFilter, us);
	std::cout<<"*** Check US Message" <<std::endl;
	std::cout <<std::endl;
	
	
	std::cout <<std::endl;
	std::cout<<"*** Check Reference US Message" <<std::endl;
	/// Set the given message as Reference Message type for MUSiiCSync
	if(igtl::SetReferenceData(us))
	{
		if(igtl::IsReferenceData(us)) /// If the message is a Reference Message
			std::cout << "Given data is reference data" << std::endl;
		else /// If the message is not a Reference Message
			std::cout << "Given data is not reference data" << std::endl;
		
		std::cout << "Set the given message as the reference message" <<std::endl;
		/// Check the Reference Message data type
		CheckMessage1(pMUSiiCFilter,us);
		CheckMessage2(pMUSiiCFilter,us);
	}
	std::cout<<"*** Check Reference US Message" <<std::endl;
	std::cout <<std::endl;

	std::cout <<std::endl;
	std::cout<<"*** Check Dummy Image Message" <<std::endl;
	//// Check DummyImage Message using pre-defined MUSiiCIOFilter
	igtl::MessageBase::Pointer img = igtl::GetDummyImageMessage();
	/// Check Method 1-1 : Just use the Device-Name of Message
	std::cout<<"Just use the Device-Name of Message" <<std::endl;
	CheckMessage1(pMUSiiCFilter, img);
	/// Check Method 1-2 : Use the Device-Name and Device-type of Message
	std::cout<<"Use the Device-Name and Device-type of Message" <<std::endl;
	CheckMessage1(pMUSiiCFilter, img, true);

	/// Check Method 2-1 : Just use the Device-Name of Message
	std::cout<<"Just use the Device-Name of Message" <<std::endl;
	CheckMessage1(pMUSiiCFilter, img);
	/// Check Method 2-2 : Use the Device-Name and Device-type of Message
	std::cout<<"Use the Device-Name and Device-type of Message" <<std::endl;
	CheckMessage1(pMUSiiCFilter, img, true);
	std::cout<<"*** Check Dummy Image Message" <<std::endl;


	std::cout<<std::endl;
	std::cout<< "***** Rmove data-types in MUSiiCIOFilter" << std::endl;
	pMUSiiCFilter->RemoveDataType(M_DUMMY_RF); /// Device Name (at MUSiiCDef.h) 

	/// Check the number of data-types of MUSiiCIOFilter
	int ss(pMUSiiCFilter->GetNumberOfDataType());
	
	std::cout<< "The number of Data-type in MUSiiCIOFilter is " << ss << std::endl;
	std::cout<<std::endl;
	std::cout<< "The information of MUSiiCIOFilter " << ss << std::endl;
	pMUSiiCFilter->PrintIOFilter();
	std::cout<< "***** Remove data-types in MUSiiCIOFilter" << std::endl;
	std::cout<<std::endl;
	std::cout<<std::endl;

	std::cout <<std::endl;
	std::cout<<"*** Check Reference US Message" <<std::endl;
	/// Check the Reference Message data type
	CheckMessage1(pMUSiiCFilter,us);
	CheckMessage2(pMUSiiCFilter,us);
	std::cout<<"*** Check Reference US Message" <<std::endl;
	std::cout <<std::endl;


	/// Check Method 1-1 : Just use the Device-Name of Message
	std::cout<<"Just use the Device-Name of Message" <<std::endl;
	CheckMessage1(pMUSiiCFilter, img);
	/// Check Method 1-2 : Use the Device-Name and Device-type of Message
	std::cout<<"Use the Device-Name and Device-type of Message" <<std::endl;
	CheckMessage1(pMUSiiCFilter, img, true);

	/// Check Method 2-1 : Just use the Device-Name of Message
	std::cout<<"Just use the Device-Name of Message" <<std::endl;
	CheckMessage1(pMUSiiCFilter, img);
	/// Check Method 2-2 : Use the Device-Name and Device-type of Message
	std::cout<<"Use the Device-Name and Device-type of Message" <<std::endl;
	CheckMessage1(pMUSiiCFilter, img, true);
	std::cout<<"*** Check Dummy Image Message" <<std::endl;


	return 0;
}