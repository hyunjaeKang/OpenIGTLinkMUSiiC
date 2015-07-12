/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/
#include "MUSiiCTCPServerWin.h"

int main(int argc, char** argv)
{
	MUSiiCTCPServerWin server;
	server.CreateServer(12345);
	int i(0);

	printf("Hello\n");

	while(1)
	{
		igtl::Sleep(1000);
		i++;
		if(i == 1000)
			i = 0;
	}

	return 0;
}