#pragma once
#include <sstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <mutex>
#include <memory>
#include <iomanip>
#include "Level.h"

// Convert date and time info from tm to a character string
// in format "YYYY-mm-DD HH:MM:SS" and send it to a stream
std::ostream& operator<< (std::ostream& stream, const tm* tm)
{
  // This section since GCC 4.8.1 did not implement std::put_time
  //  return stream << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
  return stream << 1900 + tm->tm_year << '-' <<
    std::setfill('0') << std::setw(2) << tm->tm_mon + 1 << '-'
    << std::setfill('0') << std::setw(2) << tm->tm_mday << ' '
    << std::setfill('0') << std::setw(2) << tm->tm_hour << ':'
    << std::setfill('0') << std::setw(2) << tm->tm_min << ':'
    << std::setfill('0') << std::setw(2) << tm->tm_sec;
}

/*
 * Log class.
 * typename T is output policy: stderr, stdout, Output2File, etc.
 */

template <typename T> class Log {
 public:
   Log();
   virtual ~Log();
   std::ostringstream& Get(Level level = Level::INFO);
   static Level& ReportingLevel();
protected:
   std::ostringstream os;
private:
    inline const tm* getLocalTime();
private:
    std::mutex    m_oMutex;
    Log(const Log&);
    Log& operator =(const Log&);
    Level m_level;
    tm mLocalTime;
};

template <typename T> Log<T>::Log()
{
}

template <typename T> std::ostringstream& Log<T>::Get(Level level)
{
	m_oMutex.lock();
	m_level = level;
    os << "[" << getLocalTime() << "]"
       << "[" << convertLevelToName(level) << "]\t";
    m_oMutex.unlock();
    return os;
}
/*
 * In the destructor print out the message
 */
template <typename T> Log<T>::~Log()
{
	os << std::endl;
	T::Output(os.str());
}

template <typename T> Level& Log<T>::ReportingLevel()
{
	static Level reportingLevel =  Level::INFO;
	return reportingLevel;
}

template <typename T> inline const tm* Log<T>::getLocalTime() {
	auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	localtime_r(&in_time_t, &mLocalTime);
	return &mLocalTime;
}


class OutputToFile {
public:
    static FILE*& Stream();
    static void Output(const std::string& msg);
};

inline FILE*& OutputToFile::Stream()
{
	static FILE* pStream = stderr;
	return pStream;
}

inline void OutputToFile::Output(const std::string& msg)
{   
	FILE* pStream = Stream();
	if (!pStream) return;

	fprintf(pStream, "%s", msg.c_str());
  	fflush(pStream);
}

