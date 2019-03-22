#include <iostream>
#include <string>
#include <stdio.h>
#include <thread>
#include <list>
#include <memory>
#include "Logger.h"

using namespace std;
#define LOG Logger().Get(Level::DEBUG)
int main() {
	//Log::ReportingLevel() = Level::DEBUG;
	const int count = 3;
	Logger().Get(Level::INFO) << "A loop with "    << count << " iterations";
	for (int i = 0; i != count; ++i)
	{
   		Logger().Get(Level::ERROR) << "the counter i = " << i;
	}
	LOG << "hello world";

	cout << "Level: " << convertLevelToName(Level::DEBUG) << endl;
	cout << "Level: " << convertLevelToName(Level::INFO) << endl;
	cout << "Level: " << convertLevelToName(Level::WARN) << endl;
	cout << "Level: " << convertLevelToName(Level::ERROR) << endl;
	cout << "Level: " << convertLevelToName(Level::CRITICAL) << endl;
	cout << "Level: " << convertLevelToName(Level::NONE) << endl;
	while(1) {

	}
}
