#pragma once
#include <stdint.h>
#include <string>

namespace MyTools {
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
}
