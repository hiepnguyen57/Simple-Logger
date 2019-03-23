#include <thread>
#include <list>
#include <memory>
#include "Log.h"
using namespace std;


// The thread function
void threadFunc(int id)
{
	for (int i = 0; i < 100; i++)
	{
	    // add a log message
		DCSDK_DEBUG << "Thread " << id << ", Message " << i;
	}
}

int main()
{
	//remove below commands if you want to use file logger
	// FILE* pFile = fopen("application.log", "a");
	// OutputToFile::Stream() = pFile;

	list<shared_ptr<thread>> oThreads;

	// create 100 threads
	for (int i = 0; i < 100; i++)
	{
		oThreads.push_back(shared_ptr<thread>(new thread(threadFunc, i)));
	}

	// also do logging from the main thread
	for (int i = 0; i < 100; i++)
	{
	    // add a log message
		DCSDK_INFO << "Main thread, Message " << i;
	}

	// wait for all the threads to finish
	for (auto oThread : oThreads)
	{
		oThread->join();
	}

	return 0;
}
