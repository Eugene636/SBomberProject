#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

#include "FileLoggerSingletone.h"

using namespace std;

ofstream logOut;

FileLoggerSingletone::FileLoggerSingletone() {}
FileLoggerSingletone& FileLoggerSingletone::getInstance() {
    static FileLoggerSingletone theInstance;
    return theInstance;
}
void  FileLoggerSingletone::OpenLogFile(const string& FN)
{
    logOut.open(FN, ios_base::out);
}

void FileLoggerSingletone::CloseLogFile()
{
    if (logOut.is_open())
    {
        logOut.close();
    }
}

string FileLoggerSingletone::GetCurDateTime()
{
    auto cur = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(cur);
    char buf[64] = { 0 };
    ctime_s(buf, 64, &time);
    buf[strlen(buf) - 1] = '\0';
    return string(buf);
}

void FileLoggerSingletone::WriteToLog(const string& str)
{
    if (logOut.is_open())
    {
        logOut << FileLoggerSingletone::getInstance().GetCurDateTime() << " - " << str << endl;
    }
}

void FileLoggerSingletone::WriteToLog(const string& str, int n)
{
    if (logOut.is_open())
    {
        logOut << FileLoggerSingletone::getInstance().GetCurDateTime() << " - " << str << n << endl;
    }
}

void FileLoggerSingletone::WriteToLog(const string& str, double d)
{
    if (logOut.is_open())
    {
        logOut << FileLoggerSingletone::getInstance().GetCurDateTime() << " - " << str << d << endl;
    }
}
LoggerSingleton::LoggerSingleton() {}
LoggerSingleton& LoggerSingleton::getInstance() {
    static int count = 1;
    static LoggerSingleton theInstance;
    theInstance.number_of_logstring = count++;
    return theInstance;
}

void __fastcall LoggerSingleton::WriteToLog_with_num(const std::string& str) {
    logOut << number_of_logstring << ' ';
    FileLoggerSingletone::getInstance().WriteToLog(str);
}
void __fastcall LoggerSingleton::WriteToLog_with_num(const std::string& str, int n) {
    logOut << number_of_logstring << ' ';
    FileLoggerSingletone::getInstance().WriteToLog(str, n);
}
void __fastcall LoggerSingleton::WriteToLog_with_num(const std::string& str, double d) {
    logOut << number_of_logstring << ' ';
    FileLoggerSingletone::getInstance().WriteToLog(str, d);
}
