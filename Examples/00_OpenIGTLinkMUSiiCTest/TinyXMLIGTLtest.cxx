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

/// IGTL & TinyXML Test
#include "MUSiiCIGTLUtil.h"
#include "Ext\TinyXML\tinyxml.h"
#include "Ext\TinyXML\tinystr.h"

int main(int argc, char** argv)
{
	std::string filepath ="";

	TiXmlDocument doc(filepath.c_str());

	if(!doc.LoadFile())
		std::cout << "Error of loading file" << std::endl;

	TiXmlHandle hDoc(&doc);
	
	TiXmlElement* pElement = hDoc.FirstChildElement().Element();

	return 0;

}

