#include <chrono>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include "Logger.h"

// Convert date and time info from tm to a character string
// in format "YYYY-mm-DD HH:MM:SS" and send it to a stream
std::ostream& operator<< (std::ostream& stream, const tm* tm)
{
// I had to muck around this section since GCC 4.8.1 did not implement std::put_time
//	return stream << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
	return stream << 1900 + tm->tm_year << '-' <<
		std::setfill('0') << std::setw(2) << tm->tm_mon + 1 << '-'
		<< std::setfill('0') << std::setw(2) << tm->tm_mday << ' '
		<< std::setfill('0') << std::setw(2) << tm->tm_hour << ':'
		<< std::setfill('0') << std::setw(2) << tm->tm_min << ':'
		<< std::setfill('0') << std::setw(2) << tm->tm_sec;
}

//template <typename T> Log<T>::Log():lev(logDEBUG){}
std::ostringstream& Logger::Get(Level level)
{
   m_level = level;
   mMutex.lock();
    os << "[" << getLocalTime() << "]"
    	<< "[" << convertLevelToName(level) << "]\t";
    // if (level > Level::DEBUG)
    //   os << std::string(level -Level::DEBUG, '\t');
    mMutex.unlock();
    return os;
}

Logger::Logger():m_level(Level::DEBUG){}

Logger::~Logger()
{
    // os << std::endl;
    // T::Output( os.str(),lev); // T::Output( os.str());


   // if (lev >= Log::ReportingLevel())
   // {
       os << std::endl;
      fprintf(stderr, "%s", os.str().c_str());
      fflush(stderr);
   //}
}

// Level& Log::ReportingLevel()
// {
//     static Level reportingLevel = Level::DEBUG;
//     return reportingLevel;
// }
inline const tm* Logger::getLocalTime() {
 	auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
 	localtime_r(&in_time_t, &mLocalTime);
 	return &mLocalTime;
 }