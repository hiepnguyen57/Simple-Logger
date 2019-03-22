#pragma once

#include <sstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <mutex>
#include <memory>
#include "Level.h"
//#include <ansi.h>


//inline std::string NowTime();

//enum TLogLevel {logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4, logDEBUG5};

class Log{
 public:
   Log();
   virtual ~Log();
   std::ostringstream& Get(Level level = Level::INFO);
   //static Level& ReportingLevel();
   // static std::string ToString(TLogLevel level);
   // static TLogLevel FromString(const std::string& level);
protected:
   std::ostringstream os;
private:
    inline const tm* getLocalTime();
private:
    std::mutex mMutex;
    Log(const Log&);
    Log& operator =(const Log&);
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
