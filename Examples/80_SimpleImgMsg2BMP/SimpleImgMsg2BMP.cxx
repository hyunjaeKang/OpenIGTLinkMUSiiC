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

//#include <MUSiiCIGTLUtil.h>
//#include <io.h>
//#include <direct.h>
//#include <MUSiiCIGTLFileIO.h>

#include <io.h>
#include <stdio.h>
#include <direct.h>
#include <MUSiiCIGTLFileIO.h>
#include <sys\types.h>
#include <sys\stat.h>

#define swap(a, b) { temp = (a); (a) = (b); (b) = temp; }

#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
using namespace igtl;
////////////////////////////
/// Global Variables

int index;
///////////////////////////////

// converts 8 bit data into 32 bit RGB data
void convertImage(const unsigned char* data, int size, unsigned int* cdata)
{
    int i;
    for (i = 0; i < size; i++)
    {
        unsigned char v = data[i];
		//cdata[i] = data[i] << 16 | data[i] << 8 | data[i];
		cdata[i] = v << 16 | v << 8 | v;
    }
}

/// inverts image data, so that the bitmap can be displayed properly
void invertImage(unsigned int* pData, int w, int h)
{
    int x, y, temp;
    unsigned int* p = (unsigned int*)pData;

    // flip the image on the X-axis
    for (y = 0; y < h / 2; y++)
    {
        for (x = 0; x < w; x++)
        {
            swap(p[y * w + x], p[((h - 1 - y) * w) + x]);
        }
    }
}

#ifdef WIN32

///
/// write a bitmap file to a specified location
bool writeBitmap(const char* path, unsigned char* data, int w, int h, int bitdepth)
{
    FILE* fp = fopen(path, "wb");
    if (!fp)
    {
        return false;
    }

    unsigned int* cdata = new unsigned int[w * h];
	// if input data (image) is 32 bit image,
	// then we don't need to call "convertImage"
	// convert 8 bit data to 32 bit data
    convertImage(data, w * h, cdata);
    // since the data gets flipped when written to bitmap, pre-flip the image
    invertImage((unsigned int*)cdata, w, h);

    BITMAPINFOHEADER BMIH;
    BMIH.biSize = sizeof(BITMAPINFOHEADER);
    BMIH.biBitCount = (unsigned short)bitdepth;
    BMIH.biPlanes = 1;
    BMIH.biCompression = BI_RGB;
    BMIH.biWidth = w;
    BMIH.biHeight = h;
    BMIH.biSizeImage = ((((BMIH.biWidth * BMIH.biBitCount) + 31) & ~31) >> 3) * BMIH.biHeight;

    BITMAPFILEHEADER bmfh;
    int nBitsOffset = sizeof(BITMAPFILEHEADER) + BMIH.biSize;
    LONG lImageSize = BMIH.biSizeImage;
    LONG lFileSize = nBitsOffset + lImageSize;
    bmfh.bfType = 'B' + ('M' << 8);
    bmfh.bfOffBits = nBitsOffset;
    bmfh.bfSize = lFileSize;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    // write the bitmap file header
    fwrite(&bmfh, 1, sizeof(BITMAPFILEHEADER), fp);
    // and then the bitmap info header
    fwrite(&BMIH, 1, sizeof(BITMAPINFOHEADER), fp);
    // finally, write the image data itself
    fwrite(cdata, 1, lImageSize, fp);

    fclose(fp);

	delete cdata;

    return true;
}

#else

// not implemented for non-Windows systems right now
bool writeBitmap(const char* path, unsigned char* data, int w, int h, int bitdepth)
{
    printf("this function is only available under Windows.\n");
    return false;
}

#endif

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

int ConvertIGTLImgMsg2BMP(std::string path)
{
	igtl::MUSiiCIGTLMsgFileIO::Pointer pFileIO = igtl::MUSiiCIGTLMsgFileIO::New();

	struct _finddata_t	c_file;
	intptr_t			hFile;

	_chdir(path.c_str());

	//check source directory
	if (CheckDirectory(path) <1)
	{
		std::cout << "Source directory does not exist" << std::endl;
		return 0;
	}
	else
		std::cout << "Source directory exists" << std::endl;

	if((hFile = _findfirst("*.igtl", &c_file)) == -1L)
		return false;
	else
	{
		do{
			std::string filename, num;
			std::string pathF;
			filename = c_file.name;
			printf("File name is %s\n", c_file.name);
			igtl::MessageBase::Pointer msg = pFileIO->ReadSingleFile(filename.c_str());
			if(strcmp(msg->GetDeviceType(), "IMAGE") == 0)
			{
				
				igtl::ImageMessage::Pointer img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);
				if(img->GetScalarType() == igtl::ImageMessage::TYPE_UINT8)
				{
					std::string IMG_Path =".bmp";
					IMG_Path = filename+IMG_Path;
					int x, y, z;
					img->GetDimensions(x,y,z);
					writeBitmap(IMG_Path.c_str(), (unsigned char*)img->GetScalarPointer(),x,y,32);

					printf("Index:%d :: igtl file of %s saved as BMP Image\n", index, filename.c_str());
				}
				else
				{
					std::cout << "ImageMessage does not have 8bit image data" << std::endl;
				}
			}
			else
			{
				printf("Index:%d :: igtl file of %s is not image Data\n", index, filename.c_str());
			}

			index++;
	

		}while(_findnext(hFile, &c_file) ==0);
		_findclose(hFile);
	}
}


int main(int argc, char** argv)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	
	if (argc != 2) // check number of arguments
	{
		// If not correct, print usage
		std::cerr << "Usage::   SimpleImgMsg2BMP.exe Src_Dir "  << std::endl;
		std::cerr << "Example:: SimpleImgMsg2BMP.exe C:/IGTLImgData/ "  << std::endl;
		exit(0);
	}
	
	std::string src = argv[1];
	index = 0;

	return ConvertIGTLImgMsg2BMP(src);
}