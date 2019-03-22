#include <chrono>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include "log.h"

// inline std::string NowTime()
// {
//     char buffer[11];
//     const int buffer_len = sizeof(buffer);
//     time_t t;
//     time(&t);
//     tm r = {0};
//     strftime(buffer, buffer_len, "%X", localtime_r(&t, &r));
//     buffer[buffer_len - 1] = 0;
//     struct timeval tv;
//     gettimeofday(&tv, 0);
//     char result[100];
//     const int result_len = sizeof(result);
//     snprintf(result, result_len, "%s.%03ld", buffer, (long)tv.tv_usec / 1000);
//     result[result_len - 1] = 0;
//     return result;
// }

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
std::ostringstream& Log::Get(Level level)
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

Log::Log():m_level(Level::DEBUG){}

Log::~Log()
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
inline const tm* Log::getLocalTime() {
 	auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
 	localtime_r(&in_time_t, &mLocalTime);
 	return &mLocalTime;
 }