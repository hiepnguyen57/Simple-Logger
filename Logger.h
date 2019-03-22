#pragma once

#include <sstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <mutex>
#include <memory>
#include "Level.h"

class Logger{
 public:
   Logger();
   virtual ~Logger();
   std::ostringstream& Get(Level level = Level::INFO);
   //static Level& ReportingLevel();
protected:
   std::ostringstream os;
private:
    inline const tm* getLocalTime();
private:
    std::mutex mMutex;
    Logger(const Logger&);
    Logger& operator =(const Logger&);
    Level m_level;
    tm mLocalTime;
};

// class Output2FILE {
// public:
//     static FILE*& Stream();
//     static void Output(const std::string& msg);
//     static void Output(const std::string& msg, TLogLevel level);
// };



// inline FILE*& Output2FILE::Stream()
// {
//     static FILE* pStream = stderr;
//     return pStream;
// }

// inline void Output2FILE::Output(const std::string& msg)
// {   
//     FILE* pStream = Stream();
//     if (!pStream)
//         return;
//     fprintf(pStream, "%s", msg.c_str());
//     fflush(pStream);
// }
