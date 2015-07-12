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
#include <igtlOSUtil.h> //igtl::Sleep
#include <MUSiiCigtlMsgFILEIO.h>
#include <igtlImageMessage.h>

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

#include <MUSiiCUtil.h>

//#include"MUSiiCGlobalFuntion.cxx"


igtl::ImageMessage::Pointer ConvertBase2Image(igtl::MessageBase::Pointer msg, bool debug = false)
{
	if(msg.IsNotNull())
	//if(msg != NULL)
	{
		msg->Pack();

		//socket->Send(imgMsg->GetPackPointer(), imgMsg->GetPackSize());
		//char* tempdata = new char[msg->GetPackSize()];

		//memcpy(tempdata, msg->GetPackPointer(), msg->GetPackSize());

		//igtl::MessageHeader::Pointer pHeader = igtl::MessageHeader::New();
		//pHeader->InitPack();
		//int sh = pHeader->GetPackSize();
		//memcpy(pHeader->GetPackPointer(), msg->GetPackPointer(), pHeader->GetPackSize());
		////memcpy(pHeader->GetPackPointer(), msg.GetPointer(), pHeader->GetPackSize());
		////memcpy(pHeader->GetPackPointer(), tempdata, pHeader->GetPackSize());
		//pHeader->Unpack();

		igtl::ImageMessage::Pointer  img = igtl::ImageMessage::New();
		img->SetMessageHeader(msg);
		img->AllocatePack();
		int sb = img->GetPackBodySize();
		memcpy(img->GetPackBodyPointer(),msg->GetPackBodyPointer(), img->GetPackBodySize());
		//memcpy(img->GetPackBodyPointer(), tempdata+pHeader->GetPackSize(), pHeader->GetPackSize());
		//int c = img->Unpack(1);
		int c = img->Unpack();

		if( c & igtl::MessageHeader::UNPACK_BODY) 
		{
			if(debug)
			{
				// Retrive the image data
				int   size[3];          // image dimension
				float spacing[3];       // spacing (mm/pixel)
				int   svsize[3];        // sub-volume size
				int   svoffset[3];      // sub-volume offset
				int   scalarType;       // scalar type

				//scalarType = imgMsg->GetScalarType();
				img->GetDimensions(size);
				img->GetSpacing(spacing);
				img->GetSubVolume(svsize, svoffset);

				std::cerr << "Device Type           : " << img->GetDeviceType() << std::endl;
				std::cerr << "Device Name           : " << img->GetDeviceName() << std::endl;
				std::cerr << "Dimensions            : ("
						  << size[0] << ", " << size[1] << ", " << size[2] << ")" << std::endl;
				std::cerr << "Spacing               : ("
						  << spacing[0] << ", " << spacing[1] << ", " << spacing[2] << ")" << std::endl;
				std::cerr << "Sub-Volume dimensions : ("
						  << svsize[0] << ", " << svsize[1] << ", " << svsize[2] << ")" << std::endl;
				std::cerr << "Sub-Volume offset     : ("
						  << svoffset[0] << ", " << svoffset[1] << ", " << svoffset[2] << ")" << std::endl << std::endl;
			}
			return img;
		}

		//delete tempdata;
	}
	else
		return NULL;
}

class CallbackInterface
{
public:
	/// Constructor
	CallbackInterface()
	{
		m_pDataBuffer = igtl::MUSiiCVector<igtl::MessageBase::Pointer>::New();
		m_igtlFileIO= igtl::MUSiiCigtlMsgFILEIO::New();
		igtl::MUSiiCCallbackInterface::Pointer callback2;
		callback2 = igtl::CreateLocalCallbackInterface(this, &CallbackInterface::Callbackfunction2, "Callback2");
		
		m_igtlFileIO->AddCallbackInterface(callback2);
	}
	/// Deconstructor
	~CallbackInterface()
	{
	}

	bool GetDescription(int TaskInfo, std::string& des, void* data1)
	{
		bool bData;
		std::string des_temp;
		switch(TaskInfo)
		{
			case igtl::M_READ_SINGLE_CB:
				des_temp = "Callback function of Reading Single File w/ callback";
				break;
			case igtl::M_READ_SINGLE_TH:
				des_temp = "Callback function of Reading Single File w/ callback, thread";
				break;
			case igtl::M_READ_MULTI_CB:
				des_temp = "Callback function of Reading Multi Files w/ callback";
				break;
			case igtl::M_READ_MULTI_TH:
				des_temp = "Callback function of Reading Multi Files w/ callback, thread";
				break;
			case igtl::M_WRITE_SINGLE_CB:
				des_temp = "Callback function of Writing Single File w/ callback";
				break;
			case igtl::M_WRITE_SINGLE_TH:
				des_temp = "Callback function of Writing Single File w/ callback, thread";
				break;
			case igtl::M_WRITE_MULTI_CB:
				des_temp = "Callback function of Writing Multi Files w/ callback";
				break;
			case igtl::M_WRITE_MULTI_TH:
				des_temp = "Callback function of Writing Multi Files w/ callback, thread";
				break;
			case igtl::M_WRITE_STREAM_DATA:
				des_temp = "Callback function of Writing stream Data w/ callback, thread";
				break;
		}
			
		std::string temp2;
		if(data1 == NULL)
		{
			temp2 = "_ without Data";
			bData = false;
		}
		else 
		{
			temp2 = "_ with Data";
			bData = true;
		}


		des = des_temp +temp2;
		return bData;
				
	}

	void printCallbackInfo(std::string description, bool data, int numOfRun, int Taskinfo, void* ptr, void* data1, void* data2, void* data3)
	{
		double t;
		t = *(double*)data2;
		std::string* name = (std::string*) data3;

		printf("\n");
		printf("/// %s ///\n", description.c_str());
		printf("NumOfRun: %d, TaskInfo: %d\n", numOfRun, Taskinfo);
		printf("file name is %s, timestamp: %f\n", name->c_str(), t);
		printf("\n");
		if(data)
		{
			igtl::MessageBase::Pointer msg = (igtl::MessageBase*)data1;
			igtl::ImageMessage::Pointer img =  ConvertBase2Image(msg, true);
		}
		
	}


	int Callbackfunction(int numOfRun, int TaskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
		
		std::string des;
		bool bData = GetDescription(TaskInfo,des,data1);

		printCallbackInfo(des, bData, numOfRun, TaskInfo, ptr, data1, data2, data3);
		std::string name_2;
		std::string* name = (std::string*) data3;
		igtl::MessageBase::Pointer msg;
		
		if(bData)
		{
			//msg = (igtl::MessageBase*)data1;
			switch(TaskInfo)
			{
				case igtl::M_READ_SINGLE_CB:
					name_2 = "ReWrite_S_CB_";
					name_2= name_2 + name->c_str();
					m_igtlFileIO->WriteSingleFileCB(msg, name_2);
					break;
				case igtl::M_READ_SINGLE_TH:
					name_2 = "ReWrite_S_TH_";
					name_2= name_2 + name->c_str();
					m_igtlFileIO->WriteSingleFileTH(msg, name_2);
					break;
				case igtl::M_READ_MULTI_CB:
					name_2 = "ReWrite_M_CB_";
					name_2= name_2 + name->c_str();
					m_igtlFileIO->WriteSingleFileCB(msg, name_2);
					break;
				case igtl::M_READ_MULTI_TH:
					name_2 = "ReWrite_M_TH_";
					name_2= name_2 + name->c_str();
					m_igtlFileIO->WriteSingleFileTH(msg, name_2);
					break;
			}

			
		}
		else
		{
			m_pDataBuffer->concurrent_wait_get_back(msg);
			
			name_2 = "ReWrite_M_TH_DATA_IF_";
			name_2= name_2 + name->c_str();
			m_igtlFileIO->WriteSingleFileTH(msg, name_2);
			double ts = 0.0;
		}
		return 1;
	}


	int Callbackfunction2(int numOfRun, int TaskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
		
		std::string des;
		bool bData = GetDescription(TaskInfo,des,data1);
		printCallbackInfo(des, bData, numOfRun, TaskInfo, ptr, data1, data2, data3);
		
		return 1;
	}

	int PutTempBuffer(igtl::MessageBase* msg)
	{
		m_TempBuff.push_back(msg);

		return m_TempBuff.size()-1;
	}

	template<class C> C GetData(int idx)
	{
		return (C)m_TempBuff[idx];
	}

public:
	igtl::MUSiiCVector<igtl::MessageBase::Pointer>::Pointer m_pDataBuffer;
	igtl::MUSiiCigtlMsgFILEIO::Pointer m_igtlFileIO;

	std::vector<igtl::MessageBase*>  m_TempBuff;
};

int main (int argc, char* argv[])
{
	igtl::MUSiiCigtlMsgFILEIO::Pointer igtlFile = igtl::MUSiiCigtlMsgFILEIO::New();

	igtl::MessageBase::Pointer msg;// = NULL;
	igtl::ImageMessage::Pointer img_t;
	igtl::ImageMessage::Pointer img_t2;
	igtl::ImageMessage::Pointer img_t3;
	////////////////////////////////////////////////////////////////////////
	/////Sing Flie Reading and Writing
 	msg = igtlFile->ReadSingleFile("TestImage.igtl");//"BMODE.igtl");
	msg = igtlFile->ReadSingleFile("Image_KHJ.igtl");//"BMODE.igtl");
	img_t = igtlFile->ReadSingImage("TestImage.igtl");//"BMODE.igtl");
	//img_t2 = igtlFile->ReadSingImage("Image_Test33.igtl");//"BMODE.igtl");
	//img_t2 = igtlFile->ReadSingImage("Image_9.igtl");//"BMODE.igtl");
	img_t2 = igtlFile->ReadSingImage("Image_Test33.igtl");//"BMODE.igtl");
	img_t3 = igtlFile->ReadSingImage("TestImage2.igtl");//"BMODE.igtl");
	msg = igtlFile->ReadSingleFile("USData1.igtl");//"BMODE.igtl");
	
	igtl::ImageMessage::Pointer img =  ConvertBase2Image(msg, true);
	igtl::ImageMessage::Pointer img2 = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);
	igtl::USMessage::Pointer rf = igtl::RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(msg);

	int r = igtlFile->WriteSingleFile(msg, "FakeRF2.igtl");

	
	
	//// Define callback interface
	igtl::MUSiiCCallbackInterface::Pointer callback;// = igtl::MUSiiCCallbackInterface::New();
	CallbackInterface call;
	callback = igtl::CreateLocalCallbackInterface(&call, &CallbackInterface::Callbackfunction, "Callback");
	//// Add a callback interface to MUSiiCigtlFileIO
	igtlFile->AddCallbackInterface(callback);


	/// Reading single file with callback function0
	igtlFile->ReadSingleFileCB("IRIS.igtl");
	
	/// Reading single file with thread 
	igtlFile->ReadSingleFileTH("IRIS.igtl",false); //without data interface
	igtlFile->WaitTask();
	call.m_igtlFileIO->WaitTask();


	//////Testing Data Interface
	igtl::MUSiiCVector<igtl::ImageMessage::Pointer>::Pointer pMUSiiCImageVector;
	pMUSiiCImageVector = igtl::MUSiiCVector<igtl::ImageMessage::Pointer>::New();

	igtl::MUSiiCVector<igtl::ImageMessage::Pointer>* pImageVector;
	igtl::MUSiiCVector<igtl::ImageMessage::Pointer>* pImageVector2;

	pImageVector = pMUSiiCImageVector;
	pImageVector2 = igtl::MUSiiCVector<igtl::ImageMessage::Pointer>::New();

	///////////////////////////////////////////////////////////////////////////
	std::vector<std::string> filelist;
	filelist.push_back("IRIS.igtl");
	filelist.push_back("IRIS2.igtl");
	filelist.push_back("IRIS3.igtl");
	igtlFile->ReadMultiFilesCB(filelist);
	/////////////////////////////////////////////////////////////////////////
	igtlFile->ReadMultiFilesTH(filelist, false);
	
	igtl::Sleep(5000);
	igtlFile->WaitTask();
	call.m_igtlFileIO->WaitTask();

	/////Setting the data interface
	igtlFile->SetDataInterface(call.m_pDataBuffer);
	igtlFile->ReadSingleFileTH("IRIS.igtl",true);
	igtlFile->WaitTask();
	call.m_igtlFileIO->WaitTask();



	////////////////////////////////////////////////////////////////////////
	/////Sing Flie Reading and Writing with callback
	printf("All Tasks are stoppped\n");
	/*igtl::Sleep(5000);
	igtlFile->WaitTask();
	call.m_igtlFileIO->WaitTask();*/
	return 0;
}