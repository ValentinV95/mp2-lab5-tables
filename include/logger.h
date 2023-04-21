#include <Windows.h>
#include <ostream>

class Logger
{
private:
	enum COLOR { BLUE = 1, GREEN = 2, RED = 4, BROWN = 6, INTENSITY = 8 };
	HANDLE Log_handle;
	CONSOLE_SCREEN_BUFFER_INFO buffer;
	void content(const char* _text)
	{
		const WORD old_color = buffer.wAttributes;
		SetConsoleTextAttribute(Log_handle, COLOR::INTENSITY);
		std::cout << _text << std::endl;
		SetConsoleTextAttribute(Log_handle, old_color);
	}
public:
	Logger()
	{
		Log_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(Log_handle, &buffer);
	}

	void counter(const char* operation, size_t counter)
	{
		const WORD old_color = buffer.wAttributes;
		SetConsoleTextAttribute(Log_handle, COLOR::BLUE);
		std::cout << "COUNTER | ";
		SetConsoleTextAttribute(Log_handle, COLOR::INTENSITY);
		std::cout << "Number of " << operation << ": " << counter << std::endl;
		SetConsoleTextAttribute(Log_handle, old_color);
	}
	void success(const char* text)
	{
		SetConsoleTextAttribute(Log_handle, COLOR::GREEN);
		std::cout << "SUCCESS | ";
		content(text);
	}
	void warning(const char* text)
	{
		SetConsoleTextAttribute(Log_handle, COLOR::BROWN);
		std::cout << "WARNING | ";
		content(text);
	}
	void error(const char* text)
	{
		SetConsoleTextAttribute(Log_handle, COLOR::RED);
		std::cout << "ERROR | ";
		content(text);
	}
};
