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
#include <io.h>
#include <stdio.h>
#include <direct.h>
#include <MUSiiCIGTLFileIO.h>
#include <sys\types.h>
#include <sys\stat.h>

#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
using namespace igtl;
int CheckDirectory(std::string dir_path)
{
	/// Check destination Directory
	struct stat status;

    if ( access( dir_path.c_str(), 0 ) == 0 )
    {
      struct stat status;
      stat( dir_path.c_str(), &status );

      if ( status.st_mode & S_IFDIR )
      {
         std::cout << "The directory exists." << std::endl;
      }
      else
      {
         std::cout << "The path you entered is a file." << std::endl;
      }
	}
	else
	{
      std::cout << "Path doesn't exist." << std::endl;
	  return 0;
	}

}

std::string ValidateDirectoryPath(std::string dirpath)
{
	const char s(dirpath[dirpath.length() -1]);
	if(strcmp(&s,"/") == 0 || strcmp(&s, "'\'") == 0 )
		return dirpath;
	else
		return dirpath.append("/");
}
int Convert_OldUS_NewUS(std::string src_path, std::string des_path)
{
	std::cout << "Converting USMessage(Ver 1.0) to USMessage( Ver 2.0)" << std::endl;
	struct _finddata_t	c_file;
	intptr_t			hFile;
	int					index(0);
	bool				bFilePreFix;
	std::string         sFilePreFix("converted_");

	if (src_path.compare(des_path) == 0)
	{
		std::cout << "Source Folder and Destination Folder are same!" << std::endl;
		std::cout << "Please set different folder" << std::endl;
		return 0;
	}
	else
		bFilePreFix = false;

	/*src_path = ValidateDirectoryPath(src_path);
	des_path = ValidateDirectoryPath(des_path);*/

	if (CheckDirectory(src_path) <1)
	{
		std::cout << "Source directory does not exist" << std::endl;
		return 0;
	}
	else
		std::cout << "Source directory exists" << std::endl;
	
	if (CheckDirectory(des_path) <1)
	{
		std::cout << "Destination directory does not exist" << std::endl;
		_mkdir(des_path.c_str());
		std::cout << "Destination directory is created" << std::endl;
	}
	else
		std::cout << "Destination directory exists" << std::endl;

	
	
	_chdir(src_path.c_str());

	igtl::MUSiiCIGTLMsgFileIO::Pointer pFileIO = igtl::MUSiiCIGTLMsgFileIO::New();

	if((hFile = _findfirst("*.igtl", &c_file)) == -1L)
		return false;
	else
	{
		do{
			std::string filename, num;
			std::string pathF;
			filename = c_file.name;
			std::string src_file_path = src_path+filename;
			igtl::USMessage::Pointer  msg = pFileIO->ReadSingleUSMessage(src_file_path);
			if(msg.IsNotNull())
			{
				index++;
				std::string des_file_path;
				if(bFilePreFix)
					des_file_path = des_path + sFilePreFix+filename;
				else
					des_file_path = des_path + filename;
			
				igtl::MessageBase::Pointer bmsg = (igtl::MessageBase::Pointer) msg;
				pFileIO->WriteSingleFile((igtl::MessageBase::Pointer)bmsg, des_file_path);
				std::cout << "--" << index << "-th USMessages is converted." << std::endl;
				std::cout << des_file_path << std::endl;
			}
		}while(_findnext(hFile, &c_file) ==0);
		_findclose(hFile);
	}

	std::cout << "Oveall " << index << "-USMessages are converted." << std::endl;
	std::cout << "Done" << std::endl;
}


int main(int argc, char** argv)
{
	if (argc != 3) // check number of arguments
	{
		// If not correct, print usage
		std::cerr << "Usage::   TestMUSiiCUSConvert.exe Src_Dir Des_Dir"  << std::endl;
		std::cerr << "Example:: TestMUSiiCUSConvert.exe C:/USData/ C:/USData/Converted/"  << std::endl;
		exit(0);
	}
	
	std::string src = argv[1];
	std::string des = argv[2];

	std:cout << "Source Directory : " << src << std::endl;
	std::cout<< "Destination Directory : " << des << std::endl;
	
	return Convert_OldUS_NewUS(src, des);
}