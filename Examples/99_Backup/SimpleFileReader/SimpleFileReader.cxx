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


int main (int argc, char* argv[])
{
	igtl::MUSiiCigtlMsgFILEIO::Pointer igtlFile = igtl::MUSiiCigtlMsgFILEIO::New();
	
	igtl::USMessage::Pointer rf;
	igtl::USMessage::Pointer rf2;
	rf = igtl::RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(igtlFile->ReadSingleFile("BMODE_17306002.0000000.igtl"));
	
	igtl::ImageMessage::Pointer img = igtl::ImageMessage::New();
	igtl::MessageBase::Pointer msg;
	msg = igtlFile->ReadSingleFile("2D_RF.igtl");
	img->Copy(msg);
	img->Unpack(1);

	igtl::ImageMessage::Pointer img2;
	img2 = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);

	//rf2 = igtlFile->ReadSingleMessage2<igtl::USMessage::Pointer, igtl::USMessage>("RF.igtl");
	
	return 0;
}