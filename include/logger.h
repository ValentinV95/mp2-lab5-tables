#include <Windows.h>
#include <ostream>

template<class T>
class Singleton
{
private:
	static T* instance;
protected:
	Singleton() {}
	virtual ~Singleton() {}
public:
	static T* GetInstance();
	void ResetInstance()
	{
		if (instance)
		{
			delete instance;
		}
		instance = nullptr;
	}
};

template<class T> 
T* Singleton<T>::instance = nullptr;

template<class T>
T* Singleton<T>::GetInstance()
{
	if (!instance)
	{
		instance = new T;
	}
	return instance;
}

class Logger: public Singleton<Logger>
{
private:
	enum COLOR { BLUE = 1, GREEN = 2, RED = 4, BROWN = 6, INTENSITY = 8 };
	HANDLE Log_handle;
	CONSOLE_SCREEN_BUFFER_INFO buffer;
	void content(const char* _text)
	{
		const WORD old_color = buffer.wAttributes;
		SetConsoleTextAttribute(Log_handle, INTENSITY);
		std::cout << _text << std::endl;
		SetConsoleTextAttribute(Log_handle, old_color);
	}
protected:
	Logger()
	{
		Log_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(Log_handle, &buffer);
	}
	friend class Singleton<Logger>;
public:
	void counter(const char* operation, size_t number)
	{
		const WORD old_color = buffer.wAttributes;
		SetConsoleTextAttribute(Log_handle, BLUE);
		std::cout << "COUNTER | ";
		SetConsoleTextAttribute(Log_handle, INTENSITY);
		std::cout << "Number of " << operation << ": " << number << std::endl;
		SetConsoleTextAttribute(Log_handle, old_color);
	}
	void success(const char* text)
	{
		SetConsoleTextAttribute(Log_handle, GREEN);
		std::cout << "SUCCESS | ";
		content(text);
	}
	void warning(const char* text)
	{
		SetConsoleTextAttribute(Log_handle, BROWN);
		std::cout << "WARNING | ";
		content(text);
	}
	void error(const char* text)
	{
		SetConsoleTextAttribute(Log_handle, RED);
		std::cout << "ERROR | ";
		content(text);
	}
};

#define logs_counter(name, count) Logger::GetInstance()->counter(name, count)
#define logs_success(message) Logger::GetInstance()->success(message)
#define logs_warning(message) Logger::GetInstance()->warning(message)
#define logs_error(message) Logger::GetInstance()->error(message)

void reset_logger()
{
	Logger::GetInstance()->ResetInstance();
}
