#pragma once
#include <stdint.h>
#include <string>

	class FileLoggerSingletone {
	public:
		std::string GetCurDateTime();
		void __fastcall OpenLogFile(const std::string& FN);

		void CloseLogFile();

		void __fastcall WriteToLog(const std::string& str);

		void __fastcall WriteToLog(const std::string& str, int n);

		void __fastcall WriteToLog(const std::string& str, double d);
		static FileLoggerSingletone& getInstance();

	private:
		FileLoggerSingletone();
		FileLoggerSingletone(const FileLoggerSingletone& root) = delete;
		FileLoggerSingletone& operator=(const FileLoggerSingletone&) = delete;
	};
	class LoggerSingleton {
	public:
		static LoggerSingleton& getInstance();

		void __fastcall WriteToLog_with_num(const std::string& str);
		void __fastcall WriteToLog_with_num(const std::string& str, int n);
		void __fastcall WriteToLog_with_num(const std::string& str, double d);
	private: 
		int number_of_logstring;
		LoggerSingleton();
		LoggerSingleton(const LoggerSingleton& root) = delete;
		LoggerSingleton& operator=(const LoggerSingleton&) = delete;
	};
