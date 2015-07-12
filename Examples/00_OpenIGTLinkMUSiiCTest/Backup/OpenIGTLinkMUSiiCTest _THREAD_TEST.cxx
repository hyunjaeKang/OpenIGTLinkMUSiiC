/***************************************************************************
Copyright May/2011
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/

#include "igtlMultiThreader.h"
#include "igtlOSUtil.h"
#include <stdio.h>

typedef struct {
  int   nloop;
  int   *sum;
  igtl::MutexLock::Pointer glock;
} ThreadData;

void* ThreadFunction1(void* ptr)
{
  long interval = 1; // (ms)

  // Get thread information
  igtl::MultiThreader::ThreadInfo* info = 
    static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);

  ThreadData* data = static_cast<ThreadData*>(info->UserData);
  int nloop = data->nloop;
  igtl::MutexLock::Pointer glock = data->glock;

  for (int i = 0; i < nloop; i ++)
    {
    glock->Lock();
    int s1 = *(data->sum);
    igtl::Sleep(interval);
    int s2 = *(data->sum);
    *(data->sum) = s1 + s2;
	printf("Thread1:: sum is %d\n", *(data->sum));
    glock->Unlock();
    }

  return NULL;
}

void* ThreadFunction2(void* ptr)
{
  long interval = 1; // (ms)

  // Get thread information
  igtl::MultiThreader::ThreadInfo* info = 
    static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);

  ThreadData* data = static_cast<ThreadData*>(info->UserData);
  int nloop = data->nloop;
  igtl::MutexLock::Pointer glock = data->glock;

  for (int i = 0; i < nloop; i ++)
    {
    glock->Lock();
    int s1 = *(data->sum);
    igtl::Sleep(interval);
    int s2 = *(data->sum);
    *(data->sum) = s1 + s2;
	printf("Thread2:: sum is %d\n", *(data->sum));
    glock->Unlock();
    }

  return NULL;
}

void* ThreadFunction3(void* ptr)
{
  long interval = 1; // (ms)

  // Get thread information
  igtl::MultiThreader::ThreadInfo* info = 
    static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);

  ThreadData* data = static_cast<ThreadData*>(info->UserData);
  int nloop = data->nloop;
  igtl::MutexLock::Pointer glock = data->glock;

  for (int i = 0; i < nloop; i ++)
    {
    glock->Lock();
    int s1 = *(data->sum);
    igtl::Sleep(interval);
    int s2 = *(data->sum);
    *(data->sum) = s1 + s2;
	printf("Thread3:: sum is %d\n", *(data->sum));
    glock->Unlock();
    }

  return NULL;
}

int main(int argc, char** argv)
{
	igtl::MutexLock::Pointer glock = igtl::MutexLock::New();

	int sum = 1;

	ThreadData td;
	td.nloop = 4;
	td.sum   = &sum;
	td.glock = glock;
  
	igtl::MultiThreader::Pointer threader = igtl::MultiThreader::New();

	int id1 = threader->SpawnThread((igtl::ThreadFunctionType) &ThreadFunction1, &td);
	int id2 = threader->SpawnThread((igtl::ThreadFunctionType) &ThreadFunction2, &td);
	int id3 = threader->SpawnThread((igtl::ThreadFunctionType) &ThreadFunction3, &td);

	// wait for the threads
	threader->TerminateThread(id1);
	threader->TerminateThread(id2);
	threader->TerminateThread(id3);
  


  return 0;
}