cmake_minimum_required(VERSION 2.4)

MESSAGE(STATUS "Example Directory")


SET(EXAMPLE_DIRS
    ${EXAMPLE_DIRS}
	00_OpenIGTLinkMUSiiCTest
	01_MUSiiCIOFilterTest
	02_MUSiiCTaskAbstract
	03_MUSiiCTaskInterfaceAbstract
	04_MUSiiCSyncTest
	05_MUSiiCTCPServerTest
	06_MUSiiCTCPClientTest
	07_MUSiiCVectorTest
	08_MUSiiCVectorSetTest
	09_MUSiiCConfigureTest
	
)

IF(OpenIGTLinkMUSiiC_PLATFORM_WIN32) # for Windows
  SET(EXAMPLE_DIRS
	 ${EXAMPLE_DIRS}
	 70_SimpleMUSiiCThermometer
	 71_SimpleMUSiiCThermometer2
	 10_MUSiiCRS232SimpleTest
	 11_MUSiiCFileIOTest
	 12_MUSiiCUSConvert
	 14_IGTLMessageTest
	 15_BindMessageTest
	 30_FakeRFServer
	 31_FakeEIServer
	 32_FakeImageServer
	 32_FakeTrackerServer
	 33_FakeStringServer
	 34_FakeBindImageServer
	 40_MUSiiCStreamWriter
	 41_MUSiiCStreamWriter2
	 42_MUSiiCStreamWriter3
	 50_SimpleMUSiiCSync
	 51_MUSiiCSyncAMS
	 52_MUSiiCSyncTrPA
	 80_SimpleImgMsg2BMP
	 81_SimpleFileServer
	 )
ENDIF(OpenIGTLinkMUSiiC_PLATFORM_WIN32)
  
SUBDIRS(
${EXAMPLE_DIRS}  
)
  