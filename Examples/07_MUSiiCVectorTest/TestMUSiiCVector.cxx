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
This a basic example is about how to use MUSiiCVector.

MUSiiCVector is a concurrent Vector that is based on template data structure.
This Vector is designed for thread-safety.
***************************************************************************/

#include <MUSiiCVector.h>
#include <MUSiiCIGTLUtil.h>

int main (int argc, char** argv)
{
	int i(0), sz(0);
	
	/////////////////////////////////////////
	// Example 1: Use MUSiiCVector as an object
	//            MUSiiCVector for INT data-type
	/*std::cout << "*********************************************" << std::endl;
	std::cout << "Example 01 ::                                " << std::endl;
	std::cout << "Use MUSiiCVector as an object                " << std::endl;
	std::cout << "Use the operation :: concurrent_try_get()    " << std::endl;
	igtl::MUSiiCVector<int> VInt;      /// Create an object of MUSiiCVector with int data-type

	VInt.concurrent_clear();           /// Initialize the MUSiiCVector with removing all parameters 
	for(i=0; i<10; i++)                /// Push data into the MUSiiCVector
		VInt.concurrent_push_back(i);

	sz = VInt.concurrent_size();   /// Get the size of MUSiiCVector 

	std::cout << std::endl;
	std::cout << "The size of MUSiiCVector<int> is " << VInt.concurrent_size() <<std::endl;
	for(i=0; i<sz; i++)
		std::cout<< "Value is :" << VInt[i] << std::endl;

	std::cout << std::endl;
	std::cout << "The size of MUSiiCVector<int> is " << VInt.concurrent_size() <<std::endl;
	std::cout << "*********************************************" << std::endl;
	std::cout << std::endl;
	VInt.~MUSiiCVector();*/
	/// When this program is terminated, there is an warning frm Object of OpenIGTL

	///////////////////////////////////////////
	//// Example 1-1: Use MUSiiCVector as an object
	////             MUSiiCVector for INT data-type
	//std::cout << "*********************************************" << std::endl;
	//std::cout << "Example 01 - 01 ::                           " << std::endl;
	//std::cout << "Use MUSiiCVector as an object                " << std::endl;
	//std::cout << "Use the operation :: concurrent_try_get_pop()" << std::endl;
	//igtl::MUSiiCVector<int> VInt2;      /// Create an object of MUSiiCVector with int data-type

	//VInt2.concurrent_clear();           /// Initialize the MUSiiCVector with removing all parameters 
	//for(i=0; i<10; i++)                /// Push data into the MUSiiCVector
	//	VInt2.concurrent_push_back(i);

	//sz = VInt2.concurrent_size();   /// Get the size of MUSiiCVector 

	//std::cout << std::endl;
	//std::cout << "The size of MUSiiCVector<int> is " << VInt2.concurrent_size() <<std::endl;
	//for(i=0; i<sz; i++)
	//	std::cout<< "Value is :" << VInt2(0) << std::endl;

	//std::cout << std::endl;
	//std::cout << "The size of MUSiiCVector<int> is " << VInt2.concurrent_size() <<std::endl;
	//std::cout << "*********************************************" << std::endl;
	//std::cout << std::endl;

	///////////////////////////////////////////
	//// Example 1-2: Use MUSiiCVector as an object
	////             MUSiiCVector for igtl::MessageBase data-type
	//std::cout << "*********************************************" << std::endl;
	//std::cout << "Example 01 - 02 ::                           " << std::endl;
	//std::cout << "Use MUSiiCVector as an object                " << std::endl;
	//std::cout << "Use the operation :: concurrent_try_get_pop()" << std::endl;
	//igtl::MUSiiCVector<igtl::MessageBase::Pointer> VIGTLM;      /// Create an object of MUSiiCVector with int data-type

	//VIGTLM.concurrent_clear();           /// Initialize the MUSiiCVector with removing all parameters 
	//for(i=0; i<3; i++)                /// Push data into the MUSiiCVector
	//	VIGTLM.concurrent_push_back(igtl::GetDummyUSMessage());

	//sz = VIGTLM.concurrent_size();   /// Get the size of MUSiiCVector 

	//std::cout << std::endl;
	//std::cout << "The size of MUSiiCVector<int> is " << VIGTLM.concurrent_size() <<std::endl;
	//for(i=0; i<sz; i++)
	//	igtl::PrintUSMessageMB(VIGTLM(0));

	//std::cout << std::endl;
	//std::cout << "The size of MUSiiCVector<int> is " << VIGTLM.concurrent_size() <<std::endl;
	//std::cout << "*********************************************" << std::endl;
	//std::cout << std::endl;

	
	/////////////////////////////////////////
	// Example 2: Use MUSiiCVector as an object
	//            MUSiiCVector for INT data-type
	std::cout << "*********************************************" << std::endl;
	std::cout << "Example 02 ::                                " << std::endl;
	std::cout << "Use MUSiiCVector as a pointer                " << std::endl;
	std::cout << "Use the operation :: concurrent_try_get()    " << std::endl;
	igtl::MUSiiCVector<float>::Pointer  pVInt = igtl::MUSiiCVector<float>::New();      /// Create an object of MUSiiCVector with int data-type

	pVInt->concurrent_clear();           /// Initialize the MUSiiCVector with removing all parameters 
	for(i=0; i<10; i++)                /// Push data into the MUSiiCVector
		pVInt->concurrent_push_back((float)i * 0.5);

	sz = pVInt->concurrent_size();   /// Get the size of MUSiiCVector 

	std::cout << std::endl;
	std::cout << "The size of MUSiiCVector<float> is " <<  pVInt->concurrent_size() <<std::endl;
	for(i=0; i<sz; i++)
		std::cout<< "Value is :" << pVInt->concurrent_try_GetData(i) << std::endl;

	std::cout << "*********************************************" << std::endl;
	std::cout << std::endl;


	/////////////////////////////////////////
	// Example 2-2: Use MUSiiCVector as an object
	//             MUSiiCVector for igtl::MessageBase data-type
	std::cout << "*********************************************" << std::endl;
	std::cout << "Example 01 - 02 ::                           " << std::endl;
	std::cout << "Use MUSiiCVector as an object                " << std::endl;
	std::cout << "Use the operation :: concurrent_try_get_pop()" << std::endl;
	/// Create an object of MUSiiCVector with int data-type
	igtl::MUSiiCVector<igtl::MessageBase::Pointer>::Pointer pVIGTLM = igtl::MUSiiCVector<igtl::MessageBase::Pointer>::New();      

	pVIGTLM->concurrent_clear();           /// Initialize the MUSiiCVector with removing all parameters 
	for(i=0; i<3; i++)                /// Push data into the MUSiiCVector
		pVIGTLM->concurrent_push_back(igtl::GetDummyUSMessage());

	sz = pVIGTLM->concurrent_size();   /// Get the size of MUSiiCVector 

	std::cout << std::endl;
	std::cout << "The size of MUSiiCVector<int> is " << pVIGTLM->concurrent_size() <<std::endl;
	for(i=0; i<sz; i++)
		igtl::PrintUSMessageMB(pVIGTLM->concurrent_try_GetData_pop(0));

	std::cout << std::endl;
	std::cout << "The size of MUSiiCVector<int> is " << pVIGTLM->concurrent_size() <<std::endl;

	pVIGTLM->concurrent_clear();           /// Initialize the MUSiiCVector with removing all parameters 
	std::cout << "*********************************************" << std::endl;
	std::cout << std::endl;

	return 0;

}