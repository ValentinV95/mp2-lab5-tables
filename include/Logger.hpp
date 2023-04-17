#pragma once
#include <fstream>
#include <ctime>
#include <typeinfo>
#pragma warning(disable : 4996)
struct Context {
	const char* file;
	long line;
	const char* function;
};

// Work around MSVS
#ifndef __func__
#define __func__ __FUNCTION__
#endif
#define CONTEXT() Context({ __FILE__, __LINE__, __func__})

using namespace std;

enum LogType {Info,Error};

class Logger
{
	string currentDateTime() {
		time_t t = std::time(nullptr);
		tm* now = std::localtime(&t);

		char buffer[128];
		strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
		return buffer;
	}
public:
	Logger()
	{
		log(CONTEXT(), "Program started" + currentDateTime(), Info);
	}

	static void log(Context context,string msg,LogType logType)
	{
		static ofstream outStream;
		outStream.open("MyLog.txt", ios::app);

		string fileName(context.file);
		fileName = fileName.substr(fileName.find_last_of('\\') + 1, fileName.size() - 1);

		if(logType == 0)
			outStream << "[INFO] " <<"In file - \""<< fileName <<"\"" << " Function - \"" << context.function << "\"" <<endl << "\t[MESSAGE] " << msg << endl;
		else
			outStream << "[EROR] " << "in file " << fileName << " function " << context.function << endl << "\t[MESSAGE] " << msg << endl;

		outStream.close();
	}
};