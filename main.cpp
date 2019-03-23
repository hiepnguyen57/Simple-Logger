#include <iostream>
#include <string>
#include <stdio.h>
#include <thread>
#include <list>
#include <memory>
#include "Log.h"
using namespace std;
int main() {
	Log<OutputToFile>().Get(Level::INFO) << "Hello ";
	Log<OutputToFile>().Get(Level::DEBUG) << "This is me ";
	FILE* pFile = fopen("test.log", "a");
	OutputToFile::Stream() = pFile;
	Log<OutputToFile>().Get(Level::ERROR) << "print to log file ";
	Log<OutputToFile>().Get(Level::INFO) << "print to log file ";
}
