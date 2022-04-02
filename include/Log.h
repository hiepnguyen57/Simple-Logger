#pragma once

#include <sstream>
#include <string>
#include <mutex>
#include <iomanip>
#include <memory>

#include "Level.h"

#define LOG_TAG "Logger"

#ifdef NDEBUG 
#define LOG_DEBUG(...) do{} while(0)
#define LOG_INFO(...) do{} while(0)
#define LOG_WARN(...) do{} while(0)
#define LOG_ERROR(...) do{} while(0)   
#define LOG_CRITICAL(...) do{} while(0)  
#else //DEBUG

#define LOG_DEBUG(...) Log<OutputToFile>().write(convertLevelToName(Level::DEBUG), LOG_TAG, __VA_ARGS__)
#define LOG_INFO(...) Log<OutputToFile>().write(convertLevelToName(Level::INFO), LOG_TAG, __VA_ARGS__)
#define LOG_WARN(...) Log<OutputToFile>().write(convertLevelToName(Level::WARN), LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) Log<OutputToFile>().write(convertLevelToName(Level::ERROR), LOG_TAG, __VA_ARGS__)
#define LOG_CRITICAL(...) Log<OutputToFile>().write(convertLevelToName(Level::CRITICAL), LOG_TAG, __VA_ARGS__)
#endif

/*
 * Log class.
 * typename LogPolicy is output policy: stderr, stdout, OutputToFile, etc.
 */
template <typename LogPolicy>
class Log {
public:
    Log();
    virtual ~Log();
    Level& getCurrentLevel();
    void setLogLevel(Level newLevel);

    template <typename TF, typename... TR>
    void write(TF const& f, TR const&... rest);

    template <typename TF>
    void write(TF const& f);

    void write();

protected:
    std::ostringstream os;

private:
    template<typename TF>
    inline void writeOutput(TF const& f);

private:
    std::mutex mMutex;
    Log(const Log&);
    Log& operator=(const Log&);
    Level mLevel;
    tm mLocalTime;
};

template <typename LogPolicy>
Log<LogPolicy>::Log() {}

template <typename LogPolicy> 
template <typename TF, typename... TR>
void Log<LogPolicy>::write(TF const& f, TR const&... rest) {
    writeOutput(f);
    os << " ";
    write(rest...);
}

template <typename LogPolicy> 
template <typename TF>
void Log<LogPolicy>::write(TF const& f) {
    writeOutput(f);
}

template <typename LogPolicy> 
void Log<LogPolicy>::write() {
    // handle the empty params case
}

/*
 * In the destructor print out the message
 */
template <typename LogPolicy>
Log<LogPolicy>::~Log() {
    if (mLevel != Level::NONE) {
        os << std::endl;
        LogPolicy::Output(os.str());
    }
}

template <typename LogPolicy>
Level& Log<LogPolicy>::getCurrentLevel() {
    return mLevel;
}

template <typename LogPolicy>
void Log<LogPolicy>::setLogLevel(Level newLevel) {
    mLevel = newLevel;
}

template <typename LogPolicy>
template <typename TF>
inline void Log<LogPolicy>::writeOutput(TF const& f) {
    std::lock_guard<std::mutex> lock(mMutex);
    os << f;
}

class OutputToFile {
   public:
    static FILE*& Stream();
    static void Output(const std::string& msg);
};

inline FILE*& OutputToFile::Stream() {
    static FILE* pStream = stderr;
    return pStream;
}

inline void OutputToFile::Output(const std::string& msg) {
    FILE* pStream = Stream();
    if (!pStream) return;

    fprintf(pStream, "%s", msg.c_str());
    fflush(pStream);
}