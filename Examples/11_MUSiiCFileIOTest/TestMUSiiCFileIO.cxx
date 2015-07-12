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
#include <MUSiiCIGTLFileIO.h>


#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
using namespace igtl;
int main(int argc, char** argv)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	
	igtl::MUSiiCIGTLMsgFileIO::Pointer pFileIO = igtl::MUSiiCIGTLMsgFileIO::New();

	/////
	std::string Bmode01_Path = "bmode_001.igtl";
	igtl::ImageMessage::Pointer bmode01 =  pFileIO->ReadSingleImageMessage(Bmode01_Path, false);
	//igtl::MessageBase::Pointer bMsg =  pFileIO->ReadSingleFile(Bmode01_Path);
	
	
	
	/////// Reading a 	TrackingDataMessage

	std::string TrackDataFilePath = "test7485.795497.igtl";
	igtl::TrackingDataMessage::Pointer  pTrackData = pFileIO->ReadSingleTrackingDataMessage(TrackDataFilePath);

	/// ******* Generate Dummy Message
	/// 01.Generate Dummy USMessage ///////////////////////////////
	igtl::USMessage::Pointer us           = igtl::GetDummyUSMessage2();
	/// 02.Generate Dummy ImageMessage ///////////////////////////////
	igtl::MessageBase::Pointer bimg       = igtl::GetDummyImageMessage();
	igtl::ImageMessage::Pointer img       = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(bimg);
	/// 03.Generate Dummy TrackingDataMessage ///////////////////////////////
	igtl::MessageBase::Pointer btr        = igtl::GetDummyTrackingDataMessage();
	igtl::TrackingDataMessage::Pointer tr = igtl::RetrieveMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(btr);
	/// 04.Generate Dummy StringMessage ///////////////////////////////
	igtl::MessageBase::Pointer bstr       = igtl::GetDummyStringMessage();
	igtl::StringMessage::Pointer str      = igtl::RetrieveMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(bstr);
	/// 05.Generate Dummy EIMessage ///////////////////////////////
	igtl::MessageBase::Pointer bei        = igtl::GetDummyEIMessage();
	igtl::EIMessage::Pointer ei           = igtl::RetrieveMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(bei);
	
	
	/// ******* Test Writing function
	/// 01.Write Dummy USMessage ///////////////////////////////
	pFileIO->WriteSingleFile((igtl::MessageBase::Pointer)us, "DummyUSMsg.igtl");

	/// 02.Write Dummy ImageMessage ///////////////////////////////
	pFileIO->WriteSingleFile((igtl::MessageBase::Pointer)img, "DummyImgMsg.igtl");

	/// 03.Write Dummy TrackingDataMessage ///////////////////////////////
	pFileIO->WriteSingleFile((igtl::MessageBase::Pointer)tr,  "DummyTrackingDataMsg.igtl");

	/// 04.Write Dummy StringMessage ///////////////////////////////
	pFileIO->WriteSingleFile((igtl::MessageBase::Pointer)str, "DummyStringMsg.igtl");

	/// 05.Write Dummy EIMessage ///////////////////////////////
	pFileIO->WriteSingleFile((igtl::MessageBase::Pointer)ei,  "DummyEIMsg.igtl");

	/// ******* Test Reading function
	std::string path;
	/// 01.Read Dummy USMessage ///////////////////////////////
	path = "DummyUSMsg.igtl";
	/// 01.1 Reading Method #1
	igtl::MessageBase::Pointer baseUS          = pFileIO->ReadSingleFile(path);
	igtl::USMessage::Pointer USMsg1            = igtl::RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(baseUS);
	
	/// 01.2 Reading Method #2
	igtl::USMessage::Pointer USMsg2            = pFileIO->ReadSingleUSMessage(path); 
	
	/// 01.3 Reading Method #3
	igtl::USMessage::Pointer USMsg3            = pFileIO->ReadSpecificSingleMessage<igtl::USMessage::Pointer, igtl::USMessage>(path);
	
	/// 02.Read Dummy ImageMessage ///////////////////////////////
	/// 02.1 Reading Method #1
	path = "DummyImgMsg.igtl";
	igtl::MessageBase::Pointer baseImg         = pFileIO->ReadSingleFile(path);
	igtl::ImageMessage::Pointer Img1           = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(baseImg);

	/// 02.2 Reading Method #2
	igtl::ImageMessage::Pointer Img2           = pFileIO->ReadSingleImageMessage(path); 
	
	/// 02.3 Reading Method #3
	igtl::ImageMessage::Pointer Img3           = pFileIO->ReadSpecificSingleMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(path);

	
	/// 03.Read Dummy TrackingDataMessage ///////////////////////////////
	/// 03.1 Reading Method #1
	path = "DummyTrackingDataMsg.igtl";
	igtl::MessageBase::Pointer baseTrack       = pFileIO->ReadSingleFile(path);
	igtl::TrackingDataMessage::Pointer Track1  = igtl::RetrieveMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(baseTrack);

	/// 03.2 Reading Method #2
	igtl::TrackingDataMessage::Pointer Track2  = pFileIO->ReadSingleTrackingDataMessage(path); 
	
	/// 03.3 Reading Method #3
	igtl::TrackingDataMessage::Pointer Track3  = pFileIO->ReadSpecificSingleMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(path);


	/// 04.Read Dummy StringMessage ///////////////////////////////
	path = "DummyStringMsg.igtl";
	/// 04.1 Reading Method #1
	igtl::MessageBase::Pointer baseStr         = pFileIO->ReadSingleFile(path);
	igtl::StringMessage::Pointer Str1          = igtl::RetrieveMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(baseStr);
	
	/// 04.2 Reading Method #2
	igtl::StringMessage::Pointer Str2          = pFileIO->ReadSingleStringMessage(path); 
	
	/// 04.3 Reading Method #3
	igtl::StringMessage::Pointer Str3          = pFileIO->ReadSpecificSingleMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(path);

	/// 05.Read Dummy EIMessage ///////////////////////////////
	path = "DummyEIMsg.igtl";
	/// 01.1 Reading Method #1
	igtl::MessageBase::Pointer baseEI          = pFileIO->ReadSingleFile(path);
	igtl::EIMessage::Pointer EIMsg1            = igtl::RetrieveMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(baseEI);

	/// 05.2 Reading Method #2
	igtl::EIMessage::Pointer EIMsg2            = pFileIO->ReadSingleEIMessage(path); 
	
	/// 05.3 Reading Method #3
	igtl::EIMessage::Pointer EIMsg3            = pFileIO->ReadSpecificSingleMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(path);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// ******* Test Reading of Old version USMesaage
	std::string pathOldUS1 = "2D_RF_Old.igtl";
    std::string pathOldUS2 = "2D_RF_Old2.igtl";
	/////// Test reading old USMessage
	/// 1 Reading Method #1: This method is does not work for old version USMessage
	
	/// 2 Reading Method #2
	/// In this method, Old version of USMessage automatically convert to a New version of USMessage
	igtl::USMessage::Pointer OldUS1             = pFileIO->ReadSingleUSMessage(pathOldUS1); 
	igtl::USMessage::Pointer OldUS2             = pFileIO->ReadSingleUSMessage(pathOldUS2); 

	/// 3 Reading Method #2: This method is does not work for old version USMessage
	 
	/////// Testing data-casting 
	igtl::MessageBase::Pointer B_OldUS1         = (igtl::MessageBase::Pointer)OldUS1;
	igtl::MessageBase::Pointer B_OldUS2         = (igtl::MessageBase::Pointer)OldUS2;

	/////// Testing the function of retrieve
	igtl::USMessage::Pointer C_OldUS1           = igtl::RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(B_OldUS1);
	igtl::USMessage::Pointer C_OldUS2           = igtl::RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(B_OldUS2);

	/////// Writing Old USMessage
	std::string Con_US1 = "Converted_USMsg1.igtl1";
	std::string Con_US2 = "Converted_USMsg2.igtl1";

	pFileIO->WriteSingleFile(B_OldUS1, Con_US1);
	pFileIO->WriteSingleFile(B_OldUS2, Con_US2);

	/////// Reading a converted USMessage
	/// 01.1 Reading Method #1
	igtl::MessageBase::Pointer baseCUS1          = pFileIO->ReadSingleFile(Con_US1);
	igtl::USMessage::Pointer CUSMsg11            = igtl::RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(baseCUS1);
	
	/// 01.2 Reading Method #2
	igtl::USMessage::Pointer CUSMsg12            = pFileIO->ReadSingleUSMessage(Con_US1); 
	
	/// 01.3 Reading Method #3
	igtl::USMessage::Pointer CUSMsg13            = pFileIO->ReadSpecificSingleMessage<igtl::USMessage::Pointer, igtl::USMessage>(Con_US1);

	/// 01.1 Reading Method #1
	igtl::MessageBase::Pointer baseCUS2          = pFileIO->ReadSingleFile(Con_US2);
	igtl::USMessage::Pointer CUSMsg21            = igtl::RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(baseCUS2);
	
	/// 01.2 Reading Method #2
	igtl::USMessage::Pointer CUSMsg22            = pFileIO->ReadSingleUSMessage(Con_US2); 
	
	/// 01.3 Reading Method #3
	igtl::USMessage::Pointer CUSMsg23            = pFileIO->ReadSpecificSingleMessage<igtl::USMessage::Pointer, igtl::USMessage>(Con_US2);

	
	///////////////////////////////



	return 0;
}

